#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wto.h"
#include "storage.h"
#include "dcbd.h"
#include "ams.h"
#include "z.h"
typedef struct {
    char eye[4];
    int len;
    unsigned int flag0 : 1;
    unsigned int flag1 : 1;
    unsigned int flag2 : 1;
    unsigned int flag3 : 1;
    unsigned int flag4 : 1;
    unsigned int flag5 : 1;
    unsigned int flag6 : 1;
    unsigned int flag7 : 1;
    unsigned int reserved;
} CTRL_BLOCK;

void main()
{
    char inbuff[80] = {0};
    char writeBuf[132] = {0};

    CTRL_BLOCK someCtrl = {"CTRL"};
    someCtrl.len = sizeof(CTRL_BLOCK);
    someCtrl.flag1 &= 1;
    someCtrl.flag7 &= 1;
    // someCtrl.flag6 &= 1;
    // someCtrl.reserved = 0xDEADEAD;

    IO_CTRL *sysprintIoc = openOutputAssert("SYSPRINT", 132, 132, dcbrecf + dcbrecbr);
    IO_CTRL *snapIoc = openOutputAssert("SNAP", 125, 1632, dcbrecv + dcbrecbr + dcbrecca);
    IO_CTRL *inIoc = openInputAssert("IN", 80, 80, dcbrecf);

    SNAP_HEADER header = {23, "Important Control Block"};

    snap(&snapIoc->dcb, &header, &someCtrl, sizeof(someCtrl));

    while (0 == readSync(inIoc, inbuff))
    {
        memset(writeBuf, ' ', 132);
        memcpy(writeBuf, inbuff, 80);
        writeSync(sysprintIoc, writeBuf);
    }

    closeAssert(sysprintIoc);
    closeAssert(snapIoc);
    closeAssert(inIoc);
}