from ctypes import WINFUNCTYPE, Structure, _Pointer, windll
from ctypes.wintypes import BOOL, DWORD, FILETIME, HANDLE, LPCWSTR, LPFILETIME, LPVOID, LPWORD
from enum import IntEnum
from typing import Final


class FILE_ATTRIBUTE(IntEnum):
	READONLY              = 0x00000001
	HIDDEN                = 0x00000002
	SYSTEM                = 0x00000004
	DIRECTORY             = 0x00000010
	ARCHIVE               = 0x00000020
	DEVICE                = 0x00000040
	NORMAL                = 0x00000080
	TEMPORARY             = 0x00000100
	SPARSE_FILE           = 0x00000200
	REPARSE_POINT         = 0x00000400
	COMPRESSED            = 0x00000800
	OFFLINE               = 0x00001000
	NOT_CONTENT_INDEXED   = 0x00002000
	ENCRYPTED             = 0x00004000
	INTEGRITY_STREAM      = 0x00008000
	VIRTUAL               = 0x00010000
	NO_SCRUB_DATA         = 0x00020000
	EA                    = 0x00040000
	PINNED                = 0x00080000
	UNPINNED              = 0x00100000
	RECALL_ON_OPEN        = 0x00040000
	RECALL_ON_DATA_ACCESS = 0x00400000
	STRICTLY_SEQUENTIAL   = 0x20000000


CREATE_NEW       : Final = 1
CREATE_ALWAYS    : Final = 2
OPEN_EXISTING    : Final = 3
OPEN_ALWAYS      : Final = 4
TRUNCATE_EXISTING: Final = 5


class GENERIC(IntEnum):
	READ    = 0x80000000
	WRITE   = 0x40000000
	EXECUTE = 0x20000000
	ALL     = 0x10000000


class FILE_SHARE(IntEnum):
	READ        = 0x00000001
	WRITE       = 0x00000002
	DELETE      = 0x00000004
	VALID_FLAGS = 0x00000007


INVALID_HANDLE_VALUE: Final = HANDLE(-1)


class BY_HANDLE_FILE_INFORMATION(Structure):
	dwFileAttributes    : DWORD
	ftCreationTime      : FILETIME
	ftLastAccessTime    : FILETIME
	ftLastWriteTime     : FILETIME
	dwVolumeSerialNumber: DWORD
	nFileSizeHigh       : DWORD
	nFileSizeLow        : DWORD
	nNumberOfLinks      : DWORD
	nFileIndexHigh      : DWORD
	nFileIndexLow       : DWORD
	_fields_ = [
		("dwFileAttributes", DWORD),
		("ftCreationTime", FILETIME),
		("ftLastAccessTime", FILETIME),
		("ftLastWriteTime", FILETIME),
		("dwVolumeSerialNumber", DWORD),
		("nFileSizeHigh", DWORD),
		("nFileSizeLow", DWORD),
		("nNumberOfLinks", DWORD),
		("nFileIndexHigh", DWORD),
		("nFileIndexLow", DWORD),
	]


class SECURITY_ATTRIBUTES(Structure):
	nLength             : DWORD
	lpSecurityDescriptor: LPVOID
	bInheritHandle      : BOOL
	_fields_ = [
		("nLength", DWORD),
		("lpSecurityDescriptor", LPVOID),
		("bInheritHandle", BOOL),
	]


LPBY_HANDLE_FILE_INFORMATION = PBY_HANDLE_FILE_INFORMATION = _Pointer[BY_HANDLE_FILE_INFORMATION]
LPSECURITY_ATTRIBUTES        = PSECURITY_ATTRIBUTES        = _Pointer[SECURITY_ATTRIBUTES]

kernel32_dll = windll.kernel32

GetFileInformationByHandle = WINFUNCTYPE(
	BOOL,
	HANDLE,
	LPBY_HANDLE_FILE_INFORMATION,
)(("GetFileInformationByHandle", kernel32_dll))

CreateFileW = WINFUNCTYPE(
	HANDLE,
	LPCWSTR,
	DWORD,
	DWORD,
	LPSECURITY_ATTRIBUTES,
	DWORD,
	DWORD,
	HANDLE,
)(("CreateFileW", kernel32_dll))

FileTimeToLocalFileTime = WINFUNCTYPE(
	BOOL,
	LPFILETIME,
	LPFILETIME,
)(("FileTimeToLocalFileTime", kernel32_dll))

FileTimeToDosDateTime = WINFUNCTYPE(
	BOOL,
	LPFILETIME,
	LPWORD,
	LPWORD,
)(("FileTimeToDosDateTime", kernel32_dll))

CloseHandle = WINFUNCTYPE(BOOL, HANDLE)(("CloseHandle", kernel32_dll))
