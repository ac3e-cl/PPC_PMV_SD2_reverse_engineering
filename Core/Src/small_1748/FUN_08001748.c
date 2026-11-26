/* ADC2 base init + first channel config (0x08001748).
 * handle @0x20000094, ADC2 instance 0x50000100, HAL-ish init 0x08002f90,
 * channel-config init 0x08003d74, fatal halt 0x08002244, memset 0x080099e4. */
#include <stdint.h>
#include <string.h>

typedef struct {
    uint32_t Instance;      /* 0x00 ADC2 base */
    uint32_t ClockMode;     /* 0x04 = 0x30000 */
    uint32_t Overrun;       /* 0x08 */
    uint32_t Alignment;     /* 0x0c */
    uint32_t Continuous;    /* 0x10 */
    uint32_t TrigEdge;      /* 0x14 */
    uint32_t TrigSrc;       /* 0x18 = 4 */
    uint8_t  LowPower;      /* 0x1c */
    uint8_t  DiscMode;      /* 0x1d */
    uint16_t pad1e;
    uint32_t WaitMode;      /* 0x20 = 1 */
    uint8_t  b24;           /* 0x24 */
    uint8_t  pad25[7];
    uint32_t w2c;           /* 0x2c */
    uint32_t w30;           /* 0x30 */
    uint8_t  pad34[4];
    uint8_t  b38;           /* 0x38 */
    uint32_t w3c;           /* 0x3c */
    uint8_t  b40;           /* 0x40 */
} AdcHandle;
extern volatile AdcHandle ADC2_HANDLE;

typedef struct {
    uint32_t w[8];
} AdcChannelConf;

extern int FUN_08002f90(volatile AdcHandle *hadc);
extern int FUN_08003d74(volatile AdcHandle *hadc, volatile AdcChannelConf *s);
extern void FUN_08002244(void);

void FUN_08001748(void)
{
    volatile AdcChannelConf conf;

    memset((void *)&conf, 0, sizeof conf);
    ADC2_HANDLE.Instance = 0x50000100u;
    ADC2_HANDLE.ClockMode = 0x30000u;
    ADC2_HANDLE.Overrun = 0;
    ADC2_HANDLE.Alignment = 0;
    ADC2_HANDLE.Continuous = 0;
    ADC2_HANDLE.TrigEdge = 0;
    ADC2_HANDLE.TrigSrc = 4;
    ADC2_HANDLE.LowPower = 0;
    ADC2_HANDLE.DiscMode = 0;
    ADC2_HANDLE.WaitMode = 1;
    ADC2_HANDLE.b24 = 0;
    ADC2_HANDLE.w2c = 0;
    ADC2_HANDLE.w30 = 0;
    ADC2_HANDLE.b38 = 0;
    ADC2_HANDLE.w3c = 0;
    ADC2_HANDLE.b40 = 0;
    if (FUN_08002f90((volatile AdcHandle *)&ADC2_HANDLE) != 0) {
        FUN_08002244();
    }
    conf.w[0] = 0x14f00020u;
    conf.w[1] = 6;
    conf.w[2] = 0;
    conf.w[3] = 0x7f;
    conf.w[4] = 4;
    conf.w[5] = 0;
    if (FUN_08003d74((volatile AdcHandle *)&ADC2_HANDLE, (volatile AdcChannelConf *)&conf) != 0) {
        FUN_08002244();
    }
}
