#ifndef ERROR_H
#define ERROR_H

#include <execinfo.h>

enum ReturnValue {
	Fail,
	Success,
	ErrorRead
};


void PrintError(const char *function_name, char *file_name, int line_num,
		const char *error_message);
void PrintStackTrace(int index);

#endif
