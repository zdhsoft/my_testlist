# nestjs系列笔记 
[nestjs系列笔记](https://zdhsoft.blog.csdn.net/article/details/121746302)

# nest记笔五：使用TypeORM连接mysql
- 这个比较简单，在之前的例子中，实际上已经连上了数据库了
## 1. 连接配置TypeORM
### 1.1 首先安装依赖包，**@nestjs/typeorm**, **typeorm**, **mysql2**
```bat
npm install --save @nestjs/typeorm typeorm mysql2
```
### 1.2 在项目根目录下，生成一个**ormconfig.json**文件
```json
[
  {
    "type": "mysql",
    "host": "127.0.0.1",
    "port": 3306,
    "username": "root",
    "password": "",   // 你的数据库密码
    "database": "",   // 你的数据库
    "synchronize": false,
    "entities": ["entities/*.js"]
  }
]
```
### 1.2 安装完成后，需要在appModule里面导入TypeOrmModule.
```typescript
// app.module.ts
import { Module } from '@nestjs/common';
import { TypeOrmModule } from '@nestjs/typeorm';
@Module({
  imports: [
    TypeOrmModule.forRoot(),  // typeorm默认使用ormconfig.json这个配置文件。 也可以能过forRoot的参数中确认
  ],
})
export class AppModule {}
```
### 1.3 直接在forRoot中填写配置的示例
```typescript
// app.module.ts
import { Module } from '@nestjs/common';
import { TypeOrmModule } from '@nestjs/typeorm';

@Module({
  imports: [
    TypeOrmModule.forRoot({  // 这里就是使用非ormconfig.json
    "type": "mysql",
    "host": "127.0.0.1",
    "port": 3306,
    "username": "root",
    "password": "",   // 你的数据库密码
    "database": "",   // 你的数据库
    "synchronize": false,
    "entities": ["dist/**/*.entity{ .ts,.js}"]  // 按照这里的配置，所有entity的对象可以自动注入，不需导入到任何模块了
    }),
  ],
})
export class AppModule {}
```
### 1.4 安装**全局**的typeorm-model-generator, 可以通过它来生成数据库表对应的entity代码。
```bash
npm install typeorm-model-generator -g
# 然后执行命令，按照提示，完成代码生成。
typeorm-model-generator
```
### 1.5 更多TypeORM连接配置
直接参考官网：https://typeorm.io/#/connection-options

## 2. entity 操作
- 详细内容，参考官网：https://typeorm.io/#/entities
### 2.1 准备
- 第一步：生成user相关的代码
```bash
# nest详细的命令帮助: nest --help
# 生成user模块
nest g mo user  
# 生成相应的service
nest g s user
# 生成相应的controller
nest g co user
 
```
- user.module.ts
```typescript
import { Module } from '@nestjs/common';
import { UserService } from './user.service';
import { UserController } from './user.controller';
import { TypeOrmModule } from '@nestjs/typeorm';
import { User } from './user.entity';

@Module({
    imports: [TypeOrmModule.forFeature([User])], // 这里需要申明，就可以使用User这个实体了
    providers: [UserService],
    controllers: [UserController],
    exports: [TypeOrmModule],// 加上这行
})
export class UserModule {}

```
- user.service.ts
```typescript
import { Injectable } from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { Repository } from 'typeorm';
import { User } from './user.entity';

@Injectable()
export class UserService {
    constructor(@InjectRepository(User) private usersRepository: Repository<User>) {}

    findAll() {
        return this.usersRepository.find();
    }

    findOne(id: number) {
        return this.usersRepository.findOne(id);
    }

    remove(id: number) {
        return this.usersRepository.delete(id);
    }
}
```
- user.controller.ts
 ```typescript
import { Body, Controller, Post } from '@nestjs/common';
import { XCommonRet } from 'xmcommon';
import { UserService } from './user.service';

@Controller('user')
export class UserController {
    constructor(private readonly userService: UserService) {}
    @Post('all')
    // @HttpCode(200)
    async all() {
        const r = new XCommonRet();
        r.setData(await this.userService.findAll());
        return r;
    }

    @Post('user')
    async getUser(@Body() param: { id: number }) {
        const r = new XCommonRet();
        r.setData(await this.userService.findOne(param.id));
        return r;
    }
}

```
### 2.2 生成实体
- 使用下面SQL语句，生成数据库表
```SQL
DROP TABLE IF EXISTS `user`;
CREATE TABLE `user`  (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `firstName` varchar(255) CHARACTER SET utf8 COLLATE utf8_unicode_ci NOT NULL,
  `lastName` varchar(255) CHARACTER SET utf8 COLLATE utf8_unicode_ci NOT NULL,
  `age` int(11) NOT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 1 CHARACTER SET = utf8 COLLATE = utf8_unicode_ci ROW_FORMAT = Dynamic;
```
- 使用typeorm-model-generator生成实体代码
```typescript
// src/user/user.entity.ts
import { Column, Entity, PrimaryGeneratedColumn } from 'typeorm';

@Entity('user', { schema: 'orm' })
export class User {
    @PrimaryGeneratedColumn({ type: 'int', name: 'id' })
    id: number;

    @Column('varchar', { name: 'firstName', length: 255 })
    firstName: string;

    @Column('varchar', { name: 'lastName', length: 255 })
    lastName: string;

    @Column('int', { name: 'age' })
    age: number;
}
```
- 将生成的user.ts复制到src/user/目录下，并改名为user.entity.ts

完后，就可以使用它做基本的数据库操作了。

