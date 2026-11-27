#include <stdint.h>

/* Names describe access widths, not unverified hardware identities or units. */
typedef struct { volatile uint32_t word[12]; } Registers;
extern Registers *handle_a, *handle_b, *output_handle;
extern uint16_t sample_a, sample_b, reference, limit, counter;
extern _Bool hold_outer, hold_inner;
extern uint8_t count_enabled;
extern int32_t outer_previous, outer_current, inner_previous, inner_current;
extern uint16_t read_sample(uint32_t address);
extern void write_pin(uint32_t address, uint16_t mask, uint32_t state);
extern void finish(void *handle);

void IRQ_18(void)
{
    uint16_t demand = 0;
    uint32_t output;
    int32_t outer_error;
    int32_t outer_term;
    int32_t inner_error;
    int32_t inner_term;

    while ((handle_a->word[0] & 4) != 4 || (handle_b->word[0] & 4) != 4) {}
    handle_a->word[0] = 0x14;
    sample_a = read_sample(0x50000000);
    sample_b = read_sample(0x50000100);
    if (sample_a > 3357) write_pin(0x48000c00, 4, 0);
    outer_error = reference - sample_b;
    /* Multiplication preserves the observed LSL, without shifting a negative C value. */
    outer_term = outer_error * 512;
    if (hold_outer != 1) outer_current = outer_previous + outer_error;
    else outer_current = outer_previous;
    if (outer_current + outer_term > 255)
        demand = (outer_current + outer_term) >> 8;
    else demand = 0;
    if (demand >= limit) {
        demand = limit;
        hold_outer = 1;
    } else if (demand == 0) {
        demand = 0;
        hold_outer = 1;
    } else hold_outer = 0;
    outer_previous = outer_current;
    inner_error = demand - sample_a;
    inner_term = inner_error * 64;
    if (hold_inner != 1) inner_current = inner_previous + inner_error;
    else inner_current = inner_previous;
    if (inner_current + inner_term > 127)
        output = (inner_current + inner_term) >> 7;
    else output = 65;
    if (output >= 24480) {
        output = 24480;
        hold_inner = 1;
    } else if (output <= 65) {
        output = 65;
        hold_inner = 1;
    } else hold_inner = 0;
    inner_previous = inner_current;
    output_handle->word[9] = output;
    output_handle->word[10] = output + 27200;
    output_handle->word[11] = (output >> 1) + 3000;
    if (count_enabled) counter++;
    finish(&handle_a);
    finish(&handle_b);
}
