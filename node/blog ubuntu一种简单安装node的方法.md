# ubuntu一种简单安装node的方法
- centos下安装node的方法，参考这个文章：https://zdhsoft.blog.csdn.net/article/details/73436740
# 目录 
[TOC]
# 安装过程
- 本方法适已经在16.04,18.04,20.04等ubuntu linux server成功安装过，其它ubuntu估计也差不多，没有试过
```bash
# 首先安装npm
sudo apt install npm
# 然后安装n
sudo npm install n -g
# 最后安装node 最新lts版本
sudo n lts
# npm 更新
npm install npm -g
```
- 到此结束，就可以完成node的安装了
- 如果要安装或切换其它版本，请大家了解n这个命令，比较简单易用。


