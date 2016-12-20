//
// Created by peixinho on 19/12/16.
//

#include <ml_memory.h>
#include <gc.h>
#include <stdlib.h>

void* _mlAlloc(size_t n, size_t size) {
    return GC_MALLOC(n * size);
}

void _mlFree(void *mem) {
    if(mem)
        GC_FREE(mem);
}