from ctypes import WINFUNCTYPE, Array, Structure, _Pointer, c_ssize_t, windll
from ctypes.wintypes import (
	BOOL,
	CHAR,
	HANDLE,
	INT,
	LONG,
	LPSTR,
	LPVOID,
	LPWORD,
	PINT,
	UINT,
	ULONG,
	USHORT,
)
from enum import IntEnum
from typing import Final


class ERF(Structure):
	erfOper: INT
	erfType: INT
	fError : BOOL
	_fields_ = [
		("erfOper", INT),
		("erfType", INT),
		("fError",  BOOL),
	]

PERF = _Pointer[ERF]

CB_MAX_CHUNK       : Final = UINT(32768)
CB_MAX_DISK        : Final = ULONG(0x7FFFFFFF)
CB_MAX_FILENAME    : Final = 256
CB_MAX_CABINET_NAME: Final = 256
CB_MAX_CAB_PATH    : Final = 256
CB_MAX_DISK_NAME   : Final = 256

TCOMP = USHORT

class tcompTYPE(IntEnum):
	NONE    = 0x0000
	MSZIP   = 0x0001
	QUANTUM = 0x0002
	LZX     = 0x0003

tcompLZX_WINDOW_LO: Final = 0x0F00
tcompLZX_WINDOW_HI: Final = 0x1500

tcompMASK_TYPE         : Final = 0x000F
tcompMASK_QUANTUM_LEVEL: Final = 0x00F0
tcompMASK_LZX_WINDOW   : Final = 0x1F00
tcompMASK_QUANTUM_MEM  : Final = 0x1F00
tcompMASK_RESERVED     : Final = 0xE000

tcompQUANTUM_LEVEL_HI: Final = 0x0070
tcompQUANTUM_LEVEL_LO: Final = 0x0010
tcompQUANTUM_MEM_HI  : Final = 0x1500
tcompQUANTUM_MEM_LO  : Final = 0x0A00

tcompSHIFT_LZX_WINDOW   : Final = 8
tcompSHIFT_QUANTUM_LEVEL: Final = 4
tcompSHIFT_QUANTUM_MEM  : Final = 8

def CompressionLevelFromTCOMP(tc):
	return (((tc) & tcompMASK_QUANTUM_LEVEL) >> tcompSHIFT_QUANTUM_LEVEL)

def CompressionMemoryFromTCOMP(tc):
	return (((tc) & tcompMASK_QUANTUM_MEM) >> tcompSHIFT_QUANTUM_MEM)

def CompressionTypeFromTCOMP(tc):
	return ((tc) & tcompMASK_TYPE)

def LZXCompressionWindowFromTCOMP(tc):
	return (((tc) & tcompMASK_LZX_WINDOW) >> tcompSHIFT_LZX_WINDOW)

def TCOMPfromLZXWindow(w):
	return (((w) << tcompSHIFT_LZX_WINDOW) | (tcompTYPE.LZX))

def TCOMPfromTypeLevelMemory(t, l, m):
	return (((m) << tcompSHIFT_QUANTUM_MEM) | ((l) << tcompSHIFT_QUANTUM_LEVEL) | (t))

class FCIERR(IntEnum):
	NONE           = 0
	OPEN_SRC       = 1
	READ_SRC       = 2
	ALLOC_FAIL     = 3
	TEMP_FILE      = 4
	BAD_COMPR_TYPE = 5
	CAB_FILE       = 6
	USER_ABORT     = 7
	MCI_FAIL       = 8

_A_NAME_IS_UTF: Final = 0x80
_A_EXEC       : Final = 0x40

HFCI = HANDLE

