import { execSync } from 'child_process';
import { writeFileSync } from 'fs';
import { readFileSync } from 'fs';

const KEY_FILE = 'key.txt';
const CMD_FILE = 'cmds.txt';
const MAX_FAIL = 5;
const WAIT_TIME = 1000 * 60 * 5; // 5 minutes (in milliseconds) - milliseconds * seconds * minutes

function start() {
    console.log(`Starting TSO...`);
    const key = execSync(`zowe tso start as --sko`).toString().trim();
    writeFileSync(KEY_FILE, key);

    commands().forEach(cmd => {
        console.log(`running '${cmd}'`)
        send(key, cmd);
    });

    console.log(`... key was ${key}`);
    return key;
}

function ping(key) {
    try {
        console.log(execSync(`zowe tso ping as ${key}`).toString().trim());
        return true;
    } catch (e) {
        return false;
    }
}

function stop(key) {
    try {
        console.log(execSync(`zowe tso stop as ${key}`).toString().trim());
        return true;
    } catch (e) {
        return false;
    }
}

function read() {
    try {
        return readFileSync(KEY_FILE).toString().trim();
    } catch (e) {
    }
    return `fakekey`;
}

function commands() {
    try {
        return readFileSync(CMD_FILE).toString().trim().split(/\r?\n/g);
    } catch (e) {
    }
    return [];
}

function send(key, cmd) {
    try {
        console.log(execSync(`zowe tso send as ${key} --data "${cmd}"`).toString().trim());
    } catch (e) {
        // do nothing
    }
}

function keep() {

    let failed = 0;
    let key = read();
    if (!ping(key)) {
        failed++;
        if (failed > MAX_FAIL) {
            console.log(`failed too many times`);
            process.exit(1);
        }
        key = start();
    }
}

// stop(read()); // debug
keep();
setInterval(() => {
    keep();
}, WAIT_TIME);