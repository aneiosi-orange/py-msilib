#include <io.h> /* clang -E -fkeep-system-includes */
#include <stdio.h> /* clang -E -fkeep-system-includes */
#include <assert.h> /* clang -E -fkeep-system-includes */
#include <inttypes.h> /* clang -E -fkeep-system-includes */
#include <limits.h> /* clang -E -fkeep-system-includes */
//#include <math.h> /* clang -E -fkeep-system-includes */
#include <stdarg.h> /* clang -E -fkeep-system-includes */
#include <wchar.h> /* clang -E -fkeep-system-includes */
#include <sys/types.h> /* clang -E -fkeep-system-includes */
#include <errno.h> /* clang -E -fkeep-system-includes */
#include <stdio.h> /* clang -E -fkeep-system-includes */
#include <stdlib.h> /* clang -E -fkeep-system-includes */
#include <string.h> /* clang -E -fkeep-system-includes */
//#include <ctype.h> /* clang -E -fkeep-system-includes */
# 145 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/pyport.h"
typedef uintptr_t Py_uintptr_t;
typedef intptr_t Py_intptr_t;
# 159 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/pyport.h"
typedef Py_intptr_t Py_ssize_t;
# 170 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/pyport.h"
typedef Py_ssize_t Py_hash_t;

typedef size_t Py_uhash_t;

typedef Py_ssize_t Py_ssize_clean_t;
# 242 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/pymacro.h"
__attribute__((dllimport)) uint32_t Py_PACK_FULL_VERSION(int x, int y, int z, int level, int serial);
__attribute__((dllimport)) uint32_t Py_PACK_VERSION(int x, int y);
# 48 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/pymem.h"
__attribute__((dllimport)) void * PyMem_Malloc(size_t size);
__attribute__((dllimport)) void * PyMem_Calloc(size_t nelem, size_t elsize);
__attribute__((dllimport)) void * PyMem_Realloc(void *ptr, size_t new_size);
__attribute__((dllimport)) void PyMem_Free(void *ptr);
# 95 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/pymem.h"
__attribute__((dllimport)) void * PyMem_RawMalloc(size_t size);
__attribute__((dllimport)) void * PyMem_RawCalloc(size_t nelem, size_t elsize);
__attribute__((dllimport)) void * PyMem_RawRealloc(void *ptr, size_t new_size);
__attribute__((dllimport)) void PyMem_RawFree(void *ptr);

typedef enum {
    PYMEM_DOMAIN_RAW,
    PYMEM_DOMAIN_MEM,
    PYMEM_DOMAIN_OBJ
} PyMemAllocatorDomain;

typedef enum {
    PYMEM_ALLOCATOR_NOT_SET = 0,
    PYMEM_ALLOCATOR_DEFAULT = 1,
    PYMEM_ALLOCATOR_DEBUG = 2,
    PYMEM_ALLOCATOR_MALLOC = 3,
    PYMEM_ALLOCATOR_MALLOC_DEBUG = 4,
    PYMEM_ALLOCATOR_PYMALLOC = 5,
    PYMEM_ALLOCATOR_PYMALLOC_DEBUG = 6,
    PYMEM_ALLOCATOR_MIMALLOC = 7,
    PYMEM_ALLOCATOR_MIMALLOC_DEBUG = 8,
} PyMemAllocatorName;

typedef struct {
    void *ctx;
    void* (*malloc) (void *ctx, size_t size);
    void* (*calloc) (void *ctx, size_t nelem, size_t elsize);
    void* (*realloc) (void *ctx, void *ptr, size_t new_size);
    void (*free) (void *ctx, void *ptr);
} PyMemAllocatorEx;

__attribute__((dllimport)) void PyMem_GetAllocator(PyMemAllocatorDomain domain,
                                    PyMemAllocatorEx *allocator);
# 65 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/pymem.h"
__attribute__((dllimport)) void PyMem_SetAllocator(PyMemAllocatorDomain domain,
                                    PyMemAllocatorEx *allocator);
# 84 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/pymem.h"
__attribute__((dllimport)) void PyMem_SetupDebugHooks(void);
# 12 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/pytypedefs.h"
typedef struct PyModuleDef PyModuleDef;
typedef struct PyModuleDef_Slot PyModuleDef_Slot;
typedef struct PyMethodDef PyMethodDef;
typedef struct PyGetSetDef PyGetSetDef;
typedef struct PyMemberDef PyMemberDef;

typedef struct _object PyObject;
typedef struct _longobject PyLongObject;
typedef struct _typeobject PyTypeObject;
typedef struct PyCodeObject PyCodeObject;
typedef struct _frame PyFrameObject;

typedef struct _ts PyThreadState;
typedef struct _is PyInterpreterState;
# 20 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/pybuffer.h"
typedef struct {
    void *buf;
    PyObject *obj;
    Py_ssize_t len;
    Py_ssize_t itemsize;
    int readonly;
    int ndim;
    char *format;
    Py_ssize_t *shape;
    Py_ssize_t *strides;
    Py_ssize_t *suboffsets;
    void *internal;
} Py_buffer;

typedef int (*getbufferproc)(PyObject *, Py_buffer *, int);
typedef void (*releasebufferproc)(PyObject *, Py_buffer *);

__attribute__((dllimport)) int PyObject_CheckBuffer(PyObject *obj);

__attribute__((dllimport)) int PyObject_GetBuffer(PyObject *obj, Py_buffer *view,
                                   int flags);

__attribute__((dllimport)) void * PyBuffer_GetPointer(const Py_buffer *view, const Py_ssize_t *indices);

__attribute__((dllimport)) Py_ssize_t PyBuffer_SizeFromFormat(const char *format);

__attribute__((dllimport)) int PyBuffer_ToContiguous(void *buf, const Py_buffer *view,
                                      Py_ssize_t len, char order);

__attribute__((dllimport)) int PyBuffer_FromContiguous(const Py_buffer *view, const void *buf,
                                        Py_ssize_t len, char order);
# 77 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/pybuffer.h"
__attribute__((dllimport)) int PyObject_CopyData(PyObject *dest, PyObject *src);

__attribute__((dllimport)) int PyBuffer_IsContiguous(const Py_buffer *view, char fort);

__attribute__((dllimport)) void PyBuffer_FillContiguousStrides(int ndims,
                                               Py_ssize_t *shape,
                                               Py_ssize_t *strides,
                                               int itemsize,
                                               char fort);

__attribute__((dllimport)) int PyBuffer_FillInfo(Py_buffer *view, PyObject *o, void *buf,
                                  Py_ssize_t len, int readonly,
                                  int flags);

__attribute__((dllimport)) void PyBuffer_Release(Py_buffer *view);
# 93 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/pyatomic.h"
static inline int
_Py_atomic_add_int(int *obj, int value);

static inline int8_t
_Py_atomic_add_int8(int8_t *obj, int8_t value);

static inline int16_t
_Py_atomic_add_int16(int16_t *obj, int16_t value);

static inline int32_t
_Py_atomic_add_int32(int32_t *obj, int32_t value);

static inline int64_t
_Py_atomic_add_int64(int64_t *obj, int64_t value);

static inline intptr_t
_Py_atomic_add_intptr(intptr_t *obj, intptr_t value);

static inline unsigned int
_Py_atomic_add_uint(unsigned int *obj, unsigned int value);

static inline uint8_t
_Py_atomic_add_uint8(uint8_t *obj, uint8_t value);

static inline uint16_t
_Py_atomic_add_uint16(uint16_t *obj, uint16_t value);

static inline uint32_t
_Py_atomic_add_uint32(uint32_t *obj, uint32_t value);

static inline uint64_t
_Py_atomic_add_uint64(uint64_t *obj, uint64_t value);

static inline uintptr_t
_Py_atomic_add_uintptr(uintptr_t *obj, uintptr_t value);

static inline Py_ssize_t
_Py_atomic_add_ssize(Py_ssize_t *obj, Py_ssize_t value);
# 143 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/pyatomic.h"
static inline int
_Py_atomic_compare_exchange_int(int *obj, int *expected, int desired);

static inline int
_Py_atomic_compare_exchange_int8(int8_t *obj, int8_t *expected, int8_t desired);

static inline int
_Py_atomic_compare_exchange_int16(int16_t *obj, int16_t *expected, int16_t desired);

static inline int
_Py_atomic_compare_exchange_int32(int32_t *obj, int32_t *expected, int32_t desired);

static inline int
_Py_atomic_compare_exchange_int64(int64_t *obj, int64_t *expected, int64_t desired);

static inline int
_Py_atomic_compare_exchange_intptr(intptr_t *obj, intptr_t *expected, intptr_t desired);

static inline int
_Py_atomic_compare_exchange_uint(unsigned int *obj, unsigned int *expected, unsigned int desired);

static inline int
_Py_atomic_compare_exchange_uint8(uint8_t *obj, uint8_t *expected, uint8_t desired);

static inline int
_Py_atomic_compare_exchange_uint16(uint16_t *obj, uint16_t *expected, uint16_t desired);

static inline int
_Py_atomic_compare_exchange_uint32(uint32_t *obj, uint32_t *expected, uint32_t desired);

static inline int
_Py_atomic_compare_exchange_uint64(uint64_t *obj, uint64_t *expected, uint64_t desired);

static inline int
_Py_atomic_compare_exchange_uintptr(uintptr_t *obj, uintptr_t *expected, uintptr_t desired);

static inline int
_Py_atomic_compare_exchange_ssize(Py_ssize_t *obj, Py_ssize_t *expected, Py_ssize_t desired);

static inline int
_Py_atomic_compare_exchange_ptr(void *obj, void *expected, void *value);

static inline int
_Py_atomic_exchange_int(int *obj, int value);

static inline int8_t
_Py_atomic_exchange_int8(int8_t *obj, int8_t value);

static inline int16_t
_Py_atomic_exchange_int16(int16_t *obj, int16_t value);

static inline int32_t
_Py_atomic_exchange_int32(int32_t *obj, int32_t value);

static inline int64_t
_Py_atomic_exchange_int64(int64_t *obj, int64_t value);

static inline intptr_t
_Py_atomic_exchange_intptr(intptr_t *obj, intptr_t value);

static inline unsigned int
_Py_atomic_exchange_uint(unsigned int *obj, unsigned int value);

static inline uint8_t
_Py_atomic_exchange_uint8(uint8_t *obj, uint8_t value);

static inline uint16_t
_Py_atomic_exchange_uint16(uint16_t *obj, uint16_t value);

static inline uint32_t
_Py_atomic_exchange_uint32(uint32_t *obj, uint32_t value);

static inline uint64_t
_Py_atomic_exchange_uint64(uint64_t *obj, uint64_t value);

static inline uintptr_t
_Py_atomic_exchange_uintptr(uintptr_t *obj, uintptr_t value);

static inline Py_ssize_t
_Py_atomic_exchange_ssize(Py_ssize_t *obj, Py_ssize_t value);

static inline void *
_Py_atomic_exchange_ptr(void *obj, void *value);

static inline uint8_t
_Py_atomic_and_uint8(uint8_t *obj, uint8_t value);

static inline uint16_t
_Py_atomic_and_uint16(uint16_t *obj, uint16_t value);

static inline uint32_t
_Py_atomic_and_uint32(uint32_t *obj, uint32_t value);

static inline uint64_t
_Py_atomic_and_uint64(uint64_t *obj, uint64_t value);

static inline uintptr_t
_Py_atomic_and_uintptr(uintptr_t *obj, uintptr_t value);

static inline uint8_t
_Py_atomic_or_uint8(uint8_t *obj, uint8_t value);

static inline uint16_t
_Py_atomic_or_uint16(uint16_t *obj, uint16_t value);

static inline uint32_t
_Py_atomic_or_uint32(uint32_t *obj, uint32_t value);

static inline uint64_t
_Py_atomic_or_uint64(uint64_t *obj, uint64_t value);

static inline uintptr_t
_Py_atomic_or_uintptr(uintptr_t *obj, uintptr_t value);

static inline int
_Py_atomic_load_int(const int *obj);

static inline int8_t
_Py_atomic_load_int8(const int8_t *obj);

static inline int16_t
_Py_atomic_load_int16(const int16_t *obj);

static inline int32_t
_Py_atomic_load_int32(const int32_t *obj);

static inline int64_t
_Py_atomic_load_int64(const int64_t *obj);

static inline intptr_t
_Py_atomic_load_intptr(const intptr_t *obj);

static inline uint8_t
_Py_atomic_load_uint8(const uint8_t *obj);

static inline uint16_t
_Py_atomic_load_uint16(const uint16_t *obj);

static inline uint32_t
_Py_atomic_load_uint32(const uint32_t *obj);

static inline uint64_t
_Py_atomic_load_uint64(const uint64_t *obj);

static inline uintptr_t
_Py_atomic_load_uintptr(const uintptr_t *obj);

static inline unsigned int
_Py_atomic_load_uint(const unsigned int *obj);

static inline Py_ssize_t
_Py_atomic_load_ssize(const Py_ssize_t *obj);

static inline void *
_Py_atomic_load_ptr(const void *obj);

static inline int
_Py_atomic_load_int_relaxed(const int *obj);

static inline char
_Py_atomic_load_char_relaxed(const char *obj);

static inline unsigned char
_Py_atomic_load_uchar_relaxed(const unsigned char *obj);

static inline short
_Py_atomic_load_short_relaxed(const short *obj);

static inline unsigned short
_Py_atomic_load_ushort_relaxed(const unsigned short *obj);

static inline long
_Py_atomic_load_long_relaxed(const long *obj);

static inline double
_Py_atomic_load_double_relaxed(const double *obj);

static inline long long
_Py_atomic_load_llong_relaxed(const long long *obj);

static inline int8_t
_Py_atomic_load_int8_relaxed(const int8_t *obj);

static inline int16_t
_Py_atomic_load_int16_relaxed(const int16_t *obj);

static inline int32_t
_Py_atomic_load_int32_relaxed(const int32_t *obj);

static inline int64_t
_Py_atomic_load_int64_relaxed(const int64_t *obj);

static inline intptr_t
_Py_atomic_load_intptr_relaxed(const intptr_t *obj);

static inline uint8_t
_Py_atomic_load_uint8_relaxed(const uint8_t *obj);

static inline uint16_t
_Py_atomic_load_uint16_relaxed(const uint16_t *obj);

static inline uint32_t
_Py_atomic_load_uint32_relaxed(const uint32_t *obj);

static inline uint64_t
_Py_atomic_load_uint64_relaxed(const uint64_t *obj);

static inline uintptr_t
_Py_atomic_load_uintptr_relaxed(const uintptr_t *obj);

static inline unsigned int
_Py_atomic_load_uint_relaxed(const unsigned int *obj);

static inline Py_ssize_t
_Py_atomic_load_ssize_relaxed(const Py_ssize_t *obj);

static inline void *
_Py_atomic_load_ptr_relaxed(const void *obj);

static inline unsigned long long
_Py_atomic_load_ullong_relaxed(const unsigned long long *obj);

static inline void
_Py_atomic_store_int(int *obj, int value);

static inline void
_Py_atomic_store_int8(int8_t *obj, int8_t value);

static inline void
_Py_atomic_store_int16(int16_t *obj, int16_t value);

static inline void
_Py_atomic_store_int32(int32_t *obj, int32_t value);

static inline void
_Py_atomic_store_int64(int64_t *obj, int64_t value);

static inline void
_Py_atomic_store_intptr(intptr_t *obj, intptr_t value);

static inline void
_Py_atomic_store_uint8(uint8_t *obj, uint8_t value);

static inline void
_Py_atomic_store_uint16(uint16_t *obj, uint16_t value);

static inline void
_Py_atomic_store_uint32(uint32_t *obj, uint32_t value);

static inline void
_Py_atomic_store_uint64(uint64_t *obj, uint64_t value);

static inline void
_Py_atomic_store_uintptr(uintptr_t *obj, uintptr_t value);

static inline void
_Py_atomic_store_uint(unsigned int *obj, unsigned int value);

static inline void
_Py_atomic_store_ptr(void *obj, void *value);

static inline void
_Py_atomic_store_ssize(Py_ssize_t* obj, Py_ssize_t value);

static inline void
_Py_atomic_store_int_relaxed(int *obj, int value);

static inline void
_Py_atomic_store_int8_relaxed(int8_t *obj, int8_t value);

static inline void
_Py_atomic_store_int16_relaxed(int16_t *obj, int16_t value);

static inline void
_Py_atomic_store_int32_relaxed(int32_t *obj, int32_t value);

static inline void
_Py_atomic_store_int64_relaxed(int64_t *obj, int64_t value);

static inline void
_Py_atomic_store_intptr_relaxed(intptr_t *obj, intptr_t value);

static inline void
_Py_atomic_store_uint8_relaxed(uint8_t* obj, uint8_t value);

static inline void
_Py_atomic_store_uint16_relaxed(uint16_t *obj, uint16_t value);

static inline void
_Py_atomic_store_uint32_relaxed(uint32_t *obj, uint32_t value);

static inline void
_Py_atomic_store_uint64_relaxed(uint64_t *obj, uint64_t value);

static inline void
_Py_atomic_store_uintptr_relaxed(uintptr_t *obj, uintptr_t value);

static inline void
_Py_atomic_store_uint_relaxed(unsigned int *obj, unsigned int value);

static inline void
_Py_atomic_store_ptr_relaxed(void *obj, void *value);

static inline void
_Py_atomic_store_ssize_relaxed(Py_ssize_t *obj, Py_ssize_t value);

static inline void
_Py_atomic_store_ullong_relaxed(unsigned long long *obj,
                                unsigned long long value);

static inline void
_Py_atomic_store_char_relaxed(char *obj, char value);

static inline void
_Py_atomic_store_uchar_relaxed(unsigned char *obj, unsigned char value);

static inline void
_Py_atomic_store_short_relaxed(short *obj, short value);

static inline void
_Py_atomic_store_ushort_relaxed(unsigned short *obj, unsigned short value);

static inline void
_Py_atomic_store_long_relaxed(long *obj, long value);

static inline void
_Py_atomic_store_float_relaxed(float *obj, float value);

static inline void
_Py_atomic_store_double_relaxed(double *obj, double value);

static inline void
_Py_atomic_store_llong_relaxed(long long *obj, long long value);

static inline void *
_Py_atomic_load_ptr_acquire(const void *obj);

static inline uintptr_t
_Py_atomic_load_uintptr_acquire(const uintptr_t *obj);

static inline void
_Py_atomic_store_ptr_release(void *obj, void *value);

static inline void
_Py_atomic_store_uintptr_release(uintptr_t *obj, uintptr_t value);

static inline void
_Py_atomic_store_ssize_release(Py_ssize_t *obj, Py_ssize_t value);

static inline void
_Py_atomic_store_int_release(int *obj, int value);

static inline int
_Py_atomic_load_int_acquire(const int *obj);

static inline void
_Py_atomic_store_uint32_release(uint32_t *obj, uint32_t value);

static inline void
_Py_atomic_store_uint64_release(uint64_t *obj, uint64_t value);

static inline uint64_t
_Py_atomic_load_uint64_acquire(const uint64_t *obj);

static inline uint32_t
_Py_atomic_load_uint32_acquire(const uint32_t *obj);

static inline Py_ssize_t
_Py_atomic_load_ssize_acquire(const Py_ssize_t *obj);
# 556 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/pyatomic.h"
static inline void _Py_atomic_fence_seq_cst(void);

static inline void _Py_atomic_fence_acquire(void);

static inline void _Py_atomic_fence_release(void);
# 13 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/pyatomic_gcc.h"
static inline int
_Py_atomic_add_int(int *obj, int value)
{ return __atomic_fetch_add(obj, value, 5); }

static inline int8_t
_Py_atomic_add_int8(int8_t *obj, int8_t value)
{ return __atomic_fetch_add(obj, value, 5); }

static inline int16_t
_Py_atomic_add_int16(int16_t *obj, int16_t value)
{ return __atomic_fetch_add(obj, value, 5); }

static inline int32_t
_Py_atomic_add_int32(int32_t *obj, int32_t value)
{ return __atomic_fetch_add(obj, value, 5); }

static inline int64_t
_Py_atomic_add_int64(int64_t *obj, int64_t value)
{ return __atomic_fetch_add(obj, value, 5); }

static inline intptr_t
_Py_atomic_add_intptr(intptr_t *obj, intptr_t value)
{ return __atomic_fetch_add(obj, value, 5); }

static inline unsigned int
_Py_atomic_add_uint(unsigned int *obj, unsigned int value)
{ return __atomic_fetch_add(obj, value, 5); }

static inline uint8_t
_Py_atomic_add_uint8(uint8_t *obj, uint8_t value)
{ return __atomic_fetch_add(obj, value, 5); }

static inline uint16_t
_Py_atomic_add_uint16(uint16_t *obj, uint16_t value)
{ return __atomic_fetch_add(obj, value, 5); }

static inline uint32_t
_Py_atomic_add_uint32(uint32_t *obj, uint32_t value)
{ return __atomic_fetch_add(obj, value, 5); }

static inline uint64_t
_Py_atomic_add_uint64(uint64_t *obj, uint64_t value)
{ return __atomic_fetch_add(obj, value, 5); }

static inline uintptr_t
_Py_atomic_add_uintptr(uintptr_t *obj, uintptr_t value)
{ return __atomic_fetch_add(obj, value, 5); }

static inline Py_ssize_t
_Py_atomic_add_ssize(Py_ssize_t *obj, Py_ssize_t value)
{ return __atomic_fetch_add(obj, value, 5); }

static inline int
_Py_atomic_compare_exchange_int(int *obj, int *expected, int desired)
{ return __atomic_compare_exchange_n(obj, expected, desired, 0,
                                     5, 5); }

static inline int
_Py_atomic_compare_exchange_int8(int8_t *obj, int8_t *expected, int8_t desired)
{ return __atomic_compare_exchange_n(obj, expected, desired, 0,
                                     5, 5); }

static inline int
_Py_atomic_compare_exchange_int16(int16_t *obj, int16_t *expected, int16_t desired)
{ return __atomic_compare_exchange_n(obj, expected, desired, 0,
                                     5, 5); }

static inline int
_Py_atomic_compare_exchange_int32(int32_t *obj, int32_t *expected, int32_t desired)
{ return __atomic_compare_exchange_n(obj, expected, desired, 0,
                                     5, 5); }

static inline int
_Py_atomic_compare_exchange_int64(int64_t *obj, int64_t *expected, int64_t desired)
{ return __atomic_compare_exchange_n(obj, expected, desired, 0,
                                     5, 5); }

static inline int
_Py_atomic_compare_exchange_intptr(intptr_t *obj, intptr_t *expected, intptr_t desired)
{ return __atomic_compare_exchange_n(obj, expected, desired, 0,
                                     5, 5); }

static inline int
_Py_atomic_compare_exchange_uint(unsigned int *obj, unsigned int *expected, unsigned int desired)
{ return __atomic_compare_exchange_n(obj, expected, desired, 0,
                                     5, 5); }

static inline int
_Py_atomic_compare_exchange_uint8(uint8_t *obj, uint8_t *expected, uint8_t desired)
{ return __atomic_compare_exchange_n(obj, expected, desired, 0,
                                     5, 5); }

static inline int
_Py_atomic_compare_exchange_uint16(uint16_t *obj, uint16_t *expected, uint16_t desired)
{ return __atomic_compare_exchange_n(obj, expected, desired, 0,
                                     5, 5); }

static inline int
_Py_atomic_compare_exchange_uint32(uint32_t *obj, uint32_t *expected, uint32_t desired)
{ return __atomic_compare_exchange_n(obj, expected, desired, 0,
                                     5, 5); }

static inline int
_Py_atomic_compare_exchange_uint64(uint64_t *obj, uint64_t *expected, uint64_t desired)
{ return __atomic_compare_exchange_n(obj, expected, desired, 0,
                                     5, 5); }

static inline int
_Py_atomic_compare_exchange_uintptr(uintptr_t *obj, uintptr_t *expected, uintptr_t desired)
{ return __atomic_compare_exchange_n(obj, expected, desired, 0,
                                     5, 5); }

static inline int
_Py_atomic_compare_exchange_ssize(Py_ssize_t *obj, Py_ssize_t *expected, Py_ssize_t desired)
{ return __atomic_compare_exchange_n(obj, expected, desired, 0,
                                     5, 5); }

static inline int
_Py_atomic_compare_exchange_ptr(void *obj, void *expected, void *desired)
{ return __atomic_compare_exchange_n((void **)obj, (void **)expected, desired, 0,
                                     5, 5); }

static inline int
_Py_atomic_exchange_int(int *obj, int value)
{ return __atomic_exchange_n(obj, value, 5); }

static inline int8_t
_Py_atomic_exchange_int8(int8_t *obj, int8_t value)
{ return __atomic_exchange_n(obj, value, 5); }

static inline int16_t
_Py_atomic_exchange_int16(int16_t *obj, int16_t value)
{ return __atomic_exchange_n(obj, value, 5); }

static inline int32_t
_Py_atomic_exchange_int32(int32_t *obj, int32_t value)
{ return __atomic_exchange_n(obj, value, 5); }

static inline int64_t
_Py_atomic_exchange_int64(int64_t *obj, int64_t value)
{ return __atomic_exchange_n(obj, value, 5); }

static inline intptr_t
_Py_atomic_exchange_intptr(intptr_t *obj, intptr_t value)
{ return __atomic_exchange_n(obj, value, 5); }

static inline unsigned int
_Py_atomic_exchange_uint(unsigned int *obj, unsigned int value)
{ return __atomic_exchange_n(obj, value, 5); }

static inline uint8_t
_Py_atomic_exchange_uint8(uint8_t *obj, uint8_t value)
{ return __atomic_exchange_n(obj, value, 5); }

static inline uint16_t
_Py_atomic_exchange_uint16(uint16_t *obj, uint16_t value)
{ return __atomic_exchange_n(obj, value, 5); }

static inline uint32_t
_Py_atomic_exchange_uint32(uint32_t *obj, uint32_t value)
{ return __atomic_exchange_n(obj, value, 5); }

static inline uint64_t
_Py_atomic_exchange_uint64(uint64_t *obj, uint64_t value)
{ return __atomic_exchange_n(obj, value, 5); }

static inline uintptr_t
_Py_atomic_exchange_uintptr(uintptr_t *obj, uintptr_t value)
{ return __atomic_exchange_n(obj, value, 5); }

static inline Py_ssize_t
_Py_atomic_exchange_ssize(Py_ssize_t *obj, Py_ssize_t value)
{ return __atomic_exchange_n(obj, value, 5); }

static inline void *
_Py_atomic_exchange_ptr(void *obj, void *value)
{ return __atomic_exchange_n((void **)obj, value, 5); }

static inline uint8_t
_Py_atomic_and_uint8(uint8_t *obj, uint8_t value)
{ return __atomic_fetch_and(obj, value, 5); }

static inline uint16_t
_Py_atomic_and_uint16(uint16_t *obj, uint16_t value)
{ return __atomic_fetch_and(obj, value, 5); }

static inline uint32_t
_Py_atomic_and_uint32(uint32_t *obj, uint32_t value)
{ return __atomic_fetch_and(obj, value, 5); }

static inline uint64_t
_Py_atomic_and_uint64(uint64_t *obj, uint64_t value)
{ return __atomic_fetch_and(obj, value, 5); }

static inline uintptr_t
_Py_atomic_and_uintptr(uintptr_t *obj, uintptr_t value)
{ return __atomic_fetch_and(obj, value, 5); }

static inline uint8_t
_Py_atomic_or_uint8(uint8_t *obj, uint8_t value)
{ return __atomic_fetch_or(obj, value, 5); }

static inline uint16_t
_Py_atomic_or_uint16(uint16_t *obj, uint16_t value)
{ return __atomic_fetch_or(obj, value, 5); }

static inline uint32_t
_Py_atomic_or_uint32(uint32_t *obj, uint32_t value)
{ return __atomic_fetch_or(obj, value, 5); }

static inline uint64_t
_Py_atomic_or_uint64(uint64_t *obj, uint64_t value)
{ return __atomic_fetch_or(obj, value, 5); }

static inline uintptr_t
_Py_atomic_or_uintptr(uintptr_t *obj, uintptr_t value)
{ return __atomic_fetch_or(obj, value, 5); }

static inline int
_Py_atomic_load_int(const int *obj)
{ return __atomic_load_n(obj, 5); }

static inline int8_t
_Py_atomic_load_int8(const int8_t *obj)
{ return __atomic_load_n(obj, 5); }

static inline int16_t
_Py_atomic_load_int16(const int16_t *obj)
{ return __atomic_load_n(obj, 5); }

static inline int32_t
_Py_atomic_load_int32(const int32_t *obj)
{ return __atomic_load_n(obj, 5); }

static inline int64_t
_Py_atomic_load_int64(const int64_t *obj)
{ return __atomic_load_n(obj, 5); }

static inline intptr_t
_Py_atomic_load_intptr(const intptr_t *obj)
{ return __atomic_load_n(obj, 5); }

static inline uint8_t
_Py_atomic_load_uint8(const uint8_t *obj)
{ return __atomic_load_n(obj, 5); }

static inline uint16_t
_Py_atomic_load_uint16(const uint16_t *obj)
{ return __atomic_load_n(obj, 5); }

static inline uint32_t
_Py_atomic_load_uint32(const uint32_t *obj)
{ return __atomic_load_n(obj, 5); }

static inline uint64_t
_Py_atomic_load_uint64(const uint64_t *obj)
{ return __atomic_load_n(obj, 5); }

static inline uintptr_t
_Py_atomic_load_uintptr(const uintptr_t *obj)
{ return __atomic_load_n(obj, 5); }

static inline unsigned int
_Py_atomic_load_uint(const unsigned int *obj)
{ return __atomic_load_n(obj, 5); }

static inline Py_ssize_t
_Py_atomic_load_ssize(const Py_ssize_t *obj)
{ return __atomic_load_n(obj, 5); }

static inline void *
_Py_atomic_load_ptr(const void *obj)
{ return (void *)__atomic_load_n((void * const *)obj, 5); }

static inline int
_Py_atomic_load_int_relaxed(const int *obj)
{ return __atomic_load_n(obj, 0); }

static inline char
_Py_atomic_load_char_relaxed(const char *obj)
{ return __atomic_load_n(obj, 0); }

static inline unsigned char
_Py_atomic_load_uchar_relaxed(const unsigned char *obj)
{ return __atomic_load_n(obj, 0); }

static inline short
_Py_atomic_load_short_relaxed(const short *obj)
{ return __atomic_load_n(obj, 0); }

static inline unsigned short
_Py_atomic_load_ushort_relaxed(const unsigned short *obj)
{ return __atomic_load_n(obj, 0); }

static inline long
_Py_atomic_load_long_relaxed(const long *obj)
{ return __atomic_load_n(obj, 0); }

static inline float
_Py_atomic_load_float_relaxed(const float *obj)
{ float ret; __atomic_load(obj, &ret, 0); return ret; }

static inline double
_Py_atomic_load_double_relaxed(const double *obj)
{ double ret; __atomic_load(obj, &ret, 0); return ret; }

static inline int8_t
_Py_atomic_load_int8_relaxed(const int8_t *obj)
{ return __atomic_load_n(obj, 0); }

static inline int16_t
_Py_atomic_load_int16_relaxed(const int16_t *obj)
{ return __atomic_load_n(obj, 0); }

static inline int32_t
_Py_atomic_load_int32_relaxed(const int32_t *obj)
{ return __atomic_load_n(obj, 0); }

static inline int64_t
_Py_atomic_load_int64_relaxed(const int64_t *obj)
{ return __atomic_load_n(obj, 0); }

static inline intptr_t
_Py_atomic_load_intptr_relaxed(const intptr_t *obj)
{ return __atomic_load_n(obj, 0); }

static inline uint8_t
_Py_atomic_load_uint8_relaxed(const uint8_t *obj)
{ return __atomic_load_n(obj, 0); }

static inline uint16_t
_Py_atomic_load_uint16_relaxed(const uint16_t *obj)
{ return __atomic_load_n(obj, 0); }

static inline uint32_t
_Py_atomic_load_uint32_relaxed(const uint32_t *obj)
{ return __atomic_load_n(obj, 0); }

static inline uint64_t
_Py_atomic_load_uint64_relaxed(const uint64_t *obj)
{ return __atomic_load_n(obj, 0); }

static inline uintptr_t
_Py_atomic_load_uintptr_relaxed(const uintptr_t *obj)
{ return __atomic_load_n(obj, 0); }

static inline unsigned int
_Py_atomic_load_uint_relaxed(const unsigned int *obj)
{ return __atomic_load_n(obj, 0); }

static inline Py_ssize_t
_Py_atomic_load_ssize_relaxed(const Py_ssize_t *obj)
{ return __atomic_load_n(obj, 0); }

static inline void *
_Py_atomic_load_ptr_relaxed(const void *obj)
{ return (void *)__atomic_load_n((void * const *)obj, 0); }

static inline unsigned long long
_Py_atomic_load_ullong_relaxed(const unsigned long long *obj)
{ return __atomic_load_n(obj, 0); }

static inline long long
_Py_atomic_load_llong_relaxed(const long long *obj)
{ return __atomic_load_n(obj, 0); }

static inline void
_Py_atomic_store_int(int *obj, int value)
{ __atomic_store_n(obj, value, 5); }

static inline void
_Py_atomic_store_int8(int8_t *obj, int8_t value)
{ __atomic_store_n(obj, value, 5); }

static inline void
_Py_atomic_store_int16(int16_t *obj, int16_t value)
{ __atomic_store_n(obj, value, 5); }

static inline void
_Py_atomic_store_int32(int32_t *obj, int32_t value)
{ __atomic_store_n(obj, value, 5); }

static inline void
_Py_atomic_store_int64(int64_t *obj, int64_t value)
{ __atomic_store_n(obj, value, 5); }

static inline void
_Py_atomic_store_intptr(intptr_t *obj, intptr_t value)
{ __atomic_store_n(obj, value, 5); }

static inline void
_Py_atomic_store_uint8(uint8_t *obj, uint8_t value)
{ __atomic_store_n(obj, value, 5); }

static inline void
_Py_atomic_store_uint16(uint16_t *obj, uint16_t value)
{ __atomic_store_n(obj, value, 5); }

static inline void
_Py_atomic_store_uint32(uint32_t *obj, uint32_t value)
{ __atomic_store_n(obj, value, 5); }

static inline void
_Py_atomic_store_uint64(uint64_t *obj, uint64_t value)
{ __atomic_store_n(obj, value, 5); }

static inline void
_Py_atomic_store_uintptr(uintptr_t *obj, uintptr_t value)
{ __atomic_store_n(obj, value, 5); }

static inline void
_Py_atomic_store_uint(unsigned int *obj, unsigned int value)
{ __atomic_store_n(obj, value, 5); }

static inline void
_Py_atomic_store_ptr(void *obj, void *value)
{ __atomic_store_n((void **)obj, value, 5); }

static inline void
_Py_atomic_store_ssize(Py_ssize_t *obj, Py_ssize_t value)
{ __atomic_store_n(obj, value, 5); }

static inline void
_Py_atomic_store_int_relaxed(int *obj, int value)
{ __atomic_store_n(obj, value, 0); }

static inline void
_Py_atomic_store_int8_relaxed(int8_t *obj, int8_t value)
{ __atomic_store_n(obj, value, 0); }

static inline void
_Py_atomic_store_int16_relaxed(int16_t *obj, int16_t value)
{ __atomic_store_n(obj, value, 0); }

static inline void
_Py_atomic_store_int32_relaxed(int32_t *obj, int32_t value)
{ __atomic_store_n(obj, value, 0); }

static inline void
_Py_atomic_store_int64_relaxed(int64_t *obj, int64_t value)
{ __atomic_store_n(obj, value, 0); }

static inline void
_Py_atomic_store_intptr_relaxed(intptr_t *obj, intptr_t value)
{ __atomic_store_n(obj, value, 0); }

static inline void
_Py_atomic_store_uint8_relaxed(uint8_t *obj, uint8_t value)
{ __atomic_store_n(obj, value, 0); }

static inline void
_Py_atomic_store_uint16_relaxed(uint16_t *obj, uint16_t value)
{ __atomic_store_n(obj, value, 0); }

static inline void
_Py_atomic_store_uint32_relaxed(uint32_t *obj, uint32_t value)
{ __atomic_store_n(obj, value, 0); }

static inline void
_Py_atomic_store_uint64_relaxed(uint64_t *obj, uint64_t value)
{ __atomic_store_n(obj, value, 0); }

static inline void
_Py_atomic_store_uintptr_relaxed(uintptr_t *obj, uintptr_t value)
{ __atomic_store_n(obj, value, 0); }

static inline void
_Py_atomic_store_uint_relaxed(unsigned int *obj, unsigned int value)
{ __atomic_store_n(obj, value, 0); }

static inline void
_Py_atomic_store_ptr_relaxed(void *obj, void *value)
{ __atomic_store_n((void **)obj, value, 0); }

static inline void
_Py_atomic_store_ssize_relaxed(Py_ssize_t *obj, Py_ssize_t value)
{ __atomic_store_n(obj, value, 0); }

static inline void
_Py_atomic_store_ullong_relaxed(unsigned long long *obj,
                                unsigned long long value)
{ __atomic_store_n(obj, value, 0); }

static inline void
_Py_atomic_store_char_relaxed(char *obj, char value)
{ __atomic_store_n(obj, value, 0); }

static inline void
_Py_atomic_store_uchar_relaxed(unsigned char *obj, unsigned char value)
{ __atomic_store_n(obj, value, 0); }

static inline void
_Py_atomic_store_short_relaxed(short *obj, short value)
{ __atomic_store_n(obj, value, 0); }

static inline void
_Py_atomic_store_ushort_relaxed(unsigned short *obj, unsigned short value)
{ __atomic_store_n(obj, value, 0); }

static inline void
_Py_atomic_store_long_relaxed(long *obj, long value)
{ __atomic_store_n(obj, value, 0); }

static inline void
_Py_atomic_store_float_relaxed(float *obj, float value)
{ __atomic_store(obj, &value, 0); }

static inline void
_Py_atomic_store_double_relaxed(double *obj, double value)
{ __atomic_store(obj, &value, 0); }

