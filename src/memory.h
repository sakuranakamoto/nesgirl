#ifndef MEMORY_H
#define MEMORY_H
#include <stdint.h>
#include "nes.h"

enum MemoryOffsets {
    PRGROMBank0 = 0x8000,
    PRGROMBank1 = 0xC000,
};

enum MemorySizes {
    PRGROMBankSize = 0x4000,
    TotalMemSize = 0x10000,
    HeaderSize = 16
};

enum SuccessFail InitMem ();
void FreeMem();

#endif