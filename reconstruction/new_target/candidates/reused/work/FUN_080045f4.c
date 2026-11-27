typedef struct {
    volatile unsigned int word0;
    unsigned int _r4[1];
    unsigned int word8;
    unsigned int wordc;
} Dev;

typedef struct {
    Dev *dev;
    unsigned char _pad1[0x1c - 4];
    unsigned char b1c;
    unsigned char b1d;
    unsigned char _pad2[0x5c - 0x1e];
    int f5c;
    int f60;
} Cfg;

extern int FUN_08002f1c(int dev);
extern int FUN_08002f6a(int dev);
extern int FUN_08002ea6(int dev);
extern int FUN_08002ef4(int dev);
extern int FUN_08002f42(int dev);
extern int FUN_08002a18(void);

unsigned int FUN_080045f4(Cfg *param_1, int param_2)
{
    unsigned int counter = 0;
    unsigned int state = param_2;
    unsigned int mask;
    int a = FUN_08002f1c((int)param_1->dev);
    int b = FUN_08002f6a((int)param_1->dev);
    int t0;

    if (a != 0 || b != 0) {
        if ((param_1->dev->wordc & 0x2000000u) != 0
            && param_1->b1d == 1
            && param_1->b1c == 1) {
            state = 1;
            while ((param_1->dev->word0 & 0x40u) != 0x40u) {
                if (counter > 0xa33fffffu) {
                    param_1->f5c = param_1->f5c | 0x10;
                    param_1->f60 = param_1->f60 | 1;
                    return 1;
                }
                counter++;
            }
            param_1->dev->word0 = 0x40;
        }
        if (state != 2) {
            if (FUN_08002f1c((int)param_1->dev) != 0) {
                if (FUN_08002ea6((int)param_1->dev) == 0) {
                    FUN_08002ef4((int)param_1->dev);
                }
            }
        }
        if (state != 1) {
            if (FUN_08002f6a((int)param_1->dev) != 0) {
                if (FUN_08002ea6((int)param_1->dev) == 0) {
                    FUN_08002f42((int)param_1->dev);
                }
            }
        }
        switch (state) {
        case 3:
            mask = 0xc;
            break;
        case 2:
            mask = 8;
            break;
        default:
            mask = 4;
            break;
        }
        t0 = FUN_08002a18();
        while ((mask & param_1->dev->word8) != 0) {
            if ((unsigned int)(FUN_08002a18() - t0) > 5u) {
                if ((mask & param_1->dev->word8) != 0) {
                    param_1->f5c = param_1->f5c | 0x10;
                    param_1->f60 = param_1->f60 | 1;
                    return 1;
                }
            }
        }
    }
    return 0;
}
