/* Helper library for MSI creation with Python.
 * Copyright (C) 2005 Martin v. Löwis
 * Licensed to PSF under a contributor agreement.
 */

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <windows.h>
#include <fci.h>
#include <fcntl.h>
#include <msi.h>
#include <msidefs.h>
#include <msiquery.h>
#include <rpc.h>

static PyObject* MSIError;

static PyObject* _msi_UuidCreate_impl(PyObject* module) {
    UUID result;
    wchar_t* cresult;
    PyObject* oresult;

    /* May return ok, local only, and no address.
       For local only, the documentation says we still get a uuid.
       For RPC_S_UUID_NO_ADDRESS, it's not clear whether we can
       use the result. */
    if (UuidCreate(&result) == RPC_S_UUID_NO_ADDRESS) {
        PyErr_SetString(
            PyExc_NotImplementedError, "processing 'no address' result");
        return NULL;
    }

    if (UuidToStringW(&result, &cresult) == RPC_S_OUT_OF_MEMORY) {
        PyErr_SetString(PyExc_MemoryError, "out of memory in uuidgen");
        return NULL;
    }

    oresult = PyUnicode_FromWideChar(cresult, wcslen(cresult));
    RpcStringFreeW(&cresult);
    return oresult;
}

/* Helper for converting file names from UTF-8 to wchat_t*.  */
static wchar_t* utf8_to_wchar(const char* s, int* err) {
    PyObject* obj = PyUnicode_FromString(s);
    if (obj == NULL) {
        if (PyErr_ExceptionMatches(PyExc_MemoryError)) {
            *err = ENOMEM;
        } else {
            *err = EINVAL;
        }
        PyErr_Clear();
        return NULL;
    }
    wchar_t* ws = PyUnicode_AsWideCharString(obj, NULL);
    if (ws == NULL) {
        *err = ENOMEM;
        PyErr_Clear();
    }
    Py_DECREF(obj);
    return ws;
}

/* FCI callback functions */

static FNFCIALLOC(cb_alloc) { return PyMem_RawMalloc(cb); }

static FNFCIFREE(cb_free) { PyMem_RawFree(memory); }

static FNFCIOPEN(cb_open) {
    wchar_t* ws = utf8_to_wchar(pszFile, err);
    if (ws == NULL) {
        return -1;
    }
    int result = _wopen(ws, oflag | O_NOINHERIT, pmode);
    PyMem_Free(ws);
    if (result == -1)
        *err = errno;
    return result;
}

static FNFCIREAD(cb_read) {
    UINT result = (UINT)_read((int)hf, memory, cb);
    if (result != cb)
        *err = errno;
    return result;
}

static FNFCIWRITE(cb_write) {
    UINT result = (UINT)_write((int)hf, memory, cb);
    if (result != cb)
        *err = errno;
    return result;
}

static FNFCICLOSE(cb_close) {
    int result = _close((int)hf);
    if (result != 0)
        *err = errno;
    return result;
}

static FNFCISEEK(cb_seek) {
    long result = (long)_lseek((int)hf, dist, seektype);
    if (result == -1)
        *err = errno;
    return result;
}

static FNFCIDELETE(cb_delete) {
    wchar_t* ws = utf8_to_wchar(pszFile, err);
    if (ws == NULL) {
        return -1;
    }
    int result = _wremove(ws);
    PyMem_Free(ws);
    if (result != 0)
        *err = errno;
    return result;
}

static FNFCIFILEPLACED(cb_fileplaced) { return 0; }

static FNFCIGETTEMPFILE(cb_gettempfile) {
    char* name = _tempnam("", "tmp");
    if ((name != NULL) && ((int)strlen(name) < cbTempName)) {
        strcpy(pszTempName, name);
        free(name);
        return TRUE;
    }

    if (name)
        free(name);
    return FALSE;
}

static FNFCISTATUS(cb_status) {
    if (pv) {
        PyObject* result
            = PyObject_CallMethod(pv, "status", "iii", typeStatus, cb1, cb2);
        if (result == NULL)
            return -1;
        Py_DECREF(result);
    }
    return 0;
}

static FNFCIGETNEXTCABINET(cb_getnextcabinet) {
    if (pv) {
        PyObject* result
            = PyObject_CallMethod(pv, "getnextcabinet", "i", pccab->iCab);
        if (result == NULL)
            return -1;
        if (!PyBytes_Check(result)) {
            PyErr_Format(PyExc_TypeError,
                "Incorrect return type %s from getnextcabinet",
                Py_TYPE(result)->tp_name);
            Py_DECREF(result);
            return FALSE;
        }
        strncpy(pccab->szCab, PyBytes_AsString(result), sizeof(pccab->szCab));
        return TRUE;
    }
    return FALSE;
}

