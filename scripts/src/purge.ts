#! /bin/env node

import { execSync, exec } from "child_process";

const cmd = `zowe jobs list jobs --rff jobid status`;
console.log(cmd)
const resp = execSync(cmd).toString();
const entries = resp.split("\n");
entries.pop(); // remove last dummy entry

entries.forEach( (entry) => {
    const jobIdAndStatus = entry.split(" ");
    if (jobIdAndStatus[1] === "OUTPUT") {
        const delCmd = `zowe jobs delete job ${jobIdAndStatus[0]}`;
        console.log(delCmd);
        exec(delCmd, (err, stdout, stderr) => {
            if (err) console.log(err)
            if (stdout) console.log(stdout.toString());
            if (stderr) console.log(stderr.toString());
        });
    }
})