static inline void
_Py_atomic_store_llong_relaxed(long long *obj, long long value)
{ __atomic_store_n(obj, value, 0); }

static inline void *
_Py_atomic_load_ptr_acquire(const void *obj)
{ return (void *)__atomic_load_n((void * const *)obj, 2); }

static inline uintptr_t
_Py_atomic_load_uintptr_acquire(const uintptr_t *obj)
{ return (uintptr_t)__atomic_load_n(obj, 2); }

static inline void
_Py_atomic_store_ptr_release(void *obj, void *value)
{ __atomic_store_n((void **)obj, value, 3); }

static inline void
_Py_atomic_store_uintptr_release(uintptr_t *obj, uintptr_t value)
{ __atomic_store_n(obj, value, 3); }

static inline void
_Py_atomic_store_int_release(int *obj, int value)
{ __atomic_store_n(obj, value, 3); }

static inline void
_Py_atomic_store_ssize_release(Py_ssize_t *obj, Py_ssize_t value)
{ __atomic_store_n(obj, value, 3); }

static inline int
_Py_atomic_load_int_acquire(const int *obj)
{ return __atomic_load_n(obj, 2); }

static inline void
_Py_atomic_store_uint32_release(uint32_t *obj, uint32_t value)
{ __atomic_store_n(obj, value, 3); }

static inline void
_Py_atomic_store_uint64_release(uint64_t *obj, uint64_t value)
{ __atomic_store_n(obj, value, 3); }

static inline uint64_t
_Py_atomic_load_uint64_acquire(const uint64_t *obj)
{ return __atomic_load_n(obj, 2); }

static inline uint32_t
_Py_atomic_load_uint32_acquire(const uint32_t *obj)
{ return __atomic_load_n(obj, 2); }

static inline Py_ssize_t
_Py_atomic_load_ssize_acquire(const Py_ssize_t *obj)
{ return __atomic_load_n(obj, 2); }

static inline void
_Py_atomic_fence_seq_cst(void)
{ __atomic_thread_fence(5); }
 static inline void
_Py_atomic_fence_acquire(void)
{ __atomic_thread_fence(2); }
 static inline void
_Py_atomic_fence_release(void)
{ __atomic_thread_fence(3); }
# 29 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/lock.h"
typedef struct PyMutex {
    uint8_t _bits;
} PyMutex;

__attribute__((dllimport)) void PyMutex_Lock(PyMutex *m);

__attribute__((dllimport)) void PyMutex_Unlock(PyMutex *m);

__attribute__((dllimport)) int PyMutex_IsLocked(PyMutex *m);

static inline void
_PyMutex_Lock(PyMutex *m)
{
    uint8_t expected = 0;
    if (!_Py_atomic_compare_exchange_uint8(&m->_bits, &expected, 1)) {
        PyMutex_Lock(m);
    }
}

static inline void
_PyMutex_Unlock(PyMutex *m)
{
    uint8_t expected = 1;
    if (!_Py_atomic_compare_exchange_uint8(&m->_bits, &expected, 0)) {
        PyMutex_Unlock(m);
    }
}

static inline int
_PyMutex_IsLocked(PyMutex *m)
{
    return (_Py_atomic_load_uint8(&m->_bits) & 1) != 0;
}
# 70 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/critical_section.h"
typedef struct PyCriticalSection PyCriticalSection;
typedef struct PyCriticalSection2 PyCriticalSection2;

__attribute__((dllimport)) void
PyCriticalSection_Begin(PyCriticalSection *c, PyObject *op);

__attribute__((dllimport)) void
PyCriticalSection_BeginMutex(PyCriticalSection *c, PyMutex *m);

__attribute__((dllimport)) void
PyCriticalSection_End(PyCriticalSection *c);

__attribute__((dllimport)) void
PyCriticalSection2_Begin(PyCriticalSection2 *c, PyObject *a, PyObject *b);

__attribute__((dllimport)) void
PyCriticalSection2_BeginMutex(PyCriticalSection2 *c, PyMutex *m1, PyMutex *m2);

__attribute__((dllimport)) void
PyCriticalSection2_End(PyCriticalSection2 *c);
# 110 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/object.h"
struct _object {
    union {
        int64_t ob_refcnt_full;
        struct {
            uint32_t ob_refcnt;
            uint16_t ob_overflow;
            uint16_t ob_flags;
        };
    };
    PyTypeObject *ob_type;
};
# 169 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/object.h"
typedef struct {
    PyObject ob_base;
    Py_ssize_t ob_size;
} PyVarObject;

__attribute__((dllimport)) int Py_Is(PyObject *x, PyObject *y);
# 262 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/object.h"
__attribute__((dllimport)) PyTypeObject* Py_TYPE(PyObject *ob);
    static inline PyTypeObject* _Py_TYPE(PyObject *ob)
    {
        return ob->ob_type;
    }

extern __attribute__((dllimport)) PyTypeObject PyLong_Type;
extern __attribute__((dllimport)) PyTypeObject PyBool_Type;

static inline Py_ssize_t Py_SIZE(PyObject *ob) {
    (void) ((!!(_Py_TYPE(((PyObject*)((ob)))) != &PyLong_Type)) || (_assert("Py_TYPE(ob) != &PyLong_Type","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/object.h",284),0));
    (void) ((!!(_Py_TYPE(((PyObject*)((ob)))) != &PyBool_Type)) || (_assert("Py_TYPE(ob) != &PyBool_Type","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/object.h",285),0));
    return ((PyVarObject*)((ob)))->ob_size;
}

static inline int Py_IS_TYPE(PyObject *ob, PyTypeObject *type) {
    return _Py_TYPE(((PyObject*)((ob)))) == type;
}

static inline void Py_SET_TYPE(PyObject *ob, PyTypeObject *type) {
    ob->ob_type = type;
}

static inline void Py_SET_SIZE(PyVarObject *ob, Py_ssize_t size) {
    (void) ((!!(_Py_TYPE(((PyObject*)((((PyObject*)((ob))))))) != &PyLong_Type)) || (_assert("Py_TYPE(_PyObject_CAST(ob)) != &PyLong_Type","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/object.h",308),0));
    (void) ((!!(_Py_TYPE(((PyObject*)((((PyObject*)((ob))))))) != &PyBool_Type)) || (_assert("Py_TYPE(_PyObject_CAST(ob)) != &PyBool_Type","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/object.h",309),0));
    ob->ob_size = size;
}
# 336 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/object.h"
typedef PyObject * (*unaryfunc)(PyObject *);
typedef PyObject * (*binaryfunc)(PyObject *, PyObject *);
typedef PyObject * (*ternaryfunc)(PyObject *, PyObject *, PyObject *);
typedef int (*inquiry)(PyObject *);
typedef Py_ssize_t (*lenfunc)(PyObject *);
typedef PyObject *(*ssizeargfunc)(PyObject *, Py_ssize_t);
typedef PyObject *(*ssizessizeargfunc)(PyObject *, Py_ssize_t, Py_ssize_t);
typedef int(*ssizeobjargproc)(PyObject *, Py_ssize_t, PyObject *);
typedef int(*ssizessizeobjargproc)(PyObject *, Py_ssize_t, Py_ssize_t, PyObject *);
typedef int(*objobjargproc)(PyObject *, PyObject *, PyObject *);

typedef int (*objobjproc)(PyObject *, PyObject *);
typedef int (*visitproc)(PyObject *, void *);
typedef int (*traverseproc)(PyObject *, visitproc, void *);

typedef void (*freefunc)(void *);
typedef void (*destructor)(PyObject *);
typedef PyObject *(*getattrfunc)(PyObject *, char *);
typedef PyObject *(*getattrofunc)(PyObject *, PyObject *);
typedef int (*setattrfunc)(PyObject *, char *, PyObject *);
typedef int (*setattrofunc)(PyObject *, PyObject *, PyObject *);
typedef PyObject *(*reprfunc)(PyObject *);
typedef Py_hash_t (*hashfunc)(PyObject *);
typedef PyObject *(*richcmpfunc) (PyObject *, PyObject *, int);
typedef PyObject *(*getiterfunc) (PyObject *);
typedef PyObject *(*iternextfunc) (PyObject *);
typedef PyObject *(*descrgetfunc) (PyObject *, PyObject *, PyObject *);
typedef int (*descrsetfunc) (PyObject *, PyObject *, PyObject *);
typedef int (*initproc)(PyObject *, PyObject *, PyObject *);
typedef PyObject *(*newfunc)(PyTypeObject *, PyObject *, PyObject *);
typedef PyObject *(*allocfunc)(PyTypeObject *, Py_ssize_t);

typedef PyObject *(*vectorcallfunc)(PyObject *callable, PyObject *const *args,
                                    size_t nargsf, PyObject *kwnames);

typedef struct{
    int slot;
    void *pfunc;
} PyType_Slot;

typedef struct{
    const char* name;
    int basicsize;
    int itemsize;
    unsigned int flags;
    PyType_Slot *slots;
} PyType_Spec;

__attribute__((dllimport)) PyObject* PyType_FromSpec(PyType_Spec*);

__attribute__((dllimport)) PyObject* PyType_FromSpecWithBases(PyType_Spec*, PyObject*);

__attribute__((dllimport)) void* PyType_GetSlot(PyTypeObject*, int);

__attribute__((dllimport)) PyObject* PyType_FromModuleAndSpec(PyObject *, PyType_Spec *, PyObject *);
__attribute__((dllimport)) PyObject * PyType_GetModule(PyTypeObject *);
__attribute__((dllimport)) void * PyType_GetModuleState(PyTypeObject *);

__attribute__((dllimport)) PyObject * PyType_GetName(PyTypeObject *);
__attribute__((dllimport)) PyObject * PyType_GetQualName(PyTypeObject *);

__attribute__((dllimport)) PyObject * PyType_GetFullyQualifiedName(PyTypeObject *type);
__attribute__((dllimport)) PyObject * PyType_GetModuleName(PyTypeObject *type);

__attribute__((dllimport)) PyObject * PyType_FromMetaclass(PyTypeObject*, PyObject*, PyType_Spec*, PyObject*);
__attribute__((dllimport)) void * PyObject_GetTypeData(PyObject *obj, PyTypeObject *cls);
__attribute__((dllimport)) Py_ssize_t PyType_GetTypeDataSize(PyTypeObject *cls);

__attribute__((dllimport)) int PyType_GetBaseByToken(PyTypeObject *, void *, PyTypeObject **);

__attribute__((dllimport)) int PyType_IsSubtype(PyTypeObject *, PyTypeObject *);

static inline int PyObject_TypeCheck(PyObject *ob, PyTypeObject *type) {
    return Py_IS_TYPE(((PyObject*)((ob))), (type)) || PyType_IsSubtype(_Py_TYPE(((PyObject*)((ob)))), type);
}

extern __attribute__((dllimport)) PyTypeObject PyType_Type;
extern __attribute__((dllimport)) PyTypeObject PyBaseObject_Type;
extern __attribute__((dllimport)) PyTypeObject PySuper_Type;

__attribute__((dllimport)) unsigned long PyType_GetFlags(PyTypeObject*);

__attribute__((dllimport)) int PyType_Ready(PyTypeObject *);
__attribute__((dllimport)) PyObject * PyType_GenericAlloc(PyTypeObject *, Py_ssize_t);
__attribute__((dllimport)) PyObject * PyType_GenericNew(PyTypeObject *,
                                               PyObject *, PyObject *);
__attribute__((dllimport)) unsigned int PyType_ClearCache(void);
__attribute__((dllimport)) void PyType_Modified(PyTypeObject *);

__attribute__((dllimport)) PyObject * PyObject_Repr(PyObject *);
__attribute__((dllimport)) PyObject * PyObject_Str(PyObject *);
__attribute__((dllimport)) PyObject * PyObject_ASCII(PyObject *);
__attribute__((dllimport)) PyObject * PyObject_Bytes(PyObject *);
__attribute__((dllimport)) PyObject * PyObject_RichCompare(PyObject *, PyObject *, int);
__attribute__((dllimport)) int PyObject_RichCompareBool(PyObject *, PyObject *, int);
__attribute__((dllimport)) PyObject * PyObject_GetAttrString(PyObject *, const char *);
__attribute__((dllimport)) int PyObject_SetAttrString(PyObject *, const char *, PyObject *);
__attribute__((dllimport)) int PyObject_DelAttrString(PyObject *v, const char *name);
__attribute__((dllimport)) int PyObject_HasAttrString(PyObject *, const char *);
__attribute__((dllimport)) PyObject * PyObject_GetAttr(PyObject *, PyObject *);

__attribute__((dllimport)) int PyObject_GetOptionalAttr(PyObject *, PyObject *, PyObject **);
__attribute__((dllimport)) int PyObject_GetOptionalAttrString(PyObject *, const char *, PyObject **);

__attribute__((dllimport)) int PyObject_SetAttr(PyObject *, PyObject *, PyObject *);
__attribute__((dllimport)) int PyObject_DelAttr(PyObject *v, PyObject *name);
__attribute__((dllimport)) int PyObject_HasAttr(PyObject *, PyObject *);

__attribute__((dllimport)) int PyObject_HasAttrWithError(PyObject *, PyObject *);
__attribute__((dllimport)) int PyObject_HasAttrStringWithError(PyObject *, const char *);

__attribute__((dllimport)) PyObject * PyObject_SelfIter(PyObject *);
__attribute__((dllimport)) PyObject * PyObject_GenericGetAttr(PyObject *, PyObject *);
__attribute__((dllimport)) int PyObject_GenericSetAttr(PyObject *, PyObject *, PyObject *);

__attribute__((dllimport)) int PyObject_GenericSetDict(PyObject *, PyObject *, void *);

__attribute__((dllimport)) Py_hash_t PyObject_Hash(PyObject *);
__attribute__((dllimport)) Py_hash_t PyObject_HashNotImplemented(PyObject *);
__attribute__((dllimport)) int PyObject_IsTrue(PyObject *);
__attribute__((dllimport)) int PyObject_Not(PyObject *);
__attribute__((dllimport)) int PyCallable_Check(PyObject *);
__attribute__((dllimport)) void PyObject_ClearWeakRefs(PyObject *);

__attribute__((dllimport)) PyObject * PyObject_Dir(PyObject *);

__attribute__((dllimport)) int Py_ReprEnter(PyObject *);
__attribute__((dllimport)) void Py_ReprLeave(PyObject *);
# 636 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/object.h"
__attribute__((dllimport)) PyObject* Py_GetConstant(unsigned int constant_id);
__attribute__((dllimport)) PyObject* Py_GetConstantBorrowed(unsigned int constant_id);

extern __attribute__((dllimport)) PyObject _Py_NoneStruct;
# 654 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/object.h"
__attribute__((dllimport)) int Py_IsNone(PyObject *x);
# 669 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/object.h"
extern __attribute__((dllimport)) PyObject _Py_NotImplementedStruct;
# 695 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/object.h"
typedef enum {
    PYGEN_RETURN = 0,
    PYGEN_ERROR = -1,
    PYGEN_NEXT = 1
} PySendResult;

__attribute__((dllimport)) void _Py_NewReference(PyObject *op);
__attribute__((dllimport)) void _Py_NewReferenceNoTotal(PyObject *op);
__attribute__((dllimport)) void _Py_ResurrectReference(PyObject *op);
__attribute__((dllimport)) void _Py_ForgetReference(PyObject *op);
# 39 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/object.h"
typedef struct _Py_Identifier {
    const char* string;
    Py_ssize_t index;
    struct {
        uint8_t v;
    } mutex;
} _Py_Identifier;
# 61 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/object.h"
typedef struct {
    binaryfunc nb_add;
    binaryfunc nb_subtract;
    binaryfunc nb_multiply;
    binaryfunc nb_remainder;
    binaryfunc nb_divmod;
    ternaryfunc nb_power;
    unaryfunc nb_negative;
    unaryfunc nb_positive;
    unaryfunc nb_absolute;
    inquiry nb_bool;
    unaryfunc nb_invert;
    binaryfunc nb_lshift;
    binaryfunc nb_rshift;
    binaryfunc nb_and;
    binaryfunc nb_xor;
    binaryfunc nb_or;
    unaryfunc nb_int;
    void *nb_reserved;
    unaryfunc nb_float;
    binaryfunc nb_inplace_add;
    binaryfunc nb_inplace_subtract;
    binaryfunc nb_inplace_multiply;
    binaryfunc nb_inplace_remainder;
    ternaryfunc nb_inplace_power;
    binaryfunc nb_inplace_lshift;
    binaryfunc nb_inplace_rshift;
    binaryfunc nb_inplace_and;
    binaryfunc nb_inplace_xor;
    binaryfunc nb_inplace_or;
    binaryfunc nb_floor_divide;
    binaryfunc nb_true_divide;
    binaryfunc nb_inplace_floor_divide;
    binaryfunc nb_inplace_true_divide;
    unaryfunc nb_index;
    binaryfunc nb_matrix_multiply;
    binaryfunc nb_inplace_matrix_multiply;
} PyNumberMethods;

typedef struct {
    lenfunc sq_length;
    binaryfunc sq_concat;
    ssizeargfunc sq_repeat;
    ssizeargfunc sq_item;
    void *was_sq_slice;
    ssizeobjargproc sq_ass_item;
    void *was_sq_ass_slice;
    objobjproc sq_contains;
    binaryfunc sq_inplace_concat;
    ssizeargfunc sq_inplace_repeat;
} PySequenceMethods;

typedef struct {
    lenfunc mp_length;
    binaryfunc mp_subscript;
    objobjargproc mp_ass_subscript;
} PyMappingMethods;

typedef PySendResult (*sendfunc)(PyObject *iter, PyObject *value, PyObject **result);

typedef struct {
    unaryfunc am_await;
    unaryfunc am_aiter;
    unaryfunc am_anext;
    sendfunc am_send;
} PyAsyncMethods;

typedef struct {
     getbufferproc bf_getbuffer;
     releasebufferproc bf_releasebuffer;
} PyBufferProcs;

typedef Py_ssize_t printfunc;

struct _typeobject {
    PyVarObject ob_base;
    const char *tp_name;
    Py_ssize_t tp_basicsize, tp_itemsize;
    destructor tp_dealloc;
    Py_ssize_t tp_vectorcall_offset;
    getattrfunc tp_getattr;
    setattrfunc tp_setattr;
    PyAsyncMethods *tp_as_async;
    reprfunc tp_repr;
    PyNumberMethods *tp_as_number;
    PySequenceMethods *tp_as_sequence;
    PyMappingMethods *tp_as_mapping;
    hashfunc tp_hash;
    ternaryfunc tp_call;
    reprfunc tp_str;
    getattrofunc tp_getattro;
    setattrofunc tp_setattro;
    PyBufferProcs *tp_as_buffer;
    unsigned long tp_flags;
    const char *tp_doc;
    traverseproc tp_traverse;
    inquiry tp_clear;
    richcmpfunc tp_richcompare;
    Py_ssize_t tp_weaklistoffset;
    getiterfunc tp_iter;
    iternextfunc tp_iternext;
    PyMethodDef *tp_methods;
    PyMemberDef *tp_members;
    PyGetSetDef *tp_getset;
    PyTypeObject *tp_base;
    PyObject *tp_dict;
    descrgetfunc tp_descr_get;
    descrsetfunc tp_descr_set;
    Py_ssize_t tp_dictoffset;
    initproc tp_init;
    allocfunc tp_alloc;
    newfunc tp_new;
    freefunc tp_free;
    inquiry tp_is_gc;
    PyObject *tp_bases;
    PyObject *tp_mro;
    PyObject *tp_cache;
    void *tp_subclasses;
    PyObject *tp_weaklist;
    destructor tp_del;
    unsigned int tp_version_tag;
    destructor tp_finalize;
    vectorcallfunc tp_vectorcall;
    unsigned char tp_watched;
    uint16_t tp_versions_used;
};

struct _specialization_cache {
    PyObject *getitem;
    uint32_t getitem_version;
    PyObject *init;
};

typedef struct _heaptypeobject {
    PyTypeObject ht_type;
    PyAsyncMethods as_async;
    PyNumberMethods as_number;
    PyMappingMethods as_mapping;
    PySequenceMethods as_sequence;
    PyBufferProcs as_buffer;
    PyObject *ht_name, *ht_slots, *ht_qualname;
    struct _dictkeysobject *ht_cached_keys;
    PyObject *ht_module;
    char *_ht_tpname;
    void *ht_token;
    struct _specialization_cache _spec_cache;
} PyHeapTypeObject;

__attribute__((dllimport)) const char * _PyType_Name(PyTypeObject *);
__attribute__((dllimport)) PyObject * _PyType_Lookup(PyTypeObject *, PyObject *);
__attribute__((dllimport)) PyObject * _PyType_LookupRef(PyTypeObject *, PyObject *);
__attribute__((dllimport)) PyObject * PyType_GetDict(PyTypeObject *);

__attribute__((dllimport)) int PyObject_Print(PyObject *, FILE *, int);
__attribute__((dllimport)) void _Py_BreakPoint(void);
__attribute__((dllimport)) void _PyObject_Dump(PyObject *);

__attribute__((dllimport)) PyObject* _PyObject_GetAttrId(PyObject *, _Py_Identifier *);

__attribute__((dllimport)) PyObject ** _PyObject_GetDictPtr(PyObject *);
__attribute__((dllimport)) void PyObject_CallFinalizer(PyObject *);
__attribute__((dllimport)) int PyObject_CallFinalizerFromDealloc(PyObject *);

__attribute__((dllimport)) void PyUnstable_Object_ClearWeakRefsNoCallbacks(PyObject *);

__attribute__((dllimport)) PyObject *
_PyObject_GenericGetAttrWithDict(PyObject *, PyObject *, PyObject *, int);
__attribute__((dllimport)) int
_PyObject_GenericSetAttrWithDict(PyObject *, PyObject *,
                                 PyObject *, PyObject *);

__attribute__((dllimport)) PyObject * _PyObject_FunctionStr(PyObject *);
# 423 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/object.h"
__attribute__((dllimport)) void __attribute__((__noreturn__)) _PyObject_AssertFailed(
    PyObject *obj,
    const char *expr,
    const char *msg,
    const char *file,
    int line,
    const char *function);

__attribute__((dllimport)) void _PyTrash_thread_deposit_object(PyThreadState *tstate, PyObject *op);
__attribute__((dllimport)) void _PyTrash_thread_destroy_chain(PyThreadState *tstate);

__attribute__((dllimport)) int _Py_ReachedRecursionLimitWithMargin(PyThreadState *tstate, int margin_count);

__attribute__((dllimport)) void * PyObject_GetItemData(PyObject *obj);

__attribute__((dllimport)) int PyObject_VisitManagedDict(PyObject *obj, visitproc visit, void *arg);
__attribute__((dllimport)) int _PyObject_SetManagedDict(PyObject *obj, PyObject *new_dict);
__attribute__((dllimport)) void PyObject_ClearManagedDict(PyObject *obj);

typedef int(*PyType_WatchCallback)(PyTypeObject *);
__attribute__((dllimport)) int PyType_AddWatcher(PyType_WatchCallback callback);
__attribute__((dllimport)) int PyType_ClearWatcher(int watcher_id);
__attribute__((dllimport)) int PyType_Watch(int watcher_id, PyObject *type);
__attribute__((dllimport)) int PyType_Unwatch(int watcher_id, PyObject *type);

__attribute__((dllimport)) int PyUnstable_Type_AssignVersionTag(PyTypeObject *type);

typedef enum {
    PyRefTracer_CREATE = 0,
    PyRefTracer_DESTROY = 1,
} PyRefTracerEvent;

typedef int (*PyRefTracer)(PyObject *, PyRefTracerEvent event, void *);
__attribute__((dllimport)) int PyRefTracer_SetTracer(PyRefTracer tracer, void *data);
__attribute__((dllimport)) PyRefTracer PyRefTracer_GetTracer(void**);

__attribute__((dllimport)) int PyUnstable_Object_EnableDeferredRefcount(PyObject *);

__attribute__((dllimport)) int PyUnstable_Object_IsUniqueReferencedTemporary(PyObject *);

__attribute__((dllimport)) int PyUnstable_IsImmortal(PyObject *);

__attribute__((dllimport)) int PyUnstable_TryIncRef(PyObject *);
__attribute__((dllimport)) void PyUnstable_EnableTryIncRef(PyObject *);

__attribute__((dllimport)) int PyUnstable_Object_IsUniquelyReferenced(PyObject *);

static inline int
PyType_HasFeature(PyTypeObject *type, unsigned long feature)
{
    unsigned long flags;
        flags = type->tp_flags;
    return ((flags & feature) != 0);
}

static inline int PyType_Check(PyObject *op) {
    return PyType_HasFeature((_Py_TYPE(((PyObject*)((op))))), ((1UL << 31)));
}

static inline int PyType_CheckExact(PyObject *op) {
    return Py_IS_TYPE(((PyObject*)((op))), (&PyType_Type));
}

__attribute__((dllimport)) PyObject * PyType_GetModuleByDef(PyTypeObject *, PyModuleDef *);

__attribute__((dllimport)) int PyType_Freeze(PyTypeObject *type);
# 99 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/refcount.h"
__attribute__((dllimport)) Py_ssize_t Py_REFCNT(PyObject *ob);
    static inline Py_ssize_t _Py_REFCNT(PyObject *ob) {
        return ob->ob_refcnt;
    }

static inline __attribute__((always_inline)) int _Py_IsImmortal(PyObject *op)
{
    return ((int32_t)(op->ob_refcnt)) < 0;
}

static inline __attribute__((always_inline)) int _Py_IsStaticImmortal(PyObject *op)
{
    return (op->ob_flags & 4) != 0;
}

__attribute__((dllimport)) void _Py_SetRefcnt(PyObject *ob, Py_ssize_t refcnt);

static inline void Py_SET_REFCNT(PyObject *ob, Py_ssize_t refcnt) {
    (void) ((!!(refcnt >= 0)) || (_assert("refcnt >= 0","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/refcount.h",153),0));
    if (_Py_IsImmortal(((PyObject*)((ob))))) {
        return;
    }
    ob->ob_refcnt = (uint32_t)refcnt;
}
# 237 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/refcount.h"
__attribute__((dllimport)) void _Py_Dealloc(PyObject *);

__attribute__((dllimport)) void Py_IncRef(PyObject *);
__attribute__((dllimport)) void Py_DecRef(PyObject *);

__attribute__((dllimport)) void _Py_IncRef(PyObject *);
__attribute__((dllimport)) void _Py_DecRef(PyObject *);

static inline __attribute__((always_inline)) void Py_INCREF(PyObject *op)
{
    uint32_t cur_refcnt = op->ob_refcnt;
    if (cur_refcnt >= (3ULL << 30)) {
        ((void)0);
        return;
    }
    op->ob_refcnt = cur_refcnt + 1;
    ((void)0);
}
# 411 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/refcount.h"
static inline __attribute__((always_inline)) void Py_DECREF(PyObject *op)
{
    if (_Py_IsImmortal(((PyObject*)((op))))) {
        ((void)0);
        return;
    }
    ((void)0);
    if (--op->ob_refcnt == 0) {
        _Py_Dealloc(op);
    }
}
# 501 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/refcount.h"
static inline void Py_XINCREF(PyObject *op)
{
    if (op != ((void *)0)) {
        Py_INCREF(((PyObject*)((op))));
    }
}

static inline void Py_XDECREF(PyObject *op)
{
    if (op != ((void *)0)) {
        Py_DECREF(((PyObject*)((op))));
    }
}

__attribute__((dllimport)) PyObject* Py_NewRef(PyObject *obj);

__attribute__((dllimport)) PyObject* Py_XNewRef(PyObject *obj);

static inline PyObject* _Py_NewRef(PyObject *obj)
{
    Py_INCREF(((PyObject*)((obj))));
    return obj;
}

static inline PyObject* _Py_XNewRef(PyObject *obj)
{
    Py_XINCREF(((PyObject*)((obj))));
    return obj;
}
# 93 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/objimpl.h"
__attribute__((dllimport)) void * PyObject_Malloc(size_t size);

__attribute__((dllimport)) void * PyObject_Calloc(size_t nelem, size_t elsize);

__attribute__((dllimport)) void * PyObject_Realloc(void *ptr, size_t new_size);
__attribute__((dllimport)) void PyObject_Free(void *ptr);
# 117 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/objimpl.h"
__attribute__((dllimport)) PyObject * PyObject_Init(PyObject *, PyTypeObject *);
__attribute__((dllimport)) PyVarObject * PyObject_InitVar(PyVarObject *,
                                           PyTypeObject *, Py_ssize_t);

__attribute__((dllimport)) PyObject * _PyObject_New(PyTypeObject *);
__attribute__((dllimport)) PyVarObject * _PyObject_NewVar(PyTypeObject *, Py_ssize_t);
# 150 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/objimpl.h"
__attribute__((dllimport)) Py_ssize_t PyGC_Collect(void);

__attribute__((dllimport)) int PyGC_Enable(void);
__attribute__((dllimport)) int PyGC_Disable(void);
__attribute__((dllimport)) int PyGC_IsEnabled(void);

__attribute__((dllimport)) PyVarObject * _PyObject_GC_Resize(PyVarObject *, Py_ssize_t);

__attribute__((dllimport)) PyObject * _PyObject_GC_New(PyTypeObject *);
__attribute__((dllimport)) PyVarObject * _PyObject_GC_NewVar(PyTypeObject *, Py_ssize_t);

__attribute__((dllimport)) void PyObject_GC_Track(void *);

__attribute__((dllimport)) void PyObject_GC_UnTrack(void *);

__attribute__((dllimport)) void PyObject_GC_Del(void *);

__attribute__((dllimport)) int PyObject_GC_IsTracked(PyObject *);
__attribute__((dllimport)) int PyObject_GC_IsFinalized(PyObject *);

static inline size_t _PyObject_SIZE(PyTypeObject *type) {
    return ((size_t)(type->tp_basicsize));
}
# 23 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/objimpl.h"
static inline size_t _PyObject_VAR_SIZE(PyTypeObject *type, Py_ssize_t nitems) {
    size_t size = ((size_t)(type->tp_basicsize));
    size += ((size_t)(nitems)) * ((size_t)(type->tp_itemsize));
    return (((size_t)(size) + (size_t)((8) - 1)) & ~(size_t)((8) - 1));
}
# 59 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/objimpl.h"
typedef struct {
    void *ctx;
    void* (*alloc) (void *ctx, size_t size);
    void (*free) (void *ctx, void *ptr, size_t size);
} PyObjectArenaAllocator;

__attribute__((dllimport)) void PyObject_GetArenaAllocator(PyObjectArenaAllocator *allocator);

__attribute__((dllimport)) void PyObject_SetArenaAllocator(PyObjectArenaAllocator *allocator);

__attribute__((dllimport)) int PyObject_IS_GC(PyObject *obj);

__attribute__((dllimport)) int PyType_SUPPORTS_WEAKREFS(PyTypeObject *type);

__attribute__((dllimport)) PyObject ** PyObject_GET_WEAKREFS_LISTPTR(PyObject *op);

__attribute__((dllimport)) PyObject * PyUnstable_Object_GC_NewWithExtraData(PyTypeObject *,
                                                             size_t);
# 103 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/objimpl.h"
typedef int (*gcvisitobjects_t)(PyObject*, void*);
__attribute__((dllimport)) void PyUnstable_GC_VisitObjects(gcvisitobjects_t callback, void* arg);
# 30 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/pyhash.h"
__attribute__((dllimport)) Py_hash_t _Py_HashDouble(PyObject *, double);

typedef struct {
    Py_hash_t (*const hash)(const void *, Py_ssize_t);
    const char *name;
    const int hash_bits;
    const int seed_bits;
} PyHash_FuncDef;

__attribute__((dllimport)) PyHash_FuncDef* PyHash_GetFuncDef(void);

__attribute__((dllimport)) Py_hash_t Py_HashPointer(const void *ptr);

__attribute__((__deprecated__)) static inline Py_hash_t
_Py_HashPointer(const void *ptr)
{
    return Py_HashPointer(ptr);
}

__attribute__((dllimport)) Py_hash_t PyObject_GenericHash(PyObject *);

__attribute__((dllimport)) Py_hash_t Py_HashBuffer(const void *ptr, Py_ssize_t len);

__attribute__((__deprecated__)) extern __attribute__((dllimport)) int Py_DebugFlag;
__attribute__((__deprecated__)) extern __attribute__((dllimport)) int Py_VerboseFlag;
__attribute__((__deprecated__)) extern __attribute__((dllimport)) int Py_QuietFlag;
__attribute__((__deprecated__)) extern __attribute__((dllimport)) int Py_InteractiveFlag;
__attribute__((__deprecated__)) extern __attribute__((dllimport)) int Py_InspectFlag;
__attribute__((__deprecated__)) extern __attribute__((dllimport)) int Py_OptimizeFlag;
__attribute__((__deprecated__)) extern __attribute__((dllimport)) int Py_NoSiteFlag;
__attribute__((__deprecated__)) extern __attribute__((dllimport)) int Py_BytesWarningFlag;
__attribute__((__deprecated__)) extern __attribute__((dllimport)) int Py_FrozenFlag;
__attribute__((__deprecated__)) extern __attribute__((dllimport)) int Py_IgnoreEnvironmentFlag;
__attribute__((__deprecated__)) extern __attribute__((dllimport)) int Py_DontWriteBytecodeFlag;
__attribute__((__deprecated__)) extern __attribute__((dllimport)) int Py_NoUserSiteDirectory;
__attribute__((__deprecated__)) extern __attribute__((dllimport)) int Py_UnbufferedStdioFlag;
__attribute__((__deprecated__)) extern __attribute__((dllimport)) int Py_HashRandomizationFlag;
__attribute__((__deprecated__)) extern __attribute__((dllimport)) int Py_IsolatedFlag;

__attribute__((__deprecated__)) extern __attribute__((dllimport)) int Py_LegacyWindowsFSEncodingFlag;
__attribute__((__deprecated__)) extern __attribute__((dllimport)) int Py_LegacyWindowsStdioFlag;

__attribute__((dllimport)) char* Py_GETENV(const char *name);
# 20 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/bytearrayobject.h"
extern __attribute__((dllimport)) PyTypeObject PyByteArray_Type;
extern __attribute__((dllimport)) PyTypeObject PyByteArrayIter_Type;

__attribute__((dllimport)) PyObject * PyByteArray_FromObject(PyObject *);
__attribute__((dllimport)) PyObject * PyByteArray_Concat(PyObject *, PyObject *);
__attribute__((dllimport)) PyObject * PyByteArray_FromStringAndSize(const char *, Py_ssize_t);
__attribute__((dllimport)) Py_ssize_t PyByteArray_Size(PyObject *);
__attribute__((dllimport)) char * PyByteArray_AsString(PyObject *);
__attribute__((dllimport)) int PyByteArray_Resize(PyObject *, Py_ssize_t);

typedef struct {
    PyVarObject ob_base;
    Py_ssize_t ob_alloc;
    char *ob_bytes;
    char *ob_start;
    Py_ssize_t ob_exports;
} PyByteArrayObject;

extern __attribute__((dllimport)) char _PyByteArray_empty_string[];

static inline char* PyByteArray_AS_STRING(PyObject *op)
{
    PyByteArrayObject *self = ((void) ((!!(PyObject_TypeCheck(((PyObject*)(((op)))), (&PyByteArray_Type)))) || (_assert("PyByteArray_Check(op)","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/bytearrayobject.h",22),0)), ((PyByteArrayObject*)(op)));
    if (Py_SIZE(((PyObject*)((self))))) {
        return self->ob_start;
    }
    return _PyByteArray_empty_string;
}

static inline Py_ssize_t PyByteArray_GET_SIZE(PyObject *op) {
    PyByteArrayObject *self = ((void) ((!!(PyObject_TypeCheck(((PyObject*)(((op)))), (&PyByteArray_Type)))) || (_assert("PyByteArray_Check(op)","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/bytearrayobject.h",31),0)), ((PyByteArrayObject*)(op)));
    return Py_SIZE(((PyObject*)((self))));
}
# 24 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/bytesobject.h"
extern __attribute__((dllimport)) PyTypeObject PyBytes_Type;
extern __attribute__((dllimport)) PyTypeObject PyBytesIter_Type;

__attribute__((dllimport)) PyObject * PyBytes_FromStringAndSize(const char *, Py_ssize_t);
__attribute__((dllimport)) PyObject * PyBytes_FromString(const char *);
__attribute__((dllimport)) PyObject * PyBytes_FromObject(PyObject *);
__attribute__((dllimport)) PyObject * PyBytes_FromFormatV(const char*, va_list)
                                __attribute__((format(printf, 1, 0)));
__attribute__((dllimport)) PyObject * PyBytes_FromFormat(const char*, ...)
                                __attribute__((format(printf, 1, 2)));
__attribute__((dllimport)) Py_ssize_t PyBytes_Size(PyObject *);
__attribute__((dllimport)) char * PyBytes_AsString(PyObject *);
__attribute__((dllimport)) PyObject * PyBytes_Repr(PyObject *, int);
__attribute__((dllimport)) void PyBytes_Concat(PyObject **, PyObject *);
__attribute__((dllimport)) void PyBytes_ConcatAndDel(PyObject **, PyObject *);
__attribute__((dllimport)) PyObject * PyBytes_DecodeEscape(const char *, Py_ssize_t,
                                            const char *, Py_ssize_t,
                                            const char *);

__attribute__((dllimport)) int PyBytes_AsStringAndSize(
    PyObject *obj,
    char **s,
    Py_ssize_t *len
    );

typedef struct {
    PyVarObject ob_base;
    __attribute__((__deprecated__)) Py_hash_t ob_shash;
    char ob_sval[1];
} PyBytesObject;

__attribute__((dllimport)) int _PyBytes_Resize(PyObject **, Py_ssize_t);

static inline char* PyBytes_AS_STRING(PyObject *op)
{
    return ((void) ((!!(PyType_HasFeature((_Py_TYPE(((PyObject*)((op))))), ((1UL << 27))))) || (_assert("PyBytes_Check(op)","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/bytesobject.h",25),0)), ((PyBytesObject*)(op)))->ob_sval;
}

