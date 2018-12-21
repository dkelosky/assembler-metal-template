#ifndef WTOUTILS_H
#define WTOUTILS_H

typedef struct {
    short int len;
    char msg[70];
} WTO_BUF;

/**
 * wto utilties structures and function prototypes
 */
int wto(WTO_BUF *);

#endif