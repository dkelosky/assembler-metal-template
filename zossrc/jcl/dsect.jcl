//{{{settings.name}}} JOB {{{settings.account}}},
//             '{{{settings.description}}}',
//             MSGCLASS={{{settings.messageClass}}},
//             CLASS={{{settings.jobClass}}},
//             MSGLEVEL=(1,1),
//             REGION=0M
/*JOBPARM SYSAFF=*
// SET DPARM='PPCOND,EQUATE(DEF),BITF0XL,HDRSKIP,UNIQ,LP64,LEGACY'
{{#each convert.assemble.sources}}
//*
//* Assemble {{{@key}}}
//*
//         IF (RC = 0) THEN
//ASM{{@index}} EXEC PGM=ASMA90
//ASMAOPT  DD  *
{{!-- if options at this object level, use them  --}}
{{#if options}}
{{#each options}}
{{{.}}}
{{/each}}
{{!-- else use options at the higher context level  --}}
{{else}}
{{#each ../convert.assemble/options}}
{{{.}}}
{{/each}}
{{/if}}
/*
//SYSADATA DD  DISP=SHR,DSN={{{../settings.hlq}}}.ADATA({{{@key}}})
//SYSLIB   DD  DISP=SHR,DSN={{{../settings.hlq}}}.ASMMAC
{{#if includes}}
{{#each includes}}
//         DD  DISP=SHR,DSN={{{.}}}
{{/each}}
{{else}}
{{#each ../convert.assemble/includes}}
//         DD  DISP=SHR,DSN={{{.}}}
{{/each}}
{{/if}}
//SYSPRINT DD  SYSOUT=*
//SYSIN    DD  DISP=SHR,DSN={{{../settings.hlq}}}.ASMCHDR({{{@key}}})
//SYSLIN   DD  DISP=SHR,DSN={{{../settings.hlq}}}.OBJLIB({{{@key}}})
//         ENDIF
//         IF (RC = 0) THEN
//DSECT{{@index}} EXEC PGM=CCNEDSCT,
//         PARM='&DPARM,SECT(ALL)',
//         MEMLIMIT=256M
//STEPLIB  DD  DISP=SHR,DSN=CEE.SCEERUN2
//         DD  DISP=SHR,DSN=CBC.SCCNCMP
//         DD  DISP=SHR,DSN=CEE.SCEERUN
//SYSADATA DD  DISP=SHR,DSN={{{../settings.hlq}}}.ADATA({{{@key}}})
//EDCDSECT DD SYSOUT=*
//SYSPRINT DD SYSOUT=*
//SYSOUT   DD SYSOUT=*
//         ENDIF
{{/each}}
