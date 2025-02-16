*PROCESS RENT
         GBLC  &MODNAME
&MODNAME SETC  'TEMPLATE'
&MODNAME RSECT ,
&MODNAME AMODE 31
&MODNAME RMODE ANY
         SYSSTATE ARCHLVL=2
*=====================================================================*
*        Copy this module to use as a simple test program.            *
*                                                                     *
*        Register conventions:                                        *
*            R0-R9: Work                                              *
*              R10: A(WRK)                                            *
*              R11: Work                                              *
*              R12: A(CONSTANT)                                       *
*              R13: A(SAVF1SA)                                        *
*          R14-R15: Work                                              *
*=====================================================================*
*
         YREGS ,
*=====================================================================*
*        Mainline                                                     *
*                                                                     *
*        Registers upon entry:                                        *
*               R0: N/A                                               *
*               R1: A(Parm vector)                                    *
*           R2-R12: N/A                                               *
*              R13: A(SAVF1SA)                                        *
*              R14: Return address                                    *
*              R15: Entry point                                       *
*                                                                     *
*        Registers upon exit:                                         *
*           R0-R14: Restored                                          *
*              R15: Return code                                       *
*                                                                     *
*        Return code and description:                                 *
*                0: Successful                                        *
*=====================================================================*
*
         SPACE ,
***********************************************************************
*        Initial setup                                                *
***********************************************************************
*
         SAVE  (14,12),,'&MODNAME.  &SYSTIME &SYSDATE' Save regs
*
         LARL  R12,CONSTANT            -> CONSTANT
*
         USING CONSTANT,R12            CONSTANT addressabiltiy
*
         LR    R2,R1                   Copy entry parameter address
*
*        OBTAIN WRK area
*
         STORAGE OBTAIN,               Get WRK area                    +
               LENGTH=WRKLEN,            length                        +
               SP=WRKSPID,                 subpool                     +
               LOC=(24,64),                  below the line for OPEN   +
               COND=NO                         abend if no storage
*
         LR    R10,R1                  -> New storage area
*
         USING WRK,R10                 WRK addressability
*
*        Clear WRK area and init
*
         LA    R0,WRK                  -> Output address
         LHI   R1,WRKLEN               = Output length
         SLR   R15,R15                 Pad + input length
         MVCL  R0,R14                  Clear acquired storage
*
         MVC   WRKID,=A(WRKIDC)        Identifier
         MVI   WRKSP,WRKSPID           Subpool
         MVC   WRKLN,=AL3(WRKLEN)      Length
*
         ST    R2,WRKPRMS@             Save entry parameter address
*
*        Chain save areas
*
         LA    R2,WRKSAVE              -> Mainline save area
*
C        USING SAVER,R13               Caller's save area
O        USING SAVER,R2                Our save area
*
         ST    R2,C.SAVNEXT            Save caller's next save area
         ST    R13,O.SAVPREV           Save the previous save area
*
         DROP  C,O                     Drop named USINGs of save area
*
         LR    R13,R2                  -> Save area
*
         USING SAVER,R13               SAVER addressability
*
         SPACE ,
***********************************************************************
*        Test code                                                    *
***********************************************************************
*
TESTCODE DS    0H
*
*        WTO a message
*
         SLR   R0,R0                   No multiline
         WTO   'HELLO WORLD'           Issue message
*
         SPACE ,
***********************************************************************
*        Prepare to exit                                              *
***********************************************************************
*
EXIT     DS    0H
*
*        Restore caller's regs and free WRK area
*
         L     R13,SAVPREV             Point to caller's save area
*
         L     R2,WRKRC                Save return code
         L     R3,WRKRSN               Save reason code
*
         LA    R1,WRK                  R1 -> dynamicly aquired area
*
         STORAGE RELEASE,              Free storage                    +
               LENGTH=WRKLEN,                                          +
               ADDR=(R1)
*
         LR    R15,R2                  Restore return code
         LR    R0,R3                   Restore reason code
*
*        Return to caller
*
         RETURN (14,12),,RC=(15)       Return to caller
*
         SPACE ,
*=====================================================================*
*        Cosntant Area                                                *
*=====================================================================*
*
         PRINT DATA
CONSTANT DS    0D                      Alignment
         LTORG ,
*
         SPACE ,
*=====================================================================*
*        WRK Area                                                     *
*=====================================================================*
*
WRKSPID  EQU   0                       Subpool
*
WRK      DSECT ,
WRKID    DS    CL4                     Identifier
WRKIDC   EQU   C'WRK*'                 Identifier character string
WRKSP    DC    AL1(WRKSPID)            Subpool
WRKLN    DC    AL3(*-*)                Length
*
WRKPRMS@ DS    A                       -> Entry parameters
*
WRKRC    DS    F                       Return code
WRKRSN   DS    F                       Reason code
*
WRKSAVE  DS    XL(SAVER_LEN)           Mainline save area
*
WRKLEN   EQU   *-WRK                   Length of WRK DSECT
*
         SPACE ,
*=====================================================================*
*        DSECTs                                                       *
*=====================================================================*
*
         IHASAVER ,                    SAVER
*
         END   &MODNAME
