#include <stdbool.h>
#include <stdint.h>

extern void FUN_08004ed4(uint32_t grouping);
extern uint8_t FUN_08002980(uint32_t timeout);
extern void FUN_08002250(void);

bool FUN_0800294e(void)
{
    bool success = false;

    FUN_08004ed4(3u);
    if (FUN_08002980(15u) != 0u) {
        success = true;
    } else {
        FUN_08002250();
    }
    return success;
}
