*=====================================================================*
*        Miscellaneous Equates                                        *
*=====================================================================*
*
NO_SDWA        EQU  12                 ESTAEX entry code for no SDWA
*
ABENDRC        EQU  X'BAD'             2989: ABEND occurred
*
PARMMAX        EQU  100                Maximum char length for PARM=
WTOMAX         EQU  126                Max length WTO TEXT can handle
*=====================================================================*
*        Cross-Memory Equates                                         *
*=====================================================================*
*
ASC_PRIM       EQU  X'000'             Primary ASC mode
ASC_SEC        EQU  X'100'             Secondary ASC mode
ASC_AR         EQU  X'200'             AR ASC mode
ASC_HOME       EQU  X'300'             Home ASC mode
*
ALET_PASN      EQU  0                  Primary ALET
ALET_SASN      EQU  1                  Secondary ALET
ALET_HASN      EQU  2                  Home ALET