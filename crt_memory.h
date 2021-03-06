#ifndef CRT_MEMORY_H
#define CRT_MEMORY_H

#include "crt_syscall.h"
#include "crt_std.h"
#include <stddef.h>
#include <sys/mman.h>
#include <sys/user.h>

#define CRT_SIZE_USER(ptr)     (*(unsigned long *) ((unsigned long)(ptr) - 2 * sizeof(unsigned long)))
#define CRT_SIZE_ALLOC(ptr)    (*(unsigned long *) ((unsigned long)(ptr) - 1 * sizeof(unsigned long)))
#define CRT_SIZE_HDR           (2 * sizeof(unsigned long))

void free(void *ptr) {
    if (!ptr)
        return;

    _munmap((char *)(ptr) - CRT_SIZE_HDR, CRT_SIZE_ALLOC(ptr));
}

void *realloc(void * addr, size_t size){
    if (!size)
        return NULL;

    if (addr && size < CRT_SIZE_ALLOC(addr) - CRT_SIZE_HDR) {
        CRT_SIZE_USER(addr) = size;
        return addr;
    }

    size_t alloc_size = size + CRT_SIZE_HDR;

    if (alloc_size % PAGE_SIZE)
        alloc_size = ((alloc_size / PAGE_SIZE) + 1) * PAGE_SIZE;

    unsigned long mem = (unsigned long)_mmap(NULL, alloc_size, PROT_READ|PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

    if (mem < 0) {
        return NULL;
    }

    mem += CRT_SIZE_HDR;

    CRT_SIZE_USER(mem) = size;
    CRT_SIZE_ALLOC(mem) = alloc_size;

    if (addr && CRT_SIZE_USER(addr))
        memcpy((void*)mem, addr, CRT_SIZE_USER(addr));

    if (addr)
        free(addr);

    return (void*)mem;
}

void *malloc(size_t len) {
    return realloc(NULL, len);
}

#endif
