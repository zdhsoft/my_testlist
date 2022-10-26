# electron实践笔记
### 只启动app，但不打开浏览器
- 见package.json的script
```json
    "ng:serve": "ng serve -c web -o",  // 因为有-o，启动的时候，会默认启动浏览器
    "ng:serve1": "ng serve -c web",    // 去除了-o，则只会启动app
```
### 启动调试的时候，只需要npm run start就可以了
