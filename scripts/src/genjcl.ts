#! /bin/env node

// bypass immutability
process.env.ALLOW_CONFIG_MUTATIONS = "yes"; // value doesn't matter

import * as config from "config";
import * as handlebars from "handlebars";
import * as fs from "fs";

const assembles = config.get<object[]>("job.assembly")
let index: number;
// assembles.push({name: "hey"})
// assembles.forEach((ass, i) => {
    // if (ass.name === "WTO") index = i
// })
// if (index) assembles.splice(index)

const jcl = fs.readFileSync("./zossrc/jcl/template.jcl").toString();
const compiled = handlebars.compile(jcl); 
const rendered = compiled(config);

if (!fs.existsSync("./build")) fs.mkdirSync("./build");
fs.writeFileSync("./build/custom.jcl", rendered);
console.log("Generated custom JCL to ./build/custom.jcl");