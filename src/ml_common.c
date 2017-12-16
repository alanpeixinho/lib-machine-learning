//
// Created by Peixinho on 16/12/17.
//

#include <ml_common.h>
#include <stdlib.h>

ml_on_error_function ml_on_error = ml_on_error_exit;

void ml_on_error_exit(const char* message, const char* location) {
	printf("%s => %s\n", location, message);
	exit(42);
}

void ml_throw_error(const char* message, const char* location) {
	if(ml_on_error!=NULL) {
		ml_on_error(message, location);
	}
}