static inline Py_ssize_t PyBytes_GET_SIZE(PyObject *op) {
    PyBytesObject *self = ((void) ((!!(PyType_HasFeature((_Py_TYPE(((PyObject*)((op))))), ((1UL << 27))))) || (_assert("PyBytes_Check(op)","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/bytesobject.h",30),0)), ((PyBytesObject*)(op)));
    return Py_SIZE(((PyObject*)((self))));
}

__attribute__((dllimport)) PyObject* PyBytes_Join(PyObject *sep, PyObject *iterable);

__attribute__((__deprecated__)) static inline PyObject*
_PyBytes_Join(PyObject *sep, PyObject *iterable)
{
    return PyBytes_Join(sep, iterable);
}
# 94 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/unicodeobject.h"
typedef uint32_t Py_UCS4;
typedef uint16_t Py_UCS2;
typedef uint8_t Py_UCS1;

extern __attribute__((dllimport)) PyTypeObject PyUnicode_Type;
extern __attribute__((dllimport)) PyTypeObject PyUnicodeIter_Type;
# 122 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/unicodeobject.h"
__attribute__((dllimport)) PyObject* PyUnicode_FromStringAndSize(
    const char *u,
    Py_ssize_t size
    );

__attribute__((dllimport)) PyObject* PyUnicode_FromString(
    const char *u
    );

__attribute__((dllimport)) PyObject* PyUnicode_Substring(
    PyObject *str,
    Py_ssize_t start,
    Py_ssize_t end);
# 146 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/unicodeobject.h"
__attribute__((dllimport)) Py_UCS4* PyUnicode_AsUCS4(
    PyObject *unicode,
    Py_UCS4* buffer,
    Py_ssize_t buflen,
    int copy_null);

__attribute__((dllimport)) Py_UCS4* PyUnicode_AsUCS4Copy(PyObject *unicode);

__attribute__((dllimport)) Py_ssize_t PyUnicode_GetLength(
    PyObject *unicode
);

__attribute__((dllimport)) Py_UCS4 PyUnicode_ReadChar(
    PyObject *unicode,
    Py_ssize_t index
    );

__attribute__((dllimport)) int PyUnicode_WriteChar(
    PyObject *unicode,
    Py_ssize_t index,
    Py_UCS4 character
    );
# 200 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/unicodeobject.h"
__attribute__((dllimport)) int PyUnicode_Resize(
    PyObject **unicode,
    Py_ssize_t length
    );
# 218 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/unicodeobject.h"
__attribute__((dllimport)) PyObject* PyUnicode_FromEncodedObject(
    PyObject *obj,
    const char *encoding,
    const char *errors
    );
# 233 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/unicodeobject.h"
__attribute__((dllimport)) PyObject* PyUnicode_FromObject(
    PyObject *obj
    );

__attribute__((dllimport)) PyObject * PyUnicode_FromFormatV(
    const char *format,
    va_list vargs
    );
__attribute__((dllimport)) PyObject * PyUnicode_FromFormat(
    const char *format,
    ...
    );

__attribute__((dllimport)) void PyUnicode_InternInPlace(PyObject **);
__attribute__((dllimport)) PyObject * PyUnicode_InternFromString(
    const char *u
    );
# 260 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/unicodeobject.h"
__attribute__((dllimport)) PyObject* PyUnicode_FromWideChar(
    const wchar_t *w,
    Py_ssize_t size
    );
# 277 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/unicodeobject.h"
__attribute__((dllimport)) Py_ssize_t PyUnicode_AsWideChar(
    PyObject *unicode,
    wchar_t *w,
    Py_ssize_t size
    );
# 291 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/unicodeobject.h"
__attribute__((dllimport)) wchar_t* PyUnicode_AsWideCharString(
    PyObject *unicode,
    Py_ssize_t *size
    );
# 307 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/unicodeobject.h"
__attribute__((dllimport)) PyObject* PyUnicode_FromOrdinal(int ordinal);
# 330 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/unicodeobject.h"
__attribute__((dllimport)) const char* PyUnicode_GetDefaultEncoding(void);

__attribute__((dllimport)) PyObject* PyUnicode_Decode(
    const char *s,
    Py_ssize_t size,
    const char *encoding,
    const char *errors
    );
# 352 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/unicodeobject.h"
__attribute__((__deprecated__)) __attribute__((dllimport)) PyObject* PyUnicode_AsDecodedObject(
    PyObject *unicode,
    const char *encoding,
    const char *errors
    );
# 366 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/unicodeobject.h"
__attribute__((__deprecated__)) __attribute__((dllimport)) PyObject* PyUnicode_AsDecodedUnicode(
    PyObject *unicode,
    const char *encoding,
    const char *errors
    );
# 381 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/unicodeobject.h"
__attribute__((__deprecated__)) __attribute__((dllimport)) PyObject* PyUnicode_AsEncodedObject(
    PyObject *unicode,
    const char *encoding,
    const char *errors
    );

__attribute__((dllimport)) PyObject* PyUnicode_AsEncodedString(
    PyObject *unicode,
    const char *encoding,
    const char *errors
    );
# 404 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/unicodeobject.h"
__attribute__((__deprecated__)) __attribute__((dllimport)) PyObject* PyUnicode_AsEncodedUnicode(
    PyObject *unicode,
    const char *encoding,
    const char *errors
    );

__attribute__((dllimport)) PyObject* PyUnicode_BuildEncodingMap(
    PyObject* string
   );

__attribute__((dllimport)) PyObject* PyUnicode_DecodeUTF7(
    const char *string,
    Py_ssize_t length,
    const char *errors
    );

__attribute__((dllimport)) PyObject* PyUnicode_DecodeUTF7Stateful(
    const char *string,
    Py_ssize_t length,
    const char *errors,
    Py_ssize_t *consumed
    );

__attribute__((dllimport)) PyObject* PyUnicode_DecodeUTF8(
    const char *string,
    Py_ssize_t length,
    const char *errors
    );

__attribute__((dllimport)) PyObject* PyUnicode_DecodeUTF8Stateful(
    const char *string,
    Py_ssize_t length,
    const char *errors,
    Py_ssize_t *consumed
    );

__attribute__((dllimport)) PyObject* PyUnicode_AsUTF8String(
    PyObject *unicode
    );
# 462 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/unicodeobject.h"
__attribute__((dllimport)) const char * PyUnicode_AsUTF8AndSize(PyObject *unicode, Py_ssize_t *size);
# 492 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/unicodeobject.h"
__attribute__((dllimport)) PyObject* PyUnicode_DecodeUTF32(
    const char *string,
    Py_ssize_t length,
    const char *errors,
    int *byteorder
    );

__attribute__((dllimport)) PyObject* PyUnicode_DecodeUTF32Stateful(
    const char *string,
    Py_ssize_t length,
    const char *errors,
    int *byteorder,
    Py_ssize_t *consumed
    );

__attribute__((dllimport)) PyObject* PyUnicode_AsUTF32String(
    PyObject *unicode
    );
# 559 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/unicodeobject.h"
__attribute__((dllimport)) PyObject* PyUnicode_DecodeUTF16(
    const char *string,
    Py_ssize_t length,
    const char *errors,
    int *byteorder
    );

__attribute__((dllimport)) PyObject* PyUnicode_DecodeUTF16Stateful(
    const char *string,
    Py_ssize_t length,
    const char *errors,
    int *byteorder,
    Py_ssize_t *consumed
    );

__attribute__((dllimport)) PyObject* PyUnicode_AsUTF16String(
    PyObject *unicode
    );

__attribute__((dllimport)) PyObject* PyUnicode_DecodeUnicodeEscape(
    const char *string,
    Py_ssize_t length,
    const char *errors
    );

__attribute__((dllimport)) PyObject* PyUnicode_AsUnicodeEscapeString(
    PyObject *unicode
    );

__attribute__((dllimport)) PyObject* PyUnicode_DecodeRawUnicodeEscape(
    const char *string,
    Py_ssize_t length,
    const char *errors
    );

__attribute__((dllimport)) PyObject* PyUnicode_AsRawUnicodeEscapeString(
    PyObject *unicode
    );

__attribute__((dllimport)) PyObject* PyUnicode_DecodeLatin1(
    const char *string,
    Py_ssize_t length,
    const char *errors
    );

__attribute__((dllimport)) PyObject* PyUnicode_AsLatin1String(
    PyObject *unicode
    );

__attribute__((dllimport)) PyObject* PyUnicode_DecodeASCII(
    const char *string,
    Py_ssize_t length,
    const char *errors
    );

__attribute__((dllimport)) PyObject* PyUnicode_AsASCIIString(
    PyObject *unicode
    );
# 656 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/unicodeobject.h"
__attribute__((dllimport)) PyObject* PyUnicode_DecodeCharmap(
    const char *string,
    Py_ssize_t length,
    PyObject *mapping,
    const char *errors
    );

__attribute__((dllimport)) PyObject* PyUnicode_AsCharmapString(
    PyObject *unicode,
    PyObject *mapping
    );

__attribute__((dllimport)) PyObject* PyUnicode_DecodeMBCS(
    const char *string,
    Py_ssize_t length,
    const char *errors
    );

__attribute__((dllimport)) PyObject* PyUnicode_DecodeMBCSStateful(
    const char *string,
    Py_ssize_t length,
    const char *errors,
    Py_ssize_t *consumed
    );

__attribute__((dllimport)) PyObject* PyUnicode_DecodeCodePageStateful(
    int code_page,
    const char *string,
    Py_ssize_t length,
    const char *errors,
    Py_ssize_t *consumed
    );

__attribute__((dllimport)) PyObject* PyUnicode_AsMBCSString(
    PyObject *unicode
    );

__attribute__((dllimport)) PyObject* PyUnicode_EncodeCodePage(
    int code_page,
    PyObject *unicode,
    const char *errors
    );
# 719 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/unicodeobject.h"
__attribute__((dllimport)) PyObject* PyUnicode_DecodeLocaleAndSize(
    const char *str,
    Py_ssize_t len,
    const char *errors);

__attribute__((dllimport)) PyObject* PyUnicode_DecodeLocale(
    const char *str,
    const char *errors);

__attribute__((dllimport)) PyObject* PyUnicode_EncodeLocale(
    PyObject *unicode,
    const char *errors
    );

__attribute__((dllimport)) int PyUnicode_FSConverter(PyObject*, void*);

__attribute__((dllimport)) int PyUnicode_FSDecoder(PyObject*, void*);

__attribute__((dllimport)) PyObject* PyUnicode_DecodeFSDefault(
    const char *s
    );

__attribute__((dllimport)) PyObject* PyUnicode_DecodeFSDefaultAndSize(
    const char *s,
    Py_ssize_t size
    );

__attribute__((dllimport)) PyObject* PyUnicode_EncodeFSDefault(
    PyObject *unicode
    );
# 782 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/unicodeobject.h"
__attribute__((dllimport)) PyObject* PyUnicode_Concat(
    PyObject *left,
    PyObject *right
    );

__attribute__((dllimport)) void PyUnicode_Append(
    PyObject **pleft,
    PyObject *right
    );

__attribute__((dllimport)) void PyUnicode_AppendAndDel(
    PyObject **pleft,
    PyObject *right
    );
# 814 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/unicodeobject.h"
__attribute__((dllimport)) PyObject* PyUnicode_Split(
    PyObject *s,
    PyObject *sep,
    Py_ssize_t maxsplit
    );

__attribute__((dllimport)) PyObject* PyUnicode_Splitlines(
    PyObject *s,
    int keepends
    );

__attribute__((dllimport)) PyObject* PyUnicode_Partition(
    PyObject *s,
    PyObject *sep
    );

__attribute__((dllimport)) PyObject* PyUnicode_RPartition(
    PyObject *s,
    PyObject *sep
    );
# 858 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/unicodeobject.h"
__attribute__((dllimport)) PyObject* PyUnicode_RSplit(
    PyObject *s,
    PyObject *sep,
    Py_ssize_t maxsplit
    );
# 876 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/unicodeobject.h"
__attribute__((dllimport)) PyObject * PyUnicode_Translate(
    PyObject *str,
    PyObject *table,
    const char *errors
    );

__attribute__((dllimport)) PyObject* PyUnicode_Join(
    PyObject *separator,
    PyObject *seq
    );

__attribute__((dllimport)) Py_ssize_t PyUnicode_Tailmatch(
    PyObject *str,
    PyObject *substr,
    Py_ssize_t start,
    Py_ssize_t end,
    int direction
    );

__attribute__((dllimport)) Py_ssize_t PyUnicode_Find(
    PyObject *str,
    PyObject *substr,
    Py_ssize_t start,
    Py_ssize_t end,
    int direction
    );

__attribute__((dllimport)) Py_ssize_t PyUnicode_FindChar(
    PyObject *str,
    Py_UCS4 ch,
    Py_ssize_t start,
    Py_ssize_t end,
    int direction
    );

__attribute__((dllimport)) Py_ssize_t PyUnicode_Count(
    PyObject *str,
    PyObject *substr,
    Py_ssize_t start,
    Py_ssize_t end
    );

__attribute__((dllimport)) PyObject * PyUnicode_Replace(
    PyObject *str,
    PyObject *substr,
    PyObject *replstr,
    Py_ssize_t maxcount
    );

__attribute__((dllimport)) int PyUnicode_Compare(
    PyObject *left,
    PyObject *right
    );

__attribute__((dllimport)) int PyUnicode_CompareWithASCIIString(
    PyObject *left,
    const char *right
    );

__attribute__((dllimport)) int PyUnicode_EqualToUTF8(PyObject *, const char *);
__attribute__((dllimport)) int PyUnicode_EqualToUTF8AndSize(PyObject *, const char *, Py_ssize_t);

__attribute__((dllimport)) int PyUnicode_Equal(PyObject *str1, PyObject *str2);
# 989 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/unicodeobject.h"
__attribute__((dllimport)) PyObject * PyUnicode_RichCompare(
    PyObject *left,
    PyObject *right,
    int op
    );

__attribute__((dllimport)) PyObject * PyUnicode_Format(
    PyObject *format,
    PyObject *args
    );

__attribute__((dllimport)) int PyUnicode_Contains(
    PyObject *container,
    PyObject *element
    );

__attribute__((dllimport)) int PyUnicode_IsIdentifier(PyObject *s);

__attribute__((__deprecated__)) typedef wchar_t PY_UNICODE_TYPE;
__attribute__((__deprecated__)) typedef wchar_t Py_UNICODE;

static inline int Py_UNICODE_IS_SURROGATE(Py_UCS4 ch) {
    return (0xD800 <= ch && ch <= 0xDFFF);
}
static inline int Py_UNICODE_IS_HIGH_SURROGATE(Py_UCS4 ch) {
    return (0xD800 <= ch && ch <= 0xDBFF);
}
static inline int Py_UNICODE_IS_LOW_SURROGATE(Py_UCS4 ch) {
    return (0xDC00 <= ch && ch <= 0xDFFF);
}

static inline Py_UCS4 Py_UNICODE_JOIN_SURROGATES(Py_UCS4 high, Py_UCS4 low) {
    (void) ((!!(Py_UNICODE_IS_HIGH_SURROGATE(high))) || (_assert("Py_UNICODE_IS_HIGH_SURROGATE(high)","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/unicodeobject.h",28),0));
    (void) ((!!(Py_UNICODE_IS_LOW_SURROGATE(low))) || (_assert("Py_UNICODE_IS_LOW_SURROGATE(low)","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/unicodeobject.h",29),0));
    return 0x10000 + (((high & 0x03FF) << 10) | (low & 0x03FF));
}

static inline Py_UCS4 Py_UNICODE_HIGH_SURROGATE(Py_UCS4 ch) {
    (void) ((!!(0x10000 <= ch && ch <= 0x10ffff)) || (_assert("0x10000 <= ch && ch <= 0x10ffff","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/unicodeobject.h",36),0));
    return (0xD800 - (0x10000 >> 10) + (ch >> 10));
}

static inline Py_UCS4 Py_UNICODE_LOW_SURROGATE(Py_UCS4 ch) {
    (void) ((!!(0x10000 <= ch && ch <= 0x10ffff)) || (_assert("0x10000 <= ch && ch <= 0x10ffff","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/unicodeobject.h",43),0));
    return (0xDC00 + (ch & 0x3FF));
}
# 54 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/unicodeobject.h"
typedef struct {
    PyObject ob_base;
    Py_ssize_t length;
    Py_hash_t hash;
    struct {
        unsigned int interned:2;
        unsigned int kind:3;
        unsigned int compact:1;
        unsigned int ascii:1;
        unsigned int statically_allocated:1;
        unsigned int :24;
    } state;
} PyASCIIObject;

typedef struct {
    PyASCIIObject _base;
    Py_ssize_t utf8_length;
    char *utf8;
} PyCompactUnicodeObject;

typedef struct {
    PyCompactUnicodeObject _base;
    union {
        void *any;
        Py_UCS1 *latin1;
        Py_UCS2 *ucs2;
        Py_UCS4 *ucs4;
    } data;
} PyUnicodeObject;
# 209 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/unicodeobject.h"
static inline unsigned int PyUnicode_CHECK_INTERNED(PyObject *op) {
    return ((void) ((!!(PyType_HasFeature((_Py_TYPE(((PyObject*)((op))))), ((1UL << 28))))) || (_assert("PyUnicode_Check(op)","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/unicodeobject.h",213),0)), ((PyASCIIObject*)((op))))->state.interned;
}

static inline unsigned int PyUnicode_IS_READY(PyObject* _unused_op __attribute__((unused))) {
    return 1;
}

static inline unsigned int PyUnicode_IS_ASCII(PyObject *op) {
    return ((void) ((!!(PyType_HasFeature((_Py_TYPE(((PyObject*)((op))))), ((1UL << 28))))) || (_assert("PyUnicode_Check(op)","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/unicodeobject.h",227),0)), ((PyASCIIObject*)((op))))->state.ascii;
}

static inline unsigned int PyUnicode_IS_COMPACT(PyObject *op) {
    return ((void) ((!!(PyType_HasFeature((_Py_TYPE(((PyObject*)((op))))), ((1UL << 28))))) || (_assert("PyUnicode_Check(op)","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/unicodeobject.h",234),0)), ((PyASCIIObject*)((op))))->state.compact;
}

static inline int PyUnicode_IS_COMPACT_ASCII(PyObject *op) {
    return (((void) ((!!(PyType_HasFeature((_Py_TYPE(((PyObject*)((op))))), ((1UL << 28))))) || (_assert("PyUnicode_Check(op)","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/unicodeobject.h",241),0)), ((PyASCIIObject*)((op))))->state.ascii && PyUnicode_IS_COMPACT(((PyObject*)((op)))));
}

enum PyUnicode_Kind {
    PyUnicode_1BYTE_KIND = 1,
    PyUnicode_2BYTE_KIND = 2,
    PyUnicode_4BYTE_KIND = 4
};

__attribute__((dllimport)) int PyUnicode_KIND(PyObject *op);
# 263 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/unicodeobject.h"
static inline void* _PyUnicode_COMPACT_DATA(PyObject *op) {
    if (PyUnicode_IS_ASCII(((PyObject*)((op))))) {
        return ((void*)((((void) ((!!(PyType_HasFeature((_Py_TYPE(((PyObject*)((op))))), ((1UL << 28))))) || (_assert("PyUnicode_Check(op)","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/unicodeobject.h",265),0)), ((PyASCIIObject*)((op)))) + 1)));
    }
    return ((void*)((((void) ((!!(PyType_HasFeature((_Py_TYPE(((PyObject*)((op))))), ((1UL << 28))))) || (_assert("PyUnicode_Check(op)","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/unicodeobject.h",267),0)), ((PyCompactUnicodeObject*)((op)))) + 1)));
}

static inline void* _PyUnicode_NONCOMPACT_DATA(PyObject *op) {
    void *data;
    (void) ((!!(!PyUnicode_IS_COMPACT(((PyObject*)((op)))))) || (_assert("!PyUnicode_IS_COMPACT(op)","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/unicodeobject.h",272),0));
    data = ((void) ((!!(PyType_HasFeature((_Py_TYPE(((PyObject*)((op))))), ((1UL << 28))))) || (_assert("PyUnicode_Check(op)","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/unicodeobject.h",273),0)), ((PyUnicodeObject*)((op))))->data.any;
    (void) ((!!(data != ((void *)0))) || (_assert("data != NULL","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/unicodeobject.h",274),0));
    return data;
}

__attribute__((dllimport)) void* PyUnicode_DATA(PyObject *op);

static inline void* _PyUnicode_DATA(PyObject *op) {
    if (PyUnicode_IS_COMPACT(((PyObject*)((op))))) {
        return _PyUnicode_COMPACT_DATA(op);
    }
    return _PyUnicode_NONCOMPACT_DATA(op);
}
# 298 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/unicodeobject.h"
static inline Py_ssize_t PyUnicode_GET_LENGTH(PyObject *op) {
    return ((void) ((!!(PyType_HasFeature((_Py_TYPE(((PyObject*)((op))))), ((1UL << 28))))) || (_assert("PyUnicode_Check(op)","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/unicodeobject.h",299),0)), ((PyASCIIObject*)((op))))->length;
}

static inline void PyUnicode_WRITE(int kind, void *data,
                                   Py_ssize_t index, Py_UCS4 value)
{
    (void) ((!!(index >= 0)) || (_assert("index >= 0","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/unicodeobject.h",311),0));
    if (kind == PyUnicode_1BYTE_KIND) {
        (void) ((!!(value <= 0xffU)) || (_assert("value <= 0xffU","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/unicodeobject.h",313),0));
        ((Py_UCS1*)(data))[index] = ((Py_UCS1)(value));
    }
    else if (kind == PyUnicode_2BYTE_KIND) {
        (void) ((!!(value <= 0xffffU)) || (_assert("value <= 0xffffU","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/unicodeobject.h",317),0));
        ((Py_UCS2*)(data))[index] = ((Py_UCS2)(value));
    }
    else {
        (void) ((!!(kind == PyUnicode_4BYTE_KIND)) || (_assert("kind == PyUnicode_4BYTE_KIND","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/unicodeobject.h",321),0));
        (void) ((!!(value <= 0x10ffffU)) || (_assert("value <= 0x10ffffU","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/unicodeobject.h",322),0));
        ((Py_UCS4*)(data))[index] = value;
    }
}

static inline Py_UCS4 PyUnicode_READ(int kind,
                                     const void *data, Py_ssize_t index)
{
    (void) ((!!(index >= 0)) || (_assert("index >= 0","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/unicodeobject.h",335),0));
    if (kind == PyUnicode_1BYTE_KIND) {
        return ((const Py_UCS1*)(data))[index];
    }
    if (kind == PyUnicode_2BYTE_KIND) {
        return ((const Py_UCS2*)(data))[index];
    }
    (void) ((!!(kind == PyUnicode_4BYTE_KIND)) || (_assert("kind == PyUnicode_4BYTE_KIND","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/unicodeobject.h",342),0));
    return ((const Py_UCS4*)(data))[index];
}
# 354 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/unicodeobject.h"
static inline Py_UCS4 PyUnicode_READ_CHAR(PyObject *unicode, Py_ssize_t index)
{
    int kind;
    (void) ((!!(index >= 0)) || (_assert("index >= 0","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/unicodeobject.h",358),0));
    (void) ((!!(index <= PyUnicode_GET_LENGTH(((PyObject*)((unicode)))))) || (_assert("index <= PyUnicode_GET_LENGTH(unicode)","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/unicodeobject.h",360),0));
    kind = ((void)0, (((void) ((!!(PyType_HasFeature((_Py_TYPE(((PyObject*)((unicode))))), ((1UL << 28))))) || (_assert("PyUnicode_Check(unicode)","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/unicodeobject.h",362),0)), ((PyASCIIObject*)((unicode))))->state.kind));
    if (kind == PyUnicode_1BYTE_KIND) {
        return ((Py_UCS1*)(_PyUnicode_DATA(((PyObject*)((unicode))))))[index];
    }
    if (kind == PyUnicode_2BYTE_KIND) {
        return ((Py_UCS2*)(_PyUnicode_DATA(((PyObject*)((unicode))))))[index];
    }
    (void) ((!!(kind == PyUnicode_4BYTE_KIND)) || (_assert("kind == PyUnicode_4BYTE_KIND","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/unicodeobject.h",369),0));
    return ((Py_UCS4*)(_PyUnicode_DATA(((PyObject*)((unicode))))))[index];
}

static inline Py_UCS4 PyUnicode_MAX_CHAR_VALUE(PyObject *op)
{
    int kind;
    if (PyUnicode_IS_ASCII(((PyObject*)((op))))) {
        return 0x7fU;
    }
    kind = ((void)0, (((void) ((!!(PyType_HasFeature((_Py_TYPE(((PyObject*)((op))))), ((1UL << 28))))) || (_assert("PyUnicode_Check(op)","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/unicodeobject.h",386),0)), ((PyASCIIObject*)((op))))->state.kind));
    if (kind == PyUnicode_1BYTE_KIND) {
       return 0xffU;
    }
    if (kind == PyUnicode_2BYTE_KIND) {
        return 0xffffU;
    }
    (void) ((!!(kind == PyUnicode_4BYTE_KIND)) || (_assert("kind == PyUnicode_4BYTE_KIND","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/unicodeobject.h",393),0));
    return 0x10ffffU;
}
# 405 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/unicodeobject.h"
__attribute__((dllimport)) PyObject* PyUnicode_New(
    Py_ssize_t size,
    Py_UCS4 maxchar
    );

static inline int PyUnicode_READY(PyObject* _unused_op __attribute__((unused)))
{
    return 0;
}
# 435 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/unicodeobject.h"
__attribute__((dllimport)) Py_ssize_t PyUnicode_CopyCharacters(
    PyObject *to,
    Py_ssize_t to_start,
    PyObject *from,
    Py_ssize_t from_start,
    Py_ssize_t how_many
    );
# 451 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/unicodeobject.h"
__attribute__((dllimport)) Py_ssize_t PyUnicode_Fill(
    PyObject *unicode,
    Py_ssize_t start,
    Py_ssize_t length,
    Py_UCS4 fill_char
    );

__attribute__((dllimport)) PyObject* PyUnicode_FromKindAndData(
    int kind,
    const void *buffer,
    Py_ssize_t size);

typedef struct PyUnicodeWriter PyUnicodeWriter;

__attribute__((dllimport)) PyUnicodeWriter* PyUnicodeWriter_Create(Py_ssize_t length);
__attribute__((dllimport)) void PyUnicodeWriter_Discard(PyUnicodeWriter *writer);
__attribute__((dllimport)) PyObject* PyUnicodeWriter_Finish(PyUnicodeWriter *writer);

__attribute__((dllimport)) int PyUnicodeWriter_WriteChar(
    PyUnicodeWriter *writer,
    Py_UCS4 ch);
__attribute__((dllimport)) int PyUnicodeWriter_WriteUTF8(
    PyUnicodeWriter *writer,
    const char *str,
    Py_ssize_t size);
__attribute__((dllimport)) int PyUnicodeWriter_WriteASCII(
    PyUnicodeWriter *writer,
    const char *str,
    Py_ssize_t size);
__attribute__((dllimport)) int PyUnicodeWriter_WriteWideChar(
    PyUnicodeWriter *writer,
    const wchar_t *str,
    Py_ssize_t size);
__attribute__((dllimport)) int PyUnicodeWriter_WriteUCS4(
    PyUnicodeWriter *writer,
    Py_UCS4 *str,
    Py_ssize_t size);

__attribute__((dllimport)) int PyUnicodeWriter_WriteStr(
    PyUnicodeWriter *writer,
    PyObject *obj);
__attribute__((dllimport)) int PyUnicodeWriter_WriteRepr(
    PyUnicodeWriter *writer,
    PyObject *obj);
__attribute__((dllimport)) int PyUnicodeWriter_WriteSubstring(
    PyUnicodeWriter *writer,
    PyObject *str,
    Py_ssize_t start,
    Py_ssize_t end);
__attribute__((dllimport)) int PyUnicodeWriter_Format(
    PyUnicodeWriter *writer,
    const char *format,
    ...);
__attribute__((dllimport)) int PyUnicodeWriter_DecodeUTF8Stateful(
    PyUnicodeWriter *writer,
    const char *string,
    Py_ssize_t length,
    const char *errors,
    Py_ssize_t *consumed);

typedef struct {
    PyObject *buffer;
    void *data;
    int kind;
    Py_UCS4 maxchar;
    Py_ssize_t size;
    Py_ssize_t pos;
    Py_ssize_t min_length;
    Py_UCS4 min_char;
    unsigned char overallocate;
    unsigned char readonly;
} _PyUnicodeWriter;

__attribute__((__deprecated__)) __attribute__((dllimport)) void _PyUnicodeWriter_Init(
    _PyUnicodeWriter *writer);
# 563 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/unicodeobject.h"
__attribute__((__deprecated__)) __attribute__((dllimport)) int _PyUnicodeWriter_PrepareInternal(
    _PyUnicodeWriter *writer,
    Py_ssize_t length,
    Py_UCS4 maxchar);
# 580 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/unicodeobject.h"
__attribute__((__deprecated__)) __attribute__((dllimport)) int _PyUnicodeWriter_PrepareKindInternal(
    _PyUnicodeWriter *writer,
    int kind);

__attribute__((__deprecated__)) __attribute__((dllimport)) int _PyUnicodeWriter_WriteChar(
    _PyUnicodeWriter *writer,
    Py_UCS4 ch);

__attribute__((__deprecated__)) __attribute__((dllimport)) int _PyUnicodeWriter_WriteStr(
    _PyUnicodeWriter *writer,
    PyObject *str);

__attribute__((__deprecated__)) __attribute__((dllimport)) int _PyUnicodeWriter_WriteSubstring(
    _PyUnicodeWriter *writer,
    PyObject *str,
    Py_ssize_t start,
    Py_ssize_t end);

__attribute__((__deprecated__)) __attribute__((dllimport)) int _PyUnicodeWriter_WriteASCIIString(
    _PyUnicodeWriter *writer,
    const char *str,
    Py_ssize_t len);

__attribute__((__deprecated__)) __attribute__((dllimport)) int _PyUnicodeWriter_WriteLatin1String(
    _PyUnicodeWriter *writer,
    const char *str,
    Py_ssize_t len);

__attribute__((__deprecated__)) __attribute__((dllimport)) PyObject * _PyUnicodeWriter_Finish(
    _PyUnicodeWriter *writer);

__attribute__((__deprecated__)) __attribute__((dllimport)) void _PyUnicodeWriter_Dealloc(
    _PyUnicodeWriter *writer);
# 644 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/unicodeobject.h"
__attribute__((dllimport)) const char * PyUnicode_AsUTF8(PyObject *unicode);

__attribute__((__deprecated__)) static inline const char*
_PyUnicode_AsString(PyObject *unicode)
{
    return PyUnicode_AsUTF8(unicode);
}
# 663 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/unicodeobject.h"
__attribute__((dllimport)) int _PyUnicode_IsLowercase(
    Py_UCS4 ch
    );

__attribute__((dllimport)) int _PyUnicode_IsUppercase(
    Py_UCS4 ch
    );

__attribute__((dllimport)) int _PyUnicode_IsTitlecase(
    Py_UCS4 ch
    );

__attribute__((dllimport)) int _PyUnicode_IsWhitespace(
    const Py_UCS4 ch
    );

__attribute__((dllimport)) int _PyUnicode_IsLinebreak(
    const Py_UCS4 ch
    );

__attribute__((dllimport)) Py_UCS4 _PyUnicode_ToLowercase(
    Py_UCS4 ch
    );

__attribute__((dllimport)) Py_UCS4 _PyUnicode_ToUppercase(
    Py_UCS4 ch
    );

__attribute__((dllimport)) Py_UCS4 _PyUnicode_ToTitlecase(
    Py_UCS4 ch
    );

__attribute__((dllimport)) int _PyUnicode_ToDecimalDigit(
    Py_UCS4 ch
    );

__attribute__((dllimport)) int _PyUnicode_ToDigit(
    Py_UCS4 ch
    );

__attribute__((dllimport)) double _PyUnicode_ToNumeric(
    Py_UCS4 ch
    );

__attribute__((dllimport)) int _PyUnicode_IsDecimalDigit(
    Py_UCS4 ch
    );

__attribute__((dllimport)) int _PyUnicode_IsDigit(
    Py_UCS4 ch
    );

__attribute__((dllimport)) int _PyUnicode_IsNumeric(
    Py_UCS4 ch
    );

__attribute__((dllimport)) int _PyUnicode_IsPrintable(
    Py_UCS4 ch
    );

__attribute__((dllimport)) int _PyUnicode_IsAlpha(
    Py_UCS4 ch
    );

extern __attribute__((dllimport)) const unsigned char _Py_ascii_whitespace[];

static inline int Py_UNICODE_ISSPACE(Py_UCS4 ch) {
    if (ch < 128) {
        return _Py_ascii_whitespace[ch];
    }
    return _PyUnicode_IsWhitespace(ch);
}
# 761 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/unicodeobject.h"
static inline int Py_UNICODE_ISALNUM(Py_UCS4 ch) {
   return (_PyUnicode_IsAlpha(ch)
           || _PyUnicode_IsDecimalDigit(ch)
           || _PyUnicode_IsDigit(ch)
           || _PyUnicode_IsNumeric(ch));
}

__attribute__((dllimport)) PyObject* _PyUnicode_FromId(_Py_Identifier*);

__attribute__((dllimport)) void PyErr_SetNone(PyObject *);
__attribute__((dllimport)) void PyErr_SetObject(PyObject *, PyObject *);
__attribute__((dllimport)) void PyErr_SetString(
    PyObject *exception,
    const char *string
    );
__attribute__((dllimport)) PyObject * PyErr_Occurred(void);
__attribute__((dllimport)) void PyErr_Clear(void);
__attribute__((dllimport)) void PyErr_Fetch(PyObject **, PyObject **, PyObject **);
__attribute__((dllimport)) void PyErr_Restore(PyObject *, PyObject *, PyObject *);
__attribute__((dllimport)) PyObject * PyErr_GetRaisedException(void);
__attribute__((dllimport)) void PyErr_SetRaisedException(PyObject *);

__attribute__((dllimport)) PyObject* PyErr_GetHandledException(void);
__attribute__((dllimport)) void PyErr_SetHandledException(PyObject *);

__attribute__((dllimport)) void PyErr_GetExcInfo(PyObject **, PyObject **, PyObject **);
__attribute__((dllimport)) void PyErr_SetExcInfo(PyObject *, PyObject *, PyObject *);

__attribute__((dllimport)) void __attribute__((__noreturn__)) Py_FatalError(const char *message);

__attribute__((dllimport)) int PyErr_GivenExceptionMatches(PyObject *, PyObject *);
__attribute__((dllimport)) int PyErr_ExceptionMatches(PyObject *);
__attribute__((dllimport)) void PyErr_NormalizeException(PyObject**, PyObject**, PyObject**);

__attribute__((dllimport)) int PyException_SetTraceback(PyObject *, PyObject *);
__attribute__((dllimport)) PyObject * PyException_GetTraceback(PyObject *);

__attribute__((dllimport)) PyObject * PyException_GetCause(PyObject *);
__attribute__((dllimport)) void PyException_SetCause(PyObject *, PyObject *);

__attribute__((dllimport)) PyObject * PyException_GetContext(PyObject *);
__attribute__((dllimport)) void PyException_SetContext(PyObject *, PyObject *);

__attribute__((dllimport)) PyObject * PyException_GetArgs(PyObject *);
__attribute__((dllimport)) void PyException_SetArgs(PyObject *, PyObject *);
# 67 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/pyerrors.h"
__attribute__((dllimport)) const char * PyExceptionClass_Name(PyObject *);
# 76 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/pyerrors.h"
extern __attribute__((dllimport)) PyObject * PyExc_BaseException;
extern __attribute__((dllimport)) PyObject * PyExc_Exception;
extern __attribute__((dllimport)) PyObject * PyExc_BaseExceptionGroup;

extern __attribute__((dllimport)) PyObject * PyExc_StopAsyncIteration;

extern __attribute__((dllimport)) PyObject * PyExc_StopIteration;
extern __attribute__((dllimport)) PyObject * PyExc_GeneratorExit;
extern __attribute__((dllimport)) PyObject * PyExc_ArithmeticError;
extern __attribute__((dllimport)) PyObject * PyExc_LookupError;

extern __attribute__((dllimport)) PyObject * PyExc_AssertionError;
extern __attribute__((dllimport)) PyObject * PyExc_AttributeError;
extern __attribute__((dllimport)) PyObject * PyExc_BufferError;
extern __attribute__((dllimport)) PyObject * PyExc_EOFError;
extern __attribute__((dllimport)) PyObject * PyExc_FloatingPointError;
extern __attribute__((dllimport)) PyObject * PyExc_OSError;
extern __attribute__((dllimport)) PyObject * PyExc_ImportError;

extern __attribute__((dllimport)) PyObject * PyExc_ModuleNotFoundError;

extern __attribute__((dllimport)) PyObject * PyExc_IndexError;
extern __attribute__((dllimport)) PyObject * PyExc_KeyError;
extern __attribute__((dllimport)) PyObject * PyExc_KeyboardInterrupt;
extern __attribute__((dllimport)) PyObject * PyExc_MemoryError;
extern __attribute__((dllimport)) PyObject * PyExc_NameError;
extern __attribute__((dllimport)) PyObject * PyExc_OverflowError;
extern __attribute__((dllimport)) PyObject * PyExc_RuntimeError;

extern __attribute__((dllimport)) PyObject * PyExc_RecursionError;

extern __attribute__((dllimport)) PyObject * PyExc_NotImplementedError;
extern __attribute__((dllimport)) PyObject * PyExc_SyntaxError;
extern __attribute__((dllimport)) PyObject * PyExc_IndentationError;
extern __attribute__((dllimport)) PyObject * PyExc_TabError;
extern __attribute__((dllimport)) PyObject * PyExc_ReferenceError;
extern __attribute__((dllimport)) PyObject * PyExc_SystemError;
extern __attribute__((dllimport)) PyObject * PyExc_SystemExit;
extern __attribute__((dllimport)) PyObject * PyExc_TypeError;
extern __attribute__((dllimport)) PyObject * PyExc_UnboundLocalError;
extern __attribute__((dllimport)) PyObject * PyExc_UnicodeError;
extern __attribute__((dllimport)) PyObject * PyExc_UnicodeEncodeError;
extern __attribute__((dllimport)) PyObject * PyExc_UnicodeDecodeError;
extern __attribute__((dllimport)) PyObject * PyExc_UnicodeTranslateError;
extern __attribute__((dllimport)) PyObject * PyExc_ValueError;
extern __attribute__((dllimport)) PyObject * PyExc_ZeroDivisionError;

