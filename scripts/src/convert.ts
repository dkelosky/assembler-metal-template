#! /bin/env node

// bypass immutability
process.env.ALLOW_CONFIG_MUTATIONS = "yes"; // value doesn't matter

import * as config from "config";
import * as handlebars from "handlebars";
import * as fs from "fs";

// render the JCL
const jcl = fs.readFileSync("./zossrc/jcl/dsect.jcl").toString();
const compiled = handlebars.compile(jcl);
const rendered = compiled(config);

if (!fs.existsSync("./build")) fs.mkdirSync("./build");
fs.writeFileSync("./build/convert.jcl", rendered);
console.log("Generated custom JCL to ./build/convert.jcl");