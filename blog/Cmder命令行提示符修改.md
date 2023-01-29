# Cmder命令行提示符修改

## 修改提示符后缀

- 默认的后缀是：λ

- 修改 config/cmder_prompt_config.lua

  - 这个文件会在初始化的时候创建，如果这个文件不存在，在启动cmder的时候，会创建这个文件。实际是上从vendor/cmder_prompt_config.lua.default复制过来

  - 找到prompt_lambSymbol，可以修改成自己喜欢的后缀。
  
## 增加时间

-  在命令行提示的时候，增加时间显示往往会有很多用处。

- 修改vendor/clink.lua

  ```lua
  -- 找到函数set_prompt_filter，在它的最后一行或者直接搜索prompt_lambSymbol
  clink.prompt.value = string.gsub(prompt, "{lamb}", prompt_lambSymbol)
  -- 改为
  clink.prompt.value = string.gsub(prompt, "{lamb}", os.date("%m-%d %H:%M:%S") .. prompt_lambSymbol)
  -- 每个新命令行，就会显示当前的时间
  
  ```

  

  