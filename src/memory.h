#ifndef MEMORY_H
#define MEMORY_H
#include <stdint.h>
#include "nes.h"

#define PRG_ROM_BANK_0 0x8000
#define PRG_ROM_BANK_1 0xC000
#define PRG_ROM_BANK_SIZE 0x4000

int InitMem();
int FreeMem();

#endif