extern __attribute__((dllimport)) PyObject * PyExc_BlockingIOError;
extern __attribute__((dllimport)) PyObject * PyExc_BrokenPipeError;
extern __attribute__((dllimport)) PyObject * PyExc_ChildProcessError;
extern __attribute__((dllimport)) PyObject * PyExc_ConnectionError;
extern __attribute__((dllimport)) PyObject * PyExc_ConnectionAbortedError;
extern __attribute__((dllimport)) PyObject * PyExc_ConnectionRefusedError;
extern __attribute__((dllimport)) PyObject * PyExc_ConnectionResetError;
extern __attribute__((dllimport)) PyObject * PyExc_FileExistsError;
extern __attribute__((dllimport)) PyObject * PyExc_FileNotFoundError;
extern __attribute__((dllimport)) PyObject * PyExc_InterruptedError;
extern __attribute__((dllimport)) PyObject * PyExc_IsADirectoryError;
extern __attribute__((dllimport)) PyObject * PyExc_NotADirectoryError;
extern __attribute__((dllimport)) PyObject * PyExc_PermissionError;
extern __attribute__((dllimport)) PyObject * PyExc_ProcessLookupError;
extern __attribute__((dllimport)) PyObject * PyExc_TimeoutError;

extern __attribute__((dllimport)) PyObject * PyExc_EnvironmentError;
extern __attribute__((dllimport)) PyObject * PyExc_IOError;

extern __attribute__((dllimport)) PyObject * PyExc_WindowsError;

extern __attribute__((dllimport)) PyObject * PyExc_Warning;
extern __attribute__((dllimport)) PyObject * PyExc_UserWarning;
extern __attribute__((dllimport)) PyObject * PyExc_DeprecationWarning;
extern __attribute__((dllimport)) PyObject * PyExc_PendingDeprecationWarning;
extern __attribute__((dllimport)) PyObject * PyExc_SyntaxWarning;
extern __attribute__((dllimport)) PyObject * PyExc_RuntimeWarning;
extern __attribute__((dllimport)) PyObject * PyExc_FutureWarning;
extern __attribute__((dllimport)) PyObject * PyExc_ImportWarning;
extern __attribute__((dllimport)) PyObject * PyExc_UnicodeWarning;
extern __attribute__((dllimport)) PyObject * PyExc_BytesWarning;
extern __attribute__((dllimport)) PyObject * PyExc_EncodingWarning;
extern __attribute__((dllimport)) PyObject * PyExc_ResourceWarning;

__attribute__((dllimport)) int PyErr_BadArgument(void);
__attribute__((dllimport)) PyObject * PyErr_NoMemory(void);
__attribute__((dllimport)) PyObject * PyErr_SetFromErrno(PyObject *);
__attribute__((dllimport)) PyObject * PyErr_SetFromErrnoWithFilenameObject(
    PyObject *, PyObject *);

__attribute__((dllimport)) PyObject * PyErr_SetFromErrnoWithFilenameObjects(
    PyObject *, PyObject *, PyObject *);

__attribute__((dllimport)) PyObject * PyErr_SetFromErrnoWithFilename(
    PyObject *exc,
    const char *filename
    );

__attribute__((dllimport)) PyObject * PyErr_Format(
    PyObject *exception,
    const char *format,
    ...
    );

__attribute__((dllimport)) PyObject * PyErr_FormatV(
    PyObject *exception,
    const char *format,
    va_list vargs);

__attribute__((dllimport)) PyObject * PyErr_SetFromWindowsErrWithFilename(
    int ierr,
    const char *filename
    );
__attribute__((dllimport)) PyObject * PyErr_SetFromWindowsErr(int);
__attribute__((dllimport)) PyObject * PyErr_SetExcFromWindowsErrWithFilenameObject(
    PyObject *,int, PyObject *);

__attribute__((dllimport)) PyObject * PyErr_SetExcFromWindowsErrWithFilenameObjects(
    PyObject *,int, PyObject *, PyObject *);

__attribute__((dllimport)) PyObject * PyErr_SetExcFromWindowsErrWithFilename(
    PyObject *exc,
    int ierr,
    const char *filename
    );
__attribute__((dllimport)) PyObject * PyErr_SetExcFromWindowsErr(PyObject *, int);

__attribute__((dllimport)) PyObject * PyErr_SetImportErrorSubclass(PyObject *, PyObject *,
    PyObject *, PyObject *);

__attribute__((dllimport)) PyObject * PyErr_SetImportError(PyObject *, PyObject *,
    PyObject *);

__attribute__((dllimport)) void PyErr_BadInternalCall(void);
__attribute__((dllimport)) void _PyErr_BadInternalCall(const char *filename, int lineno);

__attribute__((dllimport)) PyObject * PyErr_NewException(
    const char *name, PyObject *base, PyObject *dict);
__attribute__((dllimport)) PyObject * PyErr_NewExceptionWithDoc(
    const char *name, const char *doc, PyObject *base, PyObject *dict);
__attribute__((dllimport)) void PyErr_WriteUnraisable(PyObject *);

__attribute__((dllimport)) int PyErr_CheckSignals(void);
__attribute__((dllimport)) void PyErr_SetInterrupt(void);

__attribute__((dllimport)) int PyErr_SetInterruptEx(int signum);

__attribute__((dllimport)) void PyErr_SyntaxLocation(
    const char *filename,
    int lineno);
__attribute__((dllimport)) void PyErr_SyntaxLocationEx(
    const char *filename,
    int lineno,
    int col_offset);
__attribute__((dllimport)) PyObject * PyErr_ProgramText(
    const char *filename,
    int lineno);

__attribute__((dllimport)) PyObject * PyUnicodeDecodeError_Create(
    const char *encoding,
    const char *object,
    Py_ssize_t length,
    Py_ssize_t start,
    Py_ssize_t end,
    const char *reason
    );

__attribute__((dllimport)) PyObject * PyUnicodeEncodeError_GetEncoding(PyObject *);
__attribute__((dllimport)) PyObject * PyUnicodeDecodeError_GetEncoding(PyObject *);

__attribute__((dllimport)) PyObject * PyUnicodeEncodeError_GetObject(PyObject *);
__attribute__((dllimport)) PyObject * PyUnicodeDecodeError_GetObject(PyObject *);
__attribute__((dllimport)) PyObject * PyUnicodeTranslateError_GetObject(PyObject *);

__attribute__((dllimport)) int PyUnicodeEncodeError_GetStart(PyObject *, Py_ssize_t *);
__attribute__((dllimport)) int PyUnicodeDecodeError_GetStart(PyObject *, Py_ssize_t *);
__attribute__((dllimport)) int PyUnicodeTranslateError_GetStart(PyObject *, Py_ssize_t *);

__attribute__((dllimport)) int PyUnicodeEncodeError_SetStart(PyObject *, Py_ssize_t);
__attribute__((dllimport)) int PyUnicodeDecodeError_SetStart(PyObject *, Py_ssize_t);
__attribute__((dllimport)) int PyUnicodeTranslateError_SetStart(PyObject *, Py_ssize_t);

__attribute__((dllimport)) int PyUnicodeEncodeError_GetEnd(PyObject *, Py_ssize_t *);
__attribute__((dllimport)) int PyUnicodeDecodeError_GetEnd(PyObject *, Py_ssize_t *);
__attribute__((dllimport)) int PyUnicodeTranslateError_GetEnd(PyObject *, Py_ssize_t *);

__attribute__((dllimport)) int PyUnicodeEncodeError_SetEnd(PyObject *, Py_ssize_t);
__attribute__((dllimport)) int PyUnicodeDecodeError_SetEnd(PyObject *, Py_ssize_t);
__attribute__((dllimport)) int PyUnicodeTranslateError_SetEnd(PyObject *, Py_ssize_t);

__attribute__((dllimport)) PyObject * PyUnicodeEncodeError_GetReason(PyObject *);
__attribute__((dllimport)) PyObject * PyUnicodeDecodeError_GetReason(PyObject *);
__attribute__((dllimport)) PyObject * PyUnicodeTranslateError_GetReason(PyObject *);

__attribute__((dllimport)) int PyUnicodeEncodeError_SetReason(
    PyObject *exc,
    const char *reason
    );
__attribute__((dllimport)) int PyUnicodeDecodeError_SetReason(
    PyObject *exc,
    const char *reason
    );
__attribute__((dllimport)) int PyUnicodeTranslateError_SetReason(
    PyObject *exc,
    const char *reason
    );

__attribute__((dllimport)) int PyOS_snprintf(char *str, size_t size, const char *format, ...)
                        __attribute__((format(printf, 3, 4)));
__attribute__((dllimport)) int PyOS_vsnprintf(char *str, size_t size, const char *format, va_list va)
                        __attribute__((format(printf, 3, 0)));
# 13 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/pyerrors.h"
typedef struct {
    PyObject ob_base; PyObject *dict; PyObject *args; PyObject *notes; PyObject *traceback; PyObject *context; PyObject *cause; char suppress_context;
} PyBaseExceptionObject;

typedef struct {
    PyObject ob_base; PyObject *dict; PyObject *args; PyObject *notes; PyObject *traceback; PyObject *context; PyObject *cause; char suppress_context;
    PyObject *msg;
    PyObject *excs;
} PyBaseExceptionGroupObject;

typedef struct {
    PyObject ob_base; PyObject *dict; PyObject *args; PyObject *notes; PyObject *traceback; PyObject *context; PyObject *cause; char suppress_context;
    PyObject *msg;
    PyObject *filename;
    PyObject *lineno;
    PyObject *offset;
    PyObject *end_lineno;
    PyObject *end_offset;
    PyObject *text;
    PyObject *print_file_and_line;
    PyObject *metadata;
} PySyntaxErrorObject;

typedef struct {
    PyObject ob_base; PyObject *dict; PyObject *args; PyObject *notes; PyObject *traceback; PyObject *context; PyObject *cause; char suppress_context;
    PyObject *msg;
    PyObject *name;
    PyObject *path;
    PyObject *name_from;
} PyImportErrorObject;

typedef struct {
    PyObject ob_base; PyObject *dict; PyObject *args; PyObject *notes; PyObject *traceback; PyObject *context; PyObject *cause; char suppress_context;
    PyObject *encoding;
    PyObject *object;
    Py_ssize_t start;
    Py_ssize_t end;
    PyObject *reason;
} PyUnicodeErrorObject;

typedef struct {
    PyObject ob_base; PyObject *dict; PyObject *args; PyObject *notes; PyObject *traceback; PyObject *context; PyObject *cause; char suppress_context;
    PyObject *code;
} PySystemExitObject;

typedef struct {
    PyObject ob_base; PyObject *dict; PyObject *args; PyObject *notes; PyObject *traceback; PyObject *context; PyObject *cause; char suppress_context;
    PyObject *myerrno;
    PyObject *strerror;
    PyObject *filename;
    PyObject *filename2;
    PyObject *winerror;
    Py_ssize_t written;
} PyOSErrorObject;

typedef struct {
    PyObject ob_base; PyObject *dict; PyObject *args; PyObject *notes; PyObject *traceback; PyObject *context; PyObject *cause; char suppress_context;
    PyObject *value;
} PyStopIterationObject;

typedef struct {
    PyObject ob_base; PyObject *dict; PyObject *args; PyObject *notes; PyObject *traceback; PyObject *context; PyObject *cause; char suppress_context;
    PyObject *name;
} PyNameErrorObject;

typedef struct {
    PyObject ob_base; PyObject *dict; PyObject *args; PyObject *notes; PyObject *traceback; PyObject *context; PyObject *cause; char suppress_context;
    PyObject *obj;
    PyObject *name;
} PyAttributeErrorObject;

typedef PyOSErrorObject PyEnvironmentErrorObject;

typedef PyOSErrorObject PyWindowsErrorObject;

__attribute__((dllimport)) void _PyErr_ChainExceptions1(PyObject *);

__attribute__((dllimport)) PyObject* PyUnstable_Exc_PrepReraiseStar(
     PyObject *orig,
     PyObject *excs);

__attribute__((dllimport)) int PySignal_SetWakeupFd(int fd);

__attribute__((dllimport)) void PyErr_SyntaxLocationObject(
    PyObject *filename,
    int lineno,
    int col_offset);

__attribute__((dllimport)) void PyErr_RangedSyntaxLocationObject(
    PyObject *filename,
    int lineno,
    int col_offset,
    int end_lineno,
    int end_col_offset);

__attribute__((dllimport)) PyObject * PyErr_ProgramTextObject(
    PyObject *filename,
    int lineno);

__attribute__((dllimport)) void __attribute__((__noreturn__)) _Py_FatalErrorFunc(
    const char *func,
    const char *message);

__attribute__((dllimport)) void PyErr_FormatUnraisable(const char *, ...);

extern __attribute__((dllimport)) PyObject * PyExc_PythonFinalizationError;
# 16 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/longobject.h"
__attribute__((dllimport)) PyObject * PyLong_FromLong(long);
__attribute__((dllimport)) PyObject * PyLong_FromUnsignedLong(unsigned long);
__attribute__((dllimport)) PyObject * PyLong_FromSize_t(size_t);
__attribute__((dllimport)) PyObject * PyLong_FromSsize_t(Py_ssize_t);
__attribute__((dllimport)) PyObject * PyLong_FromDouble(double);

__attribute__((dllimport)) long PyLong_AsLong(PyObject *);
__attribute__((dllimport)) long PyLong_AsLongAndOverflow(PyObject *, int *);
__attribute__((dllimport)) Py_ssize_t PyLong_AsSsize_t(PyObject *);
__attribute__((dllimport)) size_t PyLong_AsSize_t(PyObject *);
__attribute__((dllimport)) unsigned long PyLong_AsUnsignedLong(PyObject *);
__attribute__((dllimport)) unsigned long PyLong_AsUnsignedLongMask(PyObject *);

__attribute__((dllimport)) int PyLong_AsInt(PyObject *);

__attribute__((dllimport)) PyObject* PyLong_FromInt32(int32_t value);
__attribute__((dllimport)) PyObject* PyLong_FromUInt32(uint32_t value);
__attribute__((dllimport)) PyObject* PyLong_FromInt64(int64_t value);
__attribute__((dllimport)) PyObject* PyLong_FromUInt64(uint64_t value);

__attribute__((dllimport)) int PyLong_AsInt32(PyObject *obj, int32_t *value);
__attribute__((dllimport)) int PyLong_AsUInt32(PyObject *obj, uint32_t *value);
__attribute__((dllimport)) int PyLong_AsInt64(PyObject *obj, int64_t *value);
__attribute__((dllimport)) int PyLong_AsUInt64(PyObject *obj, uint64_t *value);
# 79 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/longobject.h"
__attribute__((dllimport)) Py_ssize_t PyLong_AsNativeBytes(PyObject* v, void* buffer,
    Py_ssize_t n_bytes, int flags);
# 90 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/longobject.h"
__attribute__((dllimport)) PyObject* PyLong_FromNativeBytes(const void* buffer, size_t n_bytes,
    int flags);
__attribute__((dllimport)) PyObject* PyLong_FromUnsignedNativeBytes(const void* buffer,
    size_t n_bytes, int flags);

__attribute__((dllimport)) PyObject * PyLong_GetInfo(void);
# 150 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/longobject.h"
__attribute__((dllimport)) double PyLong_AsDouble(PyObject *);
__attribute__((dllimport)) PyObject * PyLong_FromVoidPtr(void *);
__attribute__((dllimport)) void * PyLong_AsVoidPtr(PyObject *);

__attribute__((dllimport)) PyObject * PyLong_FromLongLong(long long);
__attribute__((dllimport)) PyObject * PyLong_FromUnsignedLongLong(unsigned long long);
__attribute__((dllimport)) long long PyLong_AsLongLong(PyObject *);
__attribute__((dllimport)) unsigned long long PyLong_AsUnsignedLongLong(PyObject *);
__attribute__((dllimport)) unsigned long long PyLong_AsUnsignedLongLongMask(PyObject *);
__attribute__((dllimport)) long long PyLong_AsLongLongAndOverflow(PyObject *, int *);

__attribute__((dllimport)) PyObject * PyLong_FromString(const char *, char **, int);

__attribute__((dllimport)) unsigned long PyOS_strtoul(const char *, char **, int);
__attribute__((dllimport)) long PyOS_strtol(const char *, char **, int);

__attribute__((dllimport)) PyObject* PyLong_FromUnicodeObject(PyObject *u, int base);

__attribute__((dllimport)) int PyUnstable_Long_IsCompact(const PyLongObject* op);
__attribute__((dllimport)) Py_ssize_t PyUnstable_Long_CompactValue(const PyLongObject* op);

__attribute__((dllimport)) int PyLong_IsPositive(PyObject *obj);

__attribute__((dllimport)) int PyLong_IsNegative(PyObject *obj);

__attribute__((dllimport)) int PyLong_IsZero(PyObject *obj);

__attribute__((dllimport)) int PyLong_GetSign(PyObject *v, int *sign);

__attribute__((__deprecated__)) __attribute__((dllimport)) int _PyLong_Sign(PyObject *v);

__attribute__((dllimport)) int64_t _PyLong_NumBits(PyObject *v);
# 61 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/longobject.h"
__attribute__((dllimport)) PyObject * _PyLong_FromByteArray(
    const unsigned char* bytes, size_t n,
    int little_endian, int is_signed);
# 84 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/longobject.h"
__attribute__((dllimport)) int _PyLong_AsByteArray(PyLongObject* v,
    unsigned char* bytes, size_t n,
    int little_endian, int is_signed, int with_exceptions);

__attribute__((dllimport)) PyObject * _PyLong_GCD(PyObject *, PyObject *);
# 43 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/longintrepr.h"
typedef uint32_t digit;
typedef int32_t sdigit;
typedef uint64_t twodigits;
typedef int64_t stwodigits;
# 93 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/longintrepr.h"
typedef struct _PyLongValue {
    uintptr_t lv_tag;
    digit ob_digit[1];
} _PyLongValue;

struct _longobject {
    PyObject ob_base;
    _PyLongValue long_value;
};

__attribute__((__deprecated__)) __attribute__((dllimport)) PyLongObject* _PyLong_New(Py_ssize_t);

__attribute__((dllimport)) PyObject* _PyLong_Copy(PyLongObject *src);

__attribute__((__deprecated__)) __attribute__((dllimport)) PyLongObject* _PyLong_FromDigits(
    int negative,
    Py_ssize_t digit_count,
    digit *digits);
# 121 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/longintrepr.h"
static inline int
_PyLong_IsCompact(const PyLongObject* op) {
    (void) ((!!(PyType_HasFeature(op->ob_base.ob_type, (1UL << 24)))) || (_assert("PyType_HasFeature(op->ob_base.ob_type, Py_TPFLAGS_LONG_SUBCLASS)","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/longintrepr.h",123),0));
    return op->long_value.lv_tag < (2 << 3);
}

static inline Py_ssize_t _PyLong_CompactValue(const PyLongObject *op) {
    Py_ssize_t sign;
    (void) ((!!(PyType_HasFeature(op->ob_base.ob_type, (1UL << 24)))) || (_assert("PyType_HasFeature(op->ob_base.ob_type, Py_TPFLAGS_LONG_SUBCLASS)","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/longintrepr.h",133),0));
    (void) ((!!(_PyLong_IsCompact(op))) || (_assert("PyUnstable_Long_IsCompact(op)","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/longintrepr.h",134),0));
    sign = 1 - (op->long_value.lv_tag & 3);
    return sign * (Py_ssize_t)op->long_value.ob_digit[0];
}

typedef struct PyLongLayout {
    uint8_t bits_per_digit;
    uint8_t digit_size;
    int8_t digits_order;
    int8_t digit_endianness;
} PyLongLayout;

__attribute__((dllimport)) const PyLongLayout* PyLong_GetNativeLayout(void);

typedef struct PyLongExport {
    int64_t value;
    uint8_t negative;
    Py_ssize_t ndigits;
    const void *digits;
    Py_uintptr_t _reserved;
} PyLongExport;

__attribute__((dllimport)) int PyLong_Export(
    PyObject *obj,
    PyLongExport *export_long);
__attribute__((dllimport)) void PyLong_FreeExport(
    PyLongExport *export_long);

typedef struct PyLongWriter PyLongWriter;

__attribute__((dllimport)) PyLongWriter* PyLongWriter_Create(
    int negative,
    Py_ssize_t ndigits,
    void **digits);
__attribute__((dllimport)) PyObject* PyLongWriter_Finish(PyLongWriter *writer);
__attribute__((dllimport)) void PyLongWriter_Discard(PyLongWriter *writer);
# 17 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/boolobject.h"
extern __attribute__((dllimport)) PyLongObject _Py_FalseStruct;
extern __attribute__((dllimport)) PyLongObject _Py_TrueStruct;
# 30 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/boolobject.h"
__attribute__((dllimport)) int Py_IsTrue(PyObject *x);

__attribute__((dllimport)) int Py_IsFalse(PyObject *x);
# 49 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/boolobject.h"
__attribute__((dllimport)) PyObject * PyBool_FromLong(long);
# 14 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/floatobject.h"
extern __attribute__((dllimport)) PyTypeObject PyFloat_Type;
# 31 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/floatobject.h"
__attribute__((dllimport)) double PyFloat_GetMax(void);
__attribute__((dllimport)) double PyFloat_GetMin(void);
__attribute__((dllimport)) PyObject* PyFloat_GetInfo(void);

__attribute__((dllimport)) PyObject* PyFloat_FromString(PyObject*);

__attribute__((dllimport)) PyObject* PyFloat_FromDouble(double);

__attribute__((dllimport)) double PyFloat_AsDouble(PyObject*);

typedef struct {
    PyObject ob_base;
    double ob_fval;
} PyFloatObject;

static inline double PyFloat_AS_DOUBLE(PyObject *op) {
    return ((void) ((!!(PyObject_TypeCheck(((PyObject*)((op))), (&PyFloat_Type)))) || (_assert("PyFloat_Check(op)","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/floatobject.h",16),0)), ((PyFloatObject*)(op)))->ob_fval;
}

__attribute__((dllimport)) int PyFloat_Pack2(double x, char *p, int le);
__attribute__((dllimport)) int PyFloat_Pack4(double x, char *p, int le);
__attribute__((dllimport)) int PyFloat_Pack8(double x, char *p, int le);

__attribute__((dllimport)) double PyFloat_Unpack2(const char *p, int le);
__attribute__((dllimport)) double PyFloat_Unpack4(const char *p, int le);
__attribute__((dllimport)) double PyFloat_Unpack8(const char *p, int le);
# 11 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/complexobject.h"
extern __attribute__((dllimport)) PyTypeObject PyComplex_Type;

__attribute__((dllimport)) PyObject * PyComplex_FromDoubles(double real, double imag);

__attribute__((dllimport)) double PyComplex_RealAsDouble(PyObject *op);
__attribute__((dllimport)) double PyComplex_ImagAsDouble(PyObject *op);

typedef struct {
    double real;
    double imag;
} Py_complex;

__attribute__((dllimport)) Py_complex _Py_c_sum(Py_complex, Py_complex);
__attribute__((dllimport)) Py_complex _Py_c_diff(Py_complex, Py_complex);
__attribute__((dllimport)) Py_complex _Py_c_neg(Py_complex);
__attribute__((dllimport)) Py_complex _Py_c_prod(Py_complex, Py_complex);
__attribute__((dllimport)) Py_complex _Py_c_quot(Py_complex, Py_complex);
__attribute__((dllimport)) Py_complex _Py_c_pow(Py_complex, Py_complex);
__attribute__((dllimport)) double _Py_c_abs(Py_complex);
# 26 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/complexobject.h"
typedef struct {
    PyObject ob_base;
    Py_complex cval;
} PyComplexObject;

__attribute__((dllimport)) PyObject * PyComplex_FromCComplex(Py_complex);

__attribute__((dllimport)) Py_complex PyComplex_AsCComplex(PyObject *op);
# 18 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/rangeobject.h"
extern __attribute__((dllimport)) PyTypeObject PyRange_Type;
extern __attribute__((dllimport)) PyTypeObject PyRangeIter_Type;
extern __attribute__((dllimport)) PyTypeObject PyLongRangeIter_Type;

extern __attribute__((dllimport)) PyTypeObject PyMemoryView_Type;

__attribute__((dllimport)) PyObject * PyMemoryView_FromObject(PyObject *base);

__attribute__((dllimport)) PyObject * PyMemoryView_FromMemory(char *mem, Py_ssize_t size,
                                               int flags);

__attribute__((dllimport)) PyObject * PyMemoryView_FromBuffer(const Py_buffer *info);

__attribute__((dllimport)) PyObject * PyMemoryView_GetContiguous(PyObject *base,
                                                  int buffertype,
                                                  char order);
# 11 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/memoryobject.h"
typedef struct {
    PyObject ob_base;
    int flags;
    Py_ssize_t exports;
    Py_buffer master;
} _PyManagedBufferObject;
# 27 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/memoryobject.h"
typedef struct {
    PyVarObject ob_base;
    _PyManagedBufferObject *mbuf;
    Py_hash_t hash;
    int flags;
    Py_ssize_t exports;
    Py_buffer view;
    PyObject *weakreflist;
    Py_ssize_t ob_array[1];
} PyMemoryViewObject;

static inline Py_buffer* PyMemoryView_GET_BUFFER(PyObject *op) {
    return (&((PyMemoryViewObject*)(op))->view);
}

static inline PyObject* PyMemoryView_GET_BASE(PyObject *op) {
    return ((PyMemoryViewObject*)(op))->view.obj;
}
# 23 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/tupleobject.h"
extern __attribute__((dllimport)) PyTypeObject PyTuple_Type;
extern __attribute__((dllimport)) PyTypeObject PyTupleIter_Type;

__attribute__((dllimport)) PyObject * PyTuple_New(Py_ssize_t size);
__attribute__((dllimport)) Py_ssize_t PyTuple_Size(PyObject *);
__attribute__((dllimport)) PyObject * PyTuple_GetItem(PyObject *, Py_ssize_t);
__attribute__((dllimport)) int PyTuple_SetItem(PyObject *, Py_ssize_t, PyObject *);
__attribute__((dllimport)) PyObject * PyTuple_GetSlice(PyObject *, Py_ssize_t, Py_ssize_t);
__attribute__((dllimport)) PyObject * PyTuple_Pack(Py_ssize_t, ...);

typedef struct {
    PyVarObject ob_base;
    Py_hash_t ob_hash;
    PyObject *ob_item[1];
} PyTupleObject;

__attribute__((dllimport)) int _PyTuple_Resize(PyObject **, Py_ssize_t);

static inline Py_ssize_t PyTuple_GET_SIZE(PyObject *op) {
    PyTupleObject *tuple = ((void) ((!!(PyType_HasFeature((_Py_TYPE(((PyObject*)((op))))), ((1UL << 26))))) || (_assert("PyTuple_Check(op)","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/tupleobject.h",24),0)), ((PyTupleObject*)((op))));
    return Py_SIZE(((PyObject*)((tuple))));
}

static inline void
PyTuple_SET_ITEM(PyObject *op, Py_ssize_t index, PyObject *value) {
    PyTupleObject *tuple = ((void) ((!!(PyType_HasFeature((_Py_TYPE(((PyObject*)((op))))), ((1UL << 26))))) || (_assert("PyTuple_Check(op)","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/tupleobject.h",34),0)), ((PyTupleObject*)((op))));
    (void) ((!!(0 <= index)) || (_assert("0 <= index","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/tupleobject.h",35),0));
    (void) ((!!(index < Py_SIZE(((PyObject*)((tuple)))))) || (_assert("index < Py_SIZE(tuple)","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/tupleobject.h",36),0));
    tuple->ob_item[index] = value;
}
# 20 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/listobject.h"
extern __attribute__((dllimport)) PyTypeObject PyList_Type;
extern __attribute__((dllimport)) PyTypeObject PyListIter_Type;
extern __attribute__((dllimport)) PyTypeObject PyListRevIter_Type;

__attribute__((dllimport)) PyObject * PyList_New(Py_ssize_t size);
__attribute__((dllimport)) Py_ssize_t PyList_Size(PyObject *);

__attribute__((dllimport)) PyObject * PyList_GetItem(PyObject *, Py_ssize_t);

__attribute__((dllimport)) PyObject * PyList_GetItemRef(PyObject *, Py_ssize_t);

__attribute__((dllimport)) int PyList_SetItem(PyObject *, Py_ssize_t, PyObject *);
__attribute__((dllimport)) int PyList_Insert(PyObject *, Py_ssize_t, PyObject *);
__attribute__((dllimport)) int PyList_Append(PyObject *, PyObject *);

__attribute__((dllimport)) PyObject * PyList_GetSlice(PyObject *, Py_ssize_t, Py_ssize_t);
__attribute__((dllimport)) int PyList_SetSlice(PyObject *, Py_ssize_t, Py_ssize_t, PyObject *);

__attribute__((dllimport)) int PyList_Sort(PyObject *);
__attribute__((dllimport)) int PyList_Reverse(PyObject *);
__attribute__((dllimport)) PyObject * PyList_AsTuple(PyObject *);

typedef struct {
    PyVarObject ob_base;
    PyObject **ob_item;
    Py_ssize_t allocated;
} PyListObject;

static inline Py_ssize_t PyList_GET_SIZE(PyObject *op) {
    PyListObject *list = ((void) ((!!(PyType_HasFeature((_Py_TYPE(((PyObject*)((op))))), ((1UL << 25))))) || (_assert("PyList_Check(op)","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/listobject.h",31),0)), ((PyListObject*)((op))));
    return Py_SIZE(((PyObject*)((list))));
}

static inline void
PyList_SET_ITEM(PyObject *op, Py_ssize_t index, PyObject *value) {
    PyListObject *list = ((void) ((!!(PyType_HasFeature((_Py_TYPE(((PyObject*)((op))))), ((1UL << 25))))) || (_assert("PyList_Check(op)","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/listobject.h",44),0)), ((PyListObject*)((op))));
    (void) ((!!(0 <= index)) || (_assert("0 <= index","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/listobject.h",45),0));
    (void) ((!!(index < list->allocated)) || (_assert("index < list->allocated","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/listobject.h",46),0));
    list->ob_item[index] = value;
}

__attribute__((dllimport)) int PyList_Extend(PyObject *self, PyObject *iterable);
__attribute__((dllimport)) int PyList_Clear(PyObject *self);
# 15 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/dictobject.h"
extern __attribute__((dllimport)) PyTypeObject PyDict_Type;

__attribute__((dllimport)) PyObject * PyDict_New(void);
__attribute__((dllimport)) PyObject * PyDict_GetItem(PyObject *mp, PyObject *key);
__attribute__((dllimport)) PyObject * PyDict_GetItemWithError(PyObject *mp, PyObject *key);
__attribute__((dllimport)) int PyDict_SetItem(PyObject *mp, PyObject *key, PyObject *item);
__attribute__((dllimport)) int PyDict_DelItem(PyObject *mp, PyObject *key);
__attribute__((dllimport)) void PyDict_Clear(PyObject *mp);
__attribute__((dllimport)) int PyDict_Next(
    PyObject *mp, Py_ssize_t *pos, PyObject **key, PyObject **value);
__attribute__((dllimport)) PyObject * PyDict_Keys(PyObject *mp);
__attribute__((dllimport)) PyObject * PyDict_Values(PyObject *mp);
__attribute__((dllimport)) PyObject * PyDict_Items(PyObject *mp);
__attribute__((dllimport)) Py_ssize_t PyDict_Size(PyObject *mp);
__attribute__((dllimport)) PyObject * PyDict_Copy(PyObject *mp);
__attribute__((dllimport)) int PyDict_Contains(PyObject *mp, PyObject *key);

__attribute__((dllimport)) int PyDict_Update(PyObject *mp, PyObject *other);

__attribute__((dllimport)) int PyDict_Merge(PyObject *mp,
                             PyObject *other,
                             int override);

__attribute__((dllimport)) int PyDict_MergeFromSeq2(PyObject *d,
                                     PyObject *seq2,
                                     int override);

__attribute__((dllimport)) PyObject * PyDict_GetItemString(PyObject *dp, const char *key);
__attribute__((dllimport)) int PyDict_SetItemString(PyObject *dp, const char *key, PyObject *item);
__attribute__((dllimport)) int PyDict_DelItemString(PyObject *dp, const char *key);

__attribute__((dllimport)) int PyDict_GetItemRef(PyObject *mp, PyObject *key, PyObject **result);
__attribute__((dllimport)) int PyDict_GetItemStringRef(PyObject *mp, const char *key, PyObject **result);

__attribute__((dllimport)) PyObject * PyObject_GenericGetDict(PyObject *, void *);

extern __attribute__((dllimport)) PyTypeObject PyDictKeys_Type;
extern __attribute__((dllimport)) PyTypeObject PyDictValues_Type;
extern __attribute__((dllimport)) PyTypeObject PyDictItems_Type;
# 90 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/dictobject.h"
extern __attribute__((dllimport)) PyTypeObject PyDictIterKey_Type;
extern __attribute__((dllimport)) PyTypeObject PyDictIterValue_Type;
extern __attribute__((dllimport)) PyTypeObject PyDictIterItem_Type;

extern __attribute__((dllimport)) PyTypeObject PyDictRevIterKey_Type;
extern __attribute__((dllimport)) PyTypeObject PyDictRevIterItem_Type;
extern __attribute__((dllimport)) PyTypeObject PyDictRevIterValue_Type;

typedef struct _dictkeysobject PyDictKeysObject;
typedef struct _dictvalues PyDictValues;

typedef struct {
    PyObject ob_base;
    Py_ssize_t ma_used;
    uint64_t _ma_watcher_tag;
    PyDictKeysObject *ma_keys;
    PyDictValues *ma_values;
} PyDictObject;

__attribute__((dllimport)) PyObject * _PyDict_GetItem_KnownHash(PyObject *mp, PyObject *key,
                                                 Py_hash_t hash);

__attribute__((__deprecated__)) __attribute__((dllimport)) PyObject * _PyDict_GetItemStringWithError(PyObject *, const char *);
__attribute__((dllimport)) PyObject * PyDict_SetDefault(
    PyObject *mp, PyObject *key, PyObject *defaultobj);
# 50 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/dictobject.h"
__attribute__((dllimport)) int PyDict_SetDefaultRef(PyObject *mp, PyObject *key, PyObject *default_value, PyObject **result);

static inline Py_ssize_t PyDict_GET_SIZE(PyObject *op) {
    PyDictObject *mp;
    (void) ((!!(PyType_HasFeature((_Py_TYPE(((PyObject*)((op))))), ((1UL << 29))))) || (_assert("PyDict_Check(op)","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/dictobject.h",55),0));
    mp = ((PyDictObject*)(op));
    return mp->ma_used;
}

__attribute__((dllimport)) int PyDict_ContainsString(PyObject *mp, const char *key);

__attribute__((dllimport)) PyObject * _PyDict_NewPresized(Py_ssize_t minused);

__attribute__((dllimport)) int PyDict_Pop(PyObject *dict, PyObject *key, PyObject **result);
__attribute__((dllimport)) int PyDict_PopString(PyObject *dict, const char *key, PyObject **result);

__attribute__((__deprecated__)) __attribute__((dllimport)) PyObject * _PyDict_Pop(
    PyObject *dict,
    PyObject *key,
    PyObject *default_value);
# 88 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/dictobject.h"
typedef enum {
    PyDict_EVENT_ADDED, PyDict_EVENT_MODIFIED, PyDict_EVENT_DELETED, PyDict_EVENT_CLONED, PyDict_EVENT_CLEARED, PyDict_EVENT_DEALLOCATED,
} PyDict_WatchEvent;

typedef int(*PyDict_WatchCallback)(PyDict_WatchEvent event, PyObject* dict, PyObject* key, PyObject* new_value);

__attribute__((dllimport)) int PyDict_AddWatcher(PyDict_WatchCallback callback);
__attribute__((dllimport)) int PyDict_ClearWatcher(int watcher_id);

__attribute__((dllimport)) int PyDict_Watch(int watcher_id, PyObject* dict);
__attribute__((dllimport)) int PyDict_Unwatch(int watcher_id, PyObject* dict);
# 13 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/odictobject.h"
typedef struct _odictobject PyODictObject;

extern __attribute__((dllimport)) PyTypeObject PyODict_Type;
extern __attribute__((dllimport)) PyTypeObject PyODictIter_Type;
extern __attribute__((dllimport)) PyTypeObject PyODictKeys_Type;
extern __attribute__((dllimport)) PyTypeObject PyODictItems_Type;
extern __attribute__((dllimport)) PyTypeObject PyODictValues_Type;

__attribute__((dllimport)) PyObject * PyODict_New(void);
__attribute__((dllimport)) int PyODict_SetItem(PyObject *od, PyObject *key, PyObject *item);
__attribute__((dllimport)) int PyODict_DelItem(PyObject *od, PyObject *key);
# 10 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/enumobject.h"
extern __attribute__((dllimport)) PyTypeObject PyEnum_Type;
extern __attribute__((dllimport)) PyTypeObject PyReversed_Type;

extern __attribute__((dllimport)) PyTypeObject PySet_Type;
extern __attribute__((dllimport)) PyTypeObject PyFrozenSet_Type;
extern __attribute__((dllimport)) PyTypeObject PySetIter_Type;

__attribute__((dllimport)) PyObject * PySet_New(PyObject *);
__attribute__((dllimport)) PyObject * PyFrozenSet_New(PyObject *);

__attribute__((dllimport)) int PySet_Add(PyObject *set, PyObject *key);
__attribute__((dllimport)) int PySet_Clear(PyObject *set);
__attribute__((dllimport)) int PySet_Contains(PyObject *anyset, PyObject *key);
__attribute__((dllimport)) int PySet_Discard(PyObject *set, PyObject *key);
__attribute__((dllimport)) PyObject * PySet_Pop(PyObject *set);
__attribute__((dllimport)) Py_ssize_t PySet_Size(PyObject *anyset);
# 20 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/setobject.h"
typedef struct {
    PyObject *key;
    Py_hash_t hash;
} setentry;
# 36 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/setobject.h"
typedef struct {
    PyObject ob_base;
    Py_ssize_t fill;
    Py_ssize_t used;
    Py_ssize_t mask;
    setentry *table;
    Py_hash_t hash;
    Py_ssize_t finger;
    setentry smalltable[8];
    PyObject *weakreflist;
} PySetObject;

