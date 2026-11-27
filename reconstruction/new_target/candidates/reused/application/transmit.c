#include <stdint.h>

typedef struct {
    uint32_t identifier, id_type, frame_type, length, error_state;
    uint32_t bitrate_switch, fd_format, event_control, marker;
} TransmitHeader;
extern uint32_t can_handle[];
extern uint32_t transmit_id;
extern TransmitHeader transmit_header;
extern uint8_t transmit_data[];
extern uint32_t FUN_080055a4(void *handle);
extern int FUN_0800530c(void *handle, TransmitHeader *header, uint8_t *data);

void FUN_0800215c(uint32_t length)
{
    while (FUN_080055a4(can_handle) == 0) {}
    transmit_header.identifier = transmit_id;
    transmit_header.id_type = 0x40000000;
    transmit_header.frame_type = 0;
    transmit_header.length = length;
    transmit_header.error_state = 0x80000000;
    transmit_header.event_control = 0;
    transmit_header.marker = 0;
    transmit_header.fd_format = 0;
    transmit_header.bitrate_switch = 0;
    FUN_0800530c(can_handle, &transmit_header, transmit_data);
}
