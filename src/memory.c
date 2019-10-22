#include <stdlib.h>
#include <stdio.h>
#include "memory.h"
#include "error.h"
#include "nes.h"

int InitMem(NES_T *NES) {
	NES->mem = (uint8_t *)calloc(1,0x10000);

	if (NES->mem == NULL) {
		PrintError((const char *)__PRETTY_FUNCTION__, __FILE__,
			   __LINE__, "[-] Malloc failed");
		return FAIL;
	}
	return SUCCESS;
}

int FreeMem(uint8_t *mem) {
	if (mem == NULL) {
		PrintError((const char *)__PRETTY_FUNCTION__, __FILE__,
			   __LINE__, "[-] Pointer to memory is NULL");
		return FAIL;
	}
	return SUCCESS;
}
