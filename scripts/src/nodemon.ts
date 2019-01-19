#! /bin/env node
import { basename, dirname, extname, sep } from "path";
import { exec } from "child_process";

const nodemon = require("nodemon");

nodemon({
    ext: "c h",
    watch: "zossrc",
    exec: "echo Watching for changes",
    // script: '',
});

nodemon.on('restart', function (filePaths: string[]) {
    filePaths.forEach((filePath) => {
        const file = basename(filePath);
        const dir = dirname(filePath).split(sep);
        const folder = dir.pop();
        const cmd = `npm run upload -- ${folder}${sep}${file}`;
        console.log(cmd);
        exec(cmd, (err, stdout, stderr) => {
            if (err) console.log(err)
            if (stdout) console.log(stdout.toString());
            if (stderr) console.log(stderr.toString());
        });
    });
});