# 二次开发笔记

# 依赖环境说明
## 数据库
- 现在mongodb的数据库版本是4.x 默认安装，并默认企动就可以了。我这里已经去除了密码和用户名的验证

## node环境要求
- 请不要使用node 16或更新的版本, ykit会不生效。

## 编译环境
- 建议使用node 10.x以上的版本
- 由于前编编译使用了node-sass，所以需要C++编译环境。对于windows环境，需要ms-build，请安下面步骤安装
- 如果你的电脑有python3请卸载。如果没有python2，则请官网下载python2，并安装。请在系统环境变量增加%PYTHON_HOME%=C:\Python27, 在%PATH%增加%PYTHON_HOME%，使它可以在命令行下面执行python
- 参考文档:https://zdhsoft.blog.csdn.net/article/details/117981532
- 第三步: 要管理员权限的命令行下输入：
```BAT
npm install -g node-gyp
npm install --global --production windows-build-tools
```


## 运行
### 全局安装 nodemon
- 这个是监控文件变化，自动重启的工具，这个是针对服务器
```BAT
npm install nodemon -g
```
### 正常命令运行服务器
```BAT
npm run start
```
### 文件变化自动重启服务器
```BAT
npm run dev-server
```

### 在vscode中调试服务器
- 打开vsocde左边面版中的 调试与运行 创建lanch.json
- 然后创建一个启动项,如下中的”运行后端“
```json
{
    // Use IntelliSense to learn about possible attributes.
    // Hover to view descriptions of existing attributes.
    // For more information, visit: https://go.microsoft.com/fwlink/?linkid=830387
    "version": "0.2.0",
    "configurations": [
        {
            "type": "node",
            "request": "launch",
            "name": "运行后端",
            "skipFiles": [
                "<node_internals>/**"
            ],
            "program": "${workspaceFolder}\\server\\app.js"
        },
        {
            "type": "node",
            "request": "launch",
            "name": "安装配置服务",
            "skipFiles": [
                "<node_internals>/**"
            ],
            "program": "${workspaceFolder}\\server\\install.js"
        }
    ]
}

```


- package.json的scripts的脚本
```javascript
{
  "scripts": {
    "dev-copy-icon": "cp -r static/iconfont ./",
    "dev-server": " nodemon server/app.js dev -L",
    "install-server": " node server/install.js",
    "dev-client": "npm run dev-copy-icon && ykit s -p 4000",
    "dev": "npm run dev-server & npm run dev-client",
    "start": " node server/app.js",
    "test": "ava",
    "build-client": "ykit pack -m NODE_ENV=production",
    "npm-publish": "node ./npm-publish.js",
    "docs": "ydoc build"
  },
  "scripts-info": {
    "start": "运行生产环境服务器",
    "install-server": "初始化数据库数据，用于安装",
    "dev": "运行开发服务器",
    "dev-server": "运行后端开发服务器",
    "dev-client": "运行前端开发服务器",
    "test": "执行测试"
  },
}
```

### 配置nginx
- 由于测试服务器启动的端口与测试前端启动的端口不同，结果相互无法访问, 在这里使用nginx对这两个端口做映射成同一个域名。下面是nginx配置
- 实际调试效果，还是失败。
```conf
upstream yapi_dev_client{
    server 127.0.0.1:4000;
}

server {
    listen 80;
    server_name yapidev.zdhsoft.cn; # 三级子域名会显示ERR_CERT_COMMON_NAME_INVALID
    set $yapi_server_port 3000;

    location ^~ /api/ {
        proxy_http_version 1.1;
        proxy_set_header X-Real-IP $remote_addr;
        proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
        proxy_set_header Host $http_host;
        proxy_set_header X-NginX-Proxy true;
        proxy_set_header Upgrade $http_upgrade;
        proxy_set_header Connection "upgrade";
        proxy_pass http://127.0.0.1:$yapi_server_port$request_uri;
        proxy_redirect off;
    }


    location / {
        proxy_set_header Host $host;
        proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
        proxy_pass http://yapi_dev_client;
    }
}

```

## 问与与修复
### 1、数据库用户名密码不正确
- 将server\utils\db.js中的dbconfig注释
```javascript
// 如果你的数据库，没有设置用户名和密码的时候
//   if (config.db.user) {
//     options.user = config.db.user;
//     options.pass = config.db.pass;
//   }
```
或者你配置一个用户名写密码
### 2、在windows环境下，连接数据库返回undefined
- 将 let db = mongoose.connect 中的db放弃使用, 使用const db =  mongoose.connection;获得db
```javascript
  //let db = await mongoose.connect(connURL, option);
  const db =  mongoose.connection;
```
