# nestjs 工程创建工具
- 基于现在的模板工程，做相应的替换，达到创建nestjs的目的，减少重复的工程创建工作
## 需求说明
- 一句话需求：将指定目录下的模板文件，按照要求 替换成目标，并存放到指定的目录
### 模板说明
- 每个模板目录，都有一个template.json文件，用于描述模板的目录列表与文件列表
- 文件列表或目录列表，都是相对模板目录对应的路径
- 模板格式如下：
 ```json
{
    "dirList": [
        "b",
        "src",
        ".vscode"
    ],
    "fileList": [
        "package.json",
        "b/b.txt"
    ]
}
```
### 项目说明
- 项目配置文件 prject.json 这些都是用于替换的内容
- 项目输出目录，最终存放项目文件的目录。
- 输出的目录要求与模板的目录是对应的。
- 输出的文件，也是和模板的文件是对应的。
- 这两个参数，参考node脚本传入
```bash
node . project/demo.json c:/temp/demo
```
- 参考说明: node . project_name project_path 

```
## art-template 使用资料
- 参考:《art-template实例（超详细）》https://www.cnblogs.com/furfur-jiang/p/11393107.html
- 参考:《art-template模板总结》 https://blog.csdn.net/qq_27674439/article/details/94383037