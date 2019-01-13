#ifndef __jfcb__
#define __jfcb__

// NOTE(Kelosky): manual update
#if defined(__IBM_METAL__)
#pragma pack(packed)
#endif

struct jfcb
{
    unsigned char jfcbdsnm[44]; /* -  DATA SET NAME (DSNAME=)                             */
    union {
        struct
        {
            unsigned char _jfcipltx[7]; /* -  MODULE NAME OF NETWORK CONTROL PROGRAM */
            unsigned char _filler1;
        } _jfcb_struct1;
        struct
        {
            unsigned char _jfcbelnm[8]; /* -  DSNAME= ELEMENT (MEMBER) NAME (DSNAME=x(member)) */
        } jfcblsrd;
    } _jfcb_union1;
    unsigned char jfcbtsdm;    /* -     JOB MANAGEMENT/DATA MANAGEMENT INTERFACE         */
    unsigned char jfcbdscb[3]; /* -   TTR OF THE FORMAT 1 DSCB FOR DATA SET              */
    struct
    {
        struct
        {
            struct
            {
                unsigned char _jfcamcro[2]; /* -   CHECKPOINT/RESTART OPTION INDICATORS     */
                short int _jfcamstr;        /* -     NUMBER OF STRINGS  (AMP=('STRNO=num')) */
            } jfcrbido;
        } jfcbfrid;
    } jfcfcbid;
    short int jfcbadbf; /* -     NUMBER OF DATA BUFFERS  (AMP=('BUFND=num'))      */
    short int jfcnlrec; /* -     LOGICAL RECORD LENGTH (VSAM)              ICB438 */
    struct
    {
        unsigned char _jfctdsi1; /* -  TDSI byte 1                                 @L7C */
        unsigned char _jfctdsi2; /* -  TDSI byte 2                                 @L7C */
    } jfcbtdsi;
    unsigned char jfcbltyp; /* -     LABEL TYPE (LABEL=)                              */
    struct
    {
        char _jfcbufof;      /* -   TAPE DATA SET - THIS FIELD CONTAINS THE BUFFER */
        short int _jfcbflsq; /* -     LABEL=  FILE (DATA SET) SEQUENCE NUMBER      */
    } jfcbottr;
    short int jfcbvlsq; /* -     VOLUME= VOLUME SEQUENCE NUMBER                   */
    struct
    {
        unsigned char _jfcbops1[5]; /* -   OPEN ROUTINE INTERNAL SWITCHES   */
        unsigned char _jfcbflg1;    /* -     FLAG BYTE                      */
        unsigned char _jfcbflg2;    /* -     FLAG BYTE OF OPEN SWITCHES     */
        unsigned char _jfcbops2;    /* -     OPEN ROUTINE INTERNAL SWITCHES */
    } jfcbmask;
    unsigned char jfcbcrdt[3]; /* -   DATA SET CREATION DATE in the format: 'YYDDDD'     */
    unsigned char jfcbxpdt[3]; /* -   DATA SET EXPIRATION DATE (LABEL=EXPDT=)            */
    unsigned char jfcbind1;    /* -     INDICATOR BYTE 1                                 */
    unsigned char jfcbind2;    /* -     INDICATOR BYTE 2                                 */
    struct
    {
        union {
            struct
            {
                struct
                {
                    struct
                    {
                        struct
                        {
                            struct
                            {
                                unsigned char _jfcbufrq; /* -   ** RESERVED-O **      (DCB=BUFRQ=) */
                            } jfcbfout;
                        } jfcbufin;
                    } jfcbufno;
                    struct
                    {
                        struct
                        {
                            struct
                            {
                                unsigned char _jfcbftek; /* -     BUFFERING TECHNIQUE (DCB=BFTEK=) */
                            } jfcbfaln;
                        } jfcbhiar;
                    } jfcbgncp;
                    unsigned char _filler2;
                } jfcamsva;
                unsigned char _filler3;
            } _jfcb_struct2;
            struct
            {
                unsigned char _filler4[2];
                short int _jfcbufl; /* -     BUFFER LENGTH (DCB=BUFL=) */
            } _jfcb_struct3;
        } _jfcb_union2;
    } jfcamptr;
    unsigned char jfceropt; /* -     ERROR OPTION  (DCB=EROPT=)                       */
    struct
    {
        struct
        {
            struct
            {
                struct
                {
                    struct
                    {
                        unsigned char _jfcprtsp; /* -     NORMAL PRINTER SPACING (DCB=PRTSP=) */
                    } jfcstack;
                } jfcmode;
            } jfccode;
        } jfckeyle;
    } jfctrtch;
    unsigned char jfcden; /* -     TAPE DENSITY - 2400/3400 SERIES MAGNETIC TAPE    */
    struct
    {
        unsigned char _jfcbothi;    /* High order  byte for JFCBOTTR.  Valid only if     */
        unsigned char _jfctrkbl[2]; /* -     DATA SET OPENED FOR MOD - IF AUTOMATIC STEP */
    } jfclimct;
    struct
    {
        unsigned char _jfcdsrg1; /* -      BYTE 1 OF JFCDSORG (DCB=DSORG=)       */
        unsigned char _jfcdsrg2; /* -      BYTE 2 OF JFCDSORG (DCB=DSORG= cont.) */
    } jfcdsorg;
    unsigned char jfcrecfm; /* -     RECORD FORMAT (DCB=RECFM=) (AMP=('RECFM='))      */
    unsigned char jfcoptcd; /* -     OPTION CODES (DCB=OPTCD=)                        */
    struct
    {
        struct
        {
            short int _jfcbaxbf; /* -     NUMBER OF INDEX BUFFERS  (AMP=('BUFNI=num')) */
        } jfcbufsi;
    } jfcblksi;
    short int jfclrecl; /* -     LOGICAL RECORD LENGTH (DCB=LRECL=)               */
    struct
    {
        char _jfcbufmx; /* -   MAXIMUM NUMBER OF BUFFERS (DCB=BUFMAX=) */
    } jfcncp;
    struct
    {
        unsigned char _jfcpci; /* -     PROGRAM-CONTROLLED INTERRUPTION (PCI) FLAG */
    } jfcntm;
    union {
        struct
        {
            struct
            {
                short int _jfcrkp;       /* -     THE RELATIVE POSITION OF THE FIRST BYTE OF THE */
                unsigned char _jfccylof; /* -   CYLINDER OVERFLOW (DCB=CYLOFL=)                  */
                unsigned char _jfcdbufn; /* -     RESERVED                                       */
            } jfcrbidc;
        } jfcresrv;
        unsigned char _jfcucsid[4]; /* -   NAME OF THE UCS IMAGE TO BE LOADED (UCS=parm1) */
    } _jfcb_union3;
    union {
        unsigned char _jfcintvl; /* -   INTERVAL (DCB=INTVL=)                     */
        unsigned char _jfcucsop; /* -     OPERATION OF THE UCS IMAGE TO BE LOADED */
    } _jfcb_union4;
    struct
    {
        unsigned char _jfccpri; /* -     TRANSMISSION PRIORITY (DCB=CPRI=)   (TCAM) */
    } jfcthrsh;
    short int jfcsowa;      /* -     ** RESERVED-O **  (DCB=SOWA=)                    */
    unsigned char jfcbntcs; /* -   NUMBER OF OVERFLOW TRACKS                          */
    unsigned char jfcbnvol; /* -   NUMBER OF VOLUME SERIAL NUMBERS                    */
    struct
    {
        unsigned char _filler5[22]; /* -  FIRST 22 BYTES OF JFCBVOLS              @Z30LP9A  */
        unsigned char _jfcmsvgp[8]; /* -   ** RESERVED-O **    (MDC306)            @Z30LP9A */
    } jfcbvols;
    unsigned char jfcbextl;    /* -   LENGTH OF BLOCK OF EXTRA VOLUME SERIAL NUMBERS     */
    unsigned char jfcbexad[3]; /* -   SYSTEM VIRTUAL ADDRESS (SVA) OF FIRST JFCB         */
    struct
    {
        unsigned char _jfcrunit[3]; /* -   UNIT TYPE (EBCDIC) OF A DEVICE AT A REMOTE */
    } jfcbpqty;
    unsigned char jfcbctri; /* -     SPACE PARAMETERS (SPACE=)                        */
    struct
    {
        short int _jfcrqid;     /* -     QUEUE IDENTIFICATION (QID) USED BY ACCESS        */
        unsigned char _filler6; /* -     LAST BYTE OF JFCBSQTY  (MDC304)         @XM05457 */
    } jfcbsqty;
    unsigned char jfcflgs1;     /* -     FLAG BYTE (ICB488)                       SA53458 */
    unsigned char jfcbdqty[3];  /* -   SPACE= Directory quantity (SPACE=(,(,,dir-qty)))   */
    unsigned char jfcbflg3;     /* -     FLAG BYTE (OS/VS2)  (MDC316)            @ZA18180 */
    short int jfcbrv08;         /* -       RESERVED (OS/VS2)                     @ZA18180 */
    short int jfcbabst;         /* -     SPACE= Absolute track (ABSTR) request address    */
    unsigned int jfcbsbnm : 24; /* -   ** RESERVED-O **    (SUBALLOC=)                    */
    unsigned char jfcbdrlh[3];  /* -   SPACE= AVERAGE DATA BLOCK LENGTH (blklgth)         */
    unsigned char jfcbvlct;     /* -   VOLUME COUNT (volct)   (VOL=(,,,volct)             */
    unsigned char jfcvldq;      /* -   Volser dequeue indicators (bit placement    @05C   */
};

