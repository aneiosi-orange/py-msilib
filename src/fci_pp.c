typedef unsigned long ULONG;
typedef ULONG* PULONG;
typedef unsigned short USHORT;
typedef USHORT* PUSHORT;
typedef unsigned char UCHAR;
typedef UCHAR* PUCHAR;
typedef char* PSZ;
typedef int WINBOOL;
typedef unsigned char BYTE;
typedef unsigned int UINT;
typedef unsigned long CHECKSUM;
typedef unsigned long UOFF;
typedef unsigned long COFF;

typedef struct {
    int erfOper;
    int erfType;
    WINBOOL fError;
} ERF;
typedef ERF* PERF;

typedef unsigned short TCOMP;
#include <basetsd.h> /* clang -E -fkeep-system-includes */
typedef enum {
    FCIERR_NONE,
    FCIERR_OPEN_SRC,
    FCIERR_READ_SRC,
    FCIERR_ALLOC_FAIL,
    FCIERR_TEMP_FILE,
    FCIERR_BAD_COMPR_TYPE,
    FCIERR_CAB_FILE,
    FCIERR_USER_ABORT,
    FCIERR_MCI_FAIL
} FCIERROR;
typedef void* HFCI;

typedef struct {
    ULONG cb;
    ULONG cbFolderThresh;
    UINT cbReserveCFHeader;
    UINT cbReserveCFFolder;
    UINT cbReserveCFData;
    int iCab;
    int iDisk;
    int fFailOnIncompressible;
    USHORT setID;
    char szDisk[256];
    char szCab[256];
    char szCabPath[256];
} CCAB;

typedef CCAB* PCCAB;

typedef void* (*PFNFCIALLOC)(ULONG cb);

typedef void (*PFNFCIFREE)(void* memory);

typedef INT_PTR (*PFNFCIOPEN)(char* pszFile, int oflag, int pmode, int* err, void* pv);
typedef UINT (*PFNFCIREAD)(INT_PTR hf, void* memory, UINT cb, int* err, void* pv);
typedef UINT (*PFNFCIWRITE)(INT_PTR hf, void* memory, UINT cb, int* err, void* pv);
typedef int (*PFNFCICLOSE)(INT_PTR hf, int* err, void* pv);
typedef long (*PFNFCISEEK)(INT_PTR hf, long dist, int seektype, int* err, void* pv);
typedef int (*PFNFCIDELETE)(char* pszFile, int* err, void* pv);





typedef WINBOOL (*PFNFCIGETNEXTCABINET)(PCCAB pccab, ULONG cbPrevCab, void* pv);

typedef int (*PFNFCIFILEPLACED)(PCCAB pccab, char* pszFile, long cbFile, WINBOOL fContinuation, void* pv);

typedef INT_PTR (*PFNFCIGETOPENINFO)(char* pszName, USHORT* pdate,USHORT* ptime, USHORT* pattribs, int* err, void* pv);

typedef long (*PFNFCISTATUS)(UINT typeStatus, ULONG cb1, ULONG cb2, void* pv);

typedef WINBOOL (*PFNFCIGETTEMPFILE)(char* pszTempName, int cbTempName, void* pv);

HFCI FCICreate(PERF perf, PFNFCIFILEPLACED pfnfcifp, PFNFCIALLOC pfna,
    PFNFCIFREE pfnf, PFNFCIOPEN pfnopen, PFNFCIREAD pfnread,
    PFNFCIWRITE pfnwrite, PFNFCICLOSE pfnclose, PFNFCISEEK pfnseek,
    PFNFCIDELETE pfndelete, PFNFCIGETTEMPFILE pfnfcigtf, PCCAB pccab,
    void* pv);
WINBOOL FCIAddFile(HFCI hfci, char* pszSourceFile, char* pszFileName,
    WINBOOL fExecute, PFNFCIGETNEXTCABINET pfnfcignc, PFNFCISTATUS pfnfcis,
    PFNFCIGETOPENINFO pfnfcigoi, TCOMP typeCompress);
WINBOOL FCIFlushCabinet(HFCI hfci, WINBOOL fGetNextCab,
    PFNFCIGETNEXTCABINET pfnfcignc, PFNFCISTATUS pfnfcis);
WINBOOL FCIFlushFolder(
    HFCI hfci, PFNFCIGETNEXTCABINET pfnfcignc, PFNFCISTATUS pfnfcis);
WINBOOL FCIDestroy(HFCI hfci);
