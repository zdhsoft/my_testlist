# electron实践笔记
### 只启动app，但不打开浏览器
- 见package.json的script
```json
    "start": "npm-run-all -p electron:serve ng:serve1", // 这里使用ng:serve1
    "ng:serve": "ng serve -c web -o",  // 因为有-o，启动的时候，会默认启动浏览器
    "ng:serve1": "ng serve -c web",    // 去除了-o，则只会启动app
```
启动调试的时候，只需要npm run start就可以了
### app更换icon
- 在src/assets/icons的对应的，使用自己的替换就可以了。
- 参考文章：https://blog.csdn.net/sinat_36728518/article/details/109244202
