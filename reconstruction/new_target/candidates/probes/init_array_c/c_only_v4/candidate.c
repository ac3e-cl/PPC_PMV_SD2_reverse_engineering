#include <stdint.h>
#include <stdatomic.h>

typedef void (*init_fn_t)(void);
extern init_fn_t __preinit_array_start[];
extern init_fn_t __preinit_array_end[];
extern init_fn_t __init_array_start[];
extern init_fn_t __init_array_end[];
extern void _init(void);

void FUN_080095f4(void) {
    intptr_t bytes = (intptr_t)__preinit_array_end - (intptr_t)__preinit_array_start;
    int count = (int)(bytes >> 2);
    init_fn_t *cursor = __preinit_array_start;
    int index = 0;
    while (index != count) {
        init_fn_t current = *cursor++;
        current();
        index++;
    }

    _init();
    atomic_signal_fence(memory_order_seq_cst);

    cursor = __init_array_start;
    bytes = (intptr_t)__init_array_end - (intptr_t)__init_array_start;
    count = (int)(bytes >> 2);
    index = 0;
    while (index != count) {
        init_fn_t current = *cursor++;
        current();
        index++;
    }
}
