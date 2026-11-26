#include "registers.h"

void FUN_08002d14(Registers *r, uint32_t channels, uint32_t mode)
{
    r->AWD2CR = (r->AWD2CR & ~(channels & 0x7ffffU)) | ((0x7ffffU >> (mode & 0x18U)) & channels & 0x7ffffU);
}
