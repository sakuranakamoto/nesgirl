#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "memory.h"
#include "error.h"

int InitMem() {
	mem = malloc(0x10000);

	if (!mem) {
		PrintError((const char *)__PRETTY_FUNCTION__, __FILE__,
			   __LINE__, "[-] Malloc failed");
		return FAIL;
	}
	return SUCCESS;
}

int FreeMem() {
	if (!mem) {
		PrintError((const char *)__PRETTY_FUNCTION__, __FILE__,
			   __LINE__, "[-] Pointer to memory is NULL");
		return FAIL;
	}
	return SUCCESS;
}