class CCAB(Structure):
	cb                   : ULONG
	cbFolderThresh       : ULONG
	cbReserveCFHeader    : UINT
	cbReserveCFFolder    : UINT
	cbReserveCFData      : UINT
	iCab                 : INT
	iDisk                : INT
	fFailOnIncompressible: INT
	setID                : USHORT
	szDisk               : Array[CHAR]
	szCab                : Array[CHAR]
	szCabPath            : Array[CHAR]
	_fields_ = [
		("cb",                    ULONG),
		("cbFolderThresh",        ULONG),
		("cbReserveCFHeader",     UINT),
		("cbReserveCFFolder",     UINT),
		("cbReserveCFData",       UINT),
		("iCab",                  INT),
		("iDisk",                 INT),
		("fFailOnIncompressible", INT),
		("setID",                 USHORT),
		("szDisk",                CHAR * CB_MAX_DISK_NAME),
		("szCab",                 CHAR * CB_MAX_CABINET_NAME),
		("szCabPath",             CHAR * CB_MAX_CAB_PATH),
	]

PCCAB = _Pointer[CCAB]

PFNFCIALLOC = WINFUNCTYPE(HANDLE, ULONG)
PFNFCIFREE  = WINFUNCTYPE(None, LPVOID)

INT_PTR = c_ssize_t

PFNFCIOPEN   = WINFUNCTYPE(INT_PTR, LPSTR, INT, INT, PINT, LPVOID)
PFNFCIREAD   = WINFUNCTYPE(UINT, INT_PTR, HANDLE, UINT, PINT, LPVOID)
PFNFCIWRITE  = WINFUNCTYPE(UINT, INT_PTR, HANDLE, UINT, PINT, LPVOID)
PFNFCICLOSE  = WINFUNCTYPE(INT, INT_PTR, PINT, LPVOID)
PFNFCISEEK   = WINFUNCTYPE(LONG, INT_PTR, LONG, INT, PINT, LPVOID)
PFNFCIDELETE = WINFUNCTYPE(INT, LPSTR, PINT, LPVOID)

PFNFCIGETNEXTCABINET = WINFUNCTYPE(BOOL, PCCAB, ULONG, LPVOID)
PFNFCIFILEPLACED     = WINFUNCTYPE(INT, PCCAB, LPSTR, LONG, BOOL, LPVOID)
PFNFCIGETOPENINFO    = WINFUNCTYPE(INT_PTR, LPSTR, LPWORD, LPWORD, LPWORD, PINT, LPVOID)

class status(IntEnum):
	File    = 0
	Folder  = 1
	Cabinet = 2

PFNFCISTATUS      = WINFUNCTYPE(LONG, UINT, ULONG, ULONG, LPVOID)
PFNFCIGETTEMPFILE = WINFUNCTYPE(BOOL, LPSTR, INT, LPVOID)

cabinet_dll = windll.cabinet

FCICreate = WINFUNCTYPE(
	HFCI,
	PERF,
	PFNFCIFILEPLACED,
	PFNFCIALLOC,
	PFNFCIFREE,
	PFNFCIOPEN,
	PFNFCIREAD,
	PFNFCIWRITE,
	PFNFCICLOSE,
	PFNFCISEEK,
	PFNFCIDELETE,
	PFNFCIGETTEMPFILE,
	PCCAB,
	LPVOID,
)(("FCICreate", cabinet_dll))

FCIAddFile = WINFUNCTYPE(
	BOOL,
	HFCI,
	LPSTR,
	LPSTR,
	BOOL,
	PFNFCIGETNEXTCABINET,
	PFNFCISTATUS,
	PFNFCIGETOPENINFO,
	TCOMP,
)(("FCIAddFile", cabinet_dll))

FCIFlushCabinet = WINFUNCTYPE(
	BOOL,
	HFCI,
	BOOL,
	PFNFCIGETNEXTCABINET,
	PFNFCISTATUS,
)(("FCIFlushCabinet", cabinet_dll))

FCIFlushFolder = WINFUNCTYPE(
	BOOL,
	HFCI,
	PFNFCIGETNEXTCABINET,
	PFNFCISTATUS,
)(("FCIFlushFolder", cabinet_dll))

FCIDestroy = WINFUNCTYPE(
	BOOL,
	HFCI,
)(("FCIDestroy", cabinet_dll))
