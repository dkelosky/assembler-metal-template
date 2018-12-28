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
*              R10: A(DSA)                                            *
*          R11-R12: Work                                              *
*              R13: A(SAVF4SA)                                        *
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
         EJECT ,
*=====================================================================*
*        WTO                                                          *
*                                                                     *
*        Registers upon entry:                                        *
*               R0: N/A                                               *
*               R1: A(Parm vector)                                    *
*           R2-R12: N/A                                               *
*              R13: A(SAVF4SA)                                        *
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
        #ENTRY ROUTINE=WTO             Setup entry
*
         LG    R2,0(,R1)               -> Entry parms
         LARL  R3,WTOMOD               -> WTO parm list model
*
         SLGR  R0,R0                   No multiline
         MVC   WTODSA_WPL,0(R3)        Set WTO model
*
         WTO   TEXT=(R2),              Issue message                   +
               MF=(E,WTODSA_WPL)
*
         LGHI  R15,RTNCD00             Set RC 
*
        #EXIT  ,                       Return
*
         EJECT ,
*=====================================================================*
*        Cosntant Area                                                *
*=====================================================================*
*
         PRINT DATA
*
         DS    0D                      Alignment
WTOMOD   WTO   TEXT=,                  WTO prototype                   +
               ROUTCDE=(11),                                           +
               DESC=(6),                                               +
               MF=L
WTOMODL  EQU   WTOMOD,*-WTOMOD
*
CONSTANT DS    0D                      Literals
         LTORG ,
*
         EJECT ,
*=====================================================================*
*        DSA Area                                                     *
*=====================================================================*
*
        #DSABEG ,                      DSA beginning
        #DSANTRY ,                     DSA entry
WTODSA_WPL       DS    XL(L'WTOMODL)   WTO parameter list
        #DSAEND ,                      DSA end
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
