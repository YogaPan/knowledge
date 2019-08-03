#include <stdio.h>

#ifndef COLOR_H
#define COLOR_H

#define CLEAR "\x1b[2J"

#define NRM  "\x1b[0m"
#define RED  "\x1b[31m"
#define GRN  "\x1b[32m"
#define YEL  "\x1b[33m"
#define BLU  "\x1b[34m"
#define MAG  "\x1b[35m"
#define CYN  "\x1b[36m"
#define WHT  "\x1b[37m"
#define RESET "\033[0m"

#define IBLK "\x1b[30;1m"
#define IRED "\x1b[31;1m"
#define IGRN "\x1b[32;1m"
#define IYEL "\x1b[33;1m"
#define IBLU "\x1b[34;1m"
#define IMAG "\x1b[35;1m"
#define ICYN "\x1b[36;1m"
#define IWHT "\x1b[37;1m"

#define BG_BLK "\x1b[40m"
#define BG_RED "\x1b[41m"
#define BG_GRN "\x1b[42m"
#define BG_YEL "\x1b[43m"
#define BG_BLU "\x1b[44m"
#define BG_MAG "\x1b[45m"
#define BG_CYN "\x1b[46m"
#define BG_WHT "\x1b[47m"

#define BG_IBLK "\x1b[40;1m"
#define BG_IRED "\x1b[41;1m"
#define BG_IGRN "\x1b[42;1m"
#define BG_IYEL "\x1b[43;1m"
#define BG_IBLU "\x1b[44;1m"
#define BG_IMAG "\x1b[45;1m"
#define BG_ICYN "\x1b[46;1m"
#define BG_IWHT "\x1b[47;1m"

#define clear() printf(CLEAR)

#define printColor(color, str, ...) \
({ \
    printf(color); \
    printf(str, ##__VA_ARGS__); \
    printf(RESET); \
})

#define draw(x, y, color, str, ...) \
({ \
    printf("%c[%d;%df", 0x1B, y, x); \
    printColor(color, str, ##__VA_ARGS__); \
    fflush(stdout); \
})

#endif
