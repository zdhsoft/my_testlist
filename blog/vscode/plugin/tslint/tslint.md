# TSLINT
## 概述
- 现在开发后端主要的开发语言是Typescript，检查工具使用的是tslint。由于存在一些问题，tslint被弃用了，建议使用eslint。但是实际使用eslint的过程中，发现达不到之前使用tslint的效果。所有没有办法，还是一直使用tslint，但是每次需要手动开启。
- 直到有一天，我再次安装插件的时候，发现了tslint有一个是新版本。全称是：ms-vscode.vscode-typescript-tslint-plugin，版本是1.3.3，是microsoft的官方版本插件。 这表示了众多使用tslint者的愿意。
```text
❗IMPORTANT: TSLint has been deprecated in favor of ESLint.

Please look into migrating your projects to ESLint.

Adds tslint to VS Code using the TypeScript TSLint language service plugin.

Please refer to the tslint documentation for how to configure the linting rules.
```
## 新tslint的插件使用
- 在Vscode的插件管理，搜索tslint
- 这个时候，会看到microsoft出品的tslint, 版本是1.3.3
- 安装并启用
- 和原来tslint配置一样，在工程的根目录创建tslint.json，我这里默认配置如下：
```json
{
    "defaultSeverity": "error",
    "extends": [
        "tslint:recommended"
    ],
    "jsRules": {},
    "rules": {
        "no-namespace": false,
        "ordered-imports": false,
        "member-ordering": false,
        "object-literal-sort-keys": false,
        "trailing-comma": false,
        "no-var-requires": false,
        "no-empty": false,
        "interface-over-type-literal": false,
        "object-literal-shorthand": false,
        "no-empty-interface": false,
        "interface-name": false,
        "eofline": false,
        "variable-name":false,
        "max-classes-per-file":false,
        "quotemark": false,
        "callable-types":true,
        "no-console":true,
        "prefer-const":false,
        "no-string-literal":false,
        "forin": false,
        "radix": false,
        "curly": [true, "ignore-same-line"],
        "no-arg": true,
        "no-parameter-reassignment": true,
        "member-access": [true, "check-accessor", "check-constructor", "check-parameter-property"],
        "adjacent-overload-signatures": true,
        "label-position": false,
        "no-conditional-assignment": true,
        "no-construct": true,
        "no-duplicate-super": true,
        "no-duplicate-switch-case": true,
        "no-duplicate-variable": [true, "check-parameters"],
        "no-implicit-dependencies": [true, "dev"],
        "max-line-length": [
            true,
            {
                "limit": 160,
                "ignore-pattern": "^import |^export {(.*?)}",
                "check-strings": false,
                "check-regex": true
            }
        ],
        "typedef-whitespace":[
            true,
            {"parameter": "nospace" }
        ]
    },
    "rulesDirectory": []
}
```
- 然后就可以看到有相应的错误提示了。
- 这个办法，有一个缺点，就是不能像之前那样，当tslint当一个命令来使用，统计对所有的源代码，都作代码检查。

### 请注意
- 默认情况下，使用全局的版本的typescript， 不会加载tslint和自定义配置。
要使用本地 TSLint 安装和工作区中的自定义规则启用，您必须：
使用与 TSLint 一起安装的 TypeScript 工作区版本。
通过运行 TSLint:Manage Workspace Library Execution 命令启用工作区库执行。

