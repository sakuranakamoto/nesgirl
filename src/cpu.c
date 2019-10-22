#include "cpu.h"
#include "nes.h"

void InitCPU(NES_T *NES) {
    NES->CPU.A = 0;
    NES->CPU.X = 0;
    NES->CPU.Y = 0;
}