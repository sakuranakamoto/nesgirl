#include <stdlib.h>
#include <stdio.h>
#include "memory.h"
#include "error.h"
#include "nes.h"

enum SuccessFail InitMem(struct NES_T *NES) {
	NES->mem = (uint16_t *)malloc(TotalMemSize);

	if (NES->mem == NULL) {
		LOG(Error,stderr,"Malloc failed");
		return Fail;
	}
	return Success;
}

void FreeMem(uint8_t *mem) {
	if (mem == NULL) {
		LOG(Error,stderr,"Pointer to memory is NULL");
	}

	else {
		free(mem);
	}
}
