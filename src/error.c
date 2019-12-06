#include "error.h"
#include <stdlib.h>
#include <stdio.h>

void PrintStackTrace(FILE *fd,int index) {
	void *callstack[128];
	int frames = backtrace(callstack, 128);
	char **backtrace_output = backtrace_symbols(callstack, frames);
	for (; index < frames; ++index) {
		fprintf(fd,"\n\t%s ", backtrace_output[index]);
	}
	free(backtrace_output);
}

void Log(FILE *fd,const char *filename, const char *function,int line,enum LogType logtype, const char *message) {
	switch(logtype) {
		case Info:
			fprintf(fd, "\n[Info] %s", message);
			break;
		case Error:
			fprintf(fd, "\n[Error] %s \n\toccured in %s on line %d in function %s\n\t",message,filename,line,function);
			PrintStackTrace(fd,2);
			break;
		}
}