#! /bin/env node
import * as config from "config";
import * as mustache from "mustache";
import * as fs from "fs";

const jcl = fs.readFileSync("./zossrc/jcl/template.jcl").toString();
const rendered = mustache.render(jcl, config);

if (!fs.existsSync("./build")) fs.mkdirSync("./build");
fs.writeFileSync("./build/custom.jcl", rendered);
console.log("Generated custom JCL to ./build/custom.jcl");