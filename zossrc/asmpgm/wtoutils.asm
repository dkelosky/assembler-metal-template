*PROCESS RENT
         GBLC  &MODNAME
&MODNAME SETC  'WTOUTILS'
&MODNAME RSECT ,
&MODNAME AMODE 64
&MODNAME RMODE ANY
*
         SYSSTATE AMODE64=YES,  Set AMODE64 expansions                 +
               ARCHLVL=2,       z/Architecture                         +
               ASCENV=P         Set primary mode expansions             
*
         EJECT ,
*=====================================================================*
*        WTO Utilities module                                         *
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
         EJECT ,
*=====================================================================*
*        Equates                                                      *
*=====================================================================*
*
         COPY  #EQUS                   Copy miscellaneous equates
*
         COPY  #RCODES                 Copy return/reason code equates
*
         COPY  #REGS                   Copy register equates
*
SNAPLRCL EQU   125                     SNAP DD LRECL
SYSPLRCL EQU   132                     SYSPRINT DD LRECL
*
         EJECT ,
*=====================================================================*
*        WTO                                                          *
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
*             2989: ABEND occurred                                    *
*=====================================================================*
*
         ENTRY WTO
WTO      DS    0H
*
*        Save input regs
*
         SAVE  (14,12),,'&MODNAME.  &SYSTIME &SYSDATE' Save regs
C        USING SAVF4SA,R13             Caller's save area
*
*        Clear our DSA
*
         LG    R0,C.SAVF4SANEXT        -> Current NAB
         LGHI  R1,WTODSA_LEN           Length of our DSA
         SLGR  R15,R15                 Pad + length
         MVCL  R0,R14                  Clear our DSA
*
*        Address DSA and CONSTANT
*
         LARL  R11,CONSTANT            -> CONSTANT
         LG    R10,C.SAVF4SANEXT       -> Current NAB
         USING WTODSA,R10              WTODSA addressability
         USING CONSTANT,R11            CONSTANT addressability
*
*        Calculate NAB
*
         LG    R0,C.SAVF4SANEXT        -> Current NAB
         AGHI  R0,WTODSA_LEN           -> Next NAB
*
*        Chain save areas and set new NAB
*
         LA    R2,WTODSA_SAVE          -> Our save area
O        USING SAVF4SA,R2              Caller's save area
         STG   R13,O.SAVF4SAPREV       Save the previous save area
         STG   R0,O.SAVF4SANEXT        -> NAB
*
*        Restore input regs
*
         LMG   R14,R1,C.SAVF4SAG64RS14 -> Restore entry regs R14-R1
         DROP  C,O                     Drop named USINGs of save area
*
*        Set our save area
*
         LGR   R13,R2                  -> Save area
         USING SAVF4SA,R13             Save area addressability
*
*        Work
*
         SLGR  R0,R0                   No multiline
         MVC   WTODSA_WPL,WTOMODL          Set WTO model
*
         LG    R2,0(,R1)
*
         WTO   TEXT=(R2),              Issue message                   +
               MF=(E,WTODSA_WPL)
*
*        Exit linkage
*
         LGHI  R15,13                  Set RC 
         LG    R13,SAVF4SAPREV         -> caller's save area
*
         RETURN (14,12),,RC=(15)       Return to caller
*
         EJECT ,
*=====================================================================*
*        Cosntant Area                                                *
*=====================================================================*
*
         PRINT DATA
CONSTANT DS    0D                      Alignment
*
         DS    0D                      Alignment
WTOMOD   WTO   TEXT=,                  WTO prototype                   +
               ROUTCDE=(11),                                           +
               DESC=(6),                                               +
               MF=L
WTOMODL  EQU   WTOMOD,*-WTOMOD
*
         DS    0D                      Alignment
XTBL     EQU   *-C'0'                  Hex-to-EBCDIC translate table
         DC    C'0123456789ABCDEF'
*
         DS    0D                      Alignment
         LTORG ,
*
         EJECT ,
*=====================================================================*
*        WRK Area                                                     *
*=====================================================================*
*
WTODSA           DSECT ,
*
WTODSA_SAVE      DS    XL(SAVF4SA_LEN) Mainline save area
*
                 DS    0D              Alignment
WTODSA_WPL       DS    XL(L'WTOMODL)   WTO parameter list
*
WTODSA_WTOTX     DS    XL128           Variable text for WTO
*
WTODSA_LEN       EQU   *-WTODSA        Length of WTODSA DSECT
*
         EJECT ,
*=====================================================================*
*        DSECTs                                                       *
*=====================================================================*
*
         IHASAVER ,                                                    +
               SAVER=NO,                                               +
               SAVF4SA=YES
*
         END   &MODNAME
