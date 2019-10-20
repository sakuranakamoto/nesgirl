#ifndef ERROR_H
#define ERROR_H

#include <execinfo.h>

#define ERROR_READ -2
#define FAIL -1
#define SUCCESS 0

void PrintError(const char *function_name, char *file_name, int line_num,
		const char *error_message);
void PrintStackTrace(int index);

#endif
