#! /bin/env node
import * as config from "config";
import { exec } from "child_process";
import { readdirSync, existsSync } from "fs";
import { basename, extname } from "path";
import { Uploads } from "./doc/IUploads";

const hlq: string = config.get<string>('settings.hlq');
const uploads: Uploads = config.get<Uploads>('uploads');

Object.keys(uploads).forEach((key) => {
    const dir = `./zossrc/${key}`;
    if (existsSync(dir)) {
        const files = readdirSync(dir);
        files.forEach( (file) => {
            const fileWOutExtension = basename(file, extname(file));
            const cmd = `zowe files upload ftds ` +
                `"${dir}/${file}" ` +
                `"${hlq}.${uploads[key]}(${fileWOutExtension})"`
            console.log(cmd);
            exec(cmd, (err, stdout, stderr) => {
                if (err) console.log(err)
                if (stdout) console.log(stdout.toString());
                if (stderr) console.log(stderr.toString());
            });
        });
    }
});
