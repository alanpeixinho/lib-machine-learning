//
// Created by peixinho on 19/12/16.
//

#ifndef ML_ML_MEMORY_H
#define ML_ML_MEMORY_H

#include <ml.h>
#include <gc.h>


void* _mlAlloc(size_t n, size_t size);
void _mlFree(void *mem);

#define ml_alloc(T) ((T*) _mlAlloc (1, sizeof(T)))
#define ml_free(mem) _mlFree(mem)
#define ml_alloc_array(n, T) ((T*) _mlAlloc(n, sizeof(T)))

#endif //ML_ML_MEMORY_H