static inline Py_ssize_t PySet_GET_SIZE(PyObject *so) {
    return ((void) ((!!((Py_IS_TYPE(((PyObject*)(((so)))), (&PySet_Type)) || Py_IS_TYPE(((PyObject*)(((so)))), (&PyFrozenSet_Type)) || PyType_IsSubtype(_Py_TYPE(((PyObject*)((so)))), &PySet_Type) || PyType_IsSubtype(_Py_TYPE(((PyObject*)((so)))), &PyFrozenSet_Type)))) || (_assert("PyAnySet_Check(so)","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/setobject.h",68),0)), ((PySetObject*)(so)))->used;
}
# 14 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/methodobject.h"
extern __attribute__((dllimport)) PyTypeObject PyCFunction_Type;

typedef PyObject *(*PyCFunction)(PyObject *, PyObject *);
typedef PyObject *(*PyCFunctionFast) (PyObject *, PyObject *const *, Py_ssize_t);
typedef PyObject *(*PyCFunctionWithKeywords)(PyObject *, PyObject *,
                                             PyObject *);
typedef PyObject *(*PyCFunctionFastWithKeywords) (PyObject *,
                                                  PyObject *const *, Py_ssize_t,
                                                  PyObject *);
typedef PyObject *(*PyCMethod)(PyObject *, PyTypeObject *, PyObject *const *,
                               Py_ssize_t, PyObject *);

typedef PyCFunctionFast _PyCFunctionFast;
typedef PyCFunctionFastWithKeywords _PyCFunctionFastWithKeywords;
# 64 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/methodobject.h"
__attribute__((dllimport)) PyCFunction PyCFunction_GetFunction(PyObject *);
__attribute__((dllimport)) PyObject * PyCFunction_GetSelf(PyObject *);
__attribute__((dllimport)) int PyCFunction_GetFlags(PyObject *);

struct PyMethodDef {
    const char *ml_name;
    PyCFunction ml_meth;
    int ml_flags;
    const char *ml_doc;
};

__attribute__((dllimport)) PyObject * PyCFunction_New(PyMethodDef *, PyObject *);

__attribute__((dllimport)) PyObject * PyCFunction_NewEx(PyMethodDef *, PyObject *,
                                         PyObject *);

__attribute__((dllimport)) PyObject * PyCMethod_New(PyMethodDef *, PyObject *,
                                     PyObject *, PyTypeObject *);

typedef struct {
    PyObject ob_base;
    PyMethodDef *m_ml;
    PyObject *m_self;
    PyObject *m_module;
    PyObject *m_weakreflist;
    vectorcallfunc vectorcall;
} PyCFunctionObject;
# 23 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/methodobject.h"
typedef struct {
    PyCFunctionObject func;
    PyTypeObject *mm_class;
} PyCMethodObject;

extern __attribute__((dllimport)) PyTypeObject PyCMethod_Type;

static inline PyCFunction PyCFunction_GET_FUNCTION(PyObject *func) {
    return ((void) ((!!(PyObject_TypeCheck(((PyObject*)(((func)))), (&PyCFunction_Type)))) || (_assert("PyCFunction_Check(func)","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/methodobject.h",41),0)), ((PyCFunctionObject*)((func))))->m_ml->ml_meth;
}

static inline PyObject* PyCFunction_GET_SELF(PyObject *func_obj) {
    PyCFunctionObject *func = ((void) ((!!(PyObject_TypeCheck(((PyObject*)(((func_obj)))), (&PyCFunction_Type)))) || (_assert("PyCFunction_Check(func_obj)","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/methodobject.h",46),0)), ((PyCFunctionObject*)((func_obj))));
    if (func->m_ml->ml_flags & 0x0020) {
        return ((void *)0);
    }
    return func->m_self;
}

static inline int PyCFunction_GET_FLAGS(PyObject *func) {
    return ((void) ((!!(PyObject_TypeCheck(((PyObject*)(((func)))), (&PyCFunction_Type)))) || (_assert("PyCFunction_Check(func)","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/methodobject.h",55),0)), ((PyCFunctionObject*)((func))))->m_ml->ml_flags;
}

static inline PyTypeObject* PyCFunction_GET_CLASS(PyObject *func_obj) {
    PyCFunctionObject *func = ((void) ((!!(PyObject_TypeCheck(((PyObject*)(((func_obj)))), (&PyCFunction_Type)))) || (_assert("PyCFunction_Check(func_obj)","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/methodobject.h",60),0)), ((PyCFunctionObject*)((func_obj))));
    if (func->m_ml->ml_flags & 0x0200) {
        return ((void) ((!!(PyObject_TypeCheck(((PyObject*)(((func)))), (&PyCMethod_Type)))) || (_assert("PyCMethod_Check(func)","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/methodobject.h",62),0)), ((PyCMethodObject*)((func))))->mm_class;
    }
    return ((void *)0);
}
# 10 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/moduleobject.h"
extern __attribute__((dllimport)) PyTypeObject PyModule_Type;

__attribute__((dllimport)) PyObject * PyModule_NewObject(
    PyObject *name
    );

__attribute__((dllimport)) PyObject * PyModule_New(
    const char *name
    );
__attribute__((dllimport)) PyObject * PyModule_GetDict(PyObject *);

__attribute__((dllimport)) PyObject * PyModule_GetNameObject(PyObject *);

__attribute__((dllimport)) const char * PyModule_GetName(PyObject *);
__attribute__((__deprecated__)) __attribute__((dllimport)) const char * PyModule_GetFilename(PyObject *);
__attribute__((dllimport)) PyObject * PyModule_GetFilenameObject(PyObject *);
__attribute__((dllimport)) PyModuleDef* PyModule_GetDef(PyObject*);
__attribute__((dllimport)) void* PyModule_GetState(PyObject*);

__attribute__((dllimport)) PyObject * PyModuleDef_Init(PyModuleDef*);
extern __attribute__((dllimport)) PyTypeObject PyModuleDef_Type;

typedef struct PyModuleDef_Base {
  PyObject ob_base;
  PyObject* (*m_init)(void);
  Py_ssize_t m_index;
  PyObject* m_copy;
} PyModuleDef_Base;
# 69 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/moduleobject.h"
struct PyModuleDef_Slot {
    int slot;
    void *value;
};
# 107 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/moduleobject.h"
struct PyModuleDef {
  PyModuleDef_Base m_base;
  const char* m_name;
  const char* m_doc;
  Py_ssize_t m_size;
  PyMethodDef *m_methods;
  PyModuleDef_Slot *m_slots;
  traverseproc m_traverse;
  inquiry m_clear;
  freefunc m_free;
};
# 39 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/monitoring.h"
typedef struct _PyMonitoringState {
    uint8_t active;
    uint8_t opaque;
} PyMonitoringState;

__attribute__((dllimport)) int
PyMonitoring_EnterScope(PyMonitoringState *state_array, uint64_t *version,
                         const uint8_t *event_types, Py_ssize_t length);

__attribute__((dllimport)) int
PyMonitoring_ExitScope(void);

__attribute__((dllimport)) int
_PyMonitoring_FirePyStartEvent(PyMonitoringState *state, PyObject *codelike, int32_t offset);

__attribute__((dllimport)) int
_PyMonitoring_FirePyResumeEvent(PyMonitoringState *state, PyObject *codelike, int32_t offset);

__attribute__((dllimport)) int
_PyMonitoring_FirePyReturnEvent(PyMonitoringState *state, PyObject *codelike, int32_t offset,
                                PyObject *retval);

__attribute__((dllimport)) int
_PyMonitoring_FirePyYieldEvent(PyMonitoringState *state, PyObject *codelike, int32_t offset,
                               PyObject *retval);

__attribute__((dllimport)) int
_PyMonitoring_FireCallEvent(PyMonitoringState *state, PyObject *codelike, int32_t offset,
                            PyObject* callable, PyObject *arg0);

__attribute__((dllimport)) int
_PyMonitoring_FireLineEvent(PyMonitoringState *state, PyObject *codelike, int32_t offset,
                            int lineno);

__attribute__((dllimport)) int
_PyMonitoring_FireJumpEvent(PyMonitoringState *state, PyObject *codelike, int32_t offset,
                            PyObject *target_offset);

__attribute__((__deprecated__)) __attribute__((dllimport)) int
_PyMonitoring_FireBranchEvent(PyMonitoringState *state, PyObject *codelike, int32_t offset,
                              PyObject *target_offset);

__attribute__((dllimport)) int
_PyMonitoring_FireBranchRightEvent(PyMonitoringState *state, PyObject *codelike, int32_t offset,
                              PyObject *target_offset);

__attribute__((dllimport)) int
_PyMonitoring_FireBranchLeftEvent(PyMonitoringState *state, PyObject *codelike, int32_t offset,
                              PyObject *target_offset);

__attribute__((dllimport)) int
_PyMonitoring_FireCReturnEvent(PyMonitoringState *state, PyObject *codelike, int32_t offset,
                               PyObject *retval);

__attribute__((dllimport)) int
_PyMonitoring_FirePyThrowEvent(PyMonitoringState *state, PyObject *codelike, int32_t offset);

__attribute__((dllimport)) int
_PyMonitoring_FireRaiseEvent(PyMonitoringState *state, PyObject *codelike, int32_t offset);

__attribute__((dllimport)) int
_PyMonitoring_FireReraiseEvent(PyMonitoringState *state, PyObject *codelike, int32_t offset);

__attribute__((dllimport)) int
_PyMonitoring_FireExceptionHandledEvent(PyMonitoringState *state, PyObject *codelike, int32_t offset);

__attribute__((dllimport)) int
_PyMonitoring_FireCRaiseEvent(PyMonitoringState *state, PyObject *codelike, int32_t offset);

__attribute__((dllimport)) int
_PyMonitoring_FirePyUnwindEvent(PyMonitoringState *state, PyObject *codelike, int32_t offset);

__attribute__((dllimport)) int
_PyMonitoring_FireStopIterationEvent(PyMonitoringState *state, PyObject *codelike, int32_t offset, PyObject *value);
# 125 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/monitoring.h"
static inline int
PyMonitoring_FirePyStartEvent(PyMonitoringState *state, PyObject *codelike, int32_t offset)
{
    if ((state)->active) { return (_PyMonitoring_FirePyStartEvent(state, codelike, offset)); } else { return 0; };
}

static inline int
PyMonitoring_FirePyResumeEvent(PyMonitoringState *state, PyObject *codelike, int32_t offset)
{
    if ((state)->active) { return (_PyMonitoring_FirePyResumeEvent(state, codelike, offset)); } else { return 0; };
}

static inline int
PyMonitoring_FirePyReturnEvent(PyMonitoringState *state, PyObject *codelike, int32_t offset,
                               PyObject *retval)
{
    if ((state)->active) { return (_PyMonitoring_FirePyReturnEvent(state, codelike, offset, retval)); } else { return 0; };
}

static inline int
PyMonitoring_FirePyYieldEvent(PyMonitoringState *state, PyObject *codelike, int32_t offset,
                              PyObject *retval)
{
    if ((state)->active) { return (_PyMonitoring_FirePyYieldEvent(state, codelike, offset, retval)); } else { return 0; };
}

static inline int
PyMonitoring_FireCallEvent(PyMonitoringState *state, PyObject *codelike, int32_t offset,
                           PyObject* callable, PyObject *arg0)
{
    if ((state)->active) { return (_PyMonitoring_FireCallEvent(state, codelike, offset, callable, arg0)); } else { return 0; };
}

static inline int
PyMonitoring_FireLineEvent(PyMonitoringState *state, PyObject *codelike, int32_t offset,
                           int lineno)
{
    if ((state)->active) { return (_PyMonitoring_FireLineEvent(state, codelike, offset, lineno)); } else { return 0; };
}

static inline int
PyMonitoring_FireJumpEvent(PyMonitoringState *state, PyObject *codelike, int32_t offset,
                           PyObject *target_offset)
{
    if ((state)->active) { return (_PyMonitoring_FireJumpEvent(state, codelike, offset, target_offset)); } else { return 0; };
}

static inline int
PyMonitoring_FireBranchRightEvent(PyMonitoringState *state, PyObject *codelike, int32_t offset,
                             PyObject *target_offset)
{
    if ((state)->active) { return (_PyMonitoring_FireBranchRightEvent(state, codelike, offset, target_offset)); } else { return 0; };
}

static inline int
PyMonitoring_FireBranchLeftEvent(PyMonitoringState *state, PyObject *codelike, int32_t offset,
                             PyObject *target_offset)
{
    if ((state)->active) { return (_PyMonitoring_FireBranchLeftEvent(state, codelike, offset, target_offset)); } else { return 0; };
}

static inline int
PyMonitoring_FireCReturnEvent(PyMonitoringState *state, PyObject *codelike, int32_t offset,
                              PyObject *retval)
{
    if ((state)->active) { return (_PyMonitoring_FireCReturnEvent(state, codelike, offset, retval)); } else { return 0; };
}

static inline int
PyMonitoring_FirePyThrowEvent(PyMonitoringState *state, PyObject *codelike, int32_t offset)
{
    if ((state)->active) { return (_PyMonitoring_FirePyThrowEvent(state, codelike, offset)); } else { return 0; };
}

static inline int
PyMonitoring_FireRaiseEvent(PyMonitoringState *state, PyObject *codelike, int32_t offset)
{
    if ((state)->active) { return (_PyMonitoring_FireRaiseEvent(state, codelike, offset)); } else { return 0; };
}

static inline int
PyMonitoring_FireReraiseEvent(PyMonitoringState *state, PyObject *codelike, int32_t offset)
{
    if ((state)->active) { return (_PyMonitoring_FireReraiseEvent(state, codelike, offset)); } else { return 0; };
}

static inline int
PyMonitoring_FireExceptionHandledEvent(PyMonitoringState *state, PyObject *codelike, int32_t offset)
{
    if ((state)->active) { return (_PyMonitoring_FireExceptionHandledEvent(state, codelike, offset)); } else { return 0; };
}

static inline int
PyMonitoring_FireCRaiseEvent(PyMonitoringState *state, PyObject *codelike, int32_t offset)
{
    if ((state)->active) { return (_PyMonitoring_FireCRaiseEvent(state, codelike, offset)); } else { return 0; };
}

static inline int
PyMonitoring_FirePyUnwindEvent(PyMonitoringState *state, PyObject *codelike, int32_t offset)
{
    if ((state)->active) { return (_PyMonitoring_FirePyUnwindEvent(state, codelike, offset)); } else { return 0; };
}

static inline int
PyMonitoring_FireStopIterationEvent(PyMonitoringState *state, PyObject *codelike, int32_t offset, PyObject *value)
{
    if ((state)->active) { return (_PyMonitoring_FireStopIterationEvent(state, codelike, offset, value)); } else { return 0; };
}
# 21 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/funcobject.h"
typedef struct {
    PyObject *fc_globals; PyObject *fc_builtins; PyObject *fc_name; PyObject *fc_qualname; PyObject *fc_code; PyObject *fc_defaults; PyObject *fc_kwdefaults; PyObject *fc_closure;
} PyFrameConstructor;
# 36 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/funcobject.h"
typedef struct {
    PyObject ob_base;
    PyObject *func_globals; PyObject *func_builtins; PyObject *func_name; PyObject *func_qualname; PyObject *func_code; PyObject *func_defaults; PyObject *func_kwdefaults; PyObject *func_closure;
    PyObject *func_doc;
    PyObject *func_dict;
    PyObject *func_weakreflist;
    PyObject *func_module;
    PyObject *func_annotations;
    PyObject *func_annotate;
    PyObject *func_typeparams;
    vectorcallfunc vectorcall;
    uint32_t func_version;
} PyFunctionObject;

extern __attribute__((dllimport)) PyTypeObject PyFunction_Type;

__attribute__((dllimport)) PyObject * PyFunction_New(PyObject *, PyObject *);
__attribute__((dllimport)) PyObject * PyFunction_NewWithQualName(PyObject *, PyObject *, PyObject *);
__attribute__((dllimport)) PyObject * PyFunction_GetCode(PyObject *);
__attribute__((dllimport)) PyObject * PyFunction_GetGlobals(PyObject *);
__attribute__((dllimport)) PyObject * PyFunction_GetModule(PyObject *);
__attribute__((dllimport)) PyObject * PyFunction_GetDefaults(PyObject *);
__attribute__((dllimport)) int PyFunction_SetDefaults(PyObject *, PyObject *);
__attribute__((dllimport)) void PyFunction_SetVectorcall(PyFunctionObject *, vectorcallfunc);
__attribute__((dllimport)) PyObject * PyFunction_GetKwDefaults(PyObject *);
__attribute__((dllimport)) int PyFunction_SetKwDefaults(PyObject *, PyObject *);
__attribute__((dllimport)) PyObject * PyFunction_GetClosure(PyObject *);
__attribute__((dllimport)) int PyFunction_SetClosure(PyObject *, PyObject *);
__attribute__((dllimport)) PyObject * PyFunction_GetAnnotations(PyObject *);
__attribute__((dllimport)) int PyFunction_SetAnnotations(PyObject *, PyObject *);

static inline PyObject* PyFunction_GET_CODE(PyObject *func) {
    return ((void) ((!!(Py_IS_TYPE(((PyObject*)(((func)))), (&PyFunction_Type)))) || (_assert("PyFunction_Check(func)","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/funcobject.h",91),0)), ((PyFunctionObject*)(func)))->func_code;
}

static inline PyObject* PyFunction_GET_GLOBALS(PyObject *func) {
    return ((void) ((!!(Py_IS_TYPE(((PyObject*)(((func)))), (&PyFunction_Type)))) || (_assert("PyFunction_Check(func)","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/funcobject.h",96),0)), ((PyFunctionObject*)(func)))->func_globals;
}

static inline PyObject* PyFunction_GET_MODULE(PyObject *func) {
    return ((void) ((!!(Py_IS_TYPE(((PyObject*)(((func)))), (&PyFunction_Type)))) || (_assert("PyFunction_Check(func)","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/funcobject.h",101),0)), ((PyFunctionObject*)(func)))->func_module;
}

static inline PyObject* PyFunction_GET_DEFAULTS(PyObject *func) {
    return ((void) ((!!(Py_IS_TYPE(((PyObject*)(((func)))), (&PyFunction_Type)))) || (_assert("PyFunction_Check(func)","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/funcobject.h",106),0)), ((PyFunctionObject*)(func)))->func_defaults;
}

static inline PyObject* PyFunction_GET_KW_DEFAULTS(PyObject *func) {
    return ((void) ((!!(Py_IS_TYPE(((PyObject*)(((func)))), (&PyFunction_Type)))) || (_assert("PyFunction_Check(func)","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/funcobject.h",111),0)), ((PyFunctionObject*)(func)))->func_kwdefaults;
}

static inline PyObject* PyFunction_GET_CLOSURE(PyObject *func) {
    return ((void) ((!!(Py_IS_TYPE(((PyObject*)(((func)))), (&PyFunction_Type)))) || (_assert("PyFunction_Check(func)","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/funcobject.h",116),0)), ((PyFunctionObject*)(func)))->func_closure;
}

static inline PyObject* PyFunction_GET_ANNOTATIONS(PyObject *func) {
    return ((void) ((!!(Py_IS_TYPE(((PyObject*)(((func)))), (&PyFunction_Type)))) || (_assert("PyFunction_Check(func)","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/funcobject.h",121),0)), ((PyFunctionObject*)(func)))->func_annotations;
}

extern __attribute__((dllimport)) PyTypeObject PyClassMethod_Type;
extern __attribute__((dllimport)) PyTypeObject PyStaticMethod_Type;

__attribute__((dllimport)) PyObject * PyClassMethod_New(PyObject *);
__attribute__((dllimport)) PyObject * PyStaticMethod_New(PyObject *);
# 139 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/funcobject.h"
typedef enum {
    PyFunction_EVENT_CREATE, PyFunction_EVENT_DESTROY, PyFunction_EVENT_MODIFY_CODE, PyFunction_EVENT_MODIFY_DEFAULTS, PyFunction_EVENT_MODIFY_KWDEFAULTS,
} PyFunction_WatchEvent;
# 160 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/funcobject.h"
typedef int (*PyFunction_WatchCallback)(
  PyFunction_WatchEvent event,
  PyFunctionObject *func,
  PyObject *new_value);
# 172 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/funcobject.h"
__attribute__((dllimport)) int PyFunction_AddWatcher(PyFunction_WatchCallback callback);

__attribute__((dllimport)) int PyFunction_ClearWatcher(int watcher_id);
# 12 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/classobject.h"
typedef struct {
    PyObject ob_base;
    PyObject *im_func;
    PyObject *im_self;
    PyObject *im_weakreflist;
    vectorcallfunc vectorcall;
} PyMethodObject;

extern __attribute__((dllimport)) PyTypeObject PyMethod_Type;

__attribute__((dllimport)) PyObject * PyMethod_New(PyObject *, PyObject *);

__attribute__((dllimport)) PyObject * PyMethod_Function(PyObject *);
__attribute__((dllimport)) PyObject * PyMethod_Self(PyObject *);

static inline PyObject* PyMethod_GET_FUNCTION(PyObject *meth) {
    return ((void) ((!!(Py_IS_TYPE(((PyObject*)(((meth)))), (&PyMethod_Type)))) || (_assert("PyMethod_Check(meth)","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/classobject.h",35),0)), ((PyMethodObject*)(meth)))->im_func;
}

static inline PyObject* PyMethod_GET_SELF(PyObject *meth) {
    return ((void) ((!!(Py_IS_TYPE(((PyObject*)(((meth)))), (&PyMethod_Type)))) || (_assert("PyMethod_Check(meth)","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/classobject.h",40),0)), ((PyMethodObject*)(meth)))->im_self;
}

typedef struct {
    PyObject ob_base;
    PyObject *func;
} PyInstanceMethodObject;

extern __attribute__((dllimport)) PyTypeObject PyInstanceMethod_Type;

__attribute__((dllimport)) PyObject * PyInstanceMethod_New(PyObject *);
__attribute__((dllimport)) PyObject * PyInstanceMethod_Function(PyObject *);

static inline PyObject* PyInstanceMethod_GET_FUNCTION(PyObject *meth) {
    return ((void) ((!!(Py_IS_TYPE(((PyObject*)(((meth)))), (&PyInstanceMethod_Type)))) || (_assert("PyInstanceMethod_Check(meth)","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/classobject.h",63),0)), ((PyInstanceMethodObject*)(meth)))->func;
}
# 11 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/fileobject.h"
__attribute__((dllimport)) PyObject * PyFile_FromFd(int, const char *, const char *, int,
                                     const char *, const char *,
                                     const char *, int);
__attribute__((dllimport)) PyObject * PyFile_GetLine(PyObject *, int);
__attribute__((dllimport)) int PyFile_WriteObject(PyObject *, PyObject *, int);
__attribute__((dllimport)) int PyFile_WriteString(const char *, PyObject *);
__attribute__((dllimport)) int PyObject_AsFileDescriptor(PyObject *);

__attribute__((__deprecated__)) extern __attribute__((dllimport)) const char * Py_FileSystemDefaultEncoding;

__attribute__((__deprecated__)) extern __attribute__((dllimport)) const char * Py_FileSystemDefaultEncodeErrors;

__attribute__((__deprecated__)) extern __attribute__((dllimport)) int Py_HasFileSystemDefaultEncoding;

__attribute__((__deprecated__)) extern __attribute__((dllimport)) int Py_UTF8Mode;

__attribute__((dllimport)) char * Py_UniversalNewlineFgets(char *, int, FILE*, PyObject *);

__attribute__((dllimport)) PyObject * PyFile_NewStdPrinter(int);
extern __attribute__((dllimport)) PyTypeObject PyStdPrinter_Type;

typedef PyObject * (*Py_OpenCodeHookFunction)(PyObject *, void *);

__attribute__((dllimport)) PyObject * PyFile_OpenCode(const char *utf8path);
__attribute__((dllimport)) PyObject * PyFile_OpenCodeObject(PyObject *path);
__attribute__((dllimport)) int PyFile_SetOpenCodeHook(Py_OpenCodeHookFunction hook, void *userData);
# 21 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/pycapsule.h"
extern __attribute__((dllimport)) PyTypeObject PyCapsule_Type;

typedef void (*PyCapsule_Destructor)(PyObject *);

__attribute__((dllimport)) PyObject * PyCapsule_New(
    void *pointer,
    const char *name,
    PyCapsule_Destructor destructor);

__attribute__((dllimport)) void * PyCapsule_GetPointer(PyObject *capsule, const char *name);

__attribute__((dllimport)) PyCapsule_Destructor PyCapsule_GetDestructor(PyObject *capsule);

__attribute__((dllimport)) const char * PyCapsule_GetName(PyObject *capsule);

__attribute__((dllimport)) void * PyCapsule_GetContext(PyObject *capsule);

__attribute__((dllimport)) int PyCapsule_IsValid(PyObject *capsule, const char *name);

__attribute__((dllimport)) int PyCapsule_SetPointer(PyObject *capsule, void *pointer);

__attribute__((dllimport)) int PyCapsule_SetDestructor(PyObject *capsule, PyCapsule_Destructor destructor);

__attribute__((dllimport)) int PyCapsule_SetName(PyObject *capsule, const char *name);

__attribute__((dllimport)) int PyCapsule_SetContext(PyObject *capsule, void *context);

__attribute__((dllimport)) void * PyCapsule_Import(
    const char *name,
    int no_block);
# 11 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/code.h"
typedef struct {
    PyObject *_co_code;
    PyObject *_co_varnames;
    PyObject *_co_cellvars;
    PyObject *_co_freevars;
} _PyCoCached;

typedef struct {
    int size;
    int capacity;
    struct _PyExecutorObject *executors[1];
} _PyExecutorArray;
# 115 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/code.h"
struct PyCodeObject { PyVarObject ob_base; PyObject *co_consts; PyObject *co_names; PyObject *co_exceptiontable; int co_flags; int co_argcount; int co_posonlyargcount; int co_kwonlyargcount; int co_stacksize; int co_firstlineno; int co_nlocalsplus; int co_framesize; int co_nlocals; int co_ncellvars; int co_nfreevars; uint32_t co_version; PyObject *co_localsplusnames; PyObject *co_localspluskinds; PyObject *co_filename; PyObject *co_name; PyObject *co_qualname; PyObject *co_linetable; PyObject *co_weakreflist; _PyExecutorArray *co_executors; _PyCoCached *_co_cached; uintptr_t _co_instrumentation_version; struct _PyCoMonitoringData *_co_monitoring; Py_ssize_t _co_unique_id; int _co_firsttraceable; void *co_extra; char co_code_adaptive[(1)]; };
# 162 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/code.h"
extern __attribute__((dllimport)) PyTypeObject PyCode_Type;

static inline Py_ssize_t PyCode_GetNumFree(PyCodeObject *op) {
    (void) ((!!(Py_IS_TYPE(((PyObject*)(((op)))), (&PyCode_Type)))) || (_assert("PyCode_Check(op)","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/code.h",167),0));
    return op->co_nfreevars;
}

static inline int PyUnstable_Code_GetFirstFree(PyCodeObject *op) {
    (void) ((!!(Py_IS_TYPE(((PyObject*)(((op)))), (&PyCode_Type)))) || (_assert("PyCode_Check(op)","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/code.h",172),0));
    return op->co_nlocalsplus - op->co_nfreevars;
}

__attribute__((__deprecated__)) static inline int PyCode_GetFirstFree(PyCodeObject *op) {
    return PyUnstable_Code_GetFirstFree(op);
}

__attribute__((dllimport)) PyCodeObject * PyUnstable_Code_New(
        int, int, int, int, int, PyObject *, PyObject *,
        PyObject *, PyObject *, PyObject *, PyObject *,
        PyObject *, PyObject *, PyObject *, int, PyObject *,
        PyObject *);

__attribute__((dllimport)) PyCodeObject * PyUnstable_Code_NewWithPosOnlyArgs(
        int, int, int, int, int, int, PyObject *, PyObject *,
        PyObject *, PyObject *, PyObject *, PyObject *,
        PyObject *, PyObject *, PyObject *, int, PyObject *,
        PyObject *);

__attribute__((__deprecated__)) static inline PyCodeObject *
PyCode_New(
        int a, int b, int c, int d, int e, PyObject *f, PyObject *g,
        PyObject *h, PyObject *i, PyObject *j, PyObject *k,
        PyObject *l, PyObject *m, PyObject *n, int o, PyObject *p,
        PyObject *q)
{
    return PyUnstable_Code_New(
        a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q);
}
__attribute__((__deprecated__)) static inline PyCodeObject *
PyCode_NewWithPosOnlyArgs(
        int a, int poac, int b, int c, int d, int e, PyObject *f, PyObject *g,
        PyObject *h, PyObject *i, PyObject *j, PyObject *k,
        PyObject *l, PyObject *m, PyObject *n, int o, PyObject *p,
        PyObject *q)
{
    return PyUnstable_Code_NewWithPosOnlyArgs(
        a, poac, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q);
}

__attribute__((dllimport)) PyCodeObject *
PyCode_NewEmpty(const char *filename, const char *funcname, int firstlineno);

__attribute__((dllimport)) int PyCode_Addr2Line(PyCodeObject *, int);

__attribute__((dllimport)) int PyCode_Addr2Location(PyCodeObject *, int, int *, int *, int *, int *);

typedef enum {
    PY_CODE_EVENT_CREATE, PY_CODE_EVENT_DESTROY,
} PyCodeEvent;
# 246 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/code.h"
typedef int (*PyCode_WatchCallback)(
  PyCodeEvent event,
  PyCodeObject* co);
# 257 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/code.h"
__attribute__((dllimport)) int PyCode_AddWatcher(PyCode_WatchCallback callback);

__attribute__((dllimport)) int PyCode_ClearWatcher(int watcher_id);

struct _opaque {
    int computed_line;
    const uint8_t *lo_next;
    const uint8_t *limit;
};

typedef struct _line_offsets {
    int ar_start;
    int ar_end;
    int ar_line;
    struct _opaque opaque;
} PyCodeAddressRange;

__attribute__((dllimport)) int _PyCode_CheckLineNumber(int lasti, PyCodeAddressRange *bounds);
# 292 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/code.h"
__attribute__((dllimport)) PyObject* _PyCode_ConstantKey(PyObject *obj);

__attribute__((dllimport)) PyObject* PyCode_Optimize(PyObject *code, PyObject* consts,
                                      PyObject *names, PyObject *lnotab);

__attribute__((dllimport)) int PyUnstable_Code_GetExtra(
    PyObject *code, Py_ssize_t index, void **extra);
__attribute__((dllimport)) int PyUnstable_Code_SetExtra(
    PyObject *code, Py_ssize_t index, void *extra);

__attribute__((__deprecated__)) static inline int
_PyCode_GetExtra(PyObject *code, Py_ssize_t index, void **extra)
{
    return PyUnstable_Code_GetExtra(code, index, extra);
}
__attribute__((__deprecated__)) static inline int
_PyCode_SetExtra(PyObject *code, Py_ssize_t index, void *extra)
{
    return PyUnstable_Code_SetExtra(code, index, extra);
}

__attribute__((dllimport)) PyObject * PyCode_GetCode(PyCodeObject *code);

__attribute__((dllimport)) PyObject * PyCode_GetVarnames(PyCodeObject *code);

__attribute__((dllimport)) PyObject * PyCode_GetCellvars(PyCodeObject *code);

__attribute__((dllimport)) PyObject * PyCode_GetFreevars(PyCodeObject *code);

typedef enum _PyCodeLocationInfoKind {
    PY_CODE_LOCATION_INFO_SHORT0 = 0,
    PY_CODE_LOCATION_INFO_ONE_LINE0 = 10,
    PY_CODE_LOCATION_INFO_ONE_LINE1 = 11,
    PY_CODE_LOCATION_INFO_ONE_LINE2 = 12,
    PY_CODE_LOCATION_INFO_NO_COLUMNS = 13,
    PY_CODE_LOCATION_INFO_LONG = 14,
    PY_CODE_LOCATION_INFO_NONE = 15
} _PyCodeLocationInfoKind;
# 13 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/pyframe.h"
__attribute__((dllimport)) int PyFrame_GetLineNumber(PyFrameObject *);

__attribute__((dllimport)) PyCodeObject * PyFrame_GetCode(PyFrameObject *frame);

extern __attribute__((dllimport)) PyTypeObject PyFrame_Type;
extern __attribute__((dllimport)) PyTypeObject PyFrameLocalsProxy_Type;

__attribute__((dllimport)) PyFrameObject * PyFrame_GetBack(PyFrameObject *frame);
__attribute__((dllimport)) PyObject * PyFrame_GetLocals(PyFrameObject *frame);

__attribute__((dllimport)) PyObject * PyFrame_GetGlobals(PyFrameObject *frame);
__attribute__((dllimport)) PyObject * PyFrame_GetBuiltins(PyFrameObject *frame);

__attribute__((dllimport)) PyObject * PyFrame_GetGenerator(PyFrameObject *frame);
__attribute__((dllimport)) int PyFrame_GetLasti(PyFrameObject *frame);
__attribute__((dllimport)) PyObject* PyFrame_GetVar(PyFrameObject *frame, PyObject *name);
__attribute__((dllimport)) PyObject* PyFrame_GetVarString(PyFrameObject *frame, const char *name);

struct _PyInterpreterFrame;

__attribute__((dllimport)) PyObject * PyUnstable_InterpreterFrame_GetCode(struct _PyInterpreterFrame *frame);

__attribute__((dllimport)) int PyUnstable_InterpreterFrame_GetLasti(struct _PyInterpreterFrame *frame);

__attribute__((dllimport)) int PyUnstable_InterpreterFrame_GetLine(struct _PyInterpreterFrame *frame);

extern __attribute__((dllimport)) const PyTypeObject * const PyUnstable_ExecutableKinds[5 +1];

__attribute__((dllimport)) int PyTraceBack_Here(PyFrameObject *);
__attribute__((dllimport)) int PyTraceBack_Print(PyObject *, PyObject *);

extern __attribute__((dllimport)) PyTypeObject PyTraceBack_Type;

typedef struct _traceback PyTracebackObject;

struct _traceback {
    PyObject ob_base;
    PyTracebackObject *tb_next;
    PyFrameObject *tb_frame;
    int tb_lasti;
    int tb_lineno;
};

extern __attribute__((dllimport)) PyObject _Py_EllipsisObject;
# 26 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/sliceobject.h"
typedef struct {
    PyObject ob_base;
    PyObject *start, *stop, *step;
} PySliceObject;

extern __attribute__((dllimport)) PyTypeObject PySlice_Type;
extern __attribute__((dllimport)) PyTypeObject PyEllipsis_Type;

__attribute__((dllimport)) PyObject * PySlice_New(PyObject* start, PyObject* stop,
                                  PyObject* step);

__attribute__((dllimport)) PyObject * _PySlice_FromIndices(Py_ssize_t start, Py_ssize_t stop);
__attribute__((dllimport)) int _PySlice_GetLongIndices(PySliceObject *self, PyObject *length,
                                 PyObject **start_ptr, PyObject **stop_ptr,
                                 PyObject **step_ptr);

__attribute__((dllimport)) int PySlice_GetIndices(PyObject *r, Py_ssize_t length,
                                  Py_ssize_t *start, Py_ssize_t *stop, Py_ssize_t *step);
__attribute__((__deprecated__))
__attribute__((dllimport)) int PySlice_GetIndicesEx(PyObject *r, Py_ssize_t length,
                                     Py_ssize_t *start, Py_ssize_t *stop,
                                     Py_ssize_t *step,
                                     Py_ssize_t *slicelength);

__attribute__((dllimport)) int PySlice_Unpack(PyObject *slice,
                               Py_ssize_t *start, Py_ssize_t *stop, Py_ssize_t *step);
__attribute__((dllimport)) Py_ssize_t PySlice_AdjustIndices(Py_ssize_t length,
                                             Py_ssize_t *start, Py_ssize_t *stop,
                                             Py_ssize_t step);
# 10 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/cellobject.h"
typedef struct {
    PyObject ob_base;
    PyObject *ob_ref;
} PyCellObject;

extern __attribute__((dllimport)) PyTypeObject PyCell_Type;

__attribute__((dllimport)) PyObject * PyCell_New(PyObject *);
__attribute__((dllimport)) PyObject * PyCell_Get(PyObject *);
__attribute__((dllimport)) int PyCell_Set(PyObject *, PyObject *);

static inline PyObject* PyCell_GET(PyObject *op) {
    PyObject *res;
    PyCellObject *cell;
    (void) ((!!(Py_IS_TYPE(((PyObject*)(((op)))), (&PyCell_Type)))) || (_assert("PyCell_Check(op)","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/cellobject.h",27),0));
    cell = ((PyCellObject*)(op));
    {;
    res = cell->ob_ref;
    };
    return res;
}

static inline void PyCell_SET(PyObject *op, PyObject *value) {
    PyCellObject *cell;
    (void) ((!!(Py_IS_TYPE(((PyObject*)(((op)))), (&PyCell_Type)))) || (_assert("PyCell_Check(op)","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/cellobject.h",38),0));
    cell = ((PyCellObject*)(op));
    {;
    cell->ob_ref = value;
    };
}

extern __attribute__((dllimport)) PyTypeObject PySeqIter_Type;
extern __attribute__((dllimport)) PyTypeObject PyCallIter_Type;

__attribute__((dllimport)) PyObject * PySeqIter_New(PyObject *);

__attribute__((dllimport)) PyObject * PyCallIter_New(PyObject *, PyObject *);
# 10 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/initconfig.h"
typedef struct {
    enum {
        _PyStatus_TYPE_OK=0,
        _PyStatus_TYPE_ERROR=1,
        _PyStatus_TYPE_EXIT=2
    } _type;
    const char *func;
    const char *err_msg;
    int exitcode;
} PyStatus;

