#include <stdint.h>

typedef struct {
    uint16_t first, second;
    uint8_t zero_a, zero_b, state, terminator;
} ReportData;
extern uint8_t report_enabled;
extern uint32_t report_id;
extern uint16_t sample_first, sample_second;
extern ReportData report_data;
extern void FUN_0800215c(uint32_t length);

void FUN_080021d0(uint32_t *handle)
{
    if (*handle == 0x40001400 && report_enabled != 0) {
        report_id = 0x60010;
        report_data.first = sample_first;
        report_data.second = sample_second;
        report_data.zero_a = 0;
        report_data.zero_b = 0;
        report_data.state = 1;
        report_data.terminator = 0xff;
        FUN_0800215c(8);
    }
}