#define jfcipltx _jfcb_union1._jfcb_struct1._jfcipltx
#define jfcbelnm _jfcb_union1.jfcblsrd._jfcbelnm
#define jfcamcro jfcfcbid.jfcbfrid.jfcrbido._jfcamcro
#define jfcamstr jfcfcbid.jfcbfrid.jfcrbido._jfcamstr
#define jfctdsi1 jfcbtdsi._jfctdsi1
#define jfctdsi2 jfcbtdsi._jfctdsi2
#define jfcbufof jfcbottr._jfcbufof
#define jfcbflsq jfcbottr._jfcbflsq
#define jfcbops1 jfcbmask._jfcbops1
#define jfcbflg1 jfcbmask._jfcbflg1
#define jfcbflg2 jfcbmask._jfcbflg2
#define jfcbops2 jfcbmask._jfcbops2
#define jfcbufrq jfcamptr._jfcb_union2._jfcb_struct2.jfcamsva.jfcbufno.jfcbufin.jfcbfout._jfcbufrq
#define jfcbftek jfcamptr._jfcb_union2._jfcb_struct2.jfcamsva.jfcbgncp.jfcbhiar.jfcbfaln._jfcbftek
#define jfcbufl jfcamptr._jfcb_union2._jfcb_struct3._jfcbufl
#define jfcprtsp jfctrtch.jfckeyle.jfccode.jfcmode.jfcstack._jfcprtsp
#define jfcbothi jfclimct._jfcbothi
#define jfctrkbl jfclimct._jfctrkbl
#define jfcdsrg1 jfcdsorg._jfcdsrg1
#define jfcdsrg2 jfcdsorg._jfcdsrg2
#define jfcbaxbf jfcblksi.jfcbufsi._jfcbaxbf
#define jfcbufmx jfcncp._jfcbufmx
#define jfcpci jfcntm._jfcpci
#define jfcrkp _jfcb_union3.jfcresrv.jfcrbidc._jfcrkp
#define jfccylof _jfcb_union3.jfcresrv.jfcrbidc._jfccylof
#define jfcdbufn _jfcb_union3.jfcresrv.jfcrbidc._jfcdbufn
#define jfcucsid _jfcb_union3._jfcucsid
#define jfcintvl _jfcb_union4._jfcintvl
#define jfcucsop _jfcb_union4._jfcucsop
#define jfccpri jfcthrsh._jfccpri
#define jfcmsvgp jfcbvols._jfcmsvgp
#define jfcrunit jfcbpqty._jfcrunit
#define jfcrqid jfcbsqty._jfcrqid