__attribute__((dllimport)) PyStatus PyStatus_Ok(void);
__attribute__((dllimport)) PyStatus PyStatus_Error(const char *err_msg);
__attribute__((dllimport)) PyStatus PyStatus_NoMemory(void);
__attribute__((dllimport)) PyStatus PyStatus_Exit(int exitcode);
__attribute__((dllimport)) int PyStatus_IsError(PyStatus err);
__attribute__((dllimport)) int PyStatus_IsExit(PyStatus err);
__attribute__((dllimport)) int PyStatus_Exception(PyStatus err);

typedef struct {
    Py_ssize_t length;
    wchar_t **items;
} PyWideStringList;

__attribute__((dllimport)) PyStatus PyWideStringList_Append(PyWideStringList *list,
    const wchar_t *item);
__attribute__((dllimport)) PyStatus PyWideStringList_Insert(PyWideStringList *list,
    Py_ssize_t index,
    const wchar_t *item);

typedef struct PyPreConfig {
    int _config_init;
    int parse_argv;
    int isolated;
    int use_environment;
    int configure_locale;
    int coerce_c_locale;
    int coerce_c_locale_warn;
    int legacy_windows_fs_encoding;
    int utf8_mode;
    int dev_mode;
    int allocator;
} PyPreConfig;

__attribute__((dllimport)) void PyPreConfig_InitPythonConfig(PyPreConfig *config);
__attribute__((dllimport)) void PyPreConfig_InitIsolatedConfig(PyPreConfig *config);

typedef struct PyConfig {
    int _config_init;
    int isolated;
    int use_environment;
    int dev_mode;
    int install_signal_handlers;
    int use_hash_seed;
    unsigned long hash_seed;
    int faulthandler;
    int tracemalloc;
    int perf_profiling;
    int remote_debug;
    int import_time;
    int code_debug_ranges;
    int show_ref_count;
    int dump_refs;
    wchar_t *dump_refs_file;
    int malloc_stats;
    wchar_t *filesystem_encoding;
    wchar_t *filesystem_errors;
    wchar_t *pycache_prefix;
    int parse_argv;
    PyWideStringList orig_argv;
    PyWideStringList argv;
    PyWideStringList xoptions;
    PyWideStringList warnoptions;
    int site_import;
    int bytes_warning;
    int warn_default_encoding;
    int inspect;
    int interactive;
    int optimization_level;
    int parser_debug;
    int write_bytecode;
    int verbose;
    int quiet;
    int user_site_directory;
    int configure_c_stdio;
    int buffered_stdio;
    wchar_t *stdio_encoding;
    wchar_t *stdio_errors;
    int legacy_windows_stdio;
    wchar_t *check_hash_pycs_mode;
    int use_frozen_modules;
    int safe_path;
    int int_max_str_digits;
    int thread_inherit_context;
    int context_aware_warnings;
    int cpu_count;
    int pathconfig_warnings;
    wchar_t *program_name;
    wchar_t *pythonpath_env;
    wchar_t *home;
    wchar_t *platlibdir;
    int module_search_paths_set;
    PyWideStringList module_search_paths;
    wchar_t *stdlib_dir;
    wchar_t *executable;
    wchar_t *base_executable;
    wchar_t *prefix;
    wchar_t *base_prefix;
    wchar_t *exec_prefix;
    wchar_t *base_exec_prefix;
    int skip_source_first_line;
    wchar_t *run_command;
    wchar_t *run_module;
    wchar_t *run_filename;
    wchar_t *sys_path_0;
    int _install_importlib;
    int _init_main;
    int _is_python_build;
} PyConfig;

__attribute__((dllimport)) void PyConfig_InitPythonConfig(PyConfig *config);
__attribute__((dllimport)) void PyConfig_InitIsolatedConfig(PyConfig *config);
__attribute__((dllimport)) void PyConfig_Clear(PyConfig *);
__attribute__((dllimport)) PyStatus PyConfig_SetString(
    PyConfig *config,
    wchar_t **config_str,
    const wchar_t *str);
__attribute__((dllimport)) PyStatus PyConfig_SetBytesString(
    PyConfig *config,
    wchar_t **config_str,
    const char *str);
__attribute__((dllimport)) PyStatus PyConfig_Read(PyConfig *config);
__attribute__((dllimport)) PyStatus PyConfig_SetBytesArgv(
    PyConfig *config,
    Py_ssize_t argc,
    char * const *argv);
__attribute__((dllimport)) PyStatus PyConfig_SetArgv(PyConfig *config,
    Py_ssize_t argc,
    wchar_t * const *argv);
__attribute__((dllimport)) PyStatus PyConfig_SetWideStringList(PyConfig *config,
    PyWideStringList *list,
    Py_ssize_t length, wchar_t **items);

__attribute__((dllimport)) PyObject* PyConfig_Get(const char *name);
__attribute__((dllimport)) int PyConfig_GetInt(const char *name, int *value);
__attribute__((dllimport)) PyObject* PyConfig_Names(void);
__attribute__((dllimport)) int PyConfig_Set(const char *name, PyObject *value);

__attribute__((dllimport)) void Py_GetArgcArgv(int *argc, wchar_t ***argv);

typedef struct PyInitConfig PyInitConfig;

__attribute__((dllimport)) PyInitConfig* PyInitConfig_Create(void);
__attribute__((dllimport)) void PyInitConfig_Free(PyInitConfig *config);

__attribute__((dllimport)) int PyInitConfig_GetError(PyInitConfig* config,
    const char **err_msg);
__attribute__((dllimport)) int PyInitConfig_GetExitCode(PyInitConfig* config,
    int *exitcode);

__attribute__((dllimport)) int PyInitConfig_HasOption(PyInitConfig *config,
    const char *name);
__attribute__((dllimport)) int PyInitConfig_GetInt(PyInitConfig *config,
    const char *name,
    int64_t *value);
__attribute__((dllimport)) int PyInitConfig_GetStr(PyInitConfig *config,
    const char *name,
    char **value);
__attribute__((dllimport)) int PyInitConfig_GetStrList(PyInitConfig *config,
    const char *name,
    size_t *length,
    char ***items);
__attribute__((dllimport)) void PyInitConfig_FreeStrList(size_t length, char **items);

__attribute__((dllimport)) int PyInitConfig_SetInt(PyInitConfig *config,
    const char *name,
    int64_t value);
__attribute__((dllimport)) int PyInitConfig_SetStr(PyInitConfig *config,
    const char *name,
    const char *value);
__attribute__((dllimport)) int PyInitConfig_SetStrList(PyInitConfig *config,
    const char *name,
    size_t length,
    char * const *items);

__attribute__((dllimport)) int PyInitConfig_AddModule(PyInitConfig *config,
    const char *name,
    PyObject* (*initfunc)(void));

__attribute__((dllimport)) int Py_InitializeFromInitConfig(PyInitConfig *config);
# 14 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/pystate.h"
__attribute__((dllimport)) PyInterpreterState * PyInterpreterState_New(void);
__attribute__((dllimport)) void PyInterpreterState_Clear(PyInterpreterState *);
__attribute__((dllimport)) void PyInterpreterState_Delete(PyInterpreterState *);
# 26 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/pystate.h"
__attribute__((dllimport)) PyInterpreterState * PyInterpreterState_Get(void);

__attribute__((dllimport)) PyObject * PyInterpreterState_GetDict(PyInterpreterState *);

__attribute__((dllimport)) int64_t PyInterpreterState_GetID(PyInterpreterState *);

__attribute__((dllimport)) int PyState_AddModule(PyObject*, PyModuleDef*);
__attribute__((dllimport)) int PyState_RemoveModule(PyModuleDef*);

__attribute__((dllimport)) PyObject* PyState_FindModule(PyModuleDef*);

__attribute__((dllimport)) PyThreadState * PyThreadState_New(PyInterpreterState *);
__attribute__((dllimport)) void PyThreadState_Clear(PyThreadState *);
__attribute__((dllimport)) void PyThreadState_Delete(PyThreadState *);
# 60 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/pystate.h"
__attribute__((dllimport)) PyThreadState * PyThreadState_Get(void);

__attribute__((dllimport)) PyThreadState * PyThreadState_Swap(PyThreadState *);
__attribute__((dllimport)) PyObject * PyThreadState_GetDict(void);
__attribute__((dllimport)) int PyThreadState_SetAsyncExc(unsigned long, PyObject *);

__attribute__((dllimport)) PyInterpreterState* PyThreadState_GetInterpreter(PyThreadState *tstate);
__attribute__((dllimport)) PyFrameObject* PyThreadState_GetFrame(PyThreadState *tstate);
__attribute__((dllimport)) uint64_t PyThreadState_GetID(PyThreadState *tstate);

typedef
    enum {PyGILState_LOCKED, PyGILState_UNLOCKED}
        PyGILState_STATE;
# 102 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/pystate.h"
__attribute__((dllimport)) PyGILState_STATE PyGILState_Ensure(void);
# 112 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/pystate.h"
__attribute__((dllimport)) void PyGILState_Release(PyGILState_STATE);

__attribute__((dllimport)) PyThreadState * PyGILState_GetThisThreadState(void);

__attribute__((dllimport)) int _PyInterpreterState_RequiresIDRef(PyInterpreterState *);
__attribute__((dllimport)) void _PyInterpreterState_RequireIDRef(PyInterpreterState *, int);

typedef int (*Py_tracefunc)(PyObject *, PyFrameObject *, int, PyObject *);
# 32 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/pystate.h"
typedef struct {
    int32_t debugger_pending_call;
    char debugger_script_path[512];
} _PyRemoteDebuggerSupport;

typedef struct _err_stackitem {
    PyObject *exc_value;
    struct _err_stackitem *previous_item;
} _PyErr_StackItem;

typedef struct _stack_chunk {
    struct _stack_chunk *previous;
    size_t size;
    size_t top;
    PyObject * data[1];
} _PyStackChunk;

struct _ts {
    PyThreadState *prev;
    PyThreadState *next;
    PyInterpreterState *interp;
    uintptr_t eval_breaker;
    struct {
        unsigned int initialized:1;
        unsigned int bound:1;
        unsigned int unbound:1;
        unsigned int bound_gilstate:1;
        unsigned int active:1;
        unsigned int finalizing:1;
        unsigned int cleared:1;
        unsigned int finalized:1;
        unsigned int :24;
    } _status;
    int holds_gil;
    int _whence;
    int state;
    int py_recursion_remaining;
    int py_recursion_limit;
    int recursion_headroom;
    int tracing;
    int what_event;
    struct _PyInterpreterFrame *current_frame;
    Py_tracefunc c_profilefunc;
    Py_tracefunc c_tracefunc;
    PyObject *c_profileobj;
    PyObject *c_traceobj;
    PyObject *current_exception;
    _PyErr_StackItem *exc_info;
    PyObject *dict;
    int gilstate_counter;
    PyObject *async_exc;
    unsigned long thread_id;
    unsigned long native_thread_id;
    PyObject *delete_later;
    uintptr_t critical_section;
    int coroutine_origin_tracking_depth;
    PyObject *async_gen_firstiter;
    PyObject *async_gen_finalizer;
    PyObject *context;
    uint64_t context_ver;
    uint64_t id;
    _PyStackChunk *datastack_chunk;
    PyObject **datastack_top;
    PyObject **datastack_limit;
    _PyErr_StackItem exc_state;
    PyObject *current_executor;
    uint64_t dict_global_version;
    PyObject *threading_local_key;
    PyObject *threading_local_sentinel;
    _PyRemoteDebuggerSupport remote_debugger_support;
};

__attribute__((dllimport)) PyThreadState * PyThreadState_GetUnchecked(void);

__attribute__((__deprecated__)) static inline PyThreadState*
_PyThreadState_UncheckedGet(void)
{
    return PyThreadState_GetUnchecked();
}

__attribute__((dllimport)) void PyThreadState_EnterTracing(PyThreadState *tstate);

__attribute__((dllimport)) void PyThreadState_LeaveTracing(PyThreadState *tstate);

__attribute__((dllimport)) int PyGILState_Check(void);

__attribute__((dllimport)) PyObject* _PyThread_CurrentFrames(void);

__attribute__((dllimport)) int PyUnstable_ThreadState_SetStackProtection(
    PyThreadState *tstate,
    void *stack_start_addr,
    size_t stack_size);

__attribute__((dllimport)) void PyUnstable_ThreadState_ResetStackProtection(
    PyThreadState *tstate);

__attribute__((dllimport)) PyInterpreterState * PyInterpreterState_Main(void);
__attribute__((dllimport)) PyInterpreterState * PyInterpreterState_Head(void);
__attribute__((dllimport)) PyInterpreterState * PyInterpreterState_Next(PyInterpreterState *);
__attribute__((dllimport)) PyThreadState * PyInterpreterState_ThreadHead(PyInterpreterState *);
__attribute__((dllimport)) PyThreadState * PyThreadState_Next(PyThreadState *);
__attribute__((dllimport)) void PyThreadState_DeleteCurrent(void);

typedef PyObject* (*_PyFrameEvalFunction)(PyThreadState *tstate, struct _PyInterpreterFrame *, int);

__attribute__((dllimport)) _PyFrameEvalFunction _PyInterpreterState_GetEvalFrameFunc(
    PyInterpreterState *interp);
__attribute__((dllimport)) void _PyInterpreterState_SetEvalFrameFunc(
    PyInterpreterState *interp,
    _PyFrameEvalFunction eval_frame);
# 12 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/genobject.h"
typedef struct _PyGenObject PyGenObject;

extern __attribute__((dllimport)) PyTypeObject PyGen_Type;

__attribute__((dllimport)) PyObject * PyGen_New(PyFrameObject *);
__attribute__((dllimport)) PyObject * PyGen_NewWithQualName(PyFrameObject *,
    PyObject *name, PyObject *qualname);
__attribute__((dllimport)) PyCodeObject * PyGen_GetCode(PyGenObject *gen);

typedef struct _PyCoroObject PyCoroObject;

extern __attribute__((dllimport)) PyTypeObject PyCoro_Type;

__attribute__((dllimport)) PyObject * PyCoro_New(PyFrameObject *,
    PyObject *name, PyObject *qualname);

typedef struct _PyAsyncGenObject PyAsyncGenObject;

extern __attribute__((dllimport)) PyTypeObject PyAsyncGen_Type;
extern __attribute__((dllimport)) PyTypeObject _PyAsyncGenASend_Type;

__attribute__((dllimport)) PyObject * PyAsyncGen_New(PyFrameObject *,
    PyObject *name, PyObject *qualname);

typedef PyObject *(*getter)(PyObject *, void *);
typedef int (*setter)(PyObject *, PyObject *, void *);

struct PyGetSetDef {
    const char *name;
    getter get;
    setter set;
    const char *doc;
    void *closure;
};

extern __attribute__((dllimport)) PyTypeObject PyClassMethodDescr_Type;
extern __attribute__((dllimport)) PyTypeObject PyGetSetDescr_Type;
extern __attribute__((dllimport)) PyTypeObject PyMemberDescr_Type;
extern __attribute__((dllimport)) PyTypeObject PyMethodDescr_Type;
extern __attribute__((dllimport)) PyTypeObject PyWrapperDescr_Type;
extern __attribute__((dllimport)) PyTypeObject PyDictProxy_Type;
extern __attribute__((dllimport)) PyTypeObject PyProperty_Type;

__attribute__((dllimport)) PyObject * PyDescr_NewMethod(PyTypeObject *, PyMethodDef *);
__attribute__((dllimport)) PyObject * PyDescr_NewClassMethod(PyTypeObject *, PyMethodDef *);
__attribute__((dllimport)) PyObject * PyDescr_NewMember(PyTypeObject *, PyMemberDef *);
__attribute__((dllimport)) PyObject * PyDescr_NewGetSet(PyTypeObject *, PyGetSetDef *);

__attribute__((dllimport)) PyObject * PyDictProxy_New(PyObject *);
__attribute__((dllimport)) PyObject * PyWrapper_New(PyObject *, PyObject *);

struct PyMemberDef {
    const char *name;
    int type;
    Py_ssize_t offset;
    int flags;
    const char *doc;
};
# 88 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/descrobject.h"
__attribute__((dllimport)) PyObject * PyMember_GetOne(const char *, PyMemberDef *);
__attribute__((dllimport)) int PyMember_SetOne(char *, PyMemberDef *, PyObject *);

typedef PyObject *(*wrapperfunc)(PyObject *self, PyObject *args,
                                 void *wrapped);

typedef PyObject *(*wrapperfunc_kwds)(PyObject *self, PyObject *args,
                                      void *wrapped, PyObject *kwds);

struct wrapperbase {
    const char *name;
    int offset;
    void *function;
    wrapperfunc wrapper;
    const char *doc;
    int flags;
    PyObject *name_strobj;
};

typedef struct {
    PyObject ob_base;
    PyTypeObject *d_type;
    PyObject *d_name;
    PyObject *d_qualname;
} PyDescrObject;

typedef struct {
    PyDescrObject d_common;
    PyMethodDef *d_method;
    vectorcallfunc vectorcall;
} PyMethodDescrObject;

typedef struct {
    PyDescrObject d_common;
    PyMemberDef *d_member;
} PyMemberDescrObject;

typedef struct {
    PyDescrObject d_common;
    PyGetSetDef *d_getset;
} PyGetSetDescrObject;

typedef struct {
    PyDescrObject d_common;
    struct wrapperbase *d_base;
    void *d_wrapped;
} PyWrapperDescrObject;

__attribute__((dllimport)) PyObject * PyDescr_NewWrapper(PyTypeObject *,
                                                struct wrapperbase *, void *);
__attribute__((dllimport)) int PyDescr_IsData(PyObject *);

__attribute__((dllimport)) PyObject * Py_GenericAlias(PyObject *, PyObject *);
extern __attribute__((dllimport)) PyTypeObject Py_GenericAliasType;

__attribute__((dllimport)) int PyErr_WarnEx(
    PyObject *category,
    const char *message,
    Py_ssize_t stack_level);

__attribute__((dllimport)) int PyErr_WarnFormat(
    PyObject *category,
    Py_ssize_t stack_level,
    const char *format,
    ...);

__attribute__((dllimport)) int PyErr_ResourceWarning(
    PyObject *source,
    Py_ssize_t stack_level,
    const char *format,
    ...);

__attribute__((dllimport)) int PyErr_WarnExplicit(
    PyObject *category,
    const char *message,
    const char *filename,
    int lineno,
    const char *module,
    PyObject *registry);

__attribute__((dllimport)) int PyErr_WarnExplicitObject(
    PyObject *category,
    PyObject *message,
    PyObject *filename,
    int lineno,
    PyObject *module,
    PyObject *registry);

__attribute__((dllimport)) int PyErr_WarnExplicitFormat(
    PyObject *category,
    const char *filename, int lineno,
    const char *module, PyObject *registry,
    const char *format, ...);

typedef struct _PyWeakReference PyWeakReference;

extern __attribute__((dllimport)) PyTypeObject _PyWeakref_RefType;
extern __attribute__((dllimport)) PyTypeObject _PyWeakref_ProxyType;
extern __attribute__((dllimport)) PyTypeObject _PyWeakref_CallableProxyType;
# 26 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/weakrefobject.h"
__attribute__((dllimport)) PyObject * PyWeakref_NewRef(PyObject *ob,
                                        PyObject *callback);
__attribute__((dllimport)) PyObject * PyWeakref_NewProxy(PyObject *ob,
                                          PyObject *callback);
__attribute__((__deprecated__)) __attribute__((dllimport)) PyObject * PyWeakref_GetObject(PyObject *ref);

__attribute__((dllimport)) int PyWeakref_GetRef(PyObject *ref, PyObject **pobj);

struct _PyWeakReference {
    PyObject ob_base;
    PyObject *wr_object;
    PyObject *wr_callback;
    Py_hash_t hash;
    PyWeakReference *wr_prev;
    PyWeakReference *wr_next;
    vectorcallfunc vectorcall;
};

__attribute__((dllimport)) void _PyWeakref_ClearRef(PyWeakReference *self);

__attribute__((dllimport)) int PyWeakref_IsDead(PyObject *ref);

__attribute__((__deprecated__)) static inline PyObject* PyWeakref_GET_OBJECT(PyObject *ref_obj)
{
    PyWeakReference *ref = ((void) ((!!((PyObject_TypeCheck(((PyObject*)(((ref_obj)))), (&_PyWeakref_RefType)) || (Py_IS_TYPE(((PyObject*)(((ref_obj)))), (&_PyWeakref_ProxyType)) || Py_IS_TYPE(((PyObject*)(((ref_obj)))), (&_PyWeakref_CallableProxyType)))))) || (_assert("PyWeakref_Check(ref_obj)","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/weakrefobject.h",53),0)), ((PyWeakReference*)((ref_obj))));
    PyObject *obj = ref->wr_object;
    if (_Py_REFCNT(((PyObject*)((obj)))) > 0) {
        return obj;
    }
    return (&_Py_NoneStruct);
}
# 10 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/structseq.h"
typedef struct PyStructSequence_Field {
    const char *name;
    const char *doc;
} PyStructSequence_Field;

typedef struct PyStructSequence_Desc {
    const char *name;
    const char *doc;
    PyStructSequence_Field *fields;
    int n_in_sequence;
} PyStructSequence_Desc;

extern __attribute__((dllimport)) const char * const PyStructSequence_UnnamedField;

__attribute__((dllimport)) void PyStructSequence_InitType(PyTypeObject *type,
                                           PyStructSequence_Desc *desc);
__attribute__((dllimport)) int PyStructSequence_InitType2(PyTypeObject *type,
                                           PyStructSequence_Desc *desc);

__attribute__((dllimport)) PyTypeObject* PyStructSequence_NewType(PyStructSequence_Desc *desc);

__attribute__((dllimport)) PyObject * PyStructSequence_New(PyTypeObject* type);

__attribute__((dllimport)) void PyStructSequence_SetItem(PyObject*, Py_ssize_t, PyObject*);
__attribute__((dllimport)) PyObject* PyStructSequence_GetItem(PyObject*, Py_ssize_t);

typedef PyTupleObject PyStructSequence;
# 13 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/picklebufobject.h"
extern __attribute__((dllimport)) PyTypeObject PyPickleBuffer_Type;

__attribute__((dllimport)) PyObject * PyPickleBuffer_FromObject(PyObject *);

__attribute__((dllimport)) const Py_buffer * PyPickleBuffer_GetBuffer(PyObject *);

__attribute__((dllimport)) int PyPickleBuffer_Release(PyObject *);
# 10 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/pytime.h"
typedef int64_t PyTime_t;

__attribute__((dllimport)) double PyTime_AsSecondsDouble(PyTime_t t);
__attribute__((dllimport)) int PyTime_Monotonic(PyTime_t *result);
__attribute__((dllimport)) int PyTime_PerfCounter(PyTime_t *result);
__attribute__((dllimport)) int PyTime_Time(PyTime_t *result);

__attribute__((dllimport)) int PyTime_MonotonicRaw(PyTime_t *result);
__attribute__((dllimport)) int PyTime_PerfCounterRaw(PyTime_t *result);
__attribute__((dllimport)) int PyTime_TimeRaw(PyTime_t *result);
# 26 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/codecs.h"
__attribute__((dllimport)) int PyCodec_Register(
       PyObject *search_function
       );

__attribute__((dllimport)) int PyCodec_Unregister(
       PyObject *search_function
       );
# 45 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/codecs.h"
__attribute__((dllimport)) int PyCodec_KnownEncoding(
       const char *encoding
       );
# 59 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/codecs.h"
__attribute__((dllimport)) PyObject * PyCodec_Encode(
       PyObject *object,
       const char *encoding,
       const char *errors
       );
# 75 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/codecs.h"
__attribute__((dllimport)) PyObject * PyCodec_Decode(
       PyObject *object,
       const char *encoding,
       const char *errors
       );
# 102 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/codecs.h"
__attribute__((dllimport)) PyObject * PyCodec_Encoder(const char *encoding);

__attribute__((dllimport)) PyObject * PyCodec_Decoder(const char *encoding);

__attribute__((dllimport)) PyObject * PyCodec_IncrementalEncoder(
   const char *encoding,
   const char *errors);

__attribute__((dllimport)) PyObject * PyCodec_IncrementalDecoder(
   const char *encoding,
   const char *errors);

__attribute__((dllimport)) PyObject * PyCodec_StreamReader(
   const char *encoding,
   PyObject *stream,
   const char *errors);

__attribute__((dllimport)) PyObject * PyCodec_StreamWriter(
   const char *encoding,
   PyObject *stream,
   const char *errors);
# 142 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/codecs.h"
__attribute__((dllimport)) int PyCodec_RegisterError(const char *name, PyObject *error);

__attribute__((dllimport)) PyObject * PyCodec_LookupError(const char *name);

__attribute__((dllimport)) PyObject * PyCodec_StrictErrors(PyObject *exc);

__attribute__((dllimport)) PyObject * PyCodec_IgnoreErrors(PyObject *exc);

__attribute__((dllimport)) PyObject * PyCodec_ReplaceErrors(PyObject *exc);

__attribute__((dllimport)) PyObject * PyCodec_XMLCharRefReplaceErrors(PyObject *exc);

__attribute__((dllimport)) PyObject * PyCodec_BackslashReplaceErrors(PyObject *exc);

__attribute__((dllimport)) PyObject * PyCodec_NameReplaceErrors(PyObject *exc);

extern __attribute__((dllimport)) const char * Py_hexdigits;

typedef void *PyThread_type_lock;

typedef enum PyLockStatus {
    PY_LOCK_FAILURE = 0,
    PY_LOCK_ACQUIRED = 1,
    PY_LOCK_INTR
} PyLockStatus;

__attribute__((dllimport)) void PyThread_init_thread(void);
__attribute__((dllimport)) unsigned long PyThread_start_new_thread(void (*)(void *), void *);
# 38 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/pythread.h"
__attribute__((__deprecated__)) __attribute__((dllimport)) void __attribute__((__noreturn__)) PyThread_exit_thread(void);

__attribute__((dllimport)) unsigned long PyThread_get_thread_ident(void);

__attribute__((dllimport)) unsigned long PyThread_get_thread_native_id(void);

__attribute__((dllimport)) PyThread_type_lock PyThread_allocate_lock(void);
__attribute__((dllimport)) void PyThread_free_lock(PyThread_type_lock);
__attribute__((dllimport)) int PyThread_acquire_lock(PyThread_type_lock, int);
# 73 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/pythread.h"
__attribute__((dllimport)) PyLockStatus PyThread_acquire_lock_timed(PyThread_type_lock,
                                                     long long microseconds,
                                                     int intr_flag);

__attribute__((dllimport)) void PyThread_release_lock(PyThread_type_lock);

__attribute__((dllimport)) size_t PyThread_get_stacksize(void);
__attribute__((dllimport)) int PyThread_set_stacksize(size_t);

__attribute__((dllimport)) PyObject* PyThread_GetInfo(void);
# 94 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/pythread.h"
__attribute__((__deprecated__)) __attribute__((dllimport)) int PyThread_create_key(void);
__attribute__((__deprecated__)) __attribute__((dllimport)) void PyThread_delete_key(int key);
__attribute__((__deprecated__)) __attribute__((dllimport)) int PyThread_set_key_value(int key,
                                                          void *value);
__attribute__((__deprecated__)) __attribute__((dllimport)) void * PyThread_get_key_value(int key);
__attribute__((__deprecated__)) __attribute__((dllimport)) void PyThread_delete_key_value(int key);

__attribute__((__deprecated__)) __attribute__((dllimport)) void PyThread_ReInitTLS(void);

typedef struct _Py_tss_t Py_tss_t;

__attribute__((dllimport)) Py_tss_t * PyThread_tss_alloc(void);
__attribute__((dllimport)) void PyThread_tss_free(Py_tss_t *key);

__attribute__((dllimport)) int PyThread_tss_is_created(Py_tss_t *key);
__attribute__((dllimport)) int PyThread_tss_create(Py_tss_t *key);
__attribute__((dllimport)) void PyThread_tss_delete(Py_tss_t *key);
__attribute__((dllimport)) int PyThread_tss_set(Py_tss_t *key, void *value);
__attribute__((dllimport)) void * PyThread_tss_get(Py_tss_t *key);
# 11 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/pythread.h"
extern __attribute__((dllimport)) const long long PY_TIMEOUT_MAX;
# 35 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/pythread.h"
struct _Py_tss_t {
    int _is_initialized;
    unsigned long _key;
};

extern __attribute__((dllimport)) PyTypeObject PyContext_Type;
typedef struct _pycontextobject PyContext;

extern __attribute__((dllimport)) PyTypeObject PyContextVar_Type;
typedef struct _pycontextvarobject PyContextVar;

extern __attribute__((dllimport)) PyTypeObject PyContextToken_Type;
typedef struct _pycontexttokenobject PyContextToken;

__attribute__((dllimport)) PyObject * PyContext_New(void);
__attribute__((dllimport)) PyObject * PyContext_Copy(PyObject *);
__attribute__((dllimport)) PyObject * PyContext_CopyCurrent(void);

__attribute__((dllimport)) int PyContext_Enter(PyObject *);
__attribute__((dllimport)) int PyContext_Exit(PyObject *);

typedef enum {
    Py_CONTEXT_SWITCHED = 1,
} PyContextEvent;
# 46 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/context.h"
typedef int (*PyContext_WatchCallback)(PyContextEvent, PyObject *);
# 55 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/context.h"
__attribute__((dllimport)) int PyContext_AddWatcher(PyContext_WatchCallback callback);

__attribute__((dllimport)) int PyContext_ClearWatcher(int watcher_id);

__attribute__((dllimport)) PyObject * PyContextVar_New(
    const char *name, PyObject *default_value);
# 87 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/context.h"
__attribute__((dllimport)) int PyContextVar_Get(
    PyObject *var, PyObject *default_value, PyObject **value);

__attribute__((dllimport)) PyObject * PyContextVar_Set(PyObject *var, PyObject *value);

__attribute__((dllimport)) int PyContextVar_Reset(PyObject *var, PyObject *token);

__attribute__((dllimport)) int PyArg_Parse(PyObject *, const char *, ...);
__attribute__((dllimport)) int PyArg_ParseTuple(PyObject *, const char *, ...);
__attribute__((dllimport)) int PyArg_ParseTupleAndKeywords(PyObject *, PyObject *,
                                            const char *, char * const *, ...);
__attribute__((dllimport)) int PyArg_VaParse(PyObject *, const char *, va_list);
__attribute__((dllimport)) int PyArg_VaParseTupleAndKeywords(PyObject *, PyObject *,
                                              const char *, char * const *, va_list);

__attribute__((dllimport)) int PyArg_ValidateKeywordArguments(PyObject *);
__attribute__((dllimport)) int PyArg_UnpackTuple(PyObject *, const char *, Py_ssize_t, Py_ssize_t, ...);
__attribute__((dllimport)) PyObject * Py_BuildValue(const char *, ...);
__attribute__((dllimport)) PyObject * Py_VaBuildValue(const char *, va_list);

__attribute__((dllimport)) int PyModule_AddObjectRef(PyObject *mod, const char *name, PyObject *value);

__attribute__((dllimport)) int PyModule_Add(PyObject *mod, const char *name, PyObject *value);

__attribute__((dllimport)) int PyModule_AddObject(PyObject *mod, const char *, PyObject *value);

__attribute__((dllimport)) int PyModule_AddIntConstant(PyObject *, const char *, long);
__attribute__((dllimport)) int PyModule_AddStringConstant(PyObject *, const char *, const char *);

__attribute__((dllimport)) int PyModule_AddType(PyObject *module, PyTypeObject *type);

__attribute__((dllimport)) int PyModule_SetDocString(PyObject *, const char *);
__attribute__((dllimport)) int PyModule_AddFunctions(PyObject *, PyMethodDef *);
__attribute__((dllimport)) int PyModule_ExecDef(PyObject *module, PyModuleDef *def);
# 111 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/modsupport.h"
__attribute__((dllimport)) PyObject * PyModule_Create2(PyModuleDef*, int apiver);
# 123 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/modsupport.h"
__attribute__((dllimport)) PyObject * PyModule_FromDefAndSpec2(PyModuleDef *def,
                                                PyObject *spec,
                                                int module_api_version);

typedef struct {
    uint8_t v;
} _PyOnceFlag;

typedef struct _PyArg_Parser {
    const char *format;
    const char * const *keywords;
    const char *fname;
    const char *custom_msg;
    _PyOnceFlag once;
    int is_kwtuple_owned;
    int pos;
    int min;
    int max;
    PyObject *kwtuple;
    struct _PyArg_Parser *next;
} _PyArg_Parser;

__attribute__((dllimport)) int _PyArg_ParseTupleAndKeywordsFast(PyObject *, PyObject *,
                                                 struct _PyArg_Parser *, ...);
# 27 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/compile.h"
typedef struct {
    int cf_flags;
    int cf_feature_version;
} PyCompilerFlags;
# 49 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/compile.h"
__attribute__((dllimport)) int PyCompile_OpcodeStackEffect(int opcode, int oparg);
__attribute__((dllimport)) int PyCompile_OpcodeStackEffectWithJump(int opcode, int oparg, int jump);
# 10 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/pythonrun.h"
__attribute__((dllimport)) PyObject * Py_CompileString(const char *, const char *, int);

__attribute__((dllimport)) void PyErr_Print(void);
__attribute__((dllimport)) void PyErr_PrintEx(int);
__attribute__((dllimport)) void PyErr_Display(PyObject *, PyObject *, PyObject *);

__attribute__((dllimport)) void PyErr_DisplayException(PyObject *);

extern __attribute__((dllimport)) int (*PyOS_InputHook)(void);

__attribute__((dllimport)) int PyOS_CheckStack(void);

__attribute__((dllimport)) int PyRun_SimpleStringFlags(const char *, PyCompilerFlags *);
__attribute__((dllimport)) int PyRun_AnyFileExFlags(
    FILE *fp,
    const char *filename,
    int closeit,
    PyCompilerFlags *flags);
__attribute__((dllimport)) int PyRun_SimpleFileExFlags(
    FILE *fp,
    const char *filename,
    int closeit,
    PyCompilerFlags *flags);
__attribute__((dllimport)) int PyRun_InteractiveOneFlags(
    FILE *fp,
    const char *filename,
    PyCompilerFlags *flags);
__attribute__((dllimport)) int PyRun_InteractiveOneObject(
    FILE *fp,
    PyObject *filename,
    PyCompilerFlags *flags);
__attribute__((dllimport)) int PyRun_InteractiveLoopFlags(
    FILE *fp,
    const char *filename,
    PyCompilerFlags *flags);

__attribute__((dllimport)) PyObject * PyRun_StringFlags(const char *, int, PyObject *,
                                         PyObject *, PyCompilerFlags *);

__attribute__((dllimport)) PyObject * PyRun_FileExFlags(
    FILE *fp,
    const char *filename,
    int start,
    PyObject *globals,
    PyObject *locals,
    int closeit,
    PyCompilerFlags *flags);

__attribute__((dllimport)) PyObject * Py_CompileStringExFlags(
    const char *str,
    const char *filename,
    int start,
    PyCompilerFlags *flags,
    int optimize);
__attribute__((dllimport)) PyObject * Py_CompileStringObject(
    const char *str,
    PyObject *filename, int start,
    PyCompilerFlags *flags,
    int optimize);
# 62 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/pythonrun.h"
__attribute__((dllimport)) PyObject * PyRun_String(const char *str, int s, PyObject *g, PyObject *l);
__attribute__((dllimport)) int PyRun_AnyFile(FILE *fp, const char *name);
__attribute__((dllimport)) int PyRun_AnyFileEx(FILE *fp, const char *name, int closeit);
__attribute__((dllimport)) int PyRun_AnyFileFlags(FILE *, const char *, PyCompilerFlags *);
__attribute__((dllimport)) int PyRun_SimpleString(const char *s);
__attribute__((dllimport)) int PyRun_SimpleFile(FILE *f, const char *p);
__attribute__((dllimport)) int PyRun_SimpleFileEx(FILE *f, const char *p, int c);
__attribute__((dllimport)) int PyRun_InteractiveOne(FILE *f, const char *p);
__attribute__((dllimport)) int PyRun_InteractiveLoop(FILE *f, const char *p);
__attribute__((dllimport)) PyObject * PyRun_File(FILE *fp, const char *p, int s, PyObject *g, PyObject *l);
__attribute__((dllimport)) PyObject * PyRun_FileEx(FILE *fp, const char *p, int s, PyObject *g, PyObject *l, int c);
__attribute__((dllimport)) PyObject * PyRun_FileFlags(FILE *fp, const char *p, int s, PyObject *g, PyObject *l, PyCompilerFlags *flags);
# 95 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/pythonrun.h"
__attribute__((dllimport)) char * PyOS_Readline(FILE *, FILE *, const char *);
extern __attribute__((dllimport)) char *(*PyOS_ReadlineFunctionPointer)(FILE *, FILE *, const char *);
# 12 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/pylifecycle.h"
__attribute__((dllimport)) void Py_Initialize(void);
__attribute__((dllimport)) void Py_InitializeEx(int);
__attribute__((dllimport)) void Py_Finalize(void);

__attribute__((dllimport)) int Py_FinalizeEx(void);

__attribute__((dllimport)) int Py_IsInitialized(void);

__attribute__((dllimport)) PyThreadState * Py_NewInterpreter(void);
__attribute__((dllimport)) void Py_EndInterpreter(PyThreadState *);

__attribute__((dllimport)) int Py_AtExit(void (*func)(void));

__attribute__((dllimport)) void __attribute__((__noreturn__)) Py_Exit(int);

__attribute__((dllimport)) int Py_Main(int argc, wchar_t **argv);
__attribute__((dllimport)) int Py_BytesMain(int argc, char **argv);

__attribute__((__deprecated__)) __attribute__((dllimport)) void Py_SetProgramName(const wchar_t *);
__attribute__((__deprecated__)) __attribute__((dllimport)) wchar_t * Py_GetProgramName(void);

__attribute__((__deprecated__)) __attribute__((dllimport)) void Py_SetPythonHome(const wchar_t *);
__attribute__((__deprecated__)) __attribute__((dllimport)) wchar_t * Py_GetPythonHome(void);

