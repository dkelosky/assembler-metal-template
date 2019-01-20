//{{{settings.name}}} JOB {{{settings.account}}},
//             '{{{settings.description}}}',
//             MSGCLASS={{{settings.messageClass}}},
//             CLASS={{{settings.jobClass}}},
//             MSGLEVEL=(1,1),
//             REGION=0M
/*JOBPARM SYSAFF=*
{{#each test}}
//RUN{{@index}} EXEC PGM=AMSTEST
//STEPLIB  DD  DISP=SHR,DSN={{{../settings.hlq}}}.LOADLIB
//SYSPRINT DD  SYSOUT=*
//IN       DD  *
{{{in}}}
/*
{{/each}}
