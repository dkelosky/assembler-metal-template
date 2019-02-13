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
*             2989: ABEND occurred                                    *
*=====================================================================*
*
         EJECT ,
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
         LAM   AR0,AR15,ZEROS          Clear ARs
         LMH   R0,R15,ZEROS            Clear high-halves of GPRs
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
*        Establish recovery
*
         LARL  R14,RECOVERY            -> Recovery routine
*
         ESTAEX (R14),                 Establish recovery              +
               PARAM=WRK,                pass WRK as parm              +
               RECORD=NO,                  no LOGREC recording         +
               MF=(E,WRKSTAPL)
*
*        Open SNAP and SYSPRINT DDs
*
         MVC   WRKSNDCB,SNAPM          Copy DCB info
         MVC   WRKSYDCB,SYSPM          Copy DCB info
*
         MVC   WRKOPNPL,OPENM          Set OPEN macro model
*
         OPEN  (WRKSNDCB,(OUTPUT)),    Open output file                +
               MF=(E,WRKOPNPL)
*
         OPEN  (WRKSYDCB,(OUTPUT)),    Open output file                +
               MF=(E,WRKOPNPL)
*
*        Verify SNAP and SYSPRINT open success
*
         USING IHADCB,R1               IHADCB addressability
*
         LA    R1,WRKSNDCB             -> DCB
         TM    DCBOFLGS,DCBOFOPN       Is the file OPEN??
         JO    *+L'*+6                 Yes, continue
         EXRL  0,*                     *** S0C3 ***
*
         LA    R1,WRKSYDCB             -> DCB
         TM    DCBOFLGS,DCBOFOPN       Is the file OPEN??
         JO    *+L'*+6                 Yes, continue
         EXRL  0,*                     *** S0C3 ***
*
         DROP  R1                      Drop IHADCB
*
*        Copy entry parms
*
         L     R1,WRKPRMS@             -> Entry parameters
         JAS   R14,COPYPRMS            Copy entry parameters
*
*        WTO INIT return code / reason code
*
         MVC   WRKDESC,=CL16'INIT'     Set message description
         JAS   R14,WRITRSLT            Issue result
*
         EJECT ,
***********************************************************************
*        Test code                                                    *
***********************************************************************
*
TESTCODE DS    0H
*
*        Snap data
*
         SNAP  DCB=WRKSNDCB,                                           +
               ID=1,                                                   +
               PDATA=REGS,                                             +
               STORAGE=(WRKSNAPB,WRKSNAPE-1),                          +
               STRHDR=(SNAPHDR),                                       +
               MF=(E,WRKSNAP)