static FNFCIGETOPENINFO(cb_getopeninfo) {
    BY_HANDLE_FILE_INFORMATION bhfi;
    FILETIME filetime;
    HANDLE handle;

    wchar_t* ws = utf8_to_wchar(pszName, err);
    if (ws == NULL) {
        return -1;
    }

    /* Need Win32 handle to get time stamps */
    handle = CreateFileW(ws, GENERIC_READ, FILE_SHARE_READ, NULL,
        OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (handle == INVALID_HANDLE_VALUE) {
        PyMem_Free(ws);
        return -1;
    }

    if (GetFileInformationByHandle(handle, &bhfi) == FALSE) {
        CloseHandle(handle);
        PyMem_Free(ws);
        return -1;
    }

    FileTimeToLocalFileTime(&bhfi.ftLastWriteTime, &filetime);
    FileTimeToDosDateTime(&filetime, pdate, ptime);

    *pattribs = (int)(bhfi.dwFileAttributes
        & (_A_RDONLY | _A_SYSTEM | _A_HIDDEN | _A_ARCH));

    CloseHandle(handle);

    int result = _wopen(ws, _O_RDONLY | _O_BINARY | O_NOINHERIT);
    PyMem_Free(ws);
    return result;
}

static PyObject* _msi_FCICreate_impl(PyObject* module, const char* cabname, PyObject* files) {
    const char* p;
    CCAB ccab;
    HFCI hfci;
    ERF erf;
    Py_ssize_t i;

    if (!PyList_Check(files)) {
        PyErr_SetString(PyExc_TypeError, "FCICreate expects a list");
        return NULL;
    }

    ccab.cb = INT_MAX; /* no need to split CAB into multiple media */
    ccab.cbFolderThresh = 10000000; /* flush directory after this many bytes */
    ccab.cbReserveCFData = 0;
    ccab.cbReserveCFFolder = 0;
    ccab.cbReserveCFHeader = 0;

    ccab.iCab = 1;
    ccab.iDisk = 1;

    ccab.setID = 0;
    ccab.szDisk[0] = '\0';

    for (i = 0, p = cabname; *p; p++)
        if (*p == '\\' || *p == '/')
            i = p - cabname + 1;

    if (i >= sizeof(ccab.szCabPath)
        || strlen(cabname + i) >= sizeof(ccab.szCab)) {
        PyErr_SetString(PyExc_ValueError, "path name too long");
        return 0;
    }

    if (i > 0) {
        memcpy(ccab.szCabPath, cabname, i);
        ccab.szCabPath[i] = '\0';
        strcpy(ccab.szCab, cabname + i);
    } else {
        strcpy(ccab.szCabPath, ".\\");
        strcpy(ccab.szCab, cabname);
    }

    hfci = FCICreate(&erf, cb_fileplaced, cb_alloc, cb_free, cb_open, cb_read,
        cb_write, cb_close, cb_seek, cb_delete, cb_gettempfile, &ccab, NULL);

    if (hfci == NULL) {
        PyErr_Format(PyExc_ValueError, "FCI error %d", erf.erfOper);
        return NULL;
    }

    for (i = 0; i < PyList_Size(files); i++) {
        PyObject* item = PyList_GetItemRef(files, i);
        char *filename, *cabname;

        if (!PyArg_ParseTuple(item, "ss", &filename, &cabname)) {
            PyErr_SetString(PyExc_TypeError,
                "FCICreate expects a list of tuples containing two strings");
            FCIDestroy(hfci);
            return NULL;
        }

        if (!FCIAddFile(hfci, filename, cabname, FALSE, cb_getnextcabinet,
                cb_status, cb_getopeninfo, TCOMPfromLZXWindow(21)))
            goto err;
    }

    if (!FCIFlushCabinet(hfci, FALSE, cb_getnextcabinet, cb_status))
        goto err;

    if (!FCIDestroy(hfci))
        goto err;

    Py_RETURN_NONE;
err:
    if (erf.fError)
        PyErr_Format(PyExc_ValueError, "FCI error %d",
            erf.erfOper); /* XXX better error type */
    else
        PyErr_SetString(PyExc_ValueError, "FCI general error");

    FCIDestroy(hfci);
    return NULL;
}

typedef struct msiobj {
    PyObject_HEAD MSIHANDLE h;
} msiobj;

static void msiobj_dealloc(msiobj* msidb) {
    MsiCloseHandle(msidb->h);
    msidb->h = 0;
    PyObject_Free(msidb);
}

static PyObject* msierror(int status) {
    int code;
    char buf[2000];
    char* res = buf;
    DWORD size = Py_ARRAY_LENGTH(buf);
    MSIHANDLE err = MsiGetLastErrorRecord();

    if (err == 0) {
        switch (status) {
        case ERROR_ACCESS_DENIED:
            PyErr_SetString(MSIError, "access denied");
            return NULL;
        case ERROR_FUNCTION_FAILED:
            PyErr_SetString(MSIError, "function failed");
            return NULL;
        case ERROR_INVALID_DATA:
            PyErr_SetString(MSIError, "invalid data");
            return NULL;
        case ERROR_INVALID_HANDLE:
            PyErr_SetString(MSIError, "invalid handle");
            return NULL;
        case ERROR_INVALID_STATE:
            PyErr_SetString(MSIError, "invalid state");
            return NULL;
        case ERROR_INVALID_PARAMETER:
            PyErr_SetString(MSIError, "invalid parameter");
            return NULL;
        case ERROR_OPEN_FAILED:
            PyErr_SetString(MSIError, "open failed");
            return NULL;
        case ERROR_CREATE_FAILED:
            PyErr_SetString(MSIError, "create failed");
            return NULL;
        default:
            PyErr_Format(MSIError, "unknown error %x", status);
            return NULL;
        }
    }

    code = MsiRecordGetInteger(err, 1); /* XXX code */
    if (MsiFormatRecord(0, err, res, &size) == ERROR_MORE_DATA) {
        res = malloc(size + 1);
        if (res == NULL) {
            MsiCloseHandle(err);
            return PyErr_NoMemory();
        }
        MsiFormatRecord(0, err, res, &size);
        res[size] = '\0';
    }
    MsiCloseHandle(err);
    PyErr_SetString(MSIError, res);
    if (res != buf)
        free(res);
    return NULL;
}

// Add _PyArg_NoPositional and _PyArg_BadArgument (Python 3.13.0b2+)
#define Py_BUILD_CORE
#if PY_VERSION_HEX >= 0x030D00B2
#include <internal/pycore_modsupport.h>
#endif

// Compatible _PyCFunction_CAST (Python 3.10)
#ifndef _PyCFunction_CAST
#define _PyCFunction_CAST(func) ((PyCFunctionObject*)func)
#endif

#define _MSI_SENTINEL { NULL, NULL }

PyDoc_STRVAR(_msi_UuidCreate__doc__,
    "UuidCreate($module, /)\n"
    "--\n"
    "\n"
    "Return the string representation of a new unique identifier.");

#define _MSI_UUIDCREATE_METHODDEF                                             \
    { "UuidCreate", (PyCFunction)_msi_UuidCreate, METH_NOARGS,                \
        _msi_UuidCreate__doc__ }

static PyObject* _msi_UuidCreate_impl(PyObject* module);

static PyObject* _msi_UuidCreate(
    PyObject* module, PyObject* Py_UNUSED(ignored)) {
    return _msi_UuidCreate_impl(module);
}

PyDoc_STRVAR(_msi_FCICreate__doc__,
    "FCICreate($module, cabname, files, /)\n"
    "--\n"
    "\n"
    "Create a new CAB file.\n"
    "\n"
    "  cabname\n"
    "    the name of the CAB file\n"
    "  files\n"
    "    a list of tuples, each containing the name of the file on disk,\n"
    "    and the name of the file inside the CAB file");

#define _MSI_FCICREATE_METHODDEF                                              \
    { "FCICreate", _PyCFunction_CAST(_msi_FCICreate), METH_FASTCALL,          \
        _msi_FCICreate__doc__ }

static PyObject* _msi_FCICreate(
    PyObject* module, PyObject* const* args, Py_ssize_t nargs) {
    PyObject* return_value = NULL;
    const char* cabname;
    PyObject* files;

    if (!_PyArg_CheckPositional("FCICreate", nargs, 2, 2)) {
        goto exit;
    }
    if (!PyUnicode_Check(args[0])) {
        _PyArg_BadArgument("FCICreate", "argument 1", "str", args[0]);
        goto exit;
    }
    Py_ssize_t cabname_length;
    cabname = PyUnicode_AsUTF8AndSize(args[0], &cabname_length);
    if (cabname == NULL) {
        goto exit;
    }
    if (strlen(cabname) != (size_t)cabname_length) {
        PyErr_SetString(PyExc_ValueError, "embedded null character");
        goto exit;
    }
    files = args[1];
    return_value = _msi_FCICreate_impl(module, cabname, files);

exit:
    return return_value;
}

PyDoc_STRVAR(_msi_Database_Close__doc__,
    "Close($self, /)\n"
    "--\n"
    "\n"
    "Close the database object.");

#define _MSI_DATABASE_CLOSE_METHODDEF                                         \
    { "Close", (PyCFunction)_msi_Database_Close, METH_NOARGS,                 \
        _msi_Database_Close__doc__ }

static PyObject* _msi_Database_Close_impl(msiobj* self);

static PyObject* _msi_Database_Close(
    msiobj* self, PyObject* Py_UNUSED(ignored)) {
    return _msi_Database_Close_impl(self);
}

PyDoc_STRVAR(_msi_Record_GetFieldCount__doc__,
    "GetFieldCount($self, /)\n"
    "--\n"
    "\n"
    "Return the number of fields of the record.");

#define _MSI_RECORD_GETFIELDCOUNT_METHODDEF                                   \
    { "GetFieldCount", (PyCFunction)_msi_Record_GetFieldCount, METH_NOARGS,   \
        _msi_Record_GetFieldCount__doc__ }

static PyObject* _msi_Record_GetFieldCount_impl(msiobj* self);

static PyObject* _msi_Record_GetFieldCount(
    msiobj* self, PyObject* Py_UNUSED(ignored)) {
    return _msi_Record_GetFieldCount_impl(self);
}

PyDoc_STRVAR(_msi_Record_GetInteger__doc__,
    "GetInteger($self, field, /)\n"
    "--\n"
    "\n"
    "Return the value of field as an integer where possible.");

#define _MSI_RECORD_GETINTEGER_METHODDEF                                      \
    { "GetInteger", (PyCFunction)_msi_Record_GetInteger, METH_O,              \
        _msi_Record_GetInteger__doc__ }

static PyObject* _msi_Record_GetInteger_impl(msiobj* self, unsigned int field);

static PyObject* _msi_Record_GetInteger(msiobj* self, PyObject* arg) {
    PyObject* return_value = NULL;
    unsigned int field;

    field = (unsigned int)PyLong_AsUnsignedLongMask(arg);
    if (field == (unsigned int)-1 && PyErr_Occurred()) {
        goto exit;
    }
    return_value = _msi_Record_GetInteger_impl(self, field);

exit:
    return return_value;
}

PyDoc_STRVAR(_msi_Record_GetString__doc__,
    "GetString($self, field, /)\n"
    "--\n"
    "\n"
    "Return the value of field as a string where possible.");

#define _MSI_RECORD_GETSTRING_METHODDEF                                       \
    { "GetString", (PyCFunction)_msi_Record_GetString, METH_O,                \
        _msi_Record_GetString__doc__ }

static PyObject* _msi_Record_GetString_impl(msiobj* self, unsigned int field);

static PyObject* _msi_Record_GetString(msiobj* self, PyObject* arg) {
    PyObject* return_value = NULL;
    unsigned int field;

    field = (unsigned int)PyLong_AsUnsignedLongMask(arg);
    if (field == (unsigned int)-1 && PyErr_Occurred()) {
        goto exit;
    }
    return_value = _msi_Record_GetString_impl(self, field);

exit:
    return return_value;
}

PyDoc_STRVAR(_msi_Record_ClearData__doc__,
    "ClearData($self, /)\n"
    "--\n"
    "\n"
    "Set all fields of the record to 0.");

#define _MSI_RECORD_CLEARDATA_METHODDEF                                       \
    { "ClearData", (PyCFunction)_msi_Record_ClearData, METH_NOARGS,           \
        _msi_Record_ClearData__doc__ }

static PyObject* _msi_Record_ClearData_impl(msiobj* self);

static PyObject* _msi_Record_ClearData(
    msiobj* self, PyObject* Py_UNUSED(ignored)) {
    return _msi_Record_ClearData_impl(self);
}

PyDoc_STRVAR(_msi_Record_SetString__doc__,
    "SetString($self, field, value, /)\n"
    "--\n"
    "\n"
    "Set field to a string value.");

#define _MSI_RECORD_SETSTRING_METHODDEF                                       \
    { "SetString", _PyCFunction_CAST(_msi_Record_SetString), METH_FASTCALL,   \
        _msi_Record_SetString__doc__ }

static PyObject* _msi_Record_SetString_impl(
    msiobj* self, int field, const wchar_t* value);

static PyObject* _msi_Record_SetString(
    msiobj* self, PyObject* const* args, Py_ssize_t nargs) {
    PyObject* return_value = NULL;
    int field;
    const wchar_t* value = NULL;

    if (!_PyArg_CheckPositional("SetString", nargs, 2, 2)) {
        goto exit;
    }
    field = PyLong_AsInt(args[0]);
    if (field == -1 && PyErr_Occurred()) {
        goto exit;
    }
    if (!PyUnicode_Check(args[1])) {
        _PyArg_BadArgument("SetString", "argument 2", "str", args[1]);
        goto exit;
    }
    value = PyUnicode_AsWideCharString(args[1], NULL);
    if (value == NULL) {
        goto exit;
    }
    return_value = _msi_Record_SetString_impl(self, field, value);

exit:
    /* Cleanup for value */
    PyMem_Free((void*)value);

    return return_value;
}

PyDoc_STRVAR(_msi_Record_SetStream__doc__,
    "SetStream($self, field, value, /)\n"
    "--\n"
    "\n"
    "Set field to the contents of the file named value.");

#define _MSI_RECORD_SETSTREAM_METHODDEF                                       \
    { "SetStream", _PyCFunction_CAST(_msi_Record_SetStream), METH_FASTCALL,   \
        _msi_Record_SetStream__doc__ }

static PyObject* _msi_Record_SetStream_impl(
    msiobj* self, int field, const wchar_t* value);

static PyObject* _msi_Record_SetStream(
    msiobj* self, PyObject* const* args, Py_ssize_t nargs) {
    PyObject* return_value = NULL;
    int field;
    const wchar_t* value = NULL;

    if (!_PyArg_CheckPositional("SetStream", nargs, 2, 2)) {
        goto exit;
    }
    field = PyLong_AsInt(args[0]);
    if (field == -1 && PyErr_Occurred()) {
        goto exit;
    }
    if (!PyUnicode_Check(args[1])) {
        _PyArg_BadArgument("SetStream", "argument 2", "str", args[1]);
        goto exit;
    }
    value = PyUnicode_AsWideCharString(args[1], NULL);
    if (value == NULL) {
        goto exit;
    }
    return_value = _msi_Record_SetStream_impl(self, field, value);

exit:
    /* Cleanup for value */
    PyMem_Free((void*)value);

    return return_value;
}

PyDoc_STRVAR(_msi_Record_SetInteger__doc__,
    "SetInteger($self, field, value, /)\n"
    "--\n"
    "\n"
    "Set field to an integer value.");

#define _MSI_RECORD_SETINTEGER_METHODDEF                                      \
    { "SetInteger", _PyCFunction_CAST(_msi_Record_SetInteger), METH_FASTCALL, \
        _msi_Record_SetInteger__doc__ }

static PyObject* _msi_Record_SetInteger_impl(
    msiobj* self, int field, int value);

static PyObject* _msi_Record_SetInteger(
    msiobj* self, PyObject* const* args, Py_ssize_t nargs) {
    PyObject* return_value = NULL;
    int field;
    int value;

    if (!_PyArg_CheckPositional("SetInteger", nargs, 2, 2)) {
        goto exit;
    }
    field = PyLong_AsInt(args[0]);
    if (field == -1 && PyErr_Occurred()) {
        goto exit;
    }
    value = PyLong_AsInt(args[1]);
    if (value == -1 && PyErr_Occurred()) {
        goto exit;
    }
    return_value = _msi_Record_SetInteger_impl(self, field, value);

exit:
    return return_value;
}

PyDoc_STRVAR(_msi_SummaryInformation_GetProperty__doc__,
    "GetProperty($self, field, /)\n"
    "--\n"
    "\n"
    "Return a property of the summary.\n"
    "\n"
    "  field\n"
    "    the name of the property, one of the PID_* constants");

#define _MSI_SUMMARYINFORMATION_GETPROPERTY_METHODDEF                         \
    { "GetProperty", (PyCFunction)_msi_SummaryInformation_GetProperty,        \
        METH_O, _msi_SummaryInformation_GetProperty__doc__ }

static PyObject* _msi_SummaryInformation_GetProperty_impl(
    msiobj* self, int field);

static PyObject* _msi_SummaryInformation_GetProperty(
    msiobj* self, PyObject* arg) {
    PyObject* return_value = NULL;
    int field;

    field = PyLong_AsInt(arg);
    if (field == -1 && PyErr_Occurred()) {
        goto exit;
    }
    return_value = _msi_SummaryInformation_GetProperty_impl(self, field);

exit:
    return return_value;
}

PyDoc_STRVAR(_msi_SummaryInformation_GetPropertyCount__doc__,
    "GetPropertyCount($self, /)\n"
    "--\n"
    "\n"
    "Return the number of summary properties.");

#define _MSI_SUMMARYINFORMATION_GETPROPERTYCOUNT_METHODDEF                    \
    { "GetPropertyCount",                                                     \
        (PyCFunction)_msi_SummaryInformation_GetPropertyCount, METH_NOARGS,   \
        _msi_SummaryInformation_GetPropertyCount__doc__ }

static PyObject* _msi_SummaryInformation_GetPropertyCount_impl(msiobj* self);

static PyObject* _msi_SummaryInformation_GetPropertyCount(
    msiobj* self, PyObject* Py_UNUSED(ignored)) {
    return _msi_SummaryInformation_GetPropertyCount_impl(self);
}

PyDoc_STRVAR(_msi_SummaryInformation_SetProperty__doc__,
    "SetProperty($self, field, value, /)\n"
    "--\n"
    "\n"
    "Set a property.\n"
    "\n"
    "  field\n"
    "    the name of the property, one of the PID_* constants\n"
    "  value\n"
    "    the new value of the property (integer or string)");

#define _MSI_SUMMARYINFORMATION_SETPROPERTY_METHODDEF                         \
    { "SetProperty", _PyCFunction_CAST(_msi_SummaryInformation_SetProperty),  \
        METH_FASTCALL, _msi_SummaryInformation_SetProperty__doc__ }

static PyObject* _msi_SummaryInformation_SetProperty_impl(
    msiobj* self, int field, PyObject* data);

static PyObject* _msi_SummaryInformation_SetProperty(
    msiobj* self, PyObject* const* args, Py_ssize_t nargs) {
    PyObject* return_value = NULL;
    int field;
    PyObject* data;

    if (!_PyArg_CheckPositional("SetProperty", nargs, 2, 2)) {
        goto exit;
    }
    field = PyLong_AsInt(args[0]);
    if (field == -1 && PyErr_Occurred()) {
        goto exit;
    }
    data = args[1];
    return_value = _msi_SummaryInformation_SetProperty_impl(self, field, data);

exit:
    return return_value;
}

PyDoc_STRVAR(_msi_SummaryInformation_Persist__doc__,
    "Persist($self, /)\n"
    "--\n"
    "\n"
    "Write the modified properties to the summary information stream.");

#define _MSI_SUMMARYINFORMATION_PERSIST_METHODDEF                             \
    { "Persist", (PyCFunction)_msi_SummaryInformation_Persist, METH_NOARGS,   \
        _msi_SummaryInformation_Persist__doc__ }

static PyObject* _msi_SummaryInformation_Persist_impl(msiobj* self);

static PyObject* _msi_SummaryInformation_Persist(
    msiobj* self, PyObject* Py_UNUSED(ignored)) {
    return _msi_SummaryInformation_Persist_impl(self);
}

PyDoc_STRVAR(_msi_View_Execute__doc__,
    "Execute($self, params, /)\n"
    "--\n"
    "\n"
    "Execute the SQL query of the view.\n"
    "\n"
    "  params\n"
    "    a record describing actual values of the parameter tokens\n"
    "    in the query or None");

#define _MSI_VIEW_EXECUTE_METHODDEF                                           \
    { "Execute", (PyCFunction)_msi_View_Execute, METH_O,                      \
        _msi_View_Execute__doc__ }

PyDoc_STRVAR(_msi_View_Fetch__doc__,
    "Fetch($self, /)\n"
    "--\n"
    "\n"
    "Return a result record of the query.");

#define _MSI_VIEW_FETCH_METHODDEF                                             \
    { "Fetch", (PyCFunction)_msi_View_Fetch, METH_NOARGS,                     \
        _msi_View_Fetch__doc__ }

static PyObject* _msi_View_Fetch_impl(msiobj* self);

static PyObject* _msi_View_Fetch(msiobj* self, PyObject* Py_UNUSED(ignored)) {
    return _msi_View_Fetch_impl(self);
}

PyDoc_STRVAR(_msi_View_GetColumnInfo__doc__,
    "GetColumnInfo($self, kind, /)\n"
    "--\n"
    "\n"
    "Return a record describing the columns of the view.\n"
    "\n"
    "  kind\n"
    "    MSICOLINFO_NAMES or MSICOLINFO_TYPES");

#define _MSI_VIEW_GETCOLUMNINFO_METHODDEF                                     \
    { "GetColumnInfo", (PyCFunction)_msi_View_GetColumnInfo, METH_O,          \
        _msi_View_GetColumnInfo__doc__ }

static PyObject* _msi_View_GetColumnInfo_impl(msiobj* self, int kind);

static PyObject* _msi_View_GetColumnInfo(msiobj* self, PyObject* arg) {
    PyObject* return_value = NULL;
    int kind;

    kind = PyLong_AsInt(arg);
    if (kind == -1 && PyErr_Occurred()) {
        goto exit;
    }
    return_value = _msi_View_GetColumnInfo_impl(self, kind);

exit:
    return return_value;
}

PyDoc_STRVAR(_msi_View_Modify__doc__,
    "Modify($self, kind, data, /)\n"
    "--\n"
    "\n"
    "Modify the view.\n"
    "\n"
    "  kind\n"
    "    one of the MSIMODIFY_* constants\n"
    "  data\n"
    "    a record describing the new data");

#define _MSI_VIEW_MODIFY_METHODDEF                                            \
    { "Modify", _PyCFunction_CAST(_msi_View_Modify), METH_FASTCALL,           \
        _msi_View_Modify__doc__ }

static PyObject* _msi_View_Modify_impl(msiobj* self, int kind, PyObject* data);

static PyObject* _msi_View_Modify(
    msiobj* self, PyObject* const* args, Py_ssize_t nargs) {
    PyObject* return_value = NULL;
    int kind;
    PyObject* data;

    if (!_PyArg_CheckPositional("Modify", nargs, 2, 2)) {
        goto exit;
    }
    kind = PyLong_AsInt(args[0]);
    if (kind == -1 && PyErr_Occurred()) {
        goto exit;
    }
    data = args[1];
    return_value = _msi_View_Modify_impl(self, kind, data);

exit:
    return return_value;
}

PyDoc_STRVAR(_msi_View_Close__doc__,
    "Close($self, /)\n"
    "--\n"
    "\n"
    "Close the view.");

#define _MSI_VIEW_CLOSE_METHODDEF                                             \
    { "Close", (PyCFunction)_msi_View_Close, METH_NOARGS,                     \
        _msi_View_Close__doc__ }

static PyObject* _msi_View_Close_impl(msiobj* self);

static PyObject* _msi_View_Close(msiobj* self, PyObject* Py_UNUSED(ignored)) {
    return _msi_View_Close_impl(self);
}

PyDoc_STRVAR(_msi_Database_OpenView__doc__,
    "OpenView($self, sql, /)\n"
    "--\n"
    "\n"
    "Return a view object.\n"
    "\n"
    "  sql\n"
    "    the SQL statement to execute");

#define _MSI_DATABASE_OPENVIEW_METHODDEF                                      \
    { "OpenView", (PyCFunction)_msi_Database_OpenView, METH_O,                \
        _msi_Database_OpenView__doc__ }

static PyObject* _msi_Database_OpenView_impl(msiobj* self, const wchar_t* sql);

static PyObject* _msi_Database_OpenView(msiobj* self, PyObject* arg) {
    PyObject* return_value = NULL;
    const wchar_t* sql = NULL;

    if (!PyUnicode_Check(arg)) {
        _PyArg_BadArgument("OpenView", "argument", "str", arg);
        goto exit;
    }
    sql = PyUnicode_AsWideCharString(arg, NULL);
    if (sql == NULL) {
        goto exit;
    }
    return_value = _msi_Database_OpenView_impl(self, sql);

exit:
    /* Cleanup for sql */
    PyMem_Free((void*)sql);

    return return_value;
}

PyDoc_STRVAR(_msi_Database_Commit__doc__,
    "Commit($self, /)\n"
    "--\n"
    "\n"
    "Commit the changes pending in the current transaction.");

#define _MSI_DATABASE_COMMIT_METHODDEF                                        \
    { "Commit", (PyCFunction)_msi_Database_Commit, METH_NOARGS,               \
        _msi_Database_Commit__doc__ }

static PyObject* _msi_Database_Commit_impl(msiobj* self);

static PyObject* _msi_Database_Commit(
    msiobj* self, PyObject* Py_UNUSED(ignored)) {
    return _msi_Database_Commit_impl(self);
}

PyDoc_STRVAR(_msi_Database_GetSummaryInformation__doc__,
    "GetSummaryInformation($self, count, /)\n"
    "--\n"
    "\n"
    "Return a new summary information object.\n"
    "\n"
    "  count\n"
    "    the maximum number of updated values");

#define _MSI_DATABASE_GETSUMMARYINFORMATION_METHODDEF                         \
    { "GetSummaryInformation",                                                \
        (PyCFunction)_msi_Database_GetSummaryInformation, METH_O,             \
        _msi_Database_GetSummaryInformation__doc__ }

static PyObject* _msi_Database_GetSummaryInformation_impl(
    msiobj* self, int count);

static PyObject* _msi_Database_GetSummaryInformation(
    msiobj* self, PyObject* arg) {
    PyObject* return_value = NULL;
    int count;

    count = PyLong_AsInt(arg);
    if (count == -1 && PyErr_Occurred()) {
        goto exit;
    }
    return_value = _msi_Database_GetSummaryInformation_impl(self, count);

exit:
    return return_value;
}

PyDoc_STRVAR(_msi_OpenDatabase__doc__,
    "OpenDatabase($module, path, persist, /)\n"
    "--\n"
    "\n"
    "Return a new database object.\n"
    "\n"
    "  path\n"
    "    the file name of the MSI file\n"
    "  persist\n"
    "    the persistence mode");

#define _MSI_OPENDATABASE_METHODDEF                                           \
    { "OpenDatabase", _PyCFunction_CAST(_msi_OpenDatabase), METH_FASTCALL,    \
        _msi_OpenDatabase__doc__ }

static PyObject* _msi_OpenDatabase_impl(
    PyObject* module, const wchar_t* path, int persist);

static PyObject* _msi_OpenDatabase(
    PyObject* module, PyObject* const* args, Py_ssize_t nargs) {
    PyObject* return_value = NULL;
    const wchar_t* path = NULL;
    int persist;

    if (!_PyArg_CheckPositional("OpenDatabase", nargs, 2, 2)) {
        goto exit;
    }
    if (!PyUnicode_Check(args[0])) {
        _PyArg_BadArgument("OpenDatabase", "argument 1", "str", args[0]);
        goto exit;
    }
    path = PyUnicode_AsWideCharString(args[0], NULL);
    if (path == NULL) {
        goto exit;
    }
    persist = PyLong_AsInt(args[1]);
    if (persist == -1 && PyErr_Occurred()) {
        goto exit;
    }
    return_value = _msi_OpenDatabase_impl(module, path, persist);

exit:
    /* Cleanup for path */
    PyMem_Free((void*)path);

    return return_value;
}

PyDoc_STRVAR(_msi_CreateRecord__doc__,
    "CreateRecord($module, count, /)\n"
    "--\n"
    "\n"
    "Return a new record object.\n"
    "\n"
    "  count\n"
    "    the number of fields of the record");

#define _MSI_CREATERECORD_METHODDEF                                           \
    { "CreateRecord", (PyCFunction)_msi_CreateRecord, METH_O,                 \
        _msi_CreateRecord__doc__ }

static PyObject* _msi_CreateRecord_impl(PyObject* module, int count);

static PyObject* _msi_CreateRecord(PyObject* module, PyObject* arg) {
    PyObject* return_value = NULL;
    int count;

    count = PyLong_AsInt(arg);
    if (count == -1 && PyErr_Occurred()) {
        goto exit;
    }
    return_value = _msi_CreateRecord_impl(module, count);

exit:
    return return_value;
}

static PyObject* _msi_Database_Close_impl(msiobj* self) {
    int status;
    if ((status = MsiCloseHandle(self->h)) != ERROR_SUCCESS) {
        return msierror(status);
    }
    self->h = 0;
    Py_RETURN_NONE;
}

/*************************** Record objects **********************/
static PyObject* _msi_Record_GetFieldCount_impl(msiobj* self) {
    return PyLong_FromLong(MsiRecordGetFieldCount(self->h));
}

static PyObject* _msi_Record_GetInteger_impl(msiobj* self, unsigned int field) {
    int status;

    status = MsiRecordGetInteger(self->h, field);
    if (status == MSI_NULL_INTEGER) {
        PyErr_SetString(MSIError, "could not convert record field to integer");
        return NULL;
    }
    return PyLong_FromLong((long)status);
}

static PyObject* _msi_Record_GetString_impl(msiobj* self, unsigned int field) {
    unsigned int status;
    WCHAR buf[2000];
    WCHAR* res = buf;
    DWORD size = Py_ARRAY_LENGTH(buf);
    PyObject* string;

    status = MsiRecordGetStringW(self->h, field, res, &size);
    if (status == ERROR_MORE_DATA) {
        res = (WCHAR*)malloc((size + 1) * sizeof(WCHAR));
        if (res == NULL)
            return PyErr_NoMemory();
        status = MsiRecordGetStringW(self->h, field, res, &size);
    }
    if (status != ERROR_SUCCESS)
        return msierror((int)status);
    string = PyUnicode_FromWideChar(res, size);
    if (buf != res)
        free(res);
    return string;
}

static PyObject* _msi_Record_ClearData_impl(msiobj* self) {
    int status = MsiRecordClearData(self->h);
    if (status != ERROR_SUCCESS)
        return msierror(status);

    Py_RETURN_NONE;
}

static PyObject* _msi_Record_SetString_impl(
    msiobj* self, int field, const wchar_t* value) {
    int status;

    if ((status = MsiRecordSetStringW(self->h, field, value)) != ERROR_SUCCESS)
        return msierror(status);

    Py_RETURN_NONE;
}

static PyObject* _msi_Record_SetStream_impl(
    msiobj* self, int field, const wchar_t* value) {
    int status;

    if ((status = MsiRecordSetStreamW(self->h, field, value)) != ERROR_SUCCESS)
        return msierror(status);

    Py_RETURN_NONE;
}


static PyObject* _msi_Record_SetInteger_impl(
    msiobj* self, int field, int value) {
    int status;

    if ((status = MsiRecordSetInteger(self->h, field, value)) != ERROR_SUCCESS)
        return msierror(status);

    Py_RETURN_NONE;
}

static PyMethodDef record_methods[]
    = { _MSI_RECORD_GETFIELDCOUNT_METHODDEF, _MSI_RECORD_GETINTEGER_METHODDEF,
          _MSI_RECORD_GETSTRING_METHODDEF, _MSI_RECORD_SETSTRING_METHODDEF,
          _MSI_RECORD_SETSTREAM_METHODDEF, _MSI_RECORD_SETINTEGER_METHODDEF,
          _MSI_RECORD_CLEARDATA_METHODDEF, _MSI_SENTINEL };

static PyTypeObject record_Type = {
    PyVarObject_HEAD_INIT(NULL, 0) "_msi.Record", /*tp_name*/
    sizeof(msiobj),                               /*tp_basicsize*/
    0,                                            /*tp_itemsize*/
    /* methods */
    (destructor)msiobj_dealloc, /*tp_dealloc*/
    0,                          /*tp_vectorcall_offset*/
    0,                          /*tp_getattr*/
    0,                          /*tp_setattr*/
    0,                          /*tp_as_async*/
    0,                          /*tp_repr*/
    0,                          /*tp_as_number*/
    0,                          /*tp_as_sequence*/
    0,                          /*tp_as_mapping*/
    0,                          /*tp_hash*/
    0,                          /*tp_call*/
    0,                          /*tp_str*/
    PyObject_GenericGetAttr,    /*tp_getattro*/
    PyObject_GenericSetAttr,    /*tp_setattro*/
    0,                          /*tp_as_buffer*/
    Py_TPFLAGS_DEFAULT,         /*tp_flags*/
    0,                          /*tp_doc*/
    0,                          /*tp_traverse*/
    0,                          /*tp_clear*/
    0,                          /*tp_richcompare*/
    0,                          /*tp_weaklistoffset*/
    0,                          /*tp_iter*/
    0,                          /*tp_iternext*/
    record_methods,             /*tp_methods*/
    0,                          /*tp_members*/
    0,                          /*tp_getset*/
    0,                          /*tp_base*/
    0,                          /*tp_dict*/
    0,                          /*tp_descr_get*/
    0,                          /*tp_descr_set*/
    0,                          /*tp_dictoffset*/
    0,                          /*tp_init*/
    0,                          /*tp_alloc*/
    0,                          /*tp_new*/
    0,                          /*tp_free*/
    0,                          /*tp_is_gc*/
};

static PyObject* record_new(MSIHANDLE h) {
    msiobj* result = PyObject_New(struct msiobj, &record_Type);

    if (!result) {
        MsiCloseHandle(h);
        return NULL;
    }

    result->h = h;
    return (PyObject*)result;
}

/*************************** SummaryInformation objects **************/
static PyObject* _msi_SummaryInformation_GetProperty_impl(
    msiobj* self, int field) {
    int status;
    PyObject* result;
    UINT type;
    INT ival;
    FILETIME fval;
    char sbuf[1000];
    char* sval = sbuf;
    DWORD ssize = sizeof(sbuf);

    status = MsiSummaryInfoGetProperty(
        self->h, field, &type, &ival, &fval, sval, &ssize);
    if (status == ERROR_MORE_DATA) {
        ssize++;
        sval = malloc(ssize);
        if (sval == NULL) {
            return PyErr_NoMemory();
        }
        status = MsiSummaryInfoGetProperty(
            self->h, field, &type, &ival, &fval, sval, &ssize);
    }
    if (status != ERROR_SUCCESS) {
        return msierror(status);
    }

    switch (type) {
    case VT_I2:
    case VT_I4:
        result = PyLong_FromLong(ival);
        break;
    case VT_FILETIME:
        PyErr_SetString(PyExc_NotImplementedError, "FILETIME result");
        result = NULL;
        break;
    case VT_LPSTR:
        result = PyBytes_FromStringAndSize(sval, ssize);
        break;
    case VT_EMPTY:
        result = Py_NewRef(Py_None);
        break;
    default:
        PyErr_Format(PyExc_NotImplementedError, "result of type %d", type);
        result = NULL;
        break;
    }
    if (sval != sbuf)
        free(sval);
    return result;
}

static PyObject* _msi_SummaryInformation_GetPropertyCount_impl(msiobj* self) {
    int status;
    UINT result;

    status = MsiSummaryInfoGetPropertyCount(self->h, &result);
    if (status != ERROR_SUCCESS)
        return msierror(status);

    return PyLong_FromLong(result);
}

static PyObject* _msi_SummaryInformation_SetProperty_impl(
    msiobj* self, int field, PyObject* data) {
    int status;

    if (PyUnicode_Check(data)) {
        WCHAR* value = PyUnicode_AsWideCharString(data, NULL);
        if (value == NULL) {
            return NULL;
        }
        status = MsiSummaryInfoSetPropertyW(
            self->h, field, VT_LPSTR, 0, NULL, value);
        PyMem_Free(value);
    } else if (PyLong_CheckExact(data)) {
        long value = PyLong_AsLong(data);
        if (value == -1 && PyErr_Occurred()) {
            return NULL;
        }
        status = MsiSummaryInfoSetProperty(
            self->h, field, VT_I4, value, NULL, NULL);
    } else {
        PyErr_SetString(PyExc_TypeError, "unsupported type");
        return NULL;
    }

    if (status != ERROR_SUCCESS)
        return msierror(status);

    Py_RETURN_NONE;
}


static PyObject* _msi_SummaryInformation_Persist_impl(msiobj* self) {
    int status;

    status = MsiSummaryInfoPersist(self->h);
    if (status != ERROR_SUCCESS)
        return msierror(status);
    Py_RETURN_NONE;
}

static PyMethodDef summary_methods[]
    = { _MSI_SUMMARYINFORMATION_GETPROPERTY_METHODDEF,
          _MSI_SUMMARYINFORMATION_GETPROPERTYCOUNT_METHODDEF,
          _MSI_SUMMARYINFORMATION_SETPROPERTY_METHODDEF,
          _MSI_SUMMARYINFORMATION_PERSIST_METHODDEF, _MSI_SENTINEL };

static PyTypeObject summary_Type = {
    PyVarObject_HEAD_INIT(NULL, 0) "_msi.SummaryInformation", /*tp_name*/
    sizeof(msiobj),                                           /*tp_basicsize*/
    0,                                                        /*tp_itemsize*/
    /* methods */
    (destructor)msiobj_dealloc, /*tp_dealloc*/
    0,                          /*tp_vectorcall_offset*/
    0,                          /*tp_getattr*/
    0,                          /*tp_setattr*/
    0,                          /*tp_as_async*/
    0,                          /*tp_repr*/
    0,                          /*tp_as_number*/
    0,                          /*tp_as_sequence*/
    0,                          /*tp_as_mapping*/
    0,                          /*tp_hash*/
    0,                          /*tp_call*/
    0,                          /*tp_str*/
    PyObject_GenericGetAttr,    /*tp_getattro*/
    PyObject_GenericSetAttr,    /*tp_setattro*/
    0,                          /*tp_as_buffer*/
    Py_TPFLAGS_DEFAULT,         /*tp_flags*/
    0,                          /*tp_doc*/
    0,                          /*tp_traverse*/
    0,                          /*tp_clear*/
    0,                          /*tp_richcompare*/
    0,                          /*tp_weaklistoffset*/
    0,                          /*tp_iter*/
    0,                          /*tp_iternext*/
    summary_methods,            /*tp_methods*/
    0,                          /*tp_members*/
    0,                          /*tp_getset*/
    0,                          /*tp_base*/
    0,                          /*tp_dict*/
    0,                          /*tp_descr_get*/
    0,                          /*tp_descr_set*/
    0,                          /*tp_dictoffset*/
    0,                          /*tp_init*/
    0,                          /*tp_alloc*/
    0,                          /*tp_new*/
    0,                          /*tp_free*/
    0,                          /*tp_is_gc*/
};

/*************************** View objects **************/
static PyObject* _msi_View_Execute(msiobj* self, PyObject* oparams) {
    int status;
    MSIHANDLE params = 0;

    if (!Py_IsNone(oparams)) {
        if (!Py_IS_TYPE(oparams, &record_Type)) {
            PyErr_SetString(
                PyExc_TypeError, "Execute argument must be a record");
            return NULL;
        }
        params = ((msiobj*)oparams)->h;
    }

    status = MsiViewExecute(self->h, params);
    if (status != ERROR_SUCCESS)
        return msierror(status);

    Py_RETURN_NONE;
}


static PyObject* _msi_View_Fetch_impl(msiobj* self) {
    int status;
    MSIHANDLE result;

    status = MsiViewFetch(self->h, &result);
    if (status == ERROR_NO_MORE_ITEMS) {
        Py_RETURN_NONE;
    } else if (status != ERROR_SUCCESS) {
        return msierror(status);
    }

    return record_new(result);
}


static PyObject* _msi_View_GetColumnInfo_impl(msiobj* self, int kind) {
    int status;
    MSIHANDLE result;

    if ((status = MsiViewGetColumnInfo(self->h, kind, &result))
        != ERROR_SUCCESS)
        return msierror(status);

    return record_new(result);
}

static PyObject* _msi_View_Modify_impl(msiobj* self, int kind, PyObject* data) {
    int status;

    if (!Py_IS_TYPE(data, &record_Type)) {
        PyErr_SetString(PyExc_TypeError, "Modify expects a record object");
        return NULL;
    }

    if ((status = MsiViewModify(self->h, kind, ((msiobj*)data)->h))
        != ERROR_SUCCESS)
        return msierror(status);

    Py_RETURN_NONE;
}


static PyObject* _msi_View_Close_impl(msiobj* self) {
    int status;

    if ((status = MsiViewClose(self->h)) != ERROR_SUCCESS)
        return msierror(status);

    Py_RETURN_NONE;
}

static PyMethodDef view_methods[] = { _MSI_VIEW_EXECUTE_METHODDEF,
    _MSI_VIEW_GETCOLUMNINFO_METHODDEF, _MSI_VIEW_FETCH_METHODDEF,
    _MSI_VIEW_MODIFY_METHODDEF, _MSI_VIEW_CLOSE_METHODDEF, _MSI_SENTINEL };

static PyTypeObject msiview_Type = {
    PyVarObject_HEAD_INIT(NULL, 0) "_msi.View", /*tp_name*/
    sizeof(msiobj),                             /*tp_basicsize*/
    0,                                          /*tp_itemsize*/
    /* methods */
    (destructor)msiobj_dealloc, /*tp_dealloc*/
    0,                          /*tp_vectorcall_offset*/
    0,                          /*tp_getattr*/
    0,                          /*tp_setattr*/
    0,                          /*tp_as_async*/
    0,                          /*tp_repr*/
    0,                          /*tp_as_number*/
    0,                          /*tp_as_sequence*/
    0,                          /*tp_as_mapping*/
    0,                          /*tp_hash*/
    0,                          /*tp_call*/
    0,                          /*tp_str*/
    PyObject_GenericGetAttr,    /*tp_getattro*/
    PyObject_GenericSetAttr,    /*tp_setattro*/
    0,                          /*tp_as_buffer*/
    Py_TPFLAGS_DEFAULT,         /*tp_flags*/
    0,                          /*tp_doc*/
    0,                          /*tp_traverse*/
    0,                          /*tp_clear*/
    0,                          /*tp_richcompare*/
    0,                          /*tp_weaklistoffset*/
    0,                          /*tp_iter*/
    0,                          /*tp_iternext*/
    view_methods,               /*tp_methods*/
    0,                          /*tp_members*/
    0,                          /*tp_getset*/
    0,                          /*tp_base*/
    0,                          /*tp_dict*/
    0,                          /*tp_descr_get*/
    0,                          /*tp_descr_set*/
    0,                          /*tp_dictoffset*/
    0,                          /*tp_init*/
    0,                          /*tp_alloc*/
    0,                          /*tp_new*/
    0,                          /*tp_free*/
    0,                          /*tp_is_gc*/
};

/*************************** Database objects **************/


static PyObject* _msi_Database_OpenView_impl(msiobj* self, const wchar_t* sql) {
    int status;
    MSIHANDLE hView;
    msiobj* result;

    if ((status = MsiDatabaseOpenViewW(self->h, sql, &hView)) != ERROR_SUCCESS)
        return msierror(status);

    result = PyObject_New(struct msiobj, &msiview_Type);
    if (!result) {
        MsiCloseHandle(hView);
        return NULL;
    }

    result->h = hView;
    return (PyObject*)result;
}


static PyObject* _msi_Database_Commit_impl(msiobj* self) {
    int status;

    if ((status = MsiDatabaseCommit(self->h)) != ERROR_SUCCESS)
        return msierror(status);

    Py_RETURN_NONE;
}


static PyObject* _msi_Database_GetSummaryInformation_impl(
    msiobj* self, int count) {
    int status;
    MSIHANDLE result;
    msiobj* oresult;

    status = MsiGetSummaryInformation(self->h, NULL, count, &result);
    if (status != ERROR_SUCCESS)
        return msierror(status);

    oresult = PyObject_New(struct msiobj, &summary_Type);
    if (!oresult) {
        MsiCloseHandle(result);
        return NULL;
    }

    oresult->h = result;
    return (PyObject*)oresult;
}

static PyMethodDef db_methods[]
    = { _MSI_DATABASE_OPENVIEW_METHODDEF, _MSI_DATABASE_COMMIT_METHODDEF,
          _MSI_DATABASE_GETSUMMARYINFORMATION_METHODDEF,
          _MSI_DATABASE_CLOSE_METHODDEF, _MSI_SENTINEL };

static PyTypeObject msidb_Type = {
    PyVarObject_HEAD_INIT(NULL, 0) "_msi.Database", /*tp_name*/
    sizeof(msiobj),                                 /*tp_basicsize*/
    0,                                              /*tp_itemsize*/
    /* methods */
    (destructor)msiobj_dealloc, /*tp_dealloc*/
    0,                          /*tp_vectorcall_offset*/
    0,                          /*tp_getattr*/
    0,                          /*tp_setattr*/
    0,                          /*tp_as_async*/
    0,                          /*tp_repr*/
    0,                          /*tp_as_number*/
    0,                          /*tp_as_sequence*/
    0,                          /*tp_as_mapping*/
    0,                          /*tp_hash*/
    0,                          /*tp_call*/
    0,                          /*tp_str*/
    PyObject_GenericGetAttr,    /*tp_getattro*/
    PyObject_GenericSetAttr,    /*tp_setattro*/
    0,                          /*tp_as_buffer*/
    Py_TPFLAGS_DEFAULT,         /*tp_flags*/
    0,                          /*tp_doc*/
    0,                          /*tp_traverse*/
    0,                          /*tp_clear*/
    0,                          /*tp_richcompare*/
    0,                          /*tp_weaklistoffset*/
    0,                          /*tp_iter*/
    0,                          /*tp_iternext*/
    db_methods,                 /*tp_methods*/
    0,                          /*tp_members*/
    0,                          /*tp_getset*/
    0,                          /*tp_base*/
    0,                          /*tp_dict*/
    0,                          /*tp_descr_get*/
    0,                          /*tp_descr_set*/
    0,                          /*tp_dictoffset*/
    0,                          /*tp_init*/
    0,                          /*tp_alloc*/
    0,                          /*tp_new*/
    0,                          /*tp_free*/
    0,                          /*tp_is_gc*/
};

#define Py_NOT_PERSIST(x, flag)                                               \
    (x != (SIZE_T)(flag) && x != ((SIZE_T)(flag) | MSIDBOPEN_PATCHFILE))

#define Py_INVALID_PERSIST(x)                                                 \
    (Py_NOT_PERSIST(x, MSIDBOPEN_READONLY)                                    \
        && Py_NOT_PERSIST(x, MSIDBOPEN_TRANSACT)                              \
        && Py_NOT_PERSIST(x, MSIDBOPEN_DIRECT)                                \
        && Py_NOT_PERSIST(x, MSIDBOPEN_CREATE)                                \
        && Py_NOT_PERSIST(x, MSIDBOPEN_CREATEDIRECT))


static PyObject* _msi_OpenDatabase_impl(
    PyObject* module, const wchar_t* path, int persist) {
    int status;
    MSIHANDLE h;
    msiobj* result;

    /* We need to validate that persist is a valid MSIDBOPEN_* value.
       Otherwise, MsiOpenDatabase may treat the value as a pointer, leading to
       unexpected behavior. */
    if (Py_INVALID_PERSIST(persist))
        return msierror(ERROR_INVALID_PARAMETER);
    status = MsiOpenDatabaseW(path, (LPCWSTR)(SIZE_T)persist, &h);
    if (status != ERROR_SUCCESS)
        return msierror(status);

    result = PyObject_New(struct msiobj, &msidb_Type);
    if (!result) {
        MsiCloseHandle(h);
        return NULL;
    }
    result->h = h;
    return (PyObject*)result;
}


static PyObject* _msi_CreateRecord_impl(PyObject* module, int count) {
    MSIHANDLE h;

    h = MsiCreateRecord(count);
    if (h == 0)
        return msierror(0);

    return record_new(h);
}

static PyMethodDef msi_methods[] = { _MSI_UUIDCREATE_METHODDEF,
    _MSI_FCICREATE_METHODDEF, _MSI_OPENDATABASE_METHODDEF,
    _MSI_CREATERECORD_METHODDEF, _MSI_SENTINEL };

static char msi_doc[] = "Documentation";

static struct PyModuleDef _msimodule = { PyModuleDef_HEAD_INIT, "_msi",
    msi_doc, -1, msi_methods, NULL, NULL, NULL, NULL };

PyMODINIT_FUNC PyInit__msi(void) {
    PyObject* m;

    m = PyModule_Create(&_msimodule);
    if (m == NULL)
        return NULL;

    PyModule_AddIntConstant(
        m, "MSIDBOPEN_CREATEDIRECT", (long)(SIZE_T)MSIDBOPEN_CREATEDIRECT);
    PyModule_AddIntConstant(
        m, "MSIDBOPEN_CREATE", (long)(SIZE_T)MSIDBOPEN_CREATE);
    PyModule_AddIntConstant(
        m, "MSIDBOPEN_DIRECT", (long)(SIZE_T)MSIDBOPEN_DIRECT);
    PyModule_AddIntConstant(
        m, "MSIDBOPEN_READONLY", (long)(SIZE_T)MSIDBOPEN_READONLY);
    PyModule_AddIntConstant(
        m, "MSIDBOPEN_TRANSACT", (long)(SIZE_T)MSIDBOPEN_TRANSACT);
    PyModule_AddIntConstant(
        m, "MSIDBOPEN_PATCHFILE", (long)(SIZE_T)MSIDBOPEN_PATCHFILE);

    PyModule_AddIntMacro(m, MSICOLINFO_NAMES);
    PyModule_AddIntMacro(m, MSICOLINFO_TYPES);

    PyModule_AddIntMacro(m, MSIMODIFY_SEEK);
    PyModule_AddIntMacro(m, MSIMODIFY_REFRESH);
    PyModule_AddIntMacro(m, MSIMODIFY_INSERT);
    PyModule_AddIntMacro(m, MSIMODIFY_UPDATE);
    PyModule_AddIntMacro(m, MSIMODIFY_ASSIGN);
    PyModule_AddIntMacro(m, MSIMODIFY_REPLACE);
    PyModule_AddIntMacro(m, MSIMODIFY_MERGE);
    PyModule_AddIntMacro(m, MSIMODIFY_DELETE);
    PyModule_AddIntMacro(m, MSIMODIFY_INSERT_TEMPORARY);
    PyModule_AddIntMacro(m, MSIMODIFY_VALIDATE);
    PyModule_AddIntMacro(m, MSIMODIFY_VALIDATE_NEW);
    PyModule_AddIntMacro(m, MSIMODIFY_VALIDATE_FIELD);
    PyModule_AddIntMacro(m, MSIMODIFY_VALIDATE_DELETE);

    PyModule_AddIntMacro(m, PID_CODEPAGE);
    PyModule_AddIntMacro(m, PID_TITLE);
    PyModule_AddIntMacro(m, PID_SUBJECT);
    PyModule_AddIntMacro(m, PID_AUTHOR);
    PyModule_AddIntMacro(m, PID_KEYWORDS);
    PyModule_AddIntMacro(m, PID_COMMENTS);
    PyModule_AddIntMacro(m, PID_TEMPLATE);
    PyModule_AddIntMacro(m, PID_LASTAUTHOR);
    PyModule_AddIntMacro(m, PID_REVNUMBER);
    PyModule_AddIntMacro(m, PID_LASTPRINTED);
    PyModule_AddIntMacro(m, PID_CREATE_DTM);
    PyModule_AddIntMacro(m, PID_LASTSAVE_DTM);
    PyModule_AddIntMacro(m, PID_PAGECOUNT);
    PyModule_AddIntMacro(m, PID_WORDCOUNT);
    PyModule_AddIntMacro(m, PID_CHARCOUNT);
    PyModule_AddIntMacro(m, PID_APPNAME);
    PyModule_AddIntMacro(m, PID_SECURITY);

    MSIError = PyErr_NewException("_msi.MSIError", NULL, NULL);
    if (!MSIError)
        return NULL;
    PyModule_AddObject(m, "MSIError", MSIError);
#ifdef Py_GIL_DISABLED
    PyUnstable_Module_SetGIL(m, Py_MOD_GIL_NOT_USED);
#endif
    return m;
}
