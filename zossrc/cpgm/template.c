#include <stdio.h>
#include "wtoutils.h"

void main()
{
    char *message = "Hello World from Metal C";
    WTO_BUF buf = {0};
    buf.len = sprintf(buf.msg, message);
    wto(&buf);
    return;
}