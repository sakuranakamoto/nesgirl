#ifndef ERROR_H
#define ERROR_H

#include <stdlib.h>
#include <stdio.h>
#include <execinfo.h>


#define LOG(logtype,fd,message) \
	Log(fd,__FILE__,(const char *)__PRETTY_FUNCTION__,__LINE__,logtype,message)
	

enum SuccessFail {
	Fail = -1,
	Success
};

enum LogType {
	Info,
	Debug,
	Error
};

void PrintStackTrace(FILE *fd,int index);

void Log(FILE *fd, const char *filename, const char *function, int line,
	 enum LogType logtype, const char *message);

#endif
