# Zowe Assembler Example

## Setup
1. `git clone` this project
2. `npm install`
3. Create a file `config/local.json` with your project settings, e.g.:
```json
{
    "settings": {
        "hlq": "KELDA16.TEMPLATE",
        "name": "KELDA16$",
        "account": "105300000"
    }
}
```

## Usage

* `npm run allocate` -> Allocate your project data sets
* `npm run delete` -> Delete your project data sets
* `npm run genjcl` -> Generate JCL from template (see [advanced upload](#gen-jcl))
* `npm run genjcl:convert` -> Generate JCL to convert assembler DSECTs to C structures
* `npm run upload` -> Upload source to data sets (see [advanced upload](#upload))
* `npm run submit` -> Run JCL and download output
* `npm run submit:convert` -> Run JCL to convert assembler DSECTs to C structures
* `npm run build` -> Build scripts

### Advanced Usage

#### Gen JCL
 * `npm run genjcl -- assemble` -> build JCL for assemble only
 * `npm run genjcl -- compile assemble/template bind execute` -> build JCL for compile, assemble template, bind, and execute

#### Upload
 * `npm run upload -- asmpgm` -> upload asmpgm folder
 * `npm run upload -- asmpgm asmmac/#entry asmmac/#exit` upload asmpgm folder & #entry / #exit from asmmac

## Reference
https://medium.com/@dkelosky/zowe-and-hlasm-hello-world-build-deploy-695be1eb13dc
https://medium.com/@dkelosky/how-to-automate-z-os-data-set-allocation-using-zowe-json-30e70fb960d8
