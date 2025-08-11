// stddef: size_t & NULL
#ifndef STDDEF_H
#define STDDEF_H

#ifndef NULL
#define NULL ((void *)0)
#endif

typedef __SIZE_TYPE__   size_t;
typedef signed long     ssize_t;
typedef unsigned long   uintptr_t;
typedef signed long     intptr_t;
typedef signed long     ptrdiff_t;

#define KB (1024)
#define MB (1024 * KB)
#define GB (1024 * MB)

#endif