/* Values for field "jfcbtsdm" */
#define jfccat 0x80   /* -   DATA SET IS CATALOGED                          */
#define jfcvsl 0x40   /* -   VOLUME SERIAL LIST HAS BEEN CHANGED            */
#define jfcsds 0x20   /* -   SUBSYSTEM DATA SET - This dataset is either    */
#define jfcttr 0x10   /* -   A JOB STEP IS TO BE RESTARTED.  USE JFCBOTTR   */
#define jfcnwrit 0x08 /* -   DO NOT WRITE BACK THE JFCB DURING OPEN         */
#define jfcndscb 0x04 /* -   DO NOT MERGE DSCB OR LABEL FIELDS INTO THIS    */
#define jfcndcb 0x02  /* -   DO NOT MERGE DCB FIELDS INTO THIS JFCB         */
#define jfcpat 0x01   /* -   THE PATTERNING DSCB IS COMPLETE                */

/* Values for field "jfctdsi1" */
#define jfctrkno 0xF0 /* -   Track recording technique                 @L7A */
#define jfcnorec 0x00 /* -   Recording technology unknown or not       @L7A */
#define jfc18trk 0x10 /* -   18 track recording mode - (hex value)     @L7A */
#define jfc36trk 0x20 /* -   36 track recording mode - (hex value)     @L7A */
#define jfc128tk 0x30 /* -   128 track recording mode - (hex value)    @04A */
#define jfc256tk 0x40 /* -   256 track recording mode - (hex value)    @07A */
#define jfc384tk 0x50 /* -   384 track recording mode - (hex value)    @L9A */
#define jfcefmt1 0x60 /* -   Enterprise Format 1 - (hex value)         @LBA */
#define jfcefmt2 0x70 /* -   Enterprise Format 2 - (hex value)         @LEA */
#define jfceefm2 0x80 /* -   Enterprise Encryption Format 2 - (hex     @LGA */
#define jfcefmt3 0x90 /* -   Enterprise Format 3 - (hex value)         @0CA */
#define jfceefm3 0xA0 /* -   Enterprise Encryption Format 3 - (hex     @0CA */
#define jfcefmt4 0xB0 /* -   Enterprise Format 4 - (hex value)         @0DA */
#define jfceefm4 0xC0 /* -   Enterprise Encryption Format 4 - (hex     @0DA */
#define jfcmedia 0x0F /* -   Media type                                @L7A */
#define jfcnomed 0x00 /* -   Media type unknown or not specified       @L7A */
#define jfcbmed1 0x01 /* -   Cartridge System Tape - (hex value)       @L7A */
#define jfcbmed2 0x02 /* -   Enhanced Capacity Cartridge System Tape   @L7A */
#define jfcbmed3 0x03 /* -   1/2 inch / 320 meter particle media       @04A */
#define jfcbmed4 0x04 /* -   Reserved for future media type            @04A */
#define jfcbmed5 0x05 /* -   Enterprise Cartridge Tape                 @LBC */
#define jfcbmed6 0x06 /* -   Enterprise WORM Cartridge Tape            @LDC */
#define jfcbmed7 0x07 /* -   Enterprise Economy Cartridge Tape         @LDC */
#define jfcbmed8 0x08 /* -   Enterprise Economy WORM Cartridge Tape    @LDC */
#define jfcbmed9 0x09 /* -   Enterprise Extended Cartridge Tape        @LEA */
#define jfcbme10 0x0A /* -   Enterprise Extended WORM Cartridge Tape   @LEA */
#define jfcbme11 0x0B /* -   Enterprise Advanced Cartridge Tape        @0DA */
#define jfcbme12 0x0C /* -   Enterprise Advanced WORM Cartridge Tape   @0DA */
#define jfcbme13 0x0D /* -   Enterprise Advanced Economy Cartridge Tape     */

