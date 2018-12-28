#ifndef WTOUTILS_H
#define WTOUTILS_H

typedef struct {
    short int len;
    char msg[126];
} WTO_BUF;

/**
 * wto utilties structures and function prototypes
 */
void wto(WTO_BUF *);

#endif