__attribute__((__deprecated__)) __attribute__((dllimport)) wchar_t * Py_GetProgramFullPath(void);
__attribute__((__deprecated__)) __attribute__((dllimport)) wchar_t * Py_GetPrefix(void);
__attribute__((__deprecated__)) __attribute__((dllimport)) wchar_t * Py_GetExecPrefix(void);
__attribute__((__deprecated__)) __attribute__((dllimport)) wchar_t * Py_GetPath(void);

int _Py_CheckPython3(void);

__attribute__((dllimport)) const char * Py_GetVersion(void);
__attribute__((dllimport)) const char * Py_GetPlatform(void);
__attribute__((dllimport)) const char * Py_GetCopyright(void);
__attribute__((dllimport)) const char * Py_GetCompiler(void);
__attribute__((dllimport)) const char * Py_GetBuildInfo(void);

typedef void (*PyOS_sighandler_t)(int);
__attribute__((dllimport)) PyOS_sighandler_t PyOS_getsig(int);
__attribute__((dllimport)) PyOS_sighandler_t PyOS_setsig(int, PyOS_sighandler_t);

extern __attribute__((dllimport)) const unsigned long Py_Version;

__attribute__((dllimport)) int Py_IsFinalizing(void);

__attribute__((dllimport)) int Py_FrozenMain(int argc, char **argv);

__attribute__((dllimport)) PyStatus Py_PreInitialize(
    const PyPreConfig *src_config);
__attribute__((dllimport)) PyStatus Py_PreInitializeFromBytesArgs(
    const PyPreConfig *src_config,
    Py_ssize_t argc,
    char **argv);
__attribute__((dllimport)) PyStatus Py_PreInitializeFromArgs(
    const PyPreConfig *src_config,
    Py_ssize_t argc,
    wchar_t **argv);

__attribute__((dllimport)) PyStatus Py_InitializeFromConfig(
    const PyConfig *config);

__attribute__((dllimport)) int Py_RunMain(void);

__attribute__((dllimport)) void __attribute__((__noreturn__)) Py_ExitStatusException(PyStatus err);

__attribute__((dllimport)) int Py_FdIsInteractive(FILE *, const char *);

typedef struct {
    int use_main_obmalloc;
    int allow_fork;
    int allow_exec;
    int allow_threads;
    int allow_daemon_threads;
    int check_multi_interp_extensions;
    int gil;
} PyInterpreterConfig;
# 83 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/pylifecycle.h"
__attribute__((dllimport)) PyStatus Py_NewInterpreterFromConfig(
    PyThreadState **tstate_p,
    const PyInterpreterConfig *config);

typedef void (*atexit_datacallbackfunc)(void *);
__attribute__((dllimport)) int PyUnstable_AtExit(
        PyInterpreterState *, atexit_datacallbackfunc, void *);
# 10 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/ceval.h"
__attribute__((dllimport)) PyObject * PyEval_EvalCode(PyObject *, PyObject *, PyObject *);

__attribute__((dllimport)) PyObject * PyEval_EvalCodeEx(PyObject *co,
                                         PyObject *globals,
                                         PyObject *locals,
                                         PyObject *const *args, int argc,
                                         PyObject *const *kwds, int kwdc,
                                         PyObject *const *defs, int defc,
                                         PyObject *kwdefs, PyObject *closure);

__attribute__((dllimport)) PyObject * PyEval_GetBuiltins(void);
__attribute__((dllimport)) PyObject * PyEval_GetGlobals(void);
__attribute__((dllimport)) PyObject * PyEval_GetLocals(void);
__attribute__((dllimport)) PyFrameObject * PyEval_GetFrame(void);

__attribute__((dllimport)) PyObject * PyEval_GetFrameBuiltins(void);
__attribute__((dllimport)) PyObject * PyEval_GetFrameGlobals(void);
__attribute__((dllimport)) PyObject * PyEval_GetFrameLocals(void);

__attribute__((dllimport)) int Py_AddPendingCall(int (*func)(void *), void *arg);
__attribute__((dllimport)) int Py_MakePendingCalls(void);
# 57 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/ceval.h"
__attribute__((dllimport)) void Py_SetRecursionLimit(int);
__attribute__((dllimport)) int Py_GetRecursionLimit(void);

__attribute__((dllimport)) int Py_EnterRecursiveCall(const char *where);
__attribute__((dllimport)) void Py_LeaveRecursiveCall(void);

__attribute__((dllimport)) const char * PyEval_GetFuncName(PyObject *);
__attribute__((dllimport)) const char * PyEval_GetFuncDesc(PyObject *);

__attribute__((dllimport)) PyObject * PyEval_EvalFrame(PyFrameObject *);
__attribute__((dllimport)) PyObject * PyEval_EvalFrameEx(PyFrameObject *f, int exc);
# 111 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/ceval.h"
__attribute__((dllimport)) PyThreadState * PyEval_SaveThread(void);
__attribute__((dllimport)) void PyEval_RestoreThread(PyThreadState *);

__attribute__((__deprecated__)) __attribute__((dllimport)) void PyEval_InitThreads(void);

__attribute__((dllimport)) void PyEval_AcquireThread(PyThreadState *tstate);
__attribute__((dllimport)) void PyEval_ReleaseThread(PyThreadState *tstate);

__attribute__((dllimport)) void PyEval_SetProfile(Py_tracefunc, PyObject *);
__attribute__((dllimport)) void PyEval_SetProfileAllThreads(Py_tracefunc, PyObject *);
__attribute__((dllimport)) void PyEval_SetTrace(Py_tracefunc, PyObject *);
__attribute__((dllimport)) void PyEval_SetTraceAllThreads(Py_tracefunc, PyObject *);

__attribute__((dllimport)) int PyEval_MergeCompilerFlags(PyCompilerFlags *cf);

__attribute__((dllimport)) PyObject * _PyEval_EvalFrameDefault(PyThreadState *tstate, struct _PyInterpreterFrame *f, int exc);

__attribute__((dllimport)) Py_ssize_t PyUnstable_Eval_RequestCodeExtraIndex(freefunc);

__attribute__((__deprecated__)) static inline Py_ssize_t
_PyEval_RequestCodeExtraIndex(freefunc f) {
    return PyUnstable_Eval_RequestCodeExtraIndex(f);
}

__attribute__((dllimport)) int _PyEval_SliceIndex(PyObject *, Py_ssize_t *);
__attribute__((dllimport)) int _PyEval_SliceIndexNotNone(PyObject *, Py_ssize_t *);

typedef struct {
    FILE* perf_map;
    PyThread_type_lock map_lock;
} PerfMapState;

__attribute__((dllimport)) int PyUnstable_PerfMapState_Init(void);
__attribute__((dllimport)) int PyUnstable_WritePerfMapEntry(
    const void *code_addr,
    unsigned int code_size,
    const char *entry_name);
__attribute__((dllimport)) void PyUnstable_PerfMapState_Fini(void);
__attribute__((dllimport)) int PyUnstable_CopyPerfMapFile(const char* parent_filename);
__attribute__((dllimport)) int PyUnstable_PerfTrampoline_CompileCode(PyCodeObject *);
__attribute__((dllimport)) int PyUnstable_PerfTrampoline_SetPersistAfterFork(int enable);

__attribute__((dllimport)) PyObject * PySys_GetObject(const char *);
__attribute__((dllimport)) int PySys_SetObject(const char *, PyObject *);

__attribute__((__deprecated__)) __attribute__((dllimport)) void PySys_SetArgv(int, wchar_t **);
__attribute__((__deprecated__)) __attribute__((dllimport)) void PySys_SetArgvEx(int, wchar_t **, int);

__attribute__((dllimport)) void PySys_WriteStdout(const char *format, ...)
                 __attribute__((format(printf, 1, 2)));
__attribute__((dllimport)) void PySys_WriteStderr(const char *format, ...)
                 __attribute__((format(printf, 1, 2)));
__attribute__((dllimport)) void PySys_FormatStdout(const char *format, ...);
__attribute__((dllimport)) void PySys_FormatStderr(const char *format, ...);

__attribute__((__deprecated__)) __attribute__((dllimport)) void PySys_ResetWarnOptions(void);

__attribute__((dllimport)) PyObject * PySys_GetXOptions(void);

__attribute__((dllimport)) int PySys_Audit(
    const char *event,
    const char *argFormat,
    ...);

__attribute__((dllimport)) int PySys_AuditTuple(
    const char *event,
    PyObject *args);

typedef int(*Py_AuditHookFunction)(const char *, PyObject *, void *);

__attribute__((dllimport)) int PySys_AddAuditHook(Py_AuditHookFunction, void*);
# 11 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/osmodule.h"
__attribute__((dllimport)) PyObject * PyOS_FSPath(PyObject *path);

__attribute__((dllimport)) int PyOS_InterruptOccurred(void);
# 18 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/intrcheck.h"
__attribute__((__deprecated__)) __attribute__((dllimport)) void PyOS_AfterFork(void);

__attribute__((dllimport)) long PyImport_GetMagicNumber(void);
__attribute__((dllimport)) const char * PyImport_GetMagicTag(void);
__attribute__((dllimport)) PyObject * PyImport_ExecCodeModule(
    const char *name,
    PyObject *co
    );
__attribute__((dllimport)) PyObject * PyImport_ExecCodeModuleEx(
    const char *name,
    PyObject *co,
    const char *pathname
    );
__attribute__((dllimport)) PyObject * PyImport_ExecCodeModuleWithPathnames(
    const char *name,
    PyObject *co,
    const char *pathname,
    const char *cpathname
    );

__attribute__((dllimport)) PyObject * PyImport_ExecCodeModuleObject(
    PyObject *name,
    PyObject *co,
    PyObject *pathname,
    PyObject *cpathname
    );

__attribute__((dllimport)) PyObject * PyImport_GetModuleDict(void);

__attribute__((dllimport)) PyObject * PyImport_GetModule(PyObject *name);

__attribute__((dllimport)) PyObject * PyImport_AddModuleObject(
    PyObject *name
    );

__attribute__((dllimport)) PyObject * PyImport_AddModule(
    const char *name
    );

__attribute__((dllimport)) PyObject * PyImport_AddModuleRef(
    const char *name
    );

__attribute__((dllimport)) PyObject * PyImport_ImportModule(
    const char *name
    );
__attribute__((__deprecated__)) __attribute__((dllimport)) PyObject * PyImport_ImportModuleNoBlock(
    const char *name
    );
__attribute__((dllimport)) PyObject * PyImport_ImportModuleLevel(
    const char *name,
    PyObject *globals,
    PyObject *locals,
    PyObject *fromlist,
    int level
    );

__attribute__((dllimport)) PyObject * PyImport_ImportModuleLevelObject(
    PyObject *name,
    PyObject *globals,
    PyObject *locals,
    PyObject *fromlist,
    int level
    );

__attribute__((dllimport)) PyObject * PyImport_GetImporter(PyObject *path);
__attribute__((dllimport)) PyObject * PyImport_Import(PyObject *name);
__attribute__((dllimport)) PyObject * PyImport_ReloadModule(PyObject *m);

__attribute__((dllimport)) int PyImport_ImportFrozenModuleObject(
    PyObject *name
    );

__attribute__((dllimport)) int PyImport_ImportFrozenModule(
    const char *name
    );

__attribute__((dllimport)) int PyImport_AppendInittab(
    const char *name,
    PyObject* (*initfunc)(void)
    );

struct _inittab {
    const char *name;
    PyObject* (*initfunc)(void);
};

extern __attribute__((dllimport)) struct _inittab * PyImport_Inittab;
__attribute__((dllimport)) int PyImport_ExtendInittab(struct _inittab *newtab);

struct _frozen {
    const char *name;
    const unsigned char *code;
    int size;
    int is_package;
};

extern __attribute__((dllimport)) const struct _frozen * PyImport_FrozenModules;

__attribute__((dllimport)) PyObject* PyImport_ImportModuleAttr(
    PyObject *mod_name,
    PyObject *attr_name);
__attribute__((dllimport)) PyObject* PyImport_ImportModuleAttrString(
    const char *mod_name,
    const char *attr_name);
# 199 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/abstract.h"
__attribute__((dllimport)) PyObject * PyObject_CallNoArgs(PyObject *func);
# 211 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/abstract.h"
__attribute__((dllimport)) PyObject * PyObject_Call(PyObject *callable,
                                     PyObject *args, PyObject *kwargs);
# 222 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/abstract.h"
__attribute__((dllimport)) PyObject * PyObject_CallObject(PyObject *callable,
                                           PyObject *args);
# 235 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/abstract.h"
__attribute__((dllimport)) PyObject * PyObject_CallFunction(PyObject *callable,
                                             const char *format, ...);
# 247 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/abstract.h"
__attribute__((dllimport)) PyObject * PyObject_CallMethod(PyObject *obj,
                                           const char *name,
                                           const char *format, ...);
# 259 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/abstract.h"
__attribute__((dllimport)) PyObject * PyObject_CallFunctionObjArgs(PyObject *callable,
                                                    ...);
# 270 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/abstract.h"
__attribute__((dllimport)) PyObject * PyObject_CallMethodObjArgs(
    PyObject *obj,
    PyObject *name,
    ...);

__attribute__((dllimport)) Py_ssize_t PyVectorcall_NARGS(size_t nargsf);

__attribute__((dllimport)) PyObject * PyVectorcall_Call(PyObject *callable, PyObject *tuple, PyObject *dict);

__attribute__((dllimport)) PyObject * PyObject_Vectorcall(
    PyObject *callable,
    PyObject *const *args,
    size_t nargsf,
    PyObject *kwnames);

__attribute__((dllimport)) PyObject * PyObject_VectorcallMethod(
    PyObject *name, PyObject *const *args,
    size_t nargsf, PyObject *kwnames);
# 338 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/abstract.h"
__attribute__((dllimport)) PyObject * PyObject_Type(PyObject *o);
# 347 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/abstract.h"
__attribute__((dllimport)) Py_ssize_t PyObject_Size(PyObject *o);

__attribute__((dllimport)) Py_ssize_t PyObject_Length(PyObject *o);

__attribute__((dllimport)) PyObject * PyObject_GetItem(PyObject *o, PyObject *key);

__attribute__((dllimport)) int PyObject_SetItem(PyObject *o, PyObject *key, PyObject *v);

__attribute__((dllimport)) int PyObject_DelItemString(PyObject *o, const char *key);

__attribute__((dllimport)) int PyObject_DelItem(PyObject *o, PyObject *key);

__attribute__((dllimport)) PyObject * PyObject_Format(PyObject *obj,
                                       PyObject *format_spec);

__attribute__((dllimport)) PyObject * PyObject_GetIter(PyObject *);

__attribute__((dllimport)) PyObject * PyObject_GetAIter(PyObject *);

__attribute__((dllimport)) int PyIter_Check(PyObject *);

__attribute__((dllimport)) int PyAIter_Check(PyObject *);

__attribute__((dllimport)) int PyIter_NextItem(PyObject *iter, PyObject **item);
# 427 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/abstract.h"
__attribute__((dllimport)) PyObject * PyIter_Next(PyObject *);
# 439 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/abstract.h"
__attribute__((dllimport)) PySendResult PyIter_Send(PyObject *, PyObject *, PyObject **);
# 448 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/abstract.h"
__attribute__((dllimport)) int PyNumber_Check(PyObject *o);

__attribute__((dllimport)) PyObject * PyNumber_Add(PyObject *o1, PyObject *o2);

__attribute__((dllimport)) PyObject * PyNumber_Subtract(PyObject *o1, PyObject *o2);

__attribute__((dllimport)) PyObject * PyNumber_Multiply(PyObject *o1, PyObject *o2);

__attribute__((dllimport)) PyObject * PyNumber_MatrixMultiply(PyObject *o1, PyObject *o2);

__attribute__((dllimport)) PyObject * PyNumber_FloorDivide(PyObject *o1, PyObject *o2);

__attribute__((dllimport)) PyObject * PyNumber_TrueDivide(PyObject *o1, PyObject *o2);

__attribute__((dllimport)) PyObject * PyNumber_Remainder(PyObject *o1, PyObject *o2);

__attribute__((dllimport)) PyObject * PyNumber_Divmod(PyObject *o1, PyObject *o2);

__attribute__((dllimport)) PyObject * PyNumber_Power(PyObject *o1, PyObject *o2,
                                      PyObject *o3);

__attribute__((dllimport)) PyObject * PyNumber_Negative(PyObject *o);

__attribute__((dllimport)) PyObject * PyNumber_Positive(PyObject *o);

__attribute__((dllimport)) PyObject * PyNumber_Absolute(PyObject *o);

__attribute__((dllimport)) PyObject * PyNumber_Invert(PyObject *o);

__attribute__((dllimport)) PyObject * PyNumber_Lshift(PyObject *o1, PyObject *o2);

__attribute__((dllimport)) PyObject * PyNumber_Rshift(PyObject *o1, PyObject *o2);

__attribute__((dllimport)) PyObject * PyNumber_And(PyObject *o1, PyObject *o2);

__attribute__((dllimport)) PyObject * PyNumber_Xor(PyObject *o1, PyObject *o2);

__attribute__((dllimport)) PyObject * PyNumber_Or(PyObject *o1, PyObject *o2);

__attribute__((dllimport)) int PyIndex_Check(PyObject *);

__attribute__((dllimport)) PyObject * PyNumber_Index(PyObject *o);

__attribute__((dllimport)) Py_ssize_t PyNumber_AsSsize_t(PyObject *o, PyObject *exc);

__attribute__((dllimport)) PyObject * PyNumber_Long(PyObject *o);

__attribute__((dllimport)) PyObject * PyNumber_Float(PyObject *o);
# 584 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/abstract.h"
__attribute__((dllimport)) PyObject * PyNumber_InPlaceAdd(PyObject *o1, PyObject *o2);

__attribute__((dllimport)) PyObject * PyNumber_InPlaceSubtract(PyObject *o1, PyObject *o2);

__attribute__((dllimport)) PyObject * PyNumber_InPlaceMultiply(PyObject *o1, PyObject *o2);

__attribute__((dllimport)) PyObject * PyNumber_InPlaceMatrixMultiply(PyObject *o1, PyObject *o2);

__attribute__((dllimport)) PyObject * PyNumber_InPlaceFloorDivide(PyObject *o1,
                                                   PyObject *o2);

__attribute__((dllimport)) PyObject * PyNumber_InPlaceTrueDivide(PyObject *o1,
                                                  PyObject *o2);

__attribute__((dllimport)) PyObject * PyNumber_InPlaceRemainder(PyObject *o1, PyObject *o2);

__attribute__((dllimport)) PyObject * PyNumber_InPlacePower(PyObject *o1, PyObject *o2,
                                             PyObject *o3);

__attribute__((dllimport)) PyObject * PyNumber_InPlaceLshift(PyObject *o1, PyObject *o2);

__attribute__((dllimport)) PyObject * PyNumber_InPlaceRshift(PyObject *o1, PyObject *o2);

__attribute__((dllimport)) PyObject * PyNumber_InPlaceAnd(PyObject *o1, PyObject *o2);

__attribute__((dllimport)) PyObject * PyNumber_InPlaceXor(PyObject *o1, PyObject *o2);

__attribute__((dllimport)) PyObject * PyNumber_InPlaceOr(PyObject *o1, PyObject *o2);

__attribute__((dllimport)) PyObject * PyNumber_ToBase(PyObject *n, int base);
# 674 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/abstract.h"
__attribute__((dllimport)) int PySequence_Check(PyObject *o);

__attribute__((dllimport)) Py_ssize_t PySequence_Size(PyObject *o);

__attribute__((dllimport)) Py_ssize_t PySequence_Length(PyObject *o);

__attribute__((dllimport)) PyObject * PySequence_Concat(PyObject *o1, PyObject *o2);

__attribute__((dllimport)) PyObject * PySequence_Repeat(PyObject *o, Py_ssize_t count);

__attribute__((dllimport)) PyObject * PySequence_GetItem(PyObject *o, Py_ssize_t i);

__attribute__((dllimport)) PyObject * PySequence_GetSlice(PyObject *o, Py_ssize_t i1, Py_ssize_t i2);

__attribute__((dllimport)) int PySequence_SetItem(PyObject *o, Py_ssize_t i, PyObject *v);

__attribute__((dllimport)) int PySequence_DelItem(PyObject *o, Py_ssize_t i);

__attribute__((dllimport)) int PySequence_SetSlice(PyObject *o, Py_ssize_t i1, Py_ssize_t i2,
                                    PyObject *v);

__attribute__((dllimport)) int PySequence_DelSlice(PyObject *o, Py_ssize_t i1, Py_ssize_t i2);

__attribute__((dllimport)) PyObject * PySequence_Tuple(PyObject *o);

__attribute__((dllimport)) PyObject * PySequence_List(PyObject *o);
# 746 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/abstract.h"
__attribute__((dllimport)) PyObject * PySequence_Fast(PyObject *o, const char* m);

__attribute__((dllimport)) Py_ssize_t PySequence_Count(PyObject *o, PyObject *value);

__attribute__((dllimport)) int PySequence_Contains(PyObject *seq, PyObject *ob);

__attribute__((dllimport)) int PySequence_In(PyObject *o, PyObject *value);
# 777 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/abstract.h"
__attribute__((dllimport)) Py_ssize_t PySequence_Index(PyObject *o, PyObject *value);
# 786 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/abstract.h"
__attribute__((dllimport)) PyObject * PySequence_InPlaceConcat(PyObject *o1, PyObject *o2);

__attribute__((dllimport)) PyObject * PySequence_InPlaceRepeat(PyObject *o, Py_ssize_t count);

__attribute__((dllimport)) int PyMapping_Check(PyObject *o);

__attribute__((dllimport)) Py_ssize_t PyMapping_Size(PyObject *o);

__attribute__((dllimport)) Py_ssize_t PyMapping_Length(PyObject *o);
# 838 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/abstract.h"
__attribute__((dllimport)) int PyMapping_HasKeyString(PyObject *o, const char *key);

__attribute__((dllimport)) int PyMapping_HasKey(PyObject *o, PyObject *key);

__attribute__((dllimport)) int PyMapping_HasKeyWithError(PyObject *o, PyObject *key);

__attribute__((dllimport)) int PyMapping_HasKeyStringWithError(PyObject *o, const char *key);

__attribute__((dllimport)) PyObject * PyMapping_Keys(PyObject *o);

__attribute__((dllimport)) PyObject * PyMapping_Values(PyObject *o);

__attribute__((dllimport)) PyObject * PyMapping_Items(PyObject *o);

__attribute__((dllimport)) PyObject * PyMapping_GetItemString(PyObject *o,
                                               const char *key);
# 889 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/abstract.h"
__attribute__((dllimport)) int PyMapping_GetOptionalItem(PyObject *, PyObject *, PyObject **);
__attribute__((dllimport)) int PyMapping_GetOptionalItemString(PyObject *, const char *, PyObject **);

__attribute__((dllimport)) int PyMapping_SetItemString(PyObject *o, const char *key,
                                        PyObject *value);

__attribute__((dllimport)) int PyObject_IsInstance(PyObject *object, PyObject *typeorclass);

__attribute__((dllimport)) int PyObject_IsSubclass(PyObject *object, PyObject *typeorclass);

__attribute__((dllimport)) PyObject* _PyObject_CallMethodId(
    PyObject *obj,
    _Py_Identifier *name,
    const char *format, ...);
# 24 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/abstract.h"
__attribute__((dllimport)) PyObject* _PyStack_AsDict(PyObject *const *values, PyObject *kwnames);

static inline Py_ssize_t
_PyVectorcall_NARGS(size_t n)
{
    return n & ~(((size_t)(1)) << (8 * sizeof(size_t) - 1));
}

__attribute__((dllimport)) vectorcallfunc PyVectorcall_Function(PyObject *callable);
# 53 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/abstract.h"
__attribute__((dllimport)) PyObject * PyObject_VectorcallDict(
    PyObject *callable,
    PyObject *const *args,
    size_t nargsf,
    PyObject *kwargs);

__attribute__((dllimport)) PyObject * PyObject_CallOneArg(PyObject *func, PyObject *arg);

static inline PyObject *
PyObject_CallMethodNoArgs(PyObject *self, PyObject *name)
{
    size_t nargsf = 1 | (((size_t)(1)) << (8 * sizeof(size_t) - 1));
    return PyObject_VectorcallMethod(name, &self, nargsf, ((void *)0));
}

static inline PyObject *
PyObject_CallMethodOneArg(PyObject *self, PyObject *name, PyObject *arg)
{
    PyObject *args[2] = {self, arg};
    size_t nargsf = 2 | (((size_t)(1)) << (8 * sizeof(size_t) - 1));
    (void) ((!!(arg != ((void *)0))) || (_assert("arg != NULL","C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/abstract.h",73),0));
    return PyObject_VectorcallMethod(name, args, nargsf, ((void *)0));
}

__attribute__((dllimport)) Py_ssize_t PyObject_LengthHint(PyObject *o, Py_ssize_t);

extern __attribute__((dllimport)) PyTypeObject PyFilter_Type;
extern __attribute__((dllimport)) PyTypeObject PyMap_Type;
extern __attribute__((dllimport)) PyTypeObject PyZip_Type;
# 16 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/pyctype.h"
extern __attribute__((dllimport)) const unsigned int _Py_ctype_table[256];
# 29 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/pyctype.h"
extern __attribute__((dllimport)) const unsigned char _Py_ctype_tolower[256];
extern __attribute__((dllimport)) const unsigned char _Py_ctype_toupper[256];

__attribute__((dllimport)) double PyOS_string_to_double(const char *str,
                                         char **endptr,
                                         PyObject *overflow_exception);

__attribute__((dllimport)) char * PyOS_double_to_string(double val,
                                         char format_code,
                                         int precision,
                                         int flags,
                                         int *type);

__attribute__((dllimport)) int PyOS_mystrnicmp(const char *, const char *, Py_ssize_t);
__attribute__((dllimport)) int PyOS_mystricmp(const char *, const char *);
#include <sys/stat.h> /* clang -E -fkeep-system-includes */
# 44 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/fileutils.h"
__attribute__((dllimport)) wchar_t * Py_DecodeLocale(
    const char *arg,
    size_t *size);

__attribute__((dllimport)) char* Py_EncodeLocale(
    const wchar_t *text,
    size_t *error_pos);

__attribute__((dllimport)) FILE* Py_fopen(
    PyObject *path,
    const char *mode);

__attribute__((__deprecated__)) static inline FILE*
_Py_fopen_obj(PyObject *path, const char *mode)
{
    return Py_fopen(path, mode);
}

__attribute__((dllimport)) int Py_fclose(FILE *file);
# 15 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/cpython/tracemalloc.h"
__attribute__((dllimport)) int PyTraceMalloc_Track(
    unsigned int domain,
    uintptr_t ptr,
    size_t size);

__attribute__((dllimport)) int PyTraceMalloc_Untrack(
    unsigned int domain,
    uintptr_t ptr);
#include <windows.h> /* clang -E -fkeep-system-includes */
#include <fci.h> /* clang -E -fkeep-system-includes */
#include <fcntl.h> /* clang -E -fkeep-system-includes */
#include <msi.h> /* clang -E -fkeep-system-includes */
#include <msidefs.h> /* clang -E -fkeep-system-includes */
#include <msiquery.h> /* clang -E -fkeep-system-includes */
#include <rpc.h> /* clang -E -fkeep-system-includes */

static PyObject* MSIError;

static PyObject* _msi_UuidCreate_impl(PyObject* module) {
    UUID result;
    wchar_t* cresult;
    PyObject* oresult;
    if (UuidCreate(&result) == 1739l) {
        PyErr_SetString(
            PyExc_NotImplementedError, "processing 'no address' result");
        return ((void *)0);
    }
    if (UuidToStringW(&result, &cresult) == 14l) {
        PyErr_SetString(PyExc_MemoryError, "out of memory in uuidgen");
        return ((void *)0);
    }
    oresult = PyUnicode_FromWideChar(cresult, wcslen(cresult));
    RpcStringFreeW(&cresult);
    return oresult;
}

static wchar_t* utf8_to_wchar(const char* s, int* err) {
    PyObject* obj = PyUnicode_FromString(s);
    if (obj == ((void *)0)) {
        if (PyErr_ExceptionMatches(PyExc_MemoryError)) {
            *err = 12;
        } else {
            *err = 22;
        }
        PyErr_Clear();
        return ((void *)0);
    }
    wchar_t* ws = PyUnicode_AsWideCharString(obj, ((void *)0));
    if (ws == ((void *)0)) {
        *err = 12;
        PyErr_Clear();
    }
    Py_DECREF(((PyObject*)((obj))));
    return ws;
}

static void *__attribute__((__cdecl__)) cb_alloc(ULONG cb) { return PyMem_RawMalloc(cb); }

static void __attribute__((__cdecl__)) cb_free(void *memory) { PyMem_RawFree(memory); }

static INT_PTR __attribute__((__cdecl__)) cb_open(char *pszFile,int oflag,int pmode,int *err,void *pv) {
    wchar_t* ws = utf8_to_wchar(pszFile, err);
    if (ws == ((void *)0)) {
        return -1;
    }
    int result = _wopen(ws, oflag | 0x0080, pmode);
    PyMem_Free(ws);
    if (result == -1)
        *err = (*_errno());
    return result;
}

static UINT __attribute__((__cdecl__)) cb_read(INT_PTR hf,void *memory,UINT cb,int *err,void *pv) {
    UINT result = (UINT)_read((int)hf, memory, cb);
    if (result != cb)
        *err = (*_errno());
    return result;
}

static UINT __attribute__((__cdecl__)) cb_write(INT_PTR hf,void *memory,UINT cb,int *err,void *pv) {
    UINT result = (UINT)_write((int)hf, memory, cb);
    if (result != cb)
        *err = (*_errno());
    return result;
}

static int __attribute__((__cdecl__)) cb_close(INT_PTR hf,int *err,void *pv) {
    int result = _close((int)hf);
    if (result != 0)
        *err = (*_errno());
    return result;
}

static long __attribute__((__cdecl__)) cb_seek(INT_PTR hf,long dist,int seektype,int *err,void *pv) {
    long result = (long)_lseek((int)hf, dist, seektype);
    if (result == -1)
        *err = (*_errno());
    return result;
}

static int __attribute__((__cdecl__)) cb_delete(char *pszFile,int *err,void *pv) {
    wchar_t* ws = utf8_to_wchar(pszFile, err);
    if (ws == ((void *)0)) {
        return -1;
    }
    int result = _wremove(ws);
    PyMem_Free(ws);
    if (result != 0)
        *err = (*_errno());
    return result;
}

static int __attribute__((__cdecl__)) cb_fileplaced(PCCAB pccab,char *pszFile,long cbFile,WINBOOL fContinuation,void *pv) { return 0; }

static WINBOOL __attribute__((__cdecl__)) cb_gettempfile(char *pszTempName,int cbTempName,void *pv) {
    char* name = _tempnam("", "tmp");
    if ((name != ((void *)0)) && ((int)strlen(name) < cbTempName)) {
        strcpy(pszTempName, name);
        free(name);
        return 1;
    }
    if (name)
        free(name);
    return 0;
}

static long __attribute__((__cdecl__)) cb_status(UINT typeStatus,ULONG cb1,ULONG cb2,void *pv) {
    if (pv) {
        PyObject* result
            = PyObject_CallMethod(pv, "status", "iii", typeStatus, cb1, cb2);
        if (result == ((void *)0))
            return -1;
        Py_DECREF(((PyObject*)((result))));
    }
    return 0;
}

static WINBOOL __attribute__((__cdecl__)) cb_getnextcabinet(PCCAB pccab,ULONG cbPrevCab,void *pv) {
    if (pv) {
        PyObject* result
            = PyObject_CallMethod(pv, "getnextcabinet", "i", pccab->iCab);
        if (result == ((void *)0))
            return -1;
        if (!PyType_HasFeature((_Py_TYPE(((PyObject*)((result))))), ((1UL << 27)))) {
            PyErr_Format(PyExc_TypeError,
                "Incorrect return type %s from getnextcabinet",
                _Py_TYPE(((PyObject*)((result))))->tp_name);
            Py_DECREF(((PyObject*)((result))));
            return 0;
        }
        strncpy(pccab->szCab, PyBytes_AsString(result), sizeof(pccab->szCab));
        return 1;
    }
    return 0;
}

static INT_PTR __attribute__((__cdecl__)) cb_getopeninfo(char *pszName,USHORT *pdate,USHORT *ptime,USHORT *pattribs,int *err,void *pv) {
    BY_HANDLE_FILE_INFORMATION bhfi;
    FILETIME filetime;
    HANDLE handle;
    wchar_t* ws = utf8_to_wchar(pszName, err);
    if (ws == ((void *)0)) {
        return -1;
    }
    handle = CreateFileW(ws, (0x80000000l), 0x00000001, ((void *)0),
        3, 0x00000080, ((void *)0));
    if (handle == ((HANDLE) (LONG_PTR)-1)) {
        PyMem_Free(ws);
        return -1;
    }
    if (GetFileInformationByHandle(handle, &bhfi) == 0) {
        CloseHandle(handle);
        PyMem_Free(ws);
        return -1;
    }
    FileTimeToLocalFileTime(&bhfi.ftLastWriteTime, &filetime);
    FileTimeToDosDateTime(&filetime, pdate, ptime);
    *pattribs = (int)(bhfi.dwFileAttributes
        & (0x01 | 0x04 | 0x02 | 0x20));
    CloseHandle(handle);
    int result = _wopen(ws, 0x0000 | 0x8000 | 0x0080);
    PyMem_Free(ws);
    return result;
}

static PyObject* _msi_FCICreate_impl(PyObject* module, const char* cabname, PyObject* files) {
    const char* p;
    CCAB ccab;
    HFCI hfci;
    ERF erf;
    Py_ssize_t i;
    if (!PyType_HasFeature((_Py_TYPE(((PyObject*)((files))))), ((1UL << 25)))) {
        PyErr_SetString(PyExc_TypeError, "FCICreate expects a list");
        return ((void *)0);
    }
    ccab.cb = 2147483647;
    ccab.cbFolderThresh = 10000000;
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
        cb_write, cb_close, cb_seek, cb_delete, cb_gettempfile, &ccab, ((void *)0));
    if (hfci == ((void *)0)) {
        PyErr_Format(PyExc_ValueError, "FCI error %d", erf.erfOper);
        return ((void *)0);
    }
    for (i = 0; i < PyList_Size(files); i++) {
        PyObject* item = PyList_GetItemRef(files, i);
        char *filename, *cabname;
        if (!PyArg_ParseTuple(item, "ss", &filename, &cabname)) {
            PyErr_SetString(PyExc_TypeError,
                "FCICreate expects a list of tuples containing two strings");
            FCIDestroy(hfci);
            return ((void *)0);
        }
        if (!FCIAddFile(hfci, filename, cabname, 0, cb_getnextcabinet,
                cb_status, cb_getopeninfo, (((21) << 8) | (0x0003))))
            goto err;
    }
    if (!FCIFlushCabinet(hfci, 0, cb_getnextcabinet, cb_status))
        goto err;
    if (!FCIDestroy(hfci))
        goto err;
    return (&_Py_NoneStruct);
err:
    if (erf.fError)
        PyErr_Format(PyExc_ValueError, "FCI error %d",
            erf.erfOper);
    else
        PyErr_SetString(PyExc_ValueError, "FCI general error");
    FCIDestroy(hfci);
    return ((void *)0);
}

typedef struct msiobj {
    PyObject ob_base; MSIHANDLE h;
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
    DWORD size = (sizeof(buf) / sizeof((buf)[0]) + ((void)sizeof(struct { int dummy; _Static_assert(!__builtin_types_compatible_p(typeof(buf), typeof(&(buf)[0])), "!__builtin_types_compatible_p(typeof(buf), typeof(&(buf)[0]))"); }), 0));
    MSIHANDLE err = MsiGetLastErrorRecord();
    if (err == 0) {
        switch (status) {
        case 5l:
            PyErr_SetString(MSIError, "access denied");
            return ((void *)0);
        case 1627l:
            PyErr_SetString(MSIError, "function failed");
            return ((void *)0);
        case 13l:
            PyErr_SetString(MSIError, "invalid data");
            return ((void *)0);
        case 6l:
            PyErr_SetString(MSIError, "invalid handle");
            return ((void *)0);
        case 5023l:
            PyErr_SetString(MSIError, "invalid state");
            return ((void *)0);
        case 87l:
            PyErr_SetString(MSIError, "invalid parameter");
            return ((void *)0);
        case 110l:
            PyErr_SetString(MSIError, "open failed");
            return ((void *)0);
        case 1631l:
            PyErr_SetString(MSIError, "create failed");
            return ((void *)0);
        default:
            PyErr_Format(MSIError, "unknown error %x", status);
            return ((void *)0);
        }
    }
    code = MsiRecordGetInteger(err, 1);
    if (MsiFormatRecordA(0, err, res, &size) == 234l) {
        res = malloc(size + 1);
        if (res == ((void *)0)) {
            MsiCloseHandle(err);
            return PyErr_NoMemory();
        }
        MsiFormatRecordA(0, err, res, &size);
        res[size] = '\0';
    }
    MsiCloseHandle(err);
    PyErr_SetString(MSIError, res);
    if (res != buf)
        free(res);
    return ((void *)0);
}
# 13 "C:/Users/andrei.iosifescu/scoop/persist/pixi/envs/python/include/internal/pycore_modsupport.h"
extern int _PyArg_NoKwnames(const char *funcname, PyObject *kwnames);

__attribute__((dllimport)) int _PyArg_NoPositional(const char *funcname, PyObject *args);

__attribute__((dllimport)) int _PyArg_NoKeywords(const char *funcname, PyObject *kwargs);

__attribute__((dllimport)) int _PyArg_CheckPositional(const char *, Py_ssize_t, Py_ssize_t, Py_ssize_t);

extern PyObject ** _Py_VaBuildStack(
    PyObject **small_stack,
    Py_ssize_t small_stack_len,
    const char *format,
    va_list va,
    Py_ssize_t *p_nargs);

extern PyObject* _PyModule_CreateInitialized(PyModuleDef*, int apiver);

__attribute__((dllimport)) int _PyArg_ParseStack(
    PyObject *const *args,
    Py_ssize_t nargs,
    const char *format,
    ...);