/* Values for field "jfctdsi2" */
#define jfcompty 0xF0 /* -   Compaction type. Does not necessarily     @L7A */
#define jfccmpns 0x00 /* -   Compaction type unknown or not specified  @L7A */
#define jfcnocmp 0x10 /* -   Compaction not used - (hex value)         @L7A */
#define jfcbidrc 0x20 /* -   Compaction type=IDRC - (hex value)        @L7A */
#define jfcbcmpy 0x20 /* -   Compaction = YES - (hex value)            @04A */
#define jfcspecl 0x0F /* -   Special attributes                        @L7A */
#define jfcnospc 0x00 /* -   Volume has no special attributes          @L7A */
#define jfcrdcom 0x01 /* -   Read compatibility attribute. When set,   @L7A */

/* Values for field "jfcbltyp" */
#define jfcdseqn 0x80 /* -   DATASET SEQUENCE NUMBER Specified              */
#define jfcbal 0x40   /* -   AL  - ISO/ANSI (ver 1) ISO/ANSI/FIPS (ver 3)   */
#define jfcbltm 0x20  /* -   LTM - LEADING TAPE MARK                        */
#define jfcblp 0x10   /* -   BLP - BYPASS LABEL PROCESSING                  */
#define jfcsul 0x0A   /* -   SUL - STANDARD and USER LABELs                 */
#define jfcnsl 0x04   /* -   NSL - NONSTANDARD LABEL                        */
#define jfcsl 0x02    /* -   SL  - STANDARD LABEL  (default)                */
#define jfcnl 0x01    /* -   NL  - NO LABEL                                 */

/* Values for field "jfcbufof" */
#define jfcbfofl 0x80 /* -   L - Specifies that the block prefix is 4bytes  */

/* Values for field "jfcbflg1" */
#define jfcstand 0x80 /* -   VOLUME LABEL PROCESSING STANDARD               */
#define jfcslcre 0x40 /* -   CREATION OF A STANDARD LABEL IS NECESSARY      */
#define jfcsldes 0x20 /* -   DESTRUCTION OF A STANDARD LABEL IS NECESSARY   */
#define jfcdual 0x10  /* -   DUAL-DENSITY CHECK DETECTED                    */
#define jfcopen 0x0F  /* -   OPEN ROUTINE INTERNAL SWITCHES                 */
#define jfcsnsvl 0x08 /* -   VOLID EXTRACTED FROM SENSE                @LFA */
#define jfcbpwbp 0x01 /* -   PASSWORD BYPASS INDICATOR               MDC010 */

/* Values for field "jfcbflg2" */
#define jfcinop 0x80  /* -   TREAT THE INOUT OPTION OF OPEN AS INPUT        */
#define jfcoutop 0x40 /* -   TREAT THE OUTIN OPTION OF OPEN AS OUTPUT       */
#define jfcdefer 0x20 /* -   SET ONLY IN A JFCB RECORDED IN A DATA SET      */
#define jfcnrps 0x20  /* -   USE BY OPEN ROUTINES - SET TO INDICATE THAT    */
#define jfcmodnw 0x10 /* -   DISPOSITION OF THIS DATA SET HAS BEEN CHANGED  */
#define jfcsdrps 0x08 /* -   USE SEARCH DIRECT FOR ROTATIONAL POSITION      */
#define jfctrace 0x04 /* -   GTF TRACE IS TO OCCUR DURING OPEN/CLOSE/EOV    */
#define jfcbbuff 0x02 /* -   If ON, JFCBUFOF contains either a user-coded   */
#define jfcrctlg 0x01 /* -   OPEN HAS UPDATED THE TTR.  SCHEDULER STEP      */