*
*        Print data
*
         MVI   WRKOUTBF,C' '           Move in a blank
         MVC   WRKOUTBF+1(L'WRKOUTBF-1),WRKOUTBF Clear output line
         MVC   WRKOUTBF(5),=C'@TEST'   Move in a literal
*
         PUT   WRKSYDCB,WRKOUTBF       Write it
*
*        WTO a message
*
         SLR   R0,R0                   No multiline
         WTO   '&MODNAME - @TEST1'     Issue message
*
*        WAIT 10 seconds
*
*@TEST   LGHI  R2,10            10
*@TEST   MGHI  R2,100           Convert seconds to .01 units
*@TEST   ST    R2,WRKFULL       Time out interval
*@TEST
*@TEST   STIMER WAIT,           Establish watch dog timer              +
               BINTVL=WRKFULL
*
*        WAIT program execution
*
         JAS   R14,WTORWAIT            WAIT program
*
         ORG   *-4                     Backup to WTORWAIT call
         JNOP  *                         and do nothing instead
*
*        Prepare to exit
*
         J     EXIT                    Prepare to exit
*
         EJECT ,
***********************************************************************
*        ABEND resumption point                                       *
***********************************************************************
*
RESUME   DS    0H
         OI    WRKFLAG3,WRK3RSME       Note RESUME entered
*
*        WTO ABEND return code / reason code
*
         MVC   WRKDESC,=CL16'ABEND'    Set message description
         MVC   WRKRC,WRKABCC           Set RC  = ABEND RC
         MVC   WRKRSN,WRKABRSN         Set RSN = ABEND RSN
         JAS   R14,WRITRSLT            Issue result
*
*        Set exit return code / reason code
*
         MVC   WRKRC,=A(ABENDRC)       Set ABEND RC
         MVC   WRKRSN,=A(RSNCD00)      Set no RSN
*
         EJECT ,
***********************************************************************
*        Prepare to exit                                              *
***********************************************************************
*
EXIT     DS    0H
*
         USING IHADCB,R1               IHADCB addressability
*
*        Close SNAP
*
         LA    R1,WRKSNDCB             -> DCB
         TM    DCBOFLGS,DCBOFOPN       Is the file OPEN??
         JNO   EXIT1000                No, skip close
*
         CLOSE (WRKSNDCB),             Close output file               +
               MF=(E,WRKOPNPL)
*
*        Close SYSPRINT
*
EXIT1000 DS    0H
         LA    R1,WRKSYDCB             -> DCB
         TM    DCBOFLGS,DCBOFOPN       Is the file OPEN??
         JNO   EXIT2000                No, skip close
*
         CLOSE (WRKSYDCB),             Close output file               +
               MF=(E,WRKOPNPL)
*
         DROP  R1                      Drop IHADCB
*
*        WTO TERM successful
*
EXIT2000 DS    0H
         MVC   WRKDESC,=CL16'TERM'     Set message description
         MVC   WRKRC,=A(RTNCD00)       Set RC  = 0
         MVC   WRKRSN,=A(RSNCD00)      Set RSN = 0
         JAS   R14,WRITRSLT            Issue result
*
*        Drop recovery
*
         ESTAEX 0,                     Drop recovery                   +
               MF=(E,WRKSTAPL)
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
         EJECT ,
*=====================================================================*
*        COPYPRMS subroutine                                          *
*          Copies the supplied entry parameters to the local work     *
*          area.                                                      *
*                                                                     *
*          Set WRKDESC, WRKRC, and WRKRSN before calling subroutine.  *
*                                                                     *
*        Registers upon entry:                                        *
*               R0: N/A                                               *
*               R1: A(Entry parameters)                               *
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
         USING CONSTANT,R12            CONSTANT addressability
         USING WRK,R10                 WRK addressability
*
         EJECT ,
***********************************************************************
*        Routine entry point                                          *
***********************************************************************
*
COPYPRMS DS    0H
         SAVE  (14,12),,'COPYPRMS  &SYSTIME &SYSDATE' Save regs
*
*        Chain save areas
*
         LA    R2,WRKSAVS              -> Subroutine save area
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
         USING SAVER,R13               Save area addressability
*
         EJECT ,
***********************************************************************
*        Determine if we have entry parameters                        *
***********************************************************************
*
         NILH  R1,X'7FFF'              Clear high bit
         LTR   R1,R1                   Any vector pointer??
         JZ    COPYP904                No, exit RC = 4
*
         L     R1,0(,R1)               -> Len + parms
         NILH  R1,X'7FFF'              Clear high bit
         LTR   R1,R1                   Any parameter pointer??
         JZ    COPYP904                No, exit RC = 4
*
         LH    R2,0(,R1)               Parm string length
         LTR   R2,R2                   Positive length??
         JNP   COPYP904                No, exit RC = 4
*
         CHI   R2,PARMMAX              Over max length??
         JH    COPYP904                Yes, exit RC = 4
*
         EJECT ,
***********************************************************************
*        Copy entry parameters                                        *
***********************************************************************
*
         STH   R2,WRKPRMSL             Save entry length
         BCTR  R2,R0                   Less one for machine length
*
         LA    R1,L'WRKPRMSL(,R1)      -> Input text
         LA    R3,WRKPRMS              -> Work area target
         EXRL  R2,MOVEPRMS             Copy to storage area
*
*        Log that we copied entry parameters
*
         SLR   R0,R0                   No multiline
         MVC   WRKWPL,WTOMODL          Set WTO model
*
         WTO   TEXT=MSG0,              Issue message                   +
               MF=(E,WRKWPL)
*
*        Log entry parameter data
*
         MVC   WRKWTOTX(L'MESSAGE1),MESSAGE1
*
         LH    R2,WRKPRMSL             Get parms length
         BCTR  R2,R0                   Less one for machine length
*
         LA    R1,WRKPRMS                  -> Input text
         LA    R3,WRKWTOTX+(MSG1_PRM-MSG1) -> Print buffer target
         EXRL  R2,PRNTPRMS                 Copy to print buffer
*
         SLR   R0,R0                   Clear for WTO
         MVC   WRKWPL,WTOMODL          Copy WPL prototype
*
         WTO   TEXT=WRKWTOTX,          Write it                        +
               MF=(E,WRKWPL)
*
         J     COPYP900                Exit RC = 0
*
MOVEPRMS MVC   0(*-*,R3),0(R1)         *** Executed instruction ***
PRNTPRMS MVC   0(*-*,R3),0(R1)         *** Executed instruction ***
*
         EJECT ,
***********************************************************************
*        Routine exit point                                           *
***********************************************************************
*
COPYP900 DS    0H
         LHI   R15,RTNCD00             Set RC = 0
         J     COPYP999                Exit
*
COPYP904 DS    0H
         LHI   R15,RTNCD04             Set RC = 0
*->NSI   J     COPYP999                Exit
*
COPYP999 DS    0H
         L     R13,SAVPREV             Point to caller's save area
         RETURN (14,12),,RC=(15)       Return to caller
*
         DROP ,                        Drop all addressability
*
         EJECT ,
*=====================================================================*
*        WRITRSLT subroutine                                          *
*          Uses WTO to write 8-character description and return /     *
*          reason codes.                                              *
*                                                                     *
*          Set WRKDESC, WRKRC, and WRKRSN before calling subroutine.  *
*                                                                     *
*        Registers upon entry:                                        *
*           R0-R12: N/A                                               *
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
         USING CONSTANT,R12            CONSTANT addressability
         USING WRK,R10                 WRK addressability
*
         EJECT ,
***********************************************************************
*        Routine entry point                                          *
***********************************************************************
*
WRITRSLT DS    0H
         SAVE  (14,12),,'WRITRSLT  &SYSTIME &SYSDATE' Save regs
*
*        Chain save areas
*
         LA    R2,WRKSAVS              -> Subroutine save area
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
         USING SAVER,R13               Save area addressability
*
*        Build message
*
         MVC   WRKWTOTX(L'MESSAGE2),MESSAGE2 Init message
*
         MVC   WRKWTOTX+(MSG2_DSC-MSG2)(L'MSG2_DSC),WRKDESC
*
         UNPK  WRKHEX(9),WRKRC(5)      Return Code
         TR    WRKHEX,XTBL               to EBCDIC
         MVC   WRKWTOTX+(MSG2_RC-MSG2)(L'MSG2_RC),WRKHEX
*
         UNPK  WRKHEX(9),WRKRSN(5)     Reason code
         TR    WRKHEX,XTBL               to EBCDIC
         MVC   WRKWTOTX+(MSG2_RSN-MSG2)(L'MSG2_RSN),WRKHEX
*
*        Issue message
*
         SLR   R0,R0                   Clear for WTO
         MVC   WRKWPL,WTOMODL          Copy WPL prototype
*
         WTO   TEXT=WRKWTOTX,          Write it                        +
               MF=(E,WRKWPL)
*
         EJECT ,
***********************************************************************
*        Routine exit point                                           *
***********************************************************************
*
WRITR900 DS    0H
         LHI   R15,RTNCD00             Set RC = 0
*->NSI   J     WRITR999                Exit
*
WRITR999 DS    0H
         L     R13,SAVPREV             Point to caller's save area
         RETURN (14,12),,RC=(15)       Return to caller
*
         DROP ,                        Drop all addressability
*
         EJECT ,
*=====================================================================*
*        WTORWAIT subroutine                                          *
*          Uses WTOR to write a message and WAIT for a response in    *
*          order to check things out with SYSVIEW.                    *
*                                                                     *
*        Registers upon entry:                                        *
*           R0-R12: N/A                                               *
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
         USING CONSTANT,R12            CONSTANT addressability
         USING WRK,R10                 WRK addressability
*
         EJECT ,
***********************************************************************
*        Routine entry point                                          *
***********************************************************************
*
WTORWAIT DS    0H
         SAVE  (14,12),,'WTORWAIT  &SYSTIME &SYSDATE' Save regs
*
*        Chain save areas
*
         LA    R2,WRKSAVS              -> Subroutine save area
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
         USING SAVER,R13               Save area addressability
*
*        Build message
*
WTORW100 DS    0H
         XC    WRKWRPL,WRKWRPL         Clear WRPL build area
         XC    WRKECB,WRKECB           Clear ECB
*
         MVC   WRKWRPL(L'WTORMODL),WTORMODL Copy WTOR prototype
*
         WTOR  TEXT=(MSG3,WRKREPLY,L'WRKREPLY,WRKECB),                 +
               MF=(E,WRKWRPL)
*
         WAIT  ECB=WRKECB              WAIT for reply
*
         LHI   R15,RTNCD00             Set RC = 0
         OI    WRKREPLY,C' '           Make reply upper case
*
         CLI   WRKREPLY,C'C'           Continue??
         JE    WTORW900                Yes, begin termination
*
         J     WTORW100                No, re-prompt
*
         EJECT ,
***********************************************************************
*        Routine exit point                                           *
***********************************************************************
*
WTORW900 DS    0H
         LHI   R15,RTNCD00             Set RC = 0
*->NSI   J     WTORW999                Exit
*
WTORW999 DS    0H
         L     R13,SAVPREV             Point to caller's save area
         RETURN (14,12),,RC=(15)       Return to caller
*
         DROP ,                        Drop all addressability
*
         EJECT ,
*=====================================================================*
*        RETRY subroutine                                             *
*          Restore the mainline execution environment and resume      *
*          execution.                                                 *
*                                                                     *
*        Registers upon entry (W/SDWA):                               *
*               R0: Code (in decimal)                                 *
*                   20 - RTM/2 provided SDWA.  Recovery routine       *
*                        specified RETREGS=NO and FRESDWA=YES.        *
*               R1: A(WRK) (ESTAEX PARAM)                             *
*               R2: A(PIRL) Purged I/O restore list or zeros          *
*           R3-R14: N/A                                               *
*              R15: Entry point                                       *
*                                                                     *
*        Registers upon entry (W/OUT SDWA):                           *
*               R0: Code (in decimal)                                 *
*                   12 - RTM/2 did not provide SDWA                   *
*               R1: A(WRK) (ESTAEX PARAM)                             *
*               R2: A(PIRL) Purged I/O restore list or zeros          *
*           R3-R14: N/A                                               *
*              R15: Entry point                                       *
*                                                                     *
*        Registers upon exit:                                         *
*           R0-R14: Restored                                          *
*              R15: Return code                                       *
*=====================================================================*
*
         EJECT ,
***********************************************************************
*        Routine entry point                                          *
***********************************************************************
*
RETRY    DS    0H
*
*        Routine identification
*
         J     *+28                    Jump around identifier
         DC    CL8'RETRY   '
         DC    CL8'&SYSTIME'
         DC    CL8'&SYSDATE'
*
*        Restore execution environment
*
         LR    R10,R1                  -> WRK
*
         USING WRK,R10                 WRK addressability
*
         LA    R13,WRKSAVE             -> Mainline save area
         LARL  R12,CONSTANT            -> CONSTANT
*
         USING CONSTANT,R12            CONSTANT addressabiltiy
         USING SAVER,R13               SAVER addressabiltiy
*
         OI    WRKFLAG3,WRK3RTRX       Note RETRY entered
*
         EJECT ,
***********************************************************************
*        Routine exit point                                           *
***********************************************************************
*
         J     RESUME                  Continue to resumption point
*
         DROP ,                        Drop all addressability
*
         EJECT ,
*=====================================================================*
*        RECOVERY subroutine                                          *
*          Capture failure information and attempt to retry if        *
*          permitted by RTM/2                                         *
*                                                                     *
*        Registers upon entry (W/SDWA):                               *
*               R0: Code (in decimal)                                 *
*                    0 - Active I/O quiesced and restorable           *
*                    4 - Active I/O halted and not restorable         *
*                    8 - No active I/O at time of error               *
*                   16 - No I/O processing performed                  *
*               R1: A(SDWA)                                           *
*               R2: A(WRK) (ESTAEX PARAM)                             *
*           R3-R12: N/A                                               *
*              R13: A(SAVF1SA)                                        *
*              R14: Return address                                    *
*              R15: Entry point                                       *
*                                                                     *
*        Registers upon entry (W/SDWA):                               *
*               R0: Code (in decimal)                                 *
*                   12 - RTM/2 did not provide an SDWA                *
*               R1: ABEND code                                        *
*               R2: A(WRK) (ESTAEX PARAM)                             *
*           R3-R13: N/A                                               *
*              R14: Return address                                    *
*              R15: Entry point                                       *
*                                                                     *
*        Registers upon exit:                                         *
*               R0: A(Retry routine) or zeros                         *
*           R1-R13: Unpredictable                                     *
*              R14: Unchanged                                         *
*              R15: Return code (see below)                           *
*                    0 - Percolate ABEND                              *
*                    4 - Retry to supplied address; R0 -> retry addr  *
*=====================================================================*
*
         EJECT ,
***********************************************************************
*        Entry setup                                                  *
***********************************************************************
*
RECOVERY DS    0H
*
*        Routine identification
*
         J     *+28                    Jump around identifier
         DC    CL8'RECOVERY'
         DC    CL8'&SYSTIME'
         DC    CL8'&SYSDATE'
*
*        Save entry registers
*
         USING WRK,R2                  WRK addressability
*
         STM   R0,R15,WRKRREGS         Save entry registers
*
*        Establish needed addressability
*
         LR    R4,R1                   -> SDWA
         LR    R10,R2                  -> WRK
         LA    R13,WRKSAVR             -> Recovery save area
*
         DROP  R2                      Drop WRK
*
         USING SDWA,R4                 SDWA addressability
         USING WRK,R10                 WRK addressability
         USING SAVER,R13               SAVER addressability
*
         OI    WRKFLAG3,WRK3RCVY       Note RECOVERY entered
*
         CHI   R0,NO_SDWA              SDWA passed by RTM/2??
         JNE   RECOV100                Yes, capture failure information
*
*        No SDWA provided by RTM/2
*
         ST    R1,WRKABCC              Store ABEND return code
         SLGR  R4,R4                   Show no SDWA
         J     RECOV600                Bypass failure capture
*
         EJECT ,
***********************************************************************
*        Capture failure information                                  *
***********************************************************************
*
RECOV100 DS    0H
*
*        Get ABEND return code / reason code
*
         MVC   WRKABCC,SDWAABCC        Copy ABEND return code
         ICM   R15,B'1111',SDWAXPAD    SDWA extension??
         JZ    RECOV600                No, skip
*
         ICM   R15,B'1111',SDWASRVP-SDWAPTRS(R15) Service info??
         JZ    RECOV600                           No, skip
*
         USING SDWARC1,R15             SDWARC1 addressability
*
         TM    SDWACMPF,SDWARCF        ABEND reason code valid??
         JNO   RECOV600                No, do not save
*
         MVC   WRKABRSN,SDWAOCRC       ABEND reason code
*
         DROP  R15                     Drop SDWARC1
*
         EJECT ,
***********************************************************************
*        Determine whether to percolate or retry                      *
***********************************************************************
*
RECOV600 DS    0H
         TM    WRKFLAG3,WRK3RTRY       ABEND retry already attempted??
         JO    RECOV800                Yes, avoid ABEND recursion
*
         LTGR  R4,R4                   SDWA provided??
         JNP   RECOV700                No, attempt ABEND retry
*
         TM    SDWAERRD,SDWACLUP       Cleanup only recovery??
         JO    RECOV800                Yes, skip retry
*
         EJECT ,
***********************************************************************
*        Attempt retry                                                *
***********************************************************************
*
RECOV700 DS    0H
         OI    WRKFLAG3,WRK3RTRY       Show ABEND retry being attempted
         LARL  R0,RETRY                -> RETRY routine
*
         LTR   R4,R4                   SDWA provided??
         JNP   RECOV740                No, continue
*
         SETRP RC=4,RETADDR=(R0),      Request ABEND retry             +
               RECORD=IGNORE,            honor ESTAEX RECORD option    +
               WKAREA=(R4),                SDWA reg                    +
               FRESDWA=YES
*
RECOV740 DS    0H
         LHI   R15,RTNCD04             Set RC = 4 (attempt RETRY)
         J     RECOV999                Prepare to exit
*
         EJECT ,
***********************************************************************
*        Free resources before percolate                              *
***********************************************************************
*
RECOV800 DS    0H
*
         EJECT ,
***********************************************************************
*        Percolate ABEND                                              *
***********************************************************************
*
RECOV900 DS    0H
         LTGR  R4,R4                   SDWA provided??
         JNP   RECOV940                No, Skip SDWA update
*
         SETRP RC=0,                   Request ABEND percolation       +
               RECORD=IGNORE,            honor ESTAEX RECORD option    +
               WKAREA=(R4)                 SDWA reg
*
RECOV940 DS    0H
         SLR   R0,R0                   Show no retry address
         LHI   R15,RTNCD00             Set RC = 0 (percolate ABEND)
*
         EJECT ,
***********************************************************************
*        Routine exit point                                           *
***********************************************************************
*
RECOV999 DS    0H
         LM    R1,R14,WRKRREGS+4       Restore R1:R14
         BR    R14                     Return to caller
*
         DROP ,                        Drop all addressability
*
         EJECT ,
*=====================================================================*
*        Cosntant Area                                                *
*=====================================================================*
*
         PRINT DATA
CONSTANT DS    0D                      Alignment
*
ZEROS    DC    16F'0'                  Zeros
*
OPENM    OPEN  (,),MF=L                OPEN parameter list model
OPENL    EQU   *-OPENM                 OPEN parameter list model length
*
SNAPHDR  DS    0D                      Alignment
         DC    AL1(L'SNAPHTXT)
SNAPHTXT DC    C'*** &MODNAME SNAP ***'
*
         DS    0D                      Alignment
SNAPM    DCB   DDNAME=SNAP,            SNAP DCB                        +
               BLKSIZE=1632,                                           +
               DSORG=PS,                                               +
               LRECL=SNAPLRCL,                                         +
               RECFM=VBA,                                              +
               MACRF=(W)
SNAPL    EQU   *-SNAPM                 SNAP DCB length
*
         DS    0D                      Alignment
SYSPM    DCB   DDNAME=SYSPRINT,        SYSPRINT DCB                    +
               DSORG=PS,                                               +
               LRECL=SYSPLRCL,                                         +
               RECFM=F,                                                +
               MACRF=PM
SYSPL    EQU   *-SYSPM                 SYSPRINT DCB length
*
         DS    0D                      Alignment
WTOMOD   WTO   TEXT=,                  WTO prototype                   +
               ROUTCDE=(11),DESC=(6),                                  +
               MF=L
WTOMODL  EQU   WTOMOD,*-WTOMOD
*
*
         DS    0D                      Alignment
WTORMOD  WTOR  TEXT=(,,,),             WTOR prototype                  +
               ROUTCDE=(11),DESC=(6),                                  +
               MF=L
WTORMODL EQU   WTORMOD,*-WTORMOD
*
*
         DS    0D                      Alignment
MSG0     DC    Y(L'MESSAGE0-L'MSG0)    Len of message
         DC    C'&MODNAME - '
         DC    C'ENTRY PARAMETERS COPIED:'
MESSAGE0 EQU   MSG0,*-MSG0             Message 0
*
*
         DS    0D                      Alignment
MSG1     DC    Y(L'MESSAGE1-L'MSG1)    Len of message
         DC    C'           '
MSG1_PRM DC    CL(PARMMAX)' '
MESSAGE1 EQU   MSG1,*-MSG1             Message 1
*
*
         DS    0D                      Alignment
MSG2     DC    Y(L'MESSAGE2-L'MSG2)    Len of message
         DC    C'&MODNAME - '
MSG2_DSC DC    CL16' '                 Description
         DC    C' - '
         DC    C'return code: x'''
MSG2_RC  DC    CL8' '                  Return code
         DC    C''';  '
         DC    C'reason code: x'''
MSG2_RSN DC    CL8' '                  Reason code
         DC    C''''
MESSAGE2 EQU   MSG2,*-MSG2             Message 2
*
*
         DS    0D                      Alignment
MSG3     DC    Y(L'MSG3_TXT)
MSG3_TXT DC    C'&MODNAME - Waiting, reply ''C'' to continue'
MESSAGE3 EQU   MSG3,*-MSG3             Message 3
*
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
WRKSPID  EQU   0                       Subpool
*
WRK      DSECT ,
WRKID    DS    CL4                     Identifier
WRKIDC   EQU   C'WRK*'                 Identifier character string
WRKSP    DC    AL1(WRKSPID)            Subpool
WRKLN    DC    AL3(*-*)                Length
*
WRKDBLE  DS    D                       Doubleword work field
WRKFULL  DS    F                       Fullword work field
WRKHALF  DS    H                       Halfword work field
WRKREPLY DS    X                       Reply area
         DS    X                       Alignment
*
WRKABCC  DS    F                       ABEND return code
WRKABRSN DS    F                       ABEND reason code
*
WRKFLAGS DS    0F                      Fullword of flags
WRKFLAG0 DS    X                       Flag byte 0
WRKFLAG1 DS    X                       Flag byte 1
WRKFLAG2 DS    X                       Flag byte 2
*
WRKFLAG3 DS    X                       Flag byte 3 - Recovery flags
WRK3RCVY EQU   B'10000000'               RECOVERY entered
WRK3RTRY EQU   B'01000000'               RETRY scheduled
WRK3RTRX EQU   B'00100000'               RETRY executed
WRK3RSME EQU   B'00010000'               RESUME executed
*
WRKPRMS@ DS    A                       -> Entry parameters
WRKPRMSL DS    AL2                     Entry parameters length
WRKPRMS  DS    0C                      Entry parameters
         DS    XL(PARMMAX)
*
         DS    0F                      Alignment
WRKECB   DS    F                       WTOR reply ECB
*
WRKDESC  DS    CL(L'MSG2_DSC)          Description text
WRKRC    DS    F                       Return code
WRKRSN   DS    F                       Reason code
*
WRKSAVE  DS    XL(SAVER_LEN)           Mainline save area
WRKSAVS  DS    XL(SAVER_LEN)           Subroutine save area
WRKSAVR  DS    XL(SAVER_LEN)           Recovery save area
*
WRKRREGS DS    16F                     Save recovery registers
*
         DS    0D                      Alignment
WRKSNDCB DS    CL(SNAPL)               SNAP
*
         DS    0D                      Alignment
WRKSYDCB DS    CL(SYSPL)               SYSPRINT
*
         DS    0D                      Alignment
WRKOPNPL DS    CL(OPENL)               OPEN macro parameter list
*
         DS    0D                      Alignment
WRKSNAP  SNAP  MF=L                    SNAP macro list form
*
         DS    0D                      Alignment
WRKOUTBF DS    CL(SYSPLRCL)            Output buffer
*
         DS    0D                      Alignment
WRKWPL   DS    XL(L'WTOMODL)           WTO parameter list
*
         DS    0D                      Alignment
WRKWRPL  DS    XL(L'WTORMODL)          WTOR parameter list
*
         DS    0D                      Alignment
WRKSTAPL ESTAEX MF=L                   ESTAEX parameter list
*
WRKSNAPB DS    0D                      Begin on double word
WRKDATA  DS    XL16                    Date to be snapped
WRKSNAPE DS    0D                      End on double word
*
WRKWTOTX DS    XL128                   Variable text for WTO
WRKHEX   DS    D,C                     Hex-to-EBCDIC work area
         DS    XL3                     Alignment
*
WRKLEN   EQU   *-WRK                   Length of WRK DSECT
*
         EJECT ,
*=====================================================================*
*        DSECTs                                                       *
*=====================================================================*
*
         DCBD  DSORG=PS                IHADCB
         IHASAVER ,                    SAVER
         IHASDWA  ,                    SDWA
*
         END   &MODNAME