#include <stdint.h>

extern uint32_t receive_header[];
extern uint8_t receive_data[];
extern uint32_t received_identifier;
extern int FUN_08005394(void *handle, uint32_t fifo, void *header, void *data);

void FUN_08001fbc(void *handle, uint32_t unused)
{
    (void)unused;
    FUN_08005394(handle, 0x40, receive_header, receive_data);
    received_identifier = receive_header[0];
}