/* Values for field "jfcbind1" */
#define jfcrlse 0xC0  /* -   RELEASE EXTERNAL STORAGE (SPACE=(,(,),RLSE))   */
#define jfcloc 0x30   /* -   DATA SET HAS BEEN LOCATED                      */
#define jfcadded 0x0C /* -   NEW VOLUME HAS BEEN ADDED TO THE DATA SET      */
#define jfcgdg 0x02   /* -   DATA SET IS A MEMBER OF A GENERATION DATA      */
#define jfcpds 0x01   /* -   DATA SET IS A MEMBER OF A PARTITIONED DATA SET */
#define jfcbrlse 0x40 /* -   ** RESERVED-O **                               */
#define jfcbloct 0x10 /* -   ** RESERVED-O **                               */
#define jfcbnewv 0x04 /* -   ** RESERVED-O **                               */
#define jfcbpmem 0x01 /* -   ** RESERVED-O **                               */

/* Values for field "jfcbind2" */
#define jfcdisp 0xC0  /* -   BIT PATTERN FOR NEW, MOD, OLD                  */
#define jfcnew 0xC0   /* -   NEW DATA SET  (DISP=NEW)                       */
#define jfcmod 0x80   /* -   MOD DATA SET  (DISP=MOD)                       */
#define jfcold 0x40   /* -   OLD DATA SET  (DISP=OLD)                       */
#define jfcbrwpw 0x30 /* -   PASSWORD IS REQUIRED TO WRITE BUT NOT TO READ  */
#define jfcsecur 0x10 /* -   PASSWORD IS REQUIRED TO READ OR TO WRITE       */
#define jfcshare 0x08 /* -   SHARED DATA SET                                */
#define jfcent 0x04   /* -   DELETE THIS JFCB BEFORE ALLOCATION FOR A       */
#define jfcreq 0x02   /* -   STORAGE VOLUME REQUESTED                       */
#define jfctemp 0x01  /* -   DATA SET WILL BE DELETED WHEN JOB COMPLETES    */
#define jfcbstat 0x40 /* -   ** RESERVED-O **                               */
#define jfcbscty 0x10 /* -   ** RESERVED-O **                               */
#define jfcbgdga 0x04 /* -   ** RESERVED-O **                               */

/* Values for field "jfcbftek" */
#define jfcsim 0x40   /* -   S - SIMPLE BUFFERING                           */
#define jfcbbfta 0x60 /* -   A - AUTOMATIC RECORD AREA CONSTRUCTION         */
#define jfcbbftr 0x20 /* -   R - FOR BSAM CREATE BDAM PROCESSING OR BDAM    */
#define jfcexc 0x10   /* -   E - EXCHANGE BUFFERING                         */
#define jfcdyn 0x08   /* -   D - DYNAMIC BUFFERING                          */

/* Values for field "jfcbfaln" */
#define jfcdword 0x02 /* -   D - DOUBLE WORD BOUNDARY                       */
#define jfcfword 0x01 /* -   F - FULL WORD BOUNDARY                         */

/* Values for field "jfcbhiar" */
#define jfchier 0x84  /* -   ** RESERVED-O **                               */
#define jfchier1 0x04 /* -   ** RESERVED-O **                               */

/* Values for field "jfceropt" */
#define jfcacc 0x80   /* -   ACC - ACCEPT                                   */
#define jfcskp 0x40   /* -   SKP - SKIP                                     */
#define jfcabn 0x20   /* -   ABE - ABNORMAL END OF TASK                     */
#define jfctopt 0x10  /* -   T   - ON-LINE TERMINAL TEST (BTAM)      ICB349 */
#define jfcrsv02 0x08 /* RESERVED                                           */
#define jfcrsv03 0x04 /* RESERVED                                           */
#define jfcrsv04 0x02 /* RESERVED                                           */
#define jfcrsv05 0x01 /* RESERVED                                           */

/* Values for field "jfcprtsp" */
#define jfcspthr 0x19 /* -   3 - SPACE THREE LINES                          */
#define jfcsptwo 0x11 /* -   2 - SPACE TWO LINES                            */
#define jfcspone 0x09 /* -   1 - SPACE ONE LINE                             */
#define jfcspno 0x01  /* -   0 - NO SPACING                                 */

/* Values for field "jfcstack" */
#define jfctwo 0x02 /* -   2 - STACKER TWO                                */
#define jfcone 0x01 /* -   1 - STACKER ONE                                */

/* Values for field "jfcmode" */
#define jfcbin 0x80   /* -   C - Card Image (COLUMN BINARY MODE)            */
#define jfcebcd 0x40  /* -   E - EBCDIC MODE                                */
#define jfcmodeo 0x20 /* -   O - OPTICAL MARK READ MODE (3505 ONLY)  ICB394 */
#define jfcmoder 0x10 /* -   R - READ COLUMN ELIMINATE MODE (3505 AND 3525  */
#define jfcrsv06 0x08 /* RESERVED                                           */
#define jfcrsv07 0x04 /* RESERVED                                           */

