typedef struct {
    unsigned int _r[0x102];
    unsigned int r408;
    unsigned int r40c;
} Dev;

typedef struct {
    unsigned int lo;
    unsigned int hi;
} Pair;

typedef struct {
    Dev *dev;
    unsigned char _pad[216];
    unsigned char dc;
    volatile unsigned char dd;
} Cfg;

unsigned int FUN_080068d8(Cfg *param_1, unsigned int param_2, Pair *param_3)
{
    if (param_1->dd == 2) {
        return 2;
    }
    if (param_1->dc == 1) {
        return 2;
    }
    param_1->dc = 1;
    param_1->dd = 2;
    switch (param_2) {
    case 1:
        param_1->dev->r408 = (param_1->dev->r408 & 0xffffff43u) | ((param_3->lo << 2) | (param_3->hi << 7));
        break;
    case 2:
        param_1->dev->r408 = (param_1->dev->r408 & 0xffff43ffu) | ((param_3->lo << 10) | (param_3->hi << 15));
        break;
    case 4:
        param_1->dev->r408 = (param_1->dev->r408 & 0xff43ffffu) | ((param_3->lo << 18) | (param_3->hi << 23));
        break;
    case 8:
        param_1->dev->r408 = (param_1->dev->r408 & 0x43ffffffu) | ((param_3->lo << 26) | (param_3->hi << 31));
        break;
    case 16:
        param_1->dev->r40c = (param_1->dev->r40c & 0xffffff43u) | ((param_3->lo << 2) | (param_3->hi << 7));
        break;
    case 32:
        param_1->dev->r40c = (param_1->dev->r40c & 0xffff43ffu) | ((param_3->lo << 10) | (param_3->hi << 15));
        break;
    default:
        param_1->dd = 7;
        param_1->dc = 0;
        break;
    }
    if (param_1->dd == 7) {
        return 1;
    }
    param_1->dd = 1;
    param_1->dc = 0;
    return 0;
}
