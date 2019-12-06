#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>

void PrintiNESInfo(char *rom_filename, struct iNES_Header_T *iNES_Header);
void PrintCPURegs(struct CPU_T *CPU,FILE *fd);

#endif