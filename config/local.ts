export default {
    settings: {
        hlq: "KELDA16.METALC",
        name: "KELDA16$",
        account: "105300000",
    },
    deploy: {
        ftp: {
            // options not supported yet
            options: [
                "kelda16",
                "kelda16",
                "lcd 'KELDA16.APF.JCLCHECK.LOADLIB'",
                "cd 'KELDA16.WORK.LOADLIB'",
                "binary",
                "mdelete *"
            ],
        }
    },
}