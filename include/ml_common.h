//
// Created by Peixinho on 16/12/17.
//

#ifndef ML_ML_COMMON_H_H
#define ML_ML_COMMON_H_H

typedef void (*ml_on_error_function)(const char* func, const char* msg);

extern ml_on_error_function ml_on_error;

void ml_on_error_exit(const char* message, const char* location);

void ml_throw_error(const char* message, const char* location);

#endif //ML_ML_COMMON_H_H
