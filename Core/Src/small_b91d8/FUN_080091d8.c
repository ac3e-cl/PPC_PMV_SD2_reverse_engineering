/* FUN_080091d8: init/reset of a PMV object (0x080091d8, 174 bytes).
 * Null check -> optional pre-init call, state=2, sub-init(dev, obj+4),
 * then flags 0x3e..0x48 set to 1 and state byte (0x3d) finalised to 1.
 * volatile byte fields reproduce the ldrb.w/uxtb and strb.w -O0 shape. */
#include <stdint.h>

typedef struct {
    void *dev;            /* +0x00 */
    uint8_t pad[0x38];    /* +0x04 */
    volatile uint8_t b3c; /* +0x3c */
    volatile uint8_t b3d; /* +0x3d */
    volatile uint8_t b3e, b3f, b40, b41, b42;
    volatile uint8_t b43, b44, b45, b46, b47, b48;
} pmv_obj_t;

extern void FUN_080025e0(pmv_obj_t *obj);
extern void FUN_080096c4(void *dev, void *arg);

int FUN_080091d8(pmv_obj_t *obj)
{
    if (obj == 0)
        return 1;
    if (obj->b3d == 0) {
        obj->b3c = 0;
        FUN_080025e0(obj);
    }
    obj->b3d = 2;
    FUN_080096c4(obj->dev, (uint8_t *)obj + 4);
    obj->b48 = 1;
    obj->b3e = 1;
    obj->b3f = 1;
    obj->b40 = 1;
    obj->b41 = 1;
    obj->b42 = 1;
    obj->b43 = 1;
    obj->b44 = 1;
    obj->b45 = 1;
    obj->b46 = 1;
    obj->b47 = 1;
    obj->b3d = 1;
    return 0;
}