extern int _PyArg_UnpackStack(
    PyObject *const *args,
    Py_ssize_t nargs,
    const char *name,
    Py_ssize_t min,
    Py_ssize_t max,
    ...);

__attribute__((dllimport)) void _PyArg_BadArgument(
    const char *fname,
    const char *displayname,
    const char *expected,
    PyObject *arg);

__attribute__((dllimport)) int _PyArg_ParseStackAndKeywords(
    PyObject *const *args,
    Py_ssize_t nargs,
    PyObject *kwnames,
    struct _PyArg_Parser *,
    ...);

__attribute__((dllimport)) PyObject * const * _PyArg_UnpackKeywords(
    PyObject *const *args,
    Py_ssize_t nargs,
    PyObject *kwargs,
    PyObject *kwnames,
    struct _PyArg_Parser *parser,
    int minpos,
    int maxpos,
    int minkw,
    int varpos,
    PyObject **buf);
# 368 "src/msilib/_msi.c"
static const char _msi_UuidCreate__doc__[] = "UuidCreate($module, /)\n" "--\n" "\n" "Return the string representation of a new unique identifier.";
# 378 "src/msilib/_msi.c"
static PyObject* _msi_UuidCreate_impl(PyObject* module);

static PyObject* _msi_UuidCreate(
    PyObject* module, PyObject* _unused_ignored __attribute__((unused))) {
    return _msi_UuidCreate_impl(module);
}

static const char _msi_FCICreate__doc__[] = "FCICreate($module, cabname, files, /)\n" "--\n" "\n" "Create a new CAB file.\n" "\n" "  cabname\n" "    the name of the CAB file\n" "  files\n" "    a list of tuples, each containing the name of the file on disk,\n" "    and the name of the file inside the CAB file";
# 401 "src/msilib/_msi.c"
static PyObject* _msi_FCICreate(PyObject* module, PyObject* const* args, Py_ssize_t nargs) {
    PyObject* return_value = ((void *)0);
    const char* cabname;
    PyObject* files;
    if (!((!((2) == 9223372036854775807LL) && (2) <= (nargs) && (nargs) <= (2)) || _PyArg_CheckPositional(("FCICreate"), (nargs), (2), (2)))) {
        goto exit;
    }
    if (!PyType_HasFeature((_Py_TYPE(((PyObject*)((args[0]))))), ((1UL << 28)))) {
        _PyArg_BadArgument("FCICreate", "argument 1", "str", args[0]);
        goto exit;
    }
    Py_ssize_t cabname_length;
    cabname = PyUnicode_AsUTF8AndSize(args[0], &cabname_length);
    if (cabname == ((void *)0)) {
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

static const char _msi_Database_Close__doc__[] = "Close($self, /)\n" "--\n" "\n" "Close the database object.";
# 440 "src/msilib/_msi.c"
static PyObject* _msi_Database_Close_impl(msiobj* self);

static PyObject* _msi_Database_Close(
    msiobj* self, PyObject* _unused_ignored __attribute__((unused))) {
    return _msi_Database_Close_impl(self);
}

static const char _msi_Record_GetFieldCount__doc__[] = "GetFieldCount($self, /)\n" "--\n" "\n" "Return the number of fields of the record.";
# 457 "src/msilib/_msi.c"
static PyObject* _msi_Record_GetFieldCount_impl(msiobj* self);

static PyObject* _msi_Record_GetFieldCount(
    msiobj* self, PyObject* _unused_ignored __attribute__((unused))) {
    return _msi_Record_GetFieldCount_impl(self);
}

static const char _msi_Record_GetInteger__doc__[] = "GetInteger($self, field, /)\n" "--\n" "\n" "Return the value of field as an integer where possible.";
# 474 "src/msilib/_msi.c"
static PyObject* _msi_Record_GetInteger_impl(msiobj* self, unsigned int field);

static PyObject* _msi_Record_GetInteger(msiobj* self, PyObject* arg) {
    PyObject* return_value = ((void *)0);
    unsigned int field;
    field = (unsigned int)PyLong_AsUnsignedLongMask(arg);
    if (field == (unsigned int)-1 && PyErr_Occurred()) {
        goto exit;
    }
    return_value = _msi_Record_GetInteger_impl(self, field);

exit:
    return return_value;
}

static const char _msi_Record_GetString__doc__[] = "GetString($self, field, /)\n" "--\n" "\n" "Return the value of field as a string where possible.";
# 500 "src/msilib/_msi.c"
static PyObject* _msi_Record_GetString_impl(msiobj* self, unsigned int field);

static PyObject* _msi_Record_GetString(msiobj* self, PyObject* arg) {
    PyObject* return_value = ((void *)0);
    unsigned int field;
    field = (unsigned int)PyLong_AsUnsignedLongMask(arg);
    if (field == (unsigned int)-1 && PyErr_Occurred()) {
        goto exit;
    }
    return_value = _msi_Record_GetString_impl(self, field);

exit:
    return return_value;
}

static const char _msi_Record_ClearData__doc__[] = "ClearData($self, /)\n" "--\n" "\n" "Set all fields of the record to 0.";
# 526 "src/msilib/_msi.c"
static PyObject* _msi_Record_ClearData_impl(msiobj* self);

static PyObject* _msi_Record_ClearData(
    msiobj* self, PyObject* _unused_ignored __attribute__((unused))) {
    return _msi_Record_ClearData_impl(self);
}

static const char _msi_Record_SetString__doc__[] = "SetString($self, field, value, /)\n" "--\n" "\n" "Set field to a string value.";
# 543 "src/msilib/_msi.c"
static PyObject* _msi_Record_SetString_impl(
    msiobj* self, int field, const wchar_t* value);

static PyObject* _msi_Record_SetString(
    msiobj* self, PyObject* const* args, Py_ssize_t nargs) {
    PyObject* return_value = ((void *)0);
    int field;
    const wchar_t* value = ((void *)0);
    if (!((!((2) == 9223372036854775807LL) && (2) <= (nargs) && (nargs) <= (2)) || _PyArg_CheckPositional(("SetString"), (nargs), (2), (2)))) {
        goto exit;
    }
    field = PyLong_AsInt(args[0]);
    if (field == -1 && PyErr_Occurred()) {
        goto exit;
    }
    if (!PyType_HasFeature((_Py_TYPE(((PyObject*)((args[1]))))), ((1UL << 28)))) {
        _PyArg_BadArgument("SetString", "argument 2", "str", args[1]);
        goto exit;
    }
    value = PyUnicode_AsWideCharString(args[1], ((void *)0));
    if (value == ((void *)0)) {
        goto exit;
    }
    return_value = _msi_Record_SetString_impl(self, field, value);

exit:
    PyMem_Free((void*)value);
    return return_value;
}

static const char _msi_Record_SetStream__doc__[] = "SetStream($self, field, value, /)\n" "--\n" "\n" "Set field to the contents of the file named value.";
# 586 "src/msilib/_msi.c"
static PyObject* _msi_Record_SetStream_impl(
    msiobj* self, int field, const wchar_t* value);

static PyObject* _msi_Record_SetStream(
    msiobj* self, PyObject* const* args, Py_ssize_t nargs) {
    PyObject* return_value = ((void *)0);
    int field;
    const wchar_t* value = ((void *)0);
    if (!((!((2) == 9223372036854775807LL) && (2) <= (nargs) && (nargs) <= (2)) || _PyArg_CheckPositional(("SetStream"), (nargs), (2), (2)))) {
        goto exit;
    }
    field = PyLong_AsInt(args[0]);
    if (field == -1 && PyErr_Occurred()) {
        goto exit;
    }
    if (!PyType_HasFeature((_Py_TYPE(((PyObject*)((args[1]))))), ((1UL << 28)))) {
        _PyArg_BadArgument("SetStream", "argument 2", "str", args[1]);
        goto exit;
    }
    value = PyUnicode_AsWideCharString(args[1], ((void *)0));
    if (value == ((void *)0)) {
        goto exit;
    }
    return_value = _msi_Record_SetStream_impl(self, field, value);

exit:
    PyMem_Free((void*)value);
    return return_value;
}

static const char _msi_Record_SetInteger__doc__[] = "SetInteger($self, field, value, /)\n" "--\n" "\n" "Set field to an integer value.";
# 629 "src/msilib/_msi.c"
static PyObject* _msi_Record_SetInteger_impl(
    msiobj* self, int field, int value);

static PyObject* _msi_Record_SetInteger(
    msiobj* self, PyObject* const* args, Py_ssize_t nargs) {
    PyObject* return_value = ((void *)0);
    int field;
    int value;
    if (!((!((2) == 9223372036854775807LL) && (2) <= (nargs) && (nargs) <= (2)) || _PyArg_CheckPositional(("SetInteger"), (nargs), (2), (2)))) {
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

static const char _msi_SummaryInformation_GetProperty__doc__[] = "GetProperty($self, field, /)\n" "--\n" "\n" "Return a property of the summary.\n" "\n" "  field\n" "    the name of the property, one of the PID_* constants";
# 668 "src/msilib/_msi.c"
static PyObject* _msi_SummaryInformation_GetProperty_impl(
    msiobj* self, int field);

static PyObject* _msi_SummaryInformation_GetProperty(
    msiobj* self, PyObject* arg) {
    PyObject* return_value = ((void *)0);
    int field;
    field = PyLong_AsInt(arg);
    if (field == -1 && PyErr_Occurred()) {
        goto exit;
    }
    return_value = _msi_SummaryInformation_GetProperty_impl(self, field);

exit:
    return return_value;
}

static const char _msi_SummaryInformation_GetPropertyCount__doc__[] = "GetPropertyCount($self, /)\n" "--\n" "\n" "Return the number of summary properties.";
# 697 "src/msilib/_msi.c"
static PyObject* _msi_SummaryInformation_GetPropertyCount_impl(msiobj* self);

static PyObject* _msi_SummaryInformation_GetPropertyCount(
    msiobj* self, PyObject* _unused_ignored __attribute__((unused))) {
    return _msi_SummaryInformation_GetPropertyCount_impl(self);
}

static const char _msi_SummaryInformation_SetProperty__doc__[] = "SetProperty($self, field, value, /)\n" "--\n" "\n" "Set a property.\n" "\n" "  field\n" "    the name of the property, one of the PID_* constants\n" "  value\n" "    the new value of the property (integer or string)";
# 719 "src/msilib/_msi.c"
static PyObject* _msi_SummaryInformation_SetProperty_impl(
    msiobj* self, int field, PyObject* data);

static PyObject* _msi_SummaryInformation_SetProperty(
    msiobj* self, PyObject* const* args, Py_ssize_t nargs) {
    PyObject* return_value = ((void *)0);
    int field;
    PyObject* data;
    if (!((!((2) == 9223372036854775807LL) && (2) <= (nargs) && (nargs) <= (2)) || _PyArg_CheckPositional(("SetProperty"), (nargs), (2), (2)))) {
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

static const char _msi_SummaryInformation_Persist__doc__[] = "Persist($self, /)\n" "--\n" "\n" "Write the modified properties to the summary information stream.";
# 752 "src/msilib/_msi.c"
static PyObject* _msi_SummaryInformation_Persist_impl(msiobj* self);

static PyObject* _msi_SummaryInformation_Persist(
    msiobj* self, PyObject* _unused_ignored __attribute__((unused))) {
    return _msi_SummaryInformation_Persist_impl(self);
}

static const char _msi_View_Execute__doc__[] = "Execute($self, params, /)\n" "--\n" "\n" "Execute the SQL query of the view.\n" "\n" "  params\n" "    a record describing actual values of the parameter tokens\n" "    in the query or None";
# 773 "src/msilib/_msi.c"
static const char _msi_View_Fetch__doc__[] = "Fetch($self, /)\n" "--\n" "\n" "Return a result record of the query.";
# 783 "src/msilib/_msi.c"
static PyObject* _msi_View_Fetch_impl(msiobj* self);

static PyObject* _msi_View_Fetch(msiobj* self, PyObject* _unused_ignored __attribute__((unused))) {
    return _msi_View_Fetch_impl(self);
}

static const char _msi_View_GetColumnInfo__doc__[] = "GetColumnInfo($self, kind, /)\n" "--\n" "\n" "Return a record describing the columns of the view.\n" "\n" "  kind\n" "    MSICOLINFO_NAMES or MSICOLINFO_TYPES";
# 802 "src/msilib/_msi.c"
static PyObject* _msi_View_GetColumnInfo_impl(msiobj* self, int kind);

static PyObject* _msi_View_GetColumnInfo(msiobj* self, PyObject* arg) {
    PyObject* return_value = ((void *)0);
    int kind;
    kind = PyLong_AsInt(arg);
    if (kind == -1 && PyErr_Occurred()) {
        goto exit;
    }
    return_value = _msi_View_GetColumnInfo_impl(self, kind);

exit:
    return return_value;
}

static const char _msi_View_Modify__doc__[] = "Modify($self, kind, data, /)\n" "--\n" "\n" "Modify the view.\n" "\n" "  kind\n" "    one of the MSIMODIFY_* constants\n" "  data\n" "    a record describing the new data";
# 833 "src/msilib/_msi.c"
static PyObject* _msi_View_Modify_impl(msiobj* self, int kind, PyObject* data);

static PyObject* _msi_View_Modify(
    msiobj* self, PyObject* const* args, Py_ssize_t nargs) {
    PyObject* return_value = ((void *)0);
    int kind;
    PyObject* data;
    if (!((!((2) == 9223372036854775807LL) && (2) <= (nargs) && (nargs) <= (2)) || _PyArg_CheckPositional(("Modify"), (nargs), (2), (2)))) {
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

static const char _msi_View_Close__doc__[] = "Close($self, /)\n" "--\n" "\n" "Close the view.";
# 865 "src/msilib/_msi.c"
static PyObject* _msi_View_Close_impl(msiobj* self);

static PyObject* _msi_View_Close(msiobj* self, PyObject* _unused_ignored __attribute__((unused))) {
    return _msi_View_Close_impl(self);
}

static const char _msi_Database_OpenView__doc__[] = "OpenView($self, sql, /)\n" "--\n" "\n" "Return a view object.\n" "\n" "  sql\n" "    the SQL statement to execute";
# 884 "src/msilib/_msi.c"
static PyObject* _msi_Database_OpenView_impl(msiobj* self, const wchar_t* sql);

static PyObject* _msi_Database_OpenView(msiobj* self, PyObject* arg) {
    PyObject* return_value = ((void *)0);
    const wchar_t* sql = ((void *)0);
    if (!PyType_HasFeature((_Py_TYPE(((PyObject*)((arg))))), ((1UL << 28)))) {
        _PyArg_BadArgument("OpenView", "argument", "str", arg);
        goto exit;
    }
    sql = PyUnicode_AsWideCharString(arg, ((void *)0));
    if (sql == ((void *)0)) {
        goto exit;
    }
    return_value = _msi_Database_OpenView_impl(self, sql);

exit:
    PyMem_Free((void*)sql);
    return return_value;
}

static const char _msi_Database_Commit__doc__[] = "Commit($self, /)\n" "--\n" "\n" "Commit the changes pending in the current transaction.";
# 917 "src/msilib/_msi.c"
static PyObject* _msi_Database_Commit_impl(msiobj* self);

static PyObject* _msi_Database_Commit(
    msiobj* self, PyObject* _unused_ignored __attribute__((unused))) {
    return _msi_Database_Commit_impl(self);
}

static const char _msi_Database_GetSummaryInformation__doc__[] = "GetSummaryInformation($self, count, /)\n" "--\n" "\n" "Return a new summary information object.\n" "\n" "  count\n" "    the maximum number of updated values";
# 938 "src/msilib/_msi.c"
static PyObject* _msi_Database_GetSummaryInformation_impl(
    msiobj* self, int count);

static PyObject* _msi_Database_GetSummaryInformation(
    msiobj* self, PyObject* arg) {
    PyObject* return_value = ((void *)0);
    int count;
    count = PyLong_AsInt(arg);
    if (count == -1 && PyErr_Occurred()) {
        goto exit;
    }
    return_value = _msi_Database_GetSummaryInformation_impl(self, count);

exit:
    return return_value;
}

static const char _msi_OpenDatabase__doc__[] = "OpenDatabase($module, path, persist, /)\n" "--\n" "\n" "Return a new database object.\n" "\n" "  path\n" "    the file name of the MSI file\n" "  persist\n" "    the persistence mode";
# 971 "src/msilib/_msi.c"
static PyObject* _msi_OpenDatabase_impl(
    PyObject* module, const wchar_t* path, int persist);

static PyObject* _msi_OpenDatabase(
    PyObject* module, PyObject* const* args, Py_ssize_t nargs) {
    PyObject* return_value = ((void *)0);
    const wchar_t* path = ((void *)0);
    int persist;
    if (!((!((2) == 9223372036854775807LL) && (2) <= (nargs) && (nargs) <= (2)) || _PyArg_CheckPositional(("OpenDatabase"), (nargs), (2), (2)))) {
        goto exit;
    }
    if (!PyType_HasFeature((_Py_TYPE(((PyObject*)((args[0]))))), ((1UL << 28)))) {
        _PyArg_BadArgument("OpenDatabase", "argument 1", "str", args[0]);
        goto exit;
    }
    path = PyUnicode_AsWideCharString(args[0], ((void *)0));
    if (path == ((void *)0)) {
        goto exit;
    }
    persist = PyLong_AsInt(args[1]);
    if (persist == -1 && PyErr_Occurred()) {
        goto exit;
    }
    return_value = _msi_OpenDatabase_impl(module, path, persist);

exit:
    PyMem_Free((void*)path);
    return return_value;
}

static const char _msi_CreateRecord__doc__[] = "CreateRecord($module, count, /)\n" "--\n" "\n" "Return a new record object.\n" "\n" "  count\n" "    the number of fields of the record";
# 1017 "src/msilib/_msi.c"
static PyObject* _msi_CreateRecord_impl(PyObject* module, int count);

static PyObject* _msi_CreateRecord(PyObject* module, PyObject* arg) {
    PyObject* return_value = ((void *)0);
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
    if ((status = MsiCloseHandle(self->h)) != 0l) {
        return msierror(status);
    }
    self->h = 0;
    return (&_Py_NoneStruct);
}

static PyObject* _msi_Record_GetFieldCount_impl(msiobj* self) {
    return PyLong_FromLong(MsiRecordGetFieldCount(self->h));
}

static PyObject* _msi_Record_GetInteger_impl(msiobj* self, unsigned int field) {
    int status;
    status = MsiRecordGetInteger(self->h, field);
    if (status == 0x80000000) {
        PyErr_SetString(MSIError, "could not convert record field to integer");
        return ((void *)0);
    }
    return PyLong_FromLong((long)status);
}

static PyObject* _msi_Record_GetString_impl(msiobj* self, unsigned int field) {
    unsigned int status;
    WCHAR buf[2000];
    WCHAR* res = buf;
    DWORD size = (sizeof(buf) / sizeof((buf)[0]) + ((void)sizeof(struct { int dummy; _Static_assert(!__builtin_types_compatible_p(typeof(buf), typeof(&(buf)[0])), "!__builtin_types_compatible_p(typeof(buf), typeof(&(buf)[0]))"); }), 0));
    PyObject* string;
    status = MsiRecordGetStringW(self->h, field, res, &size);
    if (status == 234l) {
        res = (WCHAR*)malloc((size + 1) * sizeof(WCHAR));
        if (res == ((void *)0))
            return PyErr_NoMemory();
        status = MsiRecordGetStringW(self->h, field, res, &size);
    }
    if (status != 0l)
        return msierror((int)status);
    string = PyUnicode_FromWideChar(res, size);
    if (buf != res)
        free(res);
    return string;
}

static PyObject* _msi_Record_ClearData_impl(msiobj* self) {
    int status = MsiRecordClearData(self->h);
    if (status != 0l)
        return msierror(status);
    return (&_Py_NoneStruct);
}

static PyObject* _msi_Record_SetString_impl(
    msiobj* self, int field, const wchar_t* value) {
    int status;
    if ((status = MsiRecordSetStringW(self->h, field, value)) != 0l)
        return msierror(status);
    return (&_Py_NoneStruct);
}

static PyObject* _msi_Record_SetStream_impl(
    msiobj* self, int field, const wchar_t* value) {
    int status;
    if ((status = MsiRecordSetStreamW(self->h, field, value)) != 0l)
        return msierror(status);
    return (&_Py_NoneStruct);
}

static PyObject* _msi_Record_SetInteger_impl(
    msiobj* self, int field, int value) {
    int status;
    if ((status = MsiRecordSetInteger(self->h, field, value)) != 0l)
        return msierror(status);
    return (&_Py_NoneStruct);
}

static PyMethodDef record_methods[]
    = { { "GetFieldCount", (PyCFunction)_msi_Record_GetFieldCount, 0x0004, _msi_Record_GetFieldCount__doc__ }, { "GetInteger", (PyCFunction)_msi_Record_GetInteger, 0x0008, _msi_Record_GetInteger__doc__ },
          { "GetString", (PyCFunction)_msi_Record_GetString, 0x0008, _msi_Record_GetString__doc__ }, { "SetString", ((PyCFunction)(((void(*)(void))((_msi_Record_SetString))))), 0x0080, _msi_Record_SetString__doc__ },
          { "SetStream", ((PyCFunction)(((void(*)(void))((_msi_Record_SetStream))))), 0x0080, _msi_Record_SetStream__doc__ }, { "SetInteger", ((PyCFunction)(((void(*)(void))((_msi_Record_SetInteger))))), 0x0080, _msi_Record_SetInteger__doc__ },
          { "ClearData", (PyCFunction)_msi_Record_ClearData, 0x0004, _msi_Record_ClearData__doc__ }, { ((void *)0), ((void *)0) } };

static PyTypeObject record_Type = {
    { { { (((Py_ssize_t)(3ULL << 30)) | (((Py_ssize_t)(4 | 1)) << 48)) }, (((void *)0)) }, (0) }, "_msi.Record",
    sizeof(msiobj),
    0,
    (destructor)msiobj_dealloc,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    PyObject_GenericGetAttr,
    PyObject_GenericSetAttr,
    0,
    ( 0 | 0),
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    record_methods,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
};

static PyObject* record_new(MSIHANDLE h) {
    msiobj* result = ((struct msiobj *)_PyObject_New(&record_Type));
    if (!result) {
        MsiCloseHandle(h);
        return ((void *)0);
    }
    result->h = h;
    return (PyObject*)result;
}

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
    status = MsiSummaryInfoGetPropertyA(
        self->h, field, &type, &ival, &fval, sval, &ssize);
    if (status == 234l) {
        ssize++;
        sval = malloc(ssize);
        if (sval == ((void *)0)) {
            return PyErr_NoMemory();
        }
        status = MsiSummaryInfoGetPropertyA(
            self->h, field, &type, &ival, &fval, sval, &ssize);
    }
    if (status != 0l) {
        return msierror(status);
    }
    switch (type) {
    case VT_I2:
    case VT_I4:
        result = PyLong_FromLong(ival);
        break;
    case VT_FILETIME:
        PyErr_SetString(PyExc_NotImplementedError, "FILETIME result");
        result = ((void *)0);
        break;
    case VT_LPSTR:
        result = PyBytes_FromStringAndSize(sval, ssize);
        break;
    case VT_EMPTY:
        result = _Py_NewRef(((PyObject*)(((&_Py_NoneStruct)))));
        break;
    default:
        PyErr_Format(PyExc_NotImplementedError, "result of type %d", type);
        result = ((void *)0);
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
    if (status != 0l)
        return msierror(status);
    return PyLong_FromLong(result);
}

static PyObject* _msi_SummaryInformation_SetProperty_impl(
    msiobj* self, int field, PyObject* data) {
    int status;
    if (PyType_HasFeature((_Py_TYPE(((PyObject*)((data))))), ((1UL << 28)))) {
        WCHAR* value = PyUnicode_AsWideCharString(data, ((void *)0));
        if (value == ((void *)0)) {
            return ((void *)0);
        }
        status = MsiSummaryInfoSetPropertyW(
            self->h, field, VT_LPSTR, 0, ((void *)0), value);
        PyMem_Free(value);
    } else if (Py_IS_TYPE(((PyObject*)(((data)))), (&PyLong_Type))) {
        long value = PyLong_AsLong(data);
        if (value == -1 && PyErr_Occurred()) {
            return ((void *)0);
        }
        status = MsiSummaryInfoSetPropertyA(
            self->h, field, VT_I4, value, ((void *)0), ((void *)0));
    } else {
        PyErr_SetString(PyExc_TypeError, "unsupported type");
        return ((void *)0);
    }
    if (status != 0l)
        return msierror(status);
    return (&_Py_NoneStruct);
}

static PyObject* _msi_SummaryInformation_Persist_impl(msiobj* self) {
    int status;
    status = MsiSummaryInfoPersist(self->h);
    if (status != 0l)
        return msierror(status);
    return (&_Py_NoneStruct);
}

static PyMethodDef summary_methods[]
    = { { "GetProperty", (PyCFunction)_msi_SummaryInformation_GetProperty, 0x0008, _msi_SummaryInformation_GetProperty__doc__ },
          { "GetPropertyCount", (PyCFunction)_msi_SummaryInformation_GetPropertyCount, 0x0004, _msi_SummaryInformation_GetPropertyCount__doc__ },
          { "SetProperty", ((PyCFunction)(((void(*)(void))((_msi_SummaryInformation_SetProperty))))), 0x0080, _msi_SummaryInformation_SetProperty__doc__ },
          { "Persist", (PyCFunction)_msi_SummaryInformation_Persist, 0x0004, _msi_SummaryInformation_Persist__doc__ }, { ((void *)0), ((void *)0) } };

static PyTypeObject summary_Type = {
    { { { (((Py_ssize_t)(3ULL << 30)) | (((Py_ssize_t)(4 | 1)) << 48)) }, (((void *)0)) }, (0) }, "_msi.SummaryInformation",
    sizeof(msiobj),
    0,
    (destructor)msiobj_dealloc,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    PyObject_GenericGetAttr,
    PyObject_GenericSetAttr,
    0,
    ( 0 | 0),
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    summary_methods,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
};

static PyObject* _msi_View_Execute(msiobj* self, PyObject* oparams) {
    int status;
    MSIHANDLE params = 0;
    if (!(((oparams)) == ((&_Py_NoneStruct)))) {
        if (!Py_IS_TYPE(((PyObject*)((oparams))), (&record_Type))) {
            PyErr_SetString(
                PyExc_TypeError, "Execute argument must be a record");
            return ((void *)0);
        }
        params = ((msiobj*)oparams)->h;
    }
    status = MsiViewExecute(self->h, params);
    if (status != 0l)
        return msierror(status);
    return (&_Py_NoneStruct);
}

static PyObject* _msi_View_Fetch_impl(msiobj* self) {
    int status;
    MSIHANDLE result;
    status = MsiViewFetch(self->h, &result);
    if (status == 259l) {
        return (&_Py_NoneStruct);
    } else if (status != 0l) {
        return msierror(status);
    }
    return record_new(result);
}

static PyObject* _msi_View_GetColumnInfo_impl(msiobj* self, int kind) {
    int status;
    MSIHANDLE result;
    if ((status = MsiViewGetColumnInfo(self->h, kind, &result))
        != 0l)
        return msierror(status);
    return record_new(result);
}

static PyObject* _msi_View_Modify_impl(msiobj* self, int kind, PyObject* data) {
    int status;
    if (!Py_IS_TYPE(((PyObject*)((data))), (&record_Type))) {
        PyErr_SetString(PyExc_TypeError, "Modify expects a record object");
        return ((void *)0);
    }
    if ((status = MsiViewModify(self->h, kind, ((msiobj*)data)->h))
        != 0l)
        return msierror(status);
    return (&_Py_NoneStruct);
}

static PyObject* _msi_View_Close_impl(msiobj* self) {
    int status;
    if ((status = MsiViewClose(self->h)) != 0l)
        return msierror(status);
    return (&_Py_NoneStruct);
}

static PyMethodDef view_methods[] = { { "Execute", (PyCFunction)_msi_View_Execute, 0x0008, _msi_View_Execute__doc__ },
    { "GetColumnInfo", (PyCFunction)_msi_View_GetColumnInfo, 0x0008, _msi_View_GetColumnInfo__doc__ }, { "Fetch", (PyCFunction)_msi_View_Fetch, 0x0004, _msi_View_Fetch__doc__ },
    { "Modify", ((PyCFunction)(((void(*)(void))((_msi_View_Modify))))), 0x0080, _msi_View_Modify__doc__ }, { "Close", (PyCFunction)_msi_View_Close, 0x0004, _msi_View_Close__doc__ }, { ((void *)0), ((void *)0) } };

static PyTypeObject msiview_Type = {
    { { { (((Py_ssize_t)(3ULL << 30)) | (((Py_ssize_t)(4 | 1)) << 48)) }, (((void *)0)) }, (0) }, "_msi.View",
    sizeof(msiobj),
    0,
    (destructor)msiobj_dealloc,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    PyObject_GenericGetAttr,
    PyObject_GenericSetAttr,
    0,
    ( 0 | 0),
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    view_methods,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
};

static PyObject* _msi_Database_OpenView_impl(msiobj* self, const wchar_t* sql) {
    int status;
    MSIHANDLE hView;
    msiobj* result;
    if ((status = MsiDatabaseOpenViewW(self->h, sql, &hView)) != 0l)
        return msierror(status);
    result = ((struct msiobj *)_PyObject_New(&msiview_Type));
    if (!result) {
        MsiCloseHandle(hView);
        return ((void *)0);
    }
    result->h = hView;
    return (PyObject*)result;
}

static PyObject* _msi_Database_Commit_impl(msiobj* self) {
    int status;
    if ((status = MsiDatabaseCommit(self->h)) != 0l)
        return msierror(status);
    return (&_Py_NoneStruct);
}

static PyObject* _msi_Database_GetSummaryInformation_impl(
    msiobj* self, int count) {
    int status;
    MSIHANDLE result;
    msiobj* oresult;
    status = MsiGetSummaryInformationA(self->h, ((void *)0), count, &result);
    if (status != 0l)
        return msierror(status);
    oresult = ((struct msiobj *)_PyObject_New(&summary_Type));
    if (!oresult) {
        MsiCloseHandle(result);
        return ((void *)0);
    }
    oresult->h = result;
    return (PyObject*)oresult;
}

static PyMethodDef db_methods[]
    = { { "OpenView", (PyCFunction)_msi_Database_OpenView, 0x0008, _msi_Database_OpenView__doc__ }, { "Commit", (PyCFunction)_msi_Database_Commit, 0x0004, _msi_Database_Commit__doc__ },
          { "GetSummaryInformation", (PyCFunction)_msi_Database_GetSummaryInformation, 0x0008, _msi_Database_GetSummaryInformation__doc__ },
          { "Close", (PyCFunction)_msi_Database_Close, 0x0004, _msi_Database_Close__doc__ }, { ((void *)0), ((void *)0) } };

static PyTypeObject msidb_Type = {
    { { { (((Py_ssize_t)(3ULL << 30)) | (((Py_ssize_t)(4 | 1)) << 48)) }, (((void *)0)) }, (0) }, "_msi.Database",
    sizeof(msiobj),
    0,
    (destructor)msiobj_dealloc,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    PyObject_GenericGetAttr,
    PyObject_GenericSetAttr,
    0,
    ( 0 | 0),
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    db_methods,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
};
# 1563 "src/msilib/_msi.c"
static PyObject* _msi_OpenDatabase_impl(
    PyObject* module, const wchar_t* path, int persist) {
    int status;
    MSIHANDLE h;
    msiobj* result;
    if (((persist != (SIZE_T)((LPCTSTR)0) && persist != ((SIZE_T)((LPCTSTR)0) | 32/sizeof(*(LPCTSTR)0))) && (persist != (SIZE_T)((LPCTSTR)1) && persist != ((SIZE_T)((LPCTSTR)1) | 32/sizeof(*(LPCTSTR)0))) && (persist != (SIZE_T)((LPCTSTR)2) && persist != ((SIZE_T)((LPCTSTR)2) | 32/sizeof(*(LPCTSTR)0))) && (persist != (SIZE_T)((LPCTSTR)3) && persist != ((SIZE_T)((LPCTSTR)3) | 32/sizeof(*(LPCTSTR)0))) && (persist != (SIZE_T)((LPCTSTR)4) && persist != ((SIZE_T)((LPCTSTR)4) | 32/sizeof(*(LPCTSTR)0)))))
        return msierror(87l);
    status = MsiOpenDatabaseW(path, (LPCWSTR)(SIZE_T)persist, &h);
    if (status != 0l)
        return msierror(status);
    result = ((struct msiobj *)_PyObject_New(&msidb_Type));
    if (!result) {
        MsiCloseHandle(h);
        return ((void *)0);
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

static PyMethodDef msi_methods[] = { { "UuidCreate", (PyCFunction)_msi_UuidCreate, 0x0004, _msi_UuidCreate__doc__ },
    { "FCICreate", ((PyCFunction)(((void(*)(void))((_msi_FCICreate))))), 0x0080, _msi_FCICreate__doc__ }, { "OpenDatabase", ((PyCFunction)(((void(*)(void))((_msi_OpenDatabase))))), 0x0080, _msi_OpenDatabase__doc__ },
    { "CreateRecord", (PyCFunction)_msi_CreateRecord, 0x0008, _msi_CreateRecord__doc__ }, { ((void *)0), ((void *)0) } };

static char msi_doc[] = "Documentation";

static struct PyModuleDef _msimodule = { { { { (((Py_ssize_t)(3ULL << 30)) | (((Py_ssize_t)(4 | 1)) << 48)) }, (((void *)0)) }, ((void *)0), 0, ((void *)0), }, "_msi",
    msi_doc, -1, msi_methods, ((void *)0), ((void *)0), ((void *)0), ((void *)0) };

__attribute__((dllexport)) PyObject* PyInit__msi(void) {
    PyObject* m;
    m = PyModule_Create2((&_msimodule), 1013);
    if (m == ((void *)0))
        return ((void *)0);
    PyModule_AddIntConstant(
        m, "MSIDBOPEN_CREATEDIRECT", (long)(SIZE_T)(LPCTSTR)4);
    PyModule_AddIntConstant(
        m, "MSIDBOPEN_CREATE", (long)(SIZE_T)(LPCTSTR)3);
    PyModule_AddIntConstant(
        m, "MSIDBOPEN_DIRECT", (long)(SIZE_T)(LPCTSTR)2);
    PyModule_AddIntConstant(
        m, "MSIDBOPEN_READONLY", (long)(SIZE_T)(LPCTSTR)0);
    PyModule_AddIntConstant(
        m, "MSIDBOPEN_TRANSACT", (long)(SIZE_T)(LPCTSTR)1);
    PyModule_AddIntConstant(
        m, "MSIDBOPEN_PATCHFILE", (long)(SIZE_T)32/sizeof(*(LPCTSTR)0));
    PyModule_AddIntConstant((m), "MSICOLINFO_NAMES", (MSICOLINFO_NAMES));
    PyModule_AddIntConstant((m), "MSICOLINFO_TYPES", (MSICOLINFO_TYPES));
    PyModule_AddIntConstant((m), "MSIMODIFY_SEEK", (MSIMODIFY_SEEK));
    PyModule_AddIntConstant((m), "MSIMODIFY_REFRESH", (MSIMODIFY_REFRESH));
    PyModule_AddIntConstant((m), "MSIMODIFY_INSERT", (MSIMODIFY_INSERT));
    PyModule_AddIntConstant((m), "MSIMODIFY_UPDATE", (MSIMODIFY_UPDATE));
    PyModule_AddIntConstant((m), "MSIMODIFY_ASSIGN", (MSIMODIFY_ASSIGN));
    PyModule_AddIntConstant((m), "MSIMODIFY_REPLACE", (MSIMODIFY_REPLACE));
    PyModule_AddIntConstant((m), "MSIMODIFY_MERGE", (MSIMODIFY_MERGE));
    PyModule_AddIntConstant((m), "MSIMODIFY_DELETE", (MSIMODIFY_DELETE));
    PyModule_AddIntConstant((m), "MSIMODIFY_INSERT_TEMPORARY", (MSIMODIFY_INSERT_TEMPORARY));
    PyModule_AddIntConstant((m), "MSIMODIFY_VALIDATE", (MSIMODIFY_VALIDATE));
    PyModule_AddIntConstant((m), "MSIMODIFY_VALIDATE_NEW", (MSIMODIFY_VALIDATE_NEW));
    PyModule_AddIntConstant((m), "MSIMODIFY_VALIDATE_FIELD", (MSIMODIFY_VALIDATE_FIELD));
    PyModule_AddIntConstant((m), "MSIMODIFY_VALIDATE_DELETE", (MSIMODIFY_VALIDATE_DELETE));
    PyModule_AddIntConstant((m), "PID_CODEPAGE", ((0x1)));
    PyModule_AddIntConstant((m), "PID_TITLE", (2));
    PyModule_AddIntConstant((m), "PID_SUBJECT", (3));
    PyModule_AddIntConstant((m), "PID_AUTHOR", (4));
    PyModule_AddIntConstant((m), "PID_KEYWORDS", (5));
    PyModule_AddIntConstant((m), "PID_COMMENTS", (6));
    PyModule_AddIntConstant((m), "PID_TEMPLATE", (7));
    PyModule_AddIntConstant((m), "PID_LASTAUTHOR", (8));
    PyModule_AddIntConstant((m), "PID_REVNUMBER", (9));
    PyModule_AddIntConstant((m), "PID_LASTPRINTED", (11));
    PyModule_AddIntConstant((m), "PID_CREATE_DTM", (12));
    PyModule_AddIntConstant((m), "PID_LASTSAVE_DTM", (13));
    PyModule_AddIntConstant((m), "PID_PAGECOUNT", (14));
    PyModule_AddIntConstant((m), "PID_WORDCOUNT", (15));
    PyModule_AddIntConstant((m), "PID_CHARCOUNT", (16));
    PyModule_AddIntConstant((m), "PID_APPNAME", (18));
    PyModule_AddIntConstant((m), "PID_SECURITY", (19));
    MSIError = PyErr_NewException("_msi.MSIError", ((void *)0), ((void *)0));
    if (!MSIError)
        return ((void *)0);
    PyModule_AddObject(m, "MSIError", MSIError);
    return m;
}
