#include "cpu.h"
#include "nes.h"
#include <arpa/inet.h>
#include "memory.h"
#include <string.h>
#include <stdio.h>

void InitCPU(struct NES_T *NES) {
	NES->CPU.A = 0;
	NES->CPU.X = 0;
	NES->CPU.Y = 0;
	NES->CPU.PC =
		NES->mem[ResetAddress] + (NES->mem[ResetAddress + 1] << 8);
}