/* Values for field "jfccode" */
#define jfcnocon 0x80 /* -   N - NO CONVERSION           ** RESERVED-O **   */
#define jfcbcd 0x40   /* -   I - IBM BCD                 ** RESERVED-O **   */
#define jfcfri 0x20   /* -   F - FRIDEN                  ** RESERVED-O **   */
#define jfcbur 0x10   /* -   B - BURROUGHS               ** RESERVED-O **   */
#define jfcncr 0x08   /* -   C - NATIONAL CASH REGISTER  ** RESERVED-O **   */
#define jfcascii 0x04 /* -   A - ASCII (8-TRACK)         ** RESERVED-O **   */
#define jfctty 0x02   /* -   T - TELETYPE                ** RESERVED-O **   */
#define jfcrsv32 0x01 /* RESERVED                                           */

/* Values for field "jfctrtch" */
#define jfceven 0x23  /* -   E      - EVEN PARITY (7-track)                 */
#define jfctran 0x3B  /* -   T      - EOD/EBCDIC TRANSLATION (7-track)      */
#define jfcconv 0x13  /* -   C      - DATA CONVERSION (7-track)             */
#define jfctrev 0x2B  /* -   ET     - EVEN PARITY AND TRANSLATION (7-track) */
#define jfccomp 0x08  /* -   COMP   - ENHANCED 3480 DATA RECORDING     @T2A */
#define jfcncomp 0x04 /* -   NOCOMP - ENHANCED 3480 DATA RECORDING     @T2A */
#define jfc1trak 0x42 /* -   TBD    - RESERVED FUTURE DEVELOPMENT      @T1A */
#define jfc2trak 0x82 /* -   TBD    - RESERVED FUTURE DEVELOPMENT      @T1A */
#define jfc4trak 0xC2 /* -   TBD    - RESERVED FUTURE DEVELOPMENT      @T1A */

/* Values for field "jfcden" */
#define jfc200 0x03  /* -   0 - 200 BPI (7-track)                          */
#define jfc556 0x43  /* -   1 - 556 BPI (7-track)                          */
#define jfc800 0x83  /* -   2 - 800 BPI (7-track and 9-track)              */
#define jfc1600 0xC3 /* -   3 - 1600 BPI (9-track)                         */
#define jfc6250 0xD3 /* -   4 - 6250 BPI (9-track)                  ICB474 */

/* Values for field "jfcdsrg1" */
#define jfcorgis 0x80 /* -   IS  - INDEXED SEQUENTIAL                       */
#define jfcorgps 0x40 /* -   PS  - PHYSICAL SEQUENTIAL                      */
#define jfcorgda 0x20 /* -   DA  - DIRECT ACCESS                            */
#define jfcorgcx 0x10 /* -   CX  - COMM. LINE GROUP (BTAM,QTAM)      MDC011 */
#define jfcorgcq 0x08 /* -   CQ  - ** RESERVED-O **                  MDC012 */
#define jfcorgmq 0x04 /* -   MQ  - ** RESERVED-O **                  MDC013 */
#define jfcorgpo 0x02 /* -   PO  - PARTITIONED                              */
#define jfcorgu 0x01  /* -   ..U - UNMOVABLE - THE DATA CONTAINS LOCATION   */

/* Values for field "jfcdsrg2" */
#define jfcorggs 0x80 /* -   GS  - GRAPHICS                                 */
#define jfcorgtx 0x40 /* -       - TCAM LINE GROUP                   MDC014 */
#define jfcorgtq 0x20 /* -       - TCAM MESSAGE QUEUE                MDC015 */
#define jfcrsv13 0x10 /* RESERVED, BINARY ZERO                              */
#define jfcorgam 0x08 /* -       - VSAM                              ICB438 */
#define jfcorgtr 0x04 /* -       - TCAM 3705                         MDC016 */
#define jfcrsv15 0x02 /* RESERVED, BINARY ZERO                              */
#define jfcrsv16 0x01 /* RESERVED, BINARY ZERO                              */

/* Values for field "jfcrecfm" */
#define jfcrcfm 0xE0  /* -     - RECORD FORMAT (USASI/USASCII)              */
#define jfcfmrec 0xC0 /* -     - HIGH-ORDER TWO BITS OF JFCRECFM TO BE      */
#define jfcund 0xC0   /* -   U - UNDEFINED                                  */
#define jfcfix 0x80   /* -   F - FIXED                                      */
#define jfcvar 0x40   /* -   V - VARIABLE                                   */
#define jfcvard 0x20  /* -   D - VARIABLE (FORMAT D FOR USASI/USASCII)      */
#define jfcrfo 0x20   /* -   T - TRACK OVERFLOW                             */
#define jfcrfb 0x10   /* -   B - BLOCKED - MAY NOT OCCUR WITH UNDEFINED     */
#define jfcrfs 0x08   /* -   S - FOR FIXED LENGTH RECORD FORMAT, STANDARD   */
#define jfcchar 0x06  /* -     - CONTROL CHARACTER                          */
#define jfcasa 0x04   /* -   A - AMERICAN NATIONAL STANDARD (ASA) CONTROL   */
#define jfcmac 0x02   /* -   M - MACHINE CODE CONTROL CHARACTER             */
#define jfcnocc 0x00  /* -     - NO CONTROL CHARACTER                       */

