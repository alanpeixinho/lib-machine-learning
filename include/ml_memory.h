//
// Created by peixinho on 19/12/16.
//

#ifndef ML_ML_MEMORY_H
#define ML_ML_MEMORY_H

#include <ml.h>


void* _mlAlloc(size_t n, size_t size);
void _mlFree(void *mem);

#define mlAlloc(T) ((T*) _mlAlloc (1, sizeof(T)))
#define mlFree(mem) _mlFree(mem)
#define mlAllocArray(n, T) ((T*) _mlAlloc(n, sizeof(T)))

#endif //ML_ML_MEMORY_H
