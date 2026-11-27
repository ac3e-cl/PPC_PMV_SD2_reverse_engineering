typedef struct {
    unsigned char reserved[0xdc];
    unsigned char state_dc;
    volatile unsigned char state_dd;
} Handle;

extern void FUN_08007e7c(Handle *, unsigned int, void *);
extern void FUN_0800810c(Handle *, unsigned int);

unsigned int FUN_08007352(Handle *handle, unsigned int param_2, void *param_3)
{
    if ((unsigned char)(signed char)handle->state_dd == 2) {
        return 2;
    }
    if (handle->state_dc == 1) {
        return 2;
    }
    handle->state_dc = 1;
    handle->state_dd = 2;
    FUN_08007e7c(handle, param_2, param_3);
    FUN_0800810c(handle, param_2);
    handle->state_dd = 1;
    handle->state_dc = 0;
    return 0;
}