/* Values for field "jfcoptcd" */
#define jfcwvcsp 0x80 /* -   W - WRITE VALIDITY CHECK                       */
#define jfcallow 0x40 /* -   U - ALLOW A DATA CHECK CAUSED BY AN INVALID    */
#define jfcpcibt 0x20 /* -   C - CHAINED SCHEDULING USING THE PROGRAM       */
#define jfcbckpt 0x10 /* -   H - BYPASS EMBEDDED DOS CHECKPOINT RECORDS ON  */
#define jfcrsv18 0x08 /* RESERVED                                           */
#define jfcreduc 0x04 /* -   Z - USE REDUCED ERROR RECOVERY PROCEDURE       */
#define jfcsrchd 0x04 /* -     - USE SEARCH DIRECT (SD), INSTEAD OF SEARCH  */
#define jfcrsv21 0x02 /* RESERVED                                           */
#define jfcoptj 0x01  /* -   J - 3800 CONTROL CHARACTER  (MDC301)  @Z40MP9A */
#define jfcwvcis 0x80 /* -   W - WRITE VALIDITY CHECK                       */
#define jfcrsv17 0x40 /* RESERVED                                           */
#define jfcmast 0x20  /* -   M - MASTER INDEXES                             */
#define jfcind 0x10   /* -   I - INDEPENDENT OVERFLOW AREA                  */
#define jfccyl 0x08   /* -   Y - CYLINDER OVERFLOW AREA                     */
#define jfcrsv19 0x04 /* RESERVED                                           */
#define jfcdel 0x02   /* -   L - DELETE OPTION                              */
#define jfcreorg 0x01 /* -   R - REORGANIZATION CRITERIA                    */
#define jfcwvcbd 0x80 /* -   W - WRITE VALIDITY CHECK                       */
#define jfcover 0x40  /* -     - TRACK OVERFLOW                             */
#define jfcext 0x20   /* -   E - EXTENDED SEARCH                            */
#define jfcfeed 0x10  /* -   F - FEEDBACK                                   */
#define jfcact 0x08   /* -   A - ACTUAL ADDRESSING                          */
#define jfcrsv20 0x04 /* RESERVED                                           */
#define jfcrsv22 0x02 /* RESERVED                                           */
#define jfcrel 0x01   /* -   R - RELATIVE BLOCK ADDRESSING                  */
#define jfcoptq 0x08  /* -     - EBCDIC TO ASCII OR ASCII TO EBCDIC         */
#define jfcsdnam 0x80 /* -   W - SOURCE OR DESTINATION NAME PRECEDES        */
#define jfcwumsg 0x40 /* -   U - WORK UNIT IS A MESSAGE (DEFAULT WORK UNIT  */
#define jfccbwu 0x20  /* -   C - CONTROL BYTE PRECEDES WORK UNIT            */

/* Values for field "jfcpci" */
#define jfcpcix1 0x80 /* -   PCI=(X,) RECEIVE OPERATIONS             ICB473 */
#define jfcpcix2 0x40 /* -   PCI=(,X) SEND OPERATIONS                       */
#define jfcpcia1 0x20 /* -   PCI=(A,) RECEIVE OPERATIONS                    */
#define jfcpcia2 0x10 /* -   PCI=(,A) SEND OPERATIONS                       */
#define jfcpcin1 0x08 /* -   PCI=(N,) RECEIVE OPERATIONS                    */
#define jfcpcin2 0x04 /* -   PCI=(,N) SEND OPERATIONS                       */
#define jfcpcir1 0x02 /* -   PCI=(R,) RECEIVE OPERATIONS                    */
#define jfcpcir2 0x01 /* -   PCI=(,R) SEND OPERATIONS                       */

/* Values for field "jfcucsop" */
#define jfcbextp 0x80 /* -   JFCB EXTENSION PRESENT FOR 3800 DEVICE         */
#define jfcfold 0x40  /* -   UCS IMAGE IS TO BE LOADED IN THE FOLD MODE     */
#define jfcrsv25 0x20 /* RESERVED                                           */
#define jfcver 0x10   /* -   UCS IMAGE IS TO BE VERIFIED (UCS=x,x,VERIFY)   */
#define jfcfcbal 0x08 /* -   FORMS ARE TO BE ALIGNED (FCB=x,ALIGN)          */
#define jfcfcbvr 0x04 /* -   FORMS CONTROL BUFFER (FCB) IMAGE IS TO BE      */
#define jfcrsv26 0x02 /* RESERVED                                           */
#define jfcrsv27 0x01 /* RESERVED                                           */

