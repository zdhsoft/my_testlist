

## NPM链融服务服务器

### 概述

这里使用的npm服务器使用的开源的verdaccio  官网地址：[Verdaccio · Verdaccio：一个轻量级的开源 npm 私有部署仓库](https://verdaccio.org/zh-CN/)

因为，有些库使用包的形式，会比较方便。使用git sub moduled存在不少问题，使用非常不方便。

### 已部署的信息

- 部署在git一起的服务器，域名：http://npm.zdhsoft.cn

- 发布包有用户名：zdhsoft


- 要求包名：全部以@zdhsoft/开头,其它形式包，不支待发布。

- 示例 my-package的package.json：

```json
{
"name": "@zdhsoft/my-package",    // 注意：这里是包名，一定要@zdhsoft/开头
"version": "1.0.2",          // 注意：这里是版本号，每次发布至少要有一个小版号+1
"description": "Hello World",// 这里是包的说明 
"main": "index.js",
"scripts": {
  "test": "echo \"Error: no test specified\" && exit 1"
},
"author": "zdhsoft",          // 这里要注明作者
"license": "ISC",
"dependencies": {
  "xmcommon": "^0.1.9"
}
}

```

### 本地与生产环境registry设置

```bash
npm config set registry http://npm.lrscft.com  # 将npm.zdhsoft.cn做为默认的包源，这样，就不用再每次去设置了。
如果要还原，请用命令还原即可：
npm config set registry https://registry.npmjs.org
```

NPM链融服务服务器默认优先本地源，如果本地没有，将会使用淘宝的源：https://registry.npm.taobao.org/

### 服务器部署说明

- 官方安装说明[Installation · Verdaccio](https://verdaccio.org/docs/en/installation), 我这里只针对npm的版本，其它yarn或pnpm看官网。	windows下面，也可以同样安装使用

```bash
$>npm install -g verdaccio

$> verdaccio
warn --- config file  - /home/.config/verdaccio/config.yaml       # 注意，这里是配置文件的位置，第一次启动会默认创建
warn --- http address - http://localhost:4873/ - verdaccio/5.1.1

```

### 增加用户
```bash
npm adduser --registry http://localhost:4873/ 可以增加你第一个用户
```

### verdaccio配置

然后进行配置，看上面的打印的信息，配置的文件是 /home/.config/verdaccio/config.yaml，然后，我们可以配置, 中文注释的地方，可能增加配置

```yaml
#
# This is the default config file. It allows all users to do anything,
# so don't use it on production systems.
#
# Look here for more config file examples:
# https://github.com/verdaccio/verdaccio/tree/master/conf
#

# path to a directory with all packages
storage: ./storage  # 默认即可
# path to a directory with plugins to include
plugins: ./plugins # 默认即可

web:
title: Verdaccio # web主题显示的title
# comment out to disable gravatar support
# gravatar: false   #这里配置头像
# by default packages are ordercer ascendant (asc|desc)
# sort_packages: asc #这里配置包排序
# convert your UI to the dark side
# darkMode: true #这里配置web页面，是否显示暗主题 
# logo: http://somedomain/somelogo.png  #这里配置log 如:  ./logo.png
# favicon: http://somedomain/favicon.ico | /path/favicon.ico  #这里配置icon 如: ./favicon.ico

# translate your registry, api i18n not available yet
# i18n:
# list of the available translations https://github.com/verdaccio/ui/tree/master/i18n/translations
#   web: en-US   #这里配置语言 要注意，它是i18n下面的  web: zh-CN

auth:
htpasswd:
  file: ./htpasswd
  # Maximum amount of users allowed to register, defaults to "+inf".
  # You can set this to -1 to disable registration.
  # max_users: 1000  #这里配置用户数据  -1表示禁止注册

# a list of other known repositories we can talk to
uplinks:
npmjs:
  url: https://registry.npm.taobao.org/  #对于之外的库，使用什么源，我这里使用淘宝源

packages:
'@lr/*':  # @lr/ 开头的包 只有这里允许发布, 你可以改成自己的开头
  # scoped packages
  access: $all
  publish: $authenticated
  unpublish: $authenticated
  proxy: npmjs

'**':  # 对于其它任意包  ，只提供访问和代理的功能
  # allow all users (including non-authenticated users) to read and
  # publish all packages
  #
  # you can specify usernames/groupnames (depending on your auth plugin)
  # and three keywords: "$all", "$anonymous", "$authenticated"
  access: $all

  # allow all known users to publish/publish packages
  # (anyone can register by default, remember?)
#  publish: $authenticated
#  unpublish: $authenticated

  # if package is not available locally, proxy requests to 'npmjs' registry
  proxy: npmjs

# You can specify HTTP/1.1 server keep alive timeout in seconds for incoming connections.
# A value of 0 makes the http server behave similarly to Node.js versions prior to 8.0.0, which did not have a keep-alive timeout.
# WORKAROUND: Through given configuration you can workaround following issue https://github.com/verdaccio/verdaccio/issues/301. Set to 0 in case 60 is not enough.
server:
keepAliveTimeout: 60

middlewares:
audit:
  enabled: true

# log settings
logs: { type: stdout, format: pretty, level: http }

#experiments:
#  # support for npm token command
#  token: false
#  # disable writing body size to logs, read more on ticket 1912
#  bytesin_off: false
#  # enable tarball URL redirect for hosting tarball with a different server, the tarball_url_redirect can be a template string
#  tarball_url_redirect: 'https://mycdn.com/verdaccio/${packageName}/${filename}'
#  # the tarball_url_redirect can be a function, takes packageName and filename and returns the url, when working with a js configuration file
#  tarball_url_redirect(packageName, filename) {
#    const signedUrl = // generate a signed url
#    return signedUrl;
#  }

# This affect the web and api (not developed yet)
#i18n:
#web: en-US

```

配置完成后，重启它，就可以了。

可以使用pm2来管理：

```bash
pm2 start verdaccio
```

 ### nginx 端口映射  
 - 这是不做nginx的详细过程,只给配置。
 - 首先配置一个域名，如npm.zdhsoft.cn 指向你verdaccio所在的服务器地址。
 - 在nginx增加一个  npm.zdhsoft.cn.conf配置，如下
  ```lua
	upstream npm{
		server 127.0.0.1:4873;
	}

	server {
		listen       80;
		server_name  npm.zdhsoft.cn;
		
		location / {
			proxy_set_header Host $host;
			proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
			proxy_pass http://npm;
		}
	}
  ```
 - 然后启动nginx  

  