- 配置使用参考：https://github.com/zdhsoft/typescript-tslint-plugin
- 下面是一个tsconfig.json文件，参考[xmcommon/tsconfig.json at master · zdhsoft/xmcommon (github.com)](https://github.com/zdhsoft/xmcommon/blob/master/tsconfig.json)
```json
{
  "compilerOptions": {
    /* Visit https://aka.ms/tsconfig.json to read more about this file */
    "plugins": [
        {
            // https://github.com/zdhsoft/typescript-tslint-plugin  这块的帮助，请这个说明
            "name": "typescript-tslint-plugin" ,
            "alwaysShowRuleFailuresAsWarnings": false,
            "ignoreDefinitionFiles": true,
            // "configFile": "../tslint.json",
            "suppressWhileTypeErrorsPresent": false,
            "packageManager":"cnpm"
        }
    ],
    /* Basic Options */
    // "incremental": true,                         /* Enable incremental compilation */
    "target": "ES2017",                                /* Specify ECMAScript target version: 'ES3' (default), 'ES5', 'ES2015', 'ES2016', 'ES2017', 'ES2018', 'ES2019', 'ES2020', or 'ESNEXT'. */
    "module": "commonjs",                           /* Specify module code generation: 'none', 'commonjs', 'amd', 'system', 'umd', 'es2015', 'es2020', or 'ESNext'. */
    // "lib": [],                                   /* Specify library files to be included in the compilation. */
    // "allowJs": true,                             /* Allow javascript files to be compiled. */
    // "checkJs": true,                             /* Report errors in .js files. */
    // "jsx": "preserve",                           /* Specify JSX code generation: 'preserve', 'react-native', 'react', 'react-jsx' or 'react-jsxdev'. */
    "declaration": true,                         /* Generates corresponding '.d.ts' file. */
    // "declarationMap": true,                      /* Generates a sourcemap for each corresponding '.d.ts' file. */
    // "sourceMap": true,                           /* Generates corresponding '.map' file. */
    // "outFile": "./",                             /* Concatenate and emit output to single file. */
     "outDir": "./dist",                              /* Redirect output structure to the directory. */
    // "rootDir": "./",                             /* Specify the root directory of input files. Use to control the output directory structure with --outDir. */
    // "composite": true,                           /* Enable project compilation */
    // "tsBuildInfoFile": "./",                     /* Specify file to store incremental compilation information */
    // "removeComments": true,                      /* Do not emit comments to output. */
    // "noEmit": true,                              /* Do not emit outputs. */
    // "importHelpers": true,                       /* Import emit helpers from 'tslib'. */
    // "downlevelIteration": true,                  /* Provide full support for iterables in 'for-of', spread, and destructuring when targeting 'ES5' or 'ES3'. */
    // "isolatedModules": true,                     /* Transpile each file as a separate module (similar to 'ts.transpileModule'). */

    /* Strict Type-Checking Options */
    "strict": true,                                 /* Enable all strict type-checking options. */
    // "noImplicitAny": true,                       /* Raise error on expressions and declarations with an implied 'any' type. */
    // "strictNullChecks": true,                    /* Enable strict null checks. */
    // "strictFunctionTypes": true,                 /* Enable strict checking of function types. */
    // "strictBindCallApply": true,                 /* Enable strict 'bind', 'call', and 'apply' methods on functions. */
    // "strictPropertyInitialization": true,        /* Enable strict checking of property initialization in classes. */
    // "noImplicitThis": true,                      /* Raise error on 'this' expressions with an implied 'any' type. */
    // "alwaysStrict": true,                        /* Parse in strict mode and emit "use strict" for each source file. */

    /* Additional Checks */
    // "noUnusedLocals": true,                      /* Report errors on unused locals. */
    // "noUnusedParameters": true,                  /* Report errors on unused parameters. */
    // "noImplicitReturns": true,                   /* Report error when not all code paths in function return a value. */
    // "noFallthroughCasesInSwitch": true,          /* Report errors for fallthrough cases in switch statement. */
    // "noUncheckedIndexedAccess": true,            /* Include 'undefined' in index signature results */
    // "noPropertyAccessFromIndexSignature": true,  /* Require undeclared properties from index signatures to use element accesses. */

    /* Module Resolution Options */
    // "moduleResolution": "node",                  /* Specify module resolution strategy: 'node' (Node.js) or 'classic' (TypeScript pre-1.6). */
    // "baseUrl": "./",                             /* Base directory to resolve non-absolute module names. */
    // "paths": {},                                 /* A series of entries which re-map imports to lookup locations relative to the 'baseUrl'. */
    // "rootDirs": [],                              /* List of root folders whose combined content represents the structure of the project at runtime. */
    // "typeRoots": [],                             /* List of folders to include type definitions from. */
    // "types": [],                                 /* Type declaration files to be included in compilation. */
    // "allowSyntheticDefaultImports": true,        /* Allow default imports from modules with no default export. This does not affect code emit, just typechecking. */
    "esModuleInterop": true,                        /* Enables emit interoperability between CommonJS and ES Modules via creation of namespace objects for all imports. Implies 'allowSyntheticDefaultImports'. */
    // "preserveSymlinks": true,                    /* Do not resolve the real path of symlinks. */
    // "allowUmdGlobalAccess": true,                /* Allow accessing UMD globals from modules. */

    /* Source Map Options */
    // "sourceRoot": "./lib",                            /* Specify the location where debugger should locate TypeScript files instead of source locations. */
    // "mapRoot": "",                               /* Specify the location where debugger should locate map files instead of generated locations. */
    // "inlineSourceMap": true,                     /* Emit a single file with source maps instead of having a separate file. */
    // "inlineSources": true,                       /* Emit the source alongside the sourcemaps within a single file; requires '--inlineSourceMap' or '--sourceMap' to be set. */

    /* Experimental Options */
    // "experimentalDecorators": true,              /* Enables experimental support for ES7 decorators. */
    // "emitDecoratorMetadata": true,               /* Enables experimental support for emitting type metadata for decorators. */

    /* Advanced Options */
    "skipLibCheck": true,                           /* Skip type checking of declaration files. */
    "forceConsistentCasingInFileNames": true        /* Disallow inconsistently-cased references to the same file. */
  }
}

```