/* Values for field "jfccpri" */
#define jfcrsv53 0x80 /* RESERVED                              MDC020       */
#define jfcrsv54 0x40 /* RESERVED                              MDC019       */
#define jfcrsv55 0x20 /* RESERVED                              MDC018       */
#define jfcrsv33 0x10 /* RESERVED                                           */
#define jfcrsv34 0x08 /* RESERVED                                           */
#define jfcrecv 0x04  /* -   R - RECEIVE PRIORITY                    MDC018 */
#define jfcequal 0x02 /* -   E - EQUAL PRIORITY                      MDC019 */
#define jfcsend 0x01  /* -   S - SEND PRIORITY                       MDC020 */

/* Values for field "jfcbctri" */
#define jfcbspac 0xC0 /* -   BIT PATTERN FOR SPACE REQUESTS                 */
#define jfcbcyl 0xC0  /* -   CYL REQUEST    (SPACE=(CYL,(...)))             */
#define jfcbtrk 0x80  /* -   TRK REQUEST    (SPACE=(TRK,(...)))             */
#define jfcbavr 0x40  /* -   AVRAGE BLOCK LENGTH (blklgth) REQUEST          */
#define jfcbmsgp 0x20 /* -   ** RESERVED-O **  (MSVGP) (MDC307)    @Z30LP9A */
#define jfcblksz 0x10 /* - ON indicates that the JFCBLKSI has been set      */
#define jfcontig 0x08 /* -   CONTIG REQUEST (SPACE=(x,(x,x,),,CONTIG))      */
#define jfcmixg 0x04  /* -   MXIG REQUEST   (SPACE=(x,(x,x,),,MXIG))        */
#define jfcalx 0x02   /* -   ALX REQUEST    (SPACE=(x,(x,x,),,ALX))         */
#define jfcround 0x01 /* -   ROUND REQUEST  (SPACE=(x,(x,x,),,,ROUND))      */
#define jfcbabs 0x00  /* -   ABSTR REQUEST  (SPACE=(ABSTR,(...)))           */

/* Values for field "jfcflgs1" */
#define jfcbdlet 0x80 /* -   ** RESERVED-O ** (OS/VS1)  (MDC305)   @XM05457 */
#define jfcblsr 0x80  /* -   Batch/LSR dataset                         @P5A */
#define jfctopen 0x40 /* -   TAPE DATA SET HAS BEEN OPENED           MDC026 */
#define jfcbadsp 0x20 /* -   AUTOMATIC DATA SET PROTECTION INDICATOR        */
#define jfcbprot 0x10 /* -   RACF PROTECT REQUESTED (OS/VS2)                */
#define jfcbceov 0x08 /* -   CHKPT=EOV SPECIFIED FOR THIS DATA SET          */
#define jfcvrds 0x04  /* -   VIO DATA SET                            MDC006 */
#define jfcbckds 0x02 /* -   DATA SET IS CHECKPOINT DATASET        @ZA52824 */
#define jfcbuaff 0x01 /* -   UNIT AFFINITY SPECIFIED FOR THIS DATA SET      */

/* Values for field "jfcbflg3" */
#define jfcdqdsp 0x80 /* -   REQUEST DEQUEUE OF TAPE VOLUME WHEN DEMOUNTED  */
#define jfcbexp 0x40  /* -   EXPIRATION DATE SPECIFIED  (MDC318)   @ZA27139 */
#define jfcbbftk 0x20 /* -   LRECL=NNNNNK WAS SPECIFIED                @L1C */
#define jfcposid 0x10 /* -   JFCRBIDO CONTAINS THE PHYSICAL LOCATION   @H1A */
#define jfctemps 0x08 /* - This flag identifies a Temporary,                */
#define jfcbddtk 0x04 /* -   Set on by IEFAB434 and IEFAB492 (Alloc)        */
#define jfculeov 0x02 /* Request that volumes be unloaded and the           */
#define jfcbrv07 0x01 /* - RESERVED                          @ZA18180       */

/* Values for field "jfcvldq" */
#define jfcvldq1 0x80 /* First volser in JFCAVOLS has been dequeued  @05A   */
#define jfcvldq2 0x40 /* Second volser in JFCAVOLS has been dequeued @05A   */
#define jfcvldq3 0x20 /* Third volser in JFCAVOLS has been dequeued  @05A   */
#define jfcvldq4 0x10 /* Fourth volser in JFCAVOLS has been dequeued @05A   */
#define jfcvldq5 0x08 /* Fifth volser in JFCAVOLS has been dequeued  @05A   */
#define jfcblgth 176  /* -     LENGTH OF JFCB (x'B0')                       */

// NOTE(Kelosky): manual updates
#if defined(__IBM_METAL__)
#pragma pack(reset)
#endif
typedef struct jfcb JFCB;

#endif