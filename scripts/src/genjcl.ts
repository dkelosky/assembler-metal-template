#! /bin/env node

/**
 * Use to generate custom JCL to compile, assemble, bind, and execute all source or a subset of it
 *
 * Examples:
 *  npm run genjcl
 *  npm run genjcl -- assemble bind execute
 *  npm run genjcl -- compile assemble/template bind execute
 */

// bypass immutability
process.env.ALLOW_CONFIG_MUTATIONS = "yes"; // value doesn't matter

import * as config from "config";
import * as handlebars from "handlebars";
import * as fs from "fs";
import { dirname, basename } from "path";

// get config
const job: any = config.get('job');

// map of key in job (e.g. assemble, compile, bind, exec) with value
// as a map of source without a value
const steps = new Map<string, Map<string, null> | null>();

// get command args
const numOfParms = process.argv.length - 2;

// if input parms, add to map, then loop up job keys and keep what is in the map
if (numOfParms > 0) {
    for (let i = 0; i < numOfParms; i++) {

        // if only a job step (no sources) e.g. npm run genjcl -- assemble
        if (dirname(process.argv[2 + i]) === ".") {

            // see if it exists
            try {
                config.get(`job.${process.argv[2 + i]}`);
            } catch (err) {
                console.error(`>>> ${process.argv[2 + i]} is not in configuration`)
            }

            // add this entry to map
            steps.set(`${process.argv[2 + i]}`, null);

            // else specified step and sources, e.g. npm run genjcl -- compile assemble/template
        } else {

            const sources = steps.get(`${dirname(process.argv[2 + i])}`);

            // see if we have a map of sources attached to map of steps
            // if yes, add this source to the map
            if (sources) {
                sources.set(basename(process.argv[2 + i]).toUpperCase(), null);

                // else create the map and first entry
            } else {
                steps.set(`${dirname(process.argv[2 + i])}`, new Map<string, null>([[basename(process.argv[2 + i]).toUpperCase(), null]]));
            }
        }
    }
}

// if we have any overriding configuration on the CLI
if (steps.size > 0) {

    // loop through job steps
    Object.keys(job).forEach((step) => {

        // if step isn't in map, delete it
        if (!steps.has(step)) {
            delete job[step]

            // if it is in the map, see if we have a sources map attached
        } else {
            const nextMap = steps.get(step);
            if (nextMap) {

                // loop through sources on this step and delete ones that are absent from the map
                Object.keys(job[step].sources).forEach((source) => {
                    if (!nextMap.has(source)) {
                        delete job[step].sources[source];
                    }
                })
            }
        }
    })
}

// render the JCL
const jcl = fs.readFileSync("./zossrc/jcl/template.jcl").toString();
const compiled = handlebars.compile(jcl);
const rendered = compiled(config);

if (!fs.existsSync("./build")) fs.mkdirSync("./build");
fs.writeFileSync("./build/custom.jcl", rendered);
console.log("Generated custom JCL to ./build/custom.jcl");