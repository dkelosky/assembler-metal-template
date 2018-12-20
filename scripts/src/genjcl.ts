#! /bin/env node
import * as config from "config";
import * as handlebars from "handlebars";
import * as fs from "fs";

const jcl = fs.readFileSync("./zossrc/jcl/template.jcl").toString();
const compiled = handlebars.compile(jcl); 
const rendered = compiled(config);

if (!fs.existsSync("./build")) fs.mkdirSync("./build");
fs.writeFileSync("./build/custom.jcl", rendered);
console.log("Generated custom JCL to ./build/custom.jcl");