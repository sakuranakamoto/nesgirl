#include "error.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void PrintStackTrace(FILE *fd,int index) {
	void *callstack[128];
	int frames = backtrace(callstack, 128);
	char **backtrace_output = backtrace_symbols(callstack, frames);
	fprintf(fd, "[Stack Trace]");
	for (; index < frames; ++index) {
		fprintf(fd,"\n\t > %s ", backtrace_output[index]);
	}
	free(backtrace_output);
}

void Log(FILE *fd,const char *filename, const char *function,int line,enum LogType logtype, const char *message) {

	time_t RawTime;
   	struct tm *LocalTime;
   	time( &RawTime);
   	LocalTime = localtime( &RawTime );
	char *local_time = asctime(LocalTime);

	switch(logtype) {
		case Info:
			fprintf(fd, "\n\n[Info]\t@ %s\t[Message]\t%s ",local_time,message);
			break;
		case Error:
			fprintf(fd, "\n\n[Error]\t@ %s\t[Cause]\t\t%s \n\t[File]\t\t%s\n\t[Line]\t\t%d\n\t[Function]\t%s\n\t",local_time,message,filename,line,function);
			PrintStackTrace(fd,2);
			break;
		case Debug:
			fprintf(fd, "\n\n[Debug]\t@ %s\t[Item]\t\t%s\n",local_time,message);
			break;
		}
}