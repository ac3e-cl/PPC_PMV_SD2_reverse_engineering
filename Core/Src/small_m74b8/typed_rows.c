typedef struct {
    volatile unsigned int m0;        /* +0x00 */
    unsigned int res1[6];            /* +0x04 */
    unsigned int r1c;                /* +0x1c */
    unsigned int res2;               /* +0x20 */
    unsigned int r24;                /* +0x24 */
    unsigned int r28;                /* +0x28 */
    unsigned int r2c;                /* +0x2c */
    unsigned char res3[0x80 - 0x30];
} Channel;

typedef struct { unsigned int a; unsigned int pad; unsigned int b, c, d; unsigned char rest[108]; } DataRow;
typedef struct { unsigned char pad[0x9c]; DataRow row[]; } DataBlock;
typedef struct { volatile unsigned int value; unsigned char pad[124]; } ControlRow;
typedef struct { unsigned char pad[0x80]; ControlRow row[]; } ControlBlock;

typedef struct {
    Channel *Instance;
    unsigned char res[0xd8];
    unsigned char dc;                /* +0xdc */
    volatile unsigned char dd;       /* +0xdd */
} Handle;

typedef struct {
    unsigned int v0;
    unsigned int v4;
    unsigned int v8;
} Param;

unsigned int FUN_080074b8(Handle *param_1, int param_2, unsigned int param_3, Param *param_4)
{
    if (param_1->dd == 2) {
        return 2;
    }
    if (param_1->dc == 1) {
        return 2;
    }
    param_1->dc = 1;
    param_1->dd = 2;
    if (param_2 == 6) {
        switch (param_3) {
        case 1:
            param_1->Instance->r1c = param_4->v0;
            break;
        case 2:
            param_1->Instance->r24 = param_4->v0;
            break;
        case 4:
            param_1->Instance->r28 = param_4->v0;
            break;
        case 8:
            param_1->Instance->r2c = param_4->v0;
            break;
        default:
            param_1->dd = 7;
            param_1->dc = 0;
            break;
        }
        if (param_1->dd == 7) {
            return 1;
        }
    } else {
        switch (param_3) {
        case 1:
            ((DataBlock *)param_1->Instance)->row[param_2].a = param_4->v0;
            break;
        case 2:
            ((DataBlock *)param_1->Instance)->row[param_2].b = param_4->v0;
            if (param_4->v4 != 0) {
                ((ControlBlock *)param_1->Instance)->row[param_2].value &= ~0x3000u;
                ((ControlBlock *)param_1->Instance)->row[param_2].value |= param_4->v4;
                if (param_4->v4 == 0x2000) {
                    ((DataBlock *)param_1->Instance)->row[param_2].a = param_4->v8;
                } else if (param_4->v4 == 0x3000) {
                    ((DataBlock *)param_1->Instance)->row[param_2].c = param_4->v8;
                }
            } else {
                ((ControlBlock *)param_1->Instance)->row[param_2].value &= ~0x3000u;
            }
            break;
        case 4:
            ((DataBlock *)param_1->Instance)->row[param_2].c = param_4->v0;
            break;
        case 8:
            ((DataBlock *)param_1->Instance)->row[param_2].d = param_4->v0;
            if (param_4->v4 != 0) {
                ((ControlBlock *)param_1->Instance)->row[param_2].value &= ~0xc000u;
                ((ControlBlock *)param_1->Instance)->row[param_2].value |= param_4->v4 << 2;
                if (param_4->v4 == 0x2000) {
                    ((DataBlock *)param_1->Instance)->row[param_2].a = param_4->v8;
                } else if (param_4->v4 == 0x3000) {
                    ((DataBlock *)param_1->Instance)->row[param_2].c = param_4->v8;
                }
            } else {
                ((ControlBlock *)param_1->Instance)->row[param_2].value &= ~0xc000u;
            }
            break;
        default:
            param_1->dd = 7;
            param_1->dc = 0;
            break;
        }
        if (param_1->dd == 7) {
            return 1;
        }
    }
    param_1->dd = 1;
    param_1->dc = 0;
    return 0;
}
