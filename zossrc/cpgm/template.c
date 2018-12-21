#include <stdio.h>
#include "wtoutils.h"

int main()
{
    char *message = "Hello World from Metal C";
    WTO_BUF buf = {0};
    buf.len = sprintf(buf.msg, message);
    return wto(&buf);
}