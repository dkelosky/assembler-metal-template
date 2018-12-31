#include "ams.h"

void open(IHADCB *dcb)
{
    OPEN_PL opl = {0};
    opl.option = OPEN_FLAG;
    OPEN_OUTPUT(*dcb, opl);
}
