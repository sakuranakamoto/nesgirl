#include <stdlib.h>
#include <stdio.h>
#include "memory.h"
#include "error.h"
#include "nes.h"

int InitMem(NES_T *NES) {
	NES->mem = (uint8_t *)malloc(MemSize);

	if (NES->mem == NULL) {
		PrintError((const char *)__PRETTY_FUNCTION__, __FILE__,
			   __LINE__, "[-] Malloc failed");
		return Fail;
	}
	return Success;
}

int FreeMem(uint8_t *mem) {
	if (mem == NULL) {
		PrintError((const char *)__PRETTY_FUNCTION__, __FILE__,
			   __LINE__, "[-] Pointer to memory is NULL");
		return Fail;
	}
	return Success;
}
