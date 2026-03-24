from ctypes import byref, get_errno, memmove, memoryview_at, py_object, pythonapi, string_at
from ctypes.wintypes import (
	BOOL,
	FILETIME,
	HANDLE,
	INT,
	LONG,
	LPSTR,
	LPVOID,
	LPWORD,
	PINT,
	UINT,
	ULONG,
	WORD,
)
from errno import EINVAL
from nt import O_BINARY, O_NOINHERIT, O_RDONLY, close, lseek, open, readinto, remove, write
from tempfile import mkstemp

from msilib.fci import (
	CB_MAX_CABINET_NAME,
	INT_PTR,
	PCCAB,
	PFNFCIALLOC,
	PFNFCICLOSE,
	PFNFCIDELETE,
	PFNFCIFILEPLACED,
	PFNFCIFREE,
	PFNFCIGETNEXTCABINET,
	PFNFCIGETOPENINFO,
	PFNFCIGETTEMPFILE,
	PFNFCIOPEN,
	PFNFCIREAD,
	PFNFCISEEK,
	PFNFCISTATUS,
	PFNFCIWRITE,
)
from msilib.fileapi import (
	BY_HANDLE_FILE_INFORMATION,
	FILE_ATTRIBUTE,
	FILE_SHARE,
	GENERIC,
	INVALID_HANDLE_VALUE,
	OPEN_EXISTING,
	CloseHandle,
	CreateFileW,
	FileTimeToDosDateTime,
	FileTimeToLocalFileTime,
	GetFileInformationByHandle,
)


def set_error(err: PINT, errno_val: int) -> None:
	"""Set error code if err pointer is valid."""
	if err:
		err.contents.value = errno_val


@PFNFCIALLOC
def cb_alloc(cb: ULONG) -> HANDLE:
	"""Allocate memory for FCI operations."""

	if pythonapi.PyMem_RawMalloc.argtypes is None:
		pythonapi.PyMem_RawMalloc.argtypes = [ULONG]
		pythonapi.PyMem_RawMalloc.restype = HANDLE

	return pythonapi.PyMem_RawMalloc(cb)


@PFNFCIFREE
def cb_free(memory: HANDLE) -> None:
	"""Free memory allocated for FCI operations."""

	if pythonapi.PyMem_RawFree.argtypes is None:
		pythonapi.PyMem_RawFree.argtypes = [HANDLE]
		pythonapi.PyMem_RawFree.restype = None

	pythonapi.PyMem_RawFree(memory)


@PFNFCIOPEN
def cb_open(pszFile: LPSTR, oflag: INT, pmode: INT, err: PINT, pv: LPVOID) -> INT_PTR:
	"""Open a file for FCI operations."""

	try:
		filename = string_at(pszFile).decode("utf-8")
	except UnicodeDecodeError, AttributeError, ValueError:
		if err:
			err.contents.value = EINVAL
		return INT_PTR(-1)

	try:
		result = open(filename, int(oflag) | O_NOINHERIT, int(pmode))
		return INT_PTR(result)
	except OSError as e:
		if err and e.errno:
			err.contents.value = e.errno
		return INT_PTR(-1)


@PFNFCIREAD
def cb_read(hf: INT_PTR, memory: HANDLE, cb: UINT, err: PINT, pv: LPVOID) -> UINT:
	"""Read from a file for FCI operations."""

	try:
		buffer = memoryview_at(memory, int(cb))
		bytes_read = readinto(int(hf), buffer)

		if bytes_read != int(cb) and err:
			err.contents.value = get_errno()

		return UINT(bytes_read)
	except OSError as e:
		if err and e.errno:
			err.contents.value = e.errno
		return UINT(0)


@PFNFCIWRITE
def cb_write(hf: INT_PTR, memory: HANDLE, cb: UINT, err: PINT, pv: LPVOID) -> UINT:
	"""Write to a file for FCI operations."""

	try:
		buffer = memoryview_at(memory, int(cb))
		bytes_written = write(int(hf), buffer)

		if bytes_written != int(cb) and err:
			err.contents.value = get_errno()

		return UINT(bytes_written)
	except OSError as e:
		if err and e.errno:
			err.contents.value = e.errno
		return UINT(0)


@PFNFCICLOSE
def cb_close(hf: INT_PTR, err: PINT, pv: LPVOID) -> INT:
	"""Close a file for FCI operations."""

	try:
		close(int(hf))
		return INT(0)
	except OSError as e:
		if err and e.errno:
			err.contents.value = e.errno
		return INT(-1)


@PFNFCISEEK
def cb_seek(hf: INT_PTR, dist: LONG, seektype: INT, err: PINT, pv: LPVOID) -> LONG:
	"""Seek in a file for FCI operations."""

	try:
		result = lseek(int(hf), int(dist), int(seektype))
		return LONG(result)
	except OSError as e:
		if err and e.errno:
			err.contents.value = e.errno
		return LONG(-1)


