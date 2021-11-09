# nestjs笔记
## vscode的调试
### vscode的任务配置
在.vscode目录下面，建一个json文件：tasks.json，为什么建这个，因为我在调试先，先运行编译
```json
{
	"version": "2.0.0",
	"tasks": [
        {
            "type": "npm",
            "script": "build",
            "group": "build",
            "problemMatcher": [],
            "label": "build",
            "detail": "nest build"
        }
    ]
}
```
注：这个是实际上是调用package.json中定义的script的build
下面是是package.json的script的内容
```json
"scripts": {
    "prebuild": "rimraf dist",
    "build": "nest build",
    "format": "prettier --write \"src/**/*.ts\" \"test/**/*.ts\"",
    "start": "nest start",
    "start:dev": "nest start --watch",
    "start:debug": "nest start --debug --watch",
    "start:prod": "node dist/main",
    "lint": "eslint \"{src,apps,libs,test}/**/*.ts\" --fix",
    "test": "jest",
    "test:watch": "jest --watch",
    "test:cov": "jest --coverage",
    "test:debug": "node --inspect-brk -r tsconfig-paths/register -r ts-node/register node_modules/.bin/jest --runInBand",
    "test:e2e": "jest --config ./test/jest-e2e.json"
  }
```
### vscode的配置调试
在左边的调试按钮，会有提示创建launch.json，我这里选择node方式
```json
{
    // 使用 IntelliSense 了解相关属性。
    // 悬停以查看现有属性的描述。
    // 欲了解更多信息，请访问: https://go.microsoft.com/fwlink/?linkid=830387
    "version": "0.2.0",
    "configurations": [
        {
            "type": "node",
            "request": "launch",
            "console":"integratedTerminal",  // 设成integratedTerminal后，就可以在vscode的调试控制台，显示nest的日志
            "name": "Launch Program",
            "skipFiles": [
                "<node_internals>/**"
            ],
            "autoAttachChildProcesses": true,
            "runtimeExecutable": "node",
            "program": "${workspaceFolder}\\dist\\main.js", //这个是编译后的程序入口
            "preLaunchTask": "build",  // 在运行之间，会调用tasks.json中label为build的任务
            "outFiles": [
                // 输出的文件
                "${workspaceFolder}/dist/**/*.js"
            ]
        }
    ]
}

```
