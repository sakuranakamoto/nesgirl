#include "error.h"
#include <stdlib.h>
#include <stdio.h>

void PrintError(const char *function_name, char *file_name, int line_num,
		const char *error_message) {
	fprintf(stderr, "%s\n%s failed in %s on line %d \n", error_message,
		function_name, file_name, line_num);
	PrintStackTrace(2);
};

void PrintStackTrace(int index) {
	void *callstack[128];
	int frames = backtrace(callstack, 128);
	char **backtrace_output = backtrace_symbols(callstack, frames);
	for (; index < frames; ++index) {
		printf("\n\t%s ", backtrace_output[index]);
	}
	printf("\n");
	free(backtrace_output);
}