@PFNFCIDELETE
def cb_delete(pszFile: LPSTR, err: PINT, pv: LPVOID) -> INT:
	"""Delete a file for FCI operations."""

	try:
		filename = string_at(pszFile).decode("utf-8")

		remove(filename)

		return INT(0)
	except (UnicodeDecodeError, OSError) as e:
		if err:
			if isinstance(e, OSError) and e.errno:
				err.contents.value = e.errno
			else:
				err.contents.value = get_errno()
		return INT(-1)


@PFNFCIFILEPLACED
def cb_fileplaced(
	pccab: PCCAB,
	pszFile: LPSTR,
	cbFile: LONG,
	fContinuation: BOOL,
	pv: LPVOID,
) -> INT:
	"""Called when a file has been placed in the cabinet."""
	return INT(0)


@PFNFCIGETTEMPFILE
def cb_gettempfile(pszTempName: LPSTR, cbTempName: INT, pv: LPVOID) -> BOOL:
	"""Generate a temporary filename for FCI operations."""

	try:
		fd, name = mkstemp(prefix="tmp")
		close(fd)
		name_bytes = name.encode("utf-8") + b'\0'
		if len(name_bytes) < int(cbTempName):
			memmove(pszTempName, name_bytes, len(name_bytes))
			return BOOL(1)

		return BOOL(0)

	except OSError, UnicodeEncodeError:
		return BOOL(0)


@PFNFCISTATUS
def cb_status(typeStatus: UINT, cb1: ULONG, cb2: ULONG, pv: LPVOID) -> LONG:
	"""Report status during FCI operations."""

	if pv and pv.value:
		try:
			obj = py_object.from_address(pv.value).value
			if not hasattr(obj, 'status'):
				return LONG(-1)
			obj.status(int(typeStatus), int(cb1), int(cb2))
			return LONG(0)
		except AttributeError, ValueError, OSError:
			return LONG(-1)

	return LONG(0)


@PFNFCIGETNEXTCABINET
def cb_getnextcabinet(pccab: PCCAB, cbPrevCab: ULONG, pv: LPVOID) -> BOOL:
	"""Get the name for the next cabinet file."""

	if pv and pv.value:
		try:
			obj = py_object.from_address(pv.value).value
			if not hasattr(obj, 'getnextcabinet'):
				return BOOL(0)
			result = obj.getnextcabinet(pccab.contents.iCab)

			if not isinstance(result, bytes):
				raise TypeError(
					f"Incorrect return type {type(result).__name__} from getnextcabinet"
				)

			pccab.contents.szCab.value = result[: CB_MAX_CABINET_NAME - 1]
			return BOOL(1)

		except AttributeError, TypeError, ValueError, OSError:
			return BOOL(0)

	return BOOL(0)


@PFNFCIGETOPENINFO
def cb_getopeninfo(
	pszName: LPSTR, pdate: LPWORD, ptime: LPWORD, pattribs: LPWORD, err: PINT, pv: LPVOID
) -> INT_PTR:
	"""Open a file and return its metadata."""

	try:
		ws = string_at(pszName).decode("utf-8")
	except UnicodeDecodeError:
		if err:
			err.contents.value = -1
		return INT_PTR(-1)

	handle = CreateFileW(
		ws, GENERIC.READ, FILE_SHARE.READ, None, OPEN_EXISTING, FILE_ATTRIBUTE.NORMAL, None
	)
	if handle == INVALID_HANDLE_VALUE:
		if err:
			err.contents.value = -1
		return INT_PTR(-1)

	bhfi = BY_HANDLE_FILE_INFORMATION()
	if not GetFileInformationByHandle(handle, byref(bhfi)):
		CloseHandle(handle)
		if err:
			err.contents.value = -1
		return INT_PTR(-1)

	filetime = FILETIME()
	FileTimeToLocalFileTime(byref(bhfi.ftLastWriteTime), byref(filetime))
	FileTimeToDosDateTime(byref(filetime), pdate, ptime)
	pattribs.contents = WORD(
		int(bhfi.dwFileAttributes)
		& (
			FILE_ATTRIBUTE.READONLY
			| FILE_ATTRIBUTE.HIDDEN
			| FILE_ATTRIBUTE.SYSTEM
			| FILE_ATTRIBUTE.ARCHIVE
		)
	)
	CloseHandle(handle)

	try:
		return INT_PTR(open(ws, O_RDONLY | O_BINARY | O_NOINHERIT))
	except OSError:
		if err:
			err.contents.value = -1
		return INT_PTR(-1)
