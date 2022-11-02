# 总结
## 调试与启动
### 启动 
  - 这个会自动编译（当文件有变化的时候，并自动更新显示的浏览器）
```bash
$npm run start
```
### 显示
  - 在浏览器输入:http://localhost:4200就可以显示了
  - 如果要启动的时候自动打开浏览器，则修改package.json中的script中的start增加一个参数 -o 就可以了
```json
	"start": "ng serve -o"
```
### 开发与调试
#### 浏览器的angular插件：angular DevTools
#### 断点与调试
- 按F12进入开发模式
- 选择soruce, 在左侧有一个网页树选择top->webpack: 就可以选择对应的源代码，打开后，可以断点
- 可以在需要断点的地方，打一个console.log日志，在控制台可以定位到对应的源代码，就可以切换到源代码，就可以断点