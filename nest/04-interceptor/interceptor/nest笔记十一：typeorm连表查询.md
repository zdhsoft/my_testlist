# nest笔记十一：typeorm连表查询
- [nestjs系列笔记](https://zdhsoft.blog.csdn.net/article/details/121746302)

- 之前的笔记：[nest记笔五：使用TypeORM连接mysql](https://zdhsoft.blog.csdn.net/article/details/121746239)，与 [nest笔记十：typeorm使用经验小结](https://blog.csdn.net/zdhsoft/article/details/127024360)可以使用typeorm的基本功能。随着开发的深入，很多已经满足不了要求了。

- 写这小结的时候，typeorm已经更新0.3.12了, 与之前0.2.x相比，变化蛮大的。这里的内容也是针对0.3.10及以上的版本。使用0.3.12好像有些bug没有解决。所以还是退回到 0.3.10。

  

## 1. 使用 typeorm-model-generator 生成对已有数据库的实体类
- typeorm可以手动改实体类，然后同步到数据库，这个功能我一直没有用。主要是担心，不小心应用到生产环境，造成数据丢失。
- 我现在的做法是使用工具改好数据库表后，再用typeorm-model-generator生成对应typeorm需要的实体类, 再将生成好的代码文件，替换现有的。
- typeorm-model-generator不能满足我的生成文件的要求，我fork了一个，然后发布了一个修改。参考这个文章[基于typeorm的nestjs项目使用@zdhsoft/tmg将数据库生成数据模型](https://zdhsoft.blog.csdn.net/article/details/126510832)

## 2. 一些特殊类型
### FindOptionsWhere 是用于生成实体类where的选项，
- 使用FindOptionsWhere的几个用处：1、typescript的语法检查，2、代码提示，提示可以有哪些做条件的字段。
- 示例
```typescript
// 一个实体类的定义
@Entity('Account')
export class Account {

    @Column('int', {
        name: 'accountType',
        comment: '账号类型',
    })
    public accountType: number;

    @Column('varchar', {
        name: 'accountId',
        comment: '用户的登陆账号',
        length: 200,
    })
    public accountId: string;
}


// 使用实例
@Injectable()
export class AccountService {
    constructor(@InjectRepository(Account) private accountRepo: Repository<Account>){
        //
    }
    public async found(paramType: number, account: string) {
        // 然后就可以定义where选项了
        const where: FindOptionsWhere<Account> = {
            accountType: paramType,
            accountId: account,
        };
        const accountRec = await this.accountRepo.createQueryBuilder().where(where).getOne();
    }
}

```
### 其它类似的
- DeepPartial<T> 用于新增记录的时候，定义新的记录实例
- FindOptionsSelect<T> 一般情况下，typeorm会返回该条记录的所有字段，其实这是没有必要的。通过它，来设置我们想要的返回字段。其实还有一个FindOptionsSelectByString，但是已经标记为：deprecated
- FindOptionsOrder<T> 排序相关字段

## 3. 事物
- 在0.3.x的版本，事物已经与0.2.x事物大不同了
```typescript
import { utils, XCommonRet, getLogger } from 'xmcommon';

class XTypeormUtils {
    /**
     * 事物
     * @param paramDS TypeORM的数据源
     * @param paramRunInTransaction 执行事物的函数
     * @param paramTransName 事物名称，没有传入空串或null
     */
    public static async transaction<T = unknown>(
        paramDS: DataSource,
        paramRunInTransaction: (paramMgr: EntityManager) => Promise<XCommonRet<T>>,
        paramTransName?: string,
    ): Promise<XCommonRet<T>> {
        let transTag = '';
        if (!utils.isEmpty(paramTransName)) {
            transTag = `[${paramTransName}]`;
        }

        const r = new XCommonRet<T>();

        const queryRunner = paramDS.createQueryRunner();
        log.info(`开始事物:${transTag}`);
        await queryRunner.startTransaction();
        try {
            // 执千事物中的逻辑
            const result = await paramRunInTransaction(queryRunner.manager);
            if (result.isNotOK) {
                log.warn(`事物${transTag}执行失败:${JSON.stringify(result)}`);
                await queryRunner.rollbackTransaction();
            } else {
                await queryRunner.commitTransaction();
            }
            r.assignFrom(result);
        } catch (e) {
            r.setError(-1, `事物异常:${String(e)}`);
            log.warn(`事物${transTag}异常:${JSON.stringify(r)}`);
            await queryRunner.rollbackTransaction();
        }
        await queryRunner.release();
        return r;
    }
}

// 使用例子
// 在app.module中，imports: [TypeOrmModule.forRoot(TypeOrmConfig)后，就可以使用DataSource了
@Injectable()
export class AccountService {
    constructor(@InjectRepository(Account) private accountRepo: Repository<Account>, private dataSource: DataSource){
        //
    }
    public async found(paramType: number, account: string) {
        // 然后就可以定义where选项了
        const where: FindOptionsWhere<Account> = {
            accountType: paramType,
            accountId: account,
        };
        const accountRec = await this.accountRepo.createQueryBuilder().where(where).getOne();
    }
    // 事物使用实现
    public async transSample() {
        const result = XTypeormUtils.transaction<Account[]>(this.dataSource, (paramMgr: EntityManager) => {
            const r = new XCommonRet<Account[]>();
            do {
                const list = await paramMgr.createQueryBuilder(Account).getMany();
                r.setOk(list);
            } while (false);
            return r;
        });
        if (result.isOK) {
            return result.data;
        } else {
            return [];
        }
    }
}


```
## 4. 一个简化处理的工具类
```typescript
import { Like, In, DataSource, EntityManager, EntityTarget, Between, MoreThanOrEqual, LessThanOrEqual } from 'typeorm';
import { utils, XCommonRet, getLogger } from 'xmcommon';
const log = getLogger(__filename);

export class XTypeormUtils {
    /**
     * 简化typeorm的Like方法
     * @param paramValue
     * @returns
     */
    public static like(paramValue?: string) {
        if (utils.isNull(paramValue)) {
            return undefined;
        } else {
            return Like(`%${paramValue}%`);
        }
    }
    /**
     * 简化typeorm的in方法
     * @param paramList
     * @returns
     */
    public static in(paramList: unknown[]) {
        return In(paramList);
    }
    /**
     * 范围
     * @param paramForm 开始值
     * @param paramTo 结束值
     * @returns 返回undefined，则表示没有表达式
     */
    public static scope<T>(paramForm?: T | null, paramTo?: T | null) {
        let v = 0;
        if (utils.isNotNull(paramForm)) {
            v += 1;
        }
        if (utils.isNotNull(paramTo)) {
            v += 2;
        }
        switch (v) {
            case 1:
                return MoreThanOrEqual<T>(paramForm as T);
            case 2:
                return LessThanOrEqual<T>(paramTo as T);
            case 3:
                return Between<T>(paramForm as T, paramTo as T);
            default:
                return undefined;
        }
    }

    /**
     * 简化typeorm的Like方法
     * @param paramValue
     * @returns
     */
    public static like_begin(paramValue?: string) {
        if (utils.isNull(paramValue)) {
            return undefined;
        } else {
            return Like(`${paramValue}%`);
        }
    }
    /**
     * 简化typeorm的Like方法
     * @param paramValue
     * @returns
     */
    public static like_end(paramValue?: string) {
        if (utils.isNull(paramValue)) {
            return undefined;
        } else {
            return Like(`%${paramValue}`);
        }
    }
    /**
     * 删除对象中，属性值为null或undefined的属性
     * @param paramWhere 要处理的对象
     * @returns 处理的对象
     */
    public static cleanNull(paramWhere: any) {
        const delKey: string[] = [];
        for (const k in paramWhere) {
            if (utils.isNull(paramWhere[k])) {
                delKey.push(k);
            }
        }

        for (const k of delKey) {
            delete paramWhere[k];
        }
        return paramWhere;
    }

    /**
     * 处理bigint的参数
     * @param paramValue 要处理的值
     */
    public static bigInt(paramValue?: number): string | undefined {
        if (utils.isNull(paramValue)) {
            return undefined;
        } else {
            return String(paramValue);
        }
    }

    /**
     * 生成查询Builder
     * @param paramMgr EntityManager
     * @param paramEntity EntityTarget<T>
     * @param paramAliasName 别名
     * @returns
     */
    public static builder<T>(
        paramMgr: EntityManager,
        paramEntity: EntityTarget<T>,
        paramAliasName: string = 'a'
    ) {
        return paramMgr.createQueryBuilder<T>(paramEntity, paramAliasName);
    }

    /**
     * 事物
     * @param paramDS TypeORM的数据源
     * @param paramRunInTransaction 执行事物的函数
     * @param paramTransName 事物名称，没有传入空串或null
     */
    public static async transaction<T = unknown>(
        paramDS: DataSource,
        paramRunInTransaction: (paramMgr: EntityManager) => Promise<XCommonRet<T>>,
    ): Promise<XCommonRet<T>>;
    public static async transaction<T = unknown>(
        paramDS: DataSource,
        paramRunInTransaction: (paramMgr: EntityManager) => Promise<XCommonRet<T>>,
        paramTransName: string,
    ): Promise<XCommonRet<T>>;
    public static async transaction<T = unknown>(
        paramDS: DataSource,
        paramRunInTransaction: (paramMgr: EntityManager) => Promise<XCommonRet<T>>,
        paramTransName?: string,
    ): Promise<XCommonRet<T>> {
        let transTag = '';
        if (!utils.isEmpty(paramTransName)) {
            transTag = `[${paramTransName}]`;
        }

        const r = new XCommonRet<T>();

        const queryRunner = paramDS.createQueryRunner();
        log.info(`开始事物:${transTag}`);
        await queryRunner.startTransaction();
        try {
            // 执千事物中的逻辑
            const result = await paramRunInTransaction(queryRunner.manager);
            if (result.isNotOK) {
                log.warn(`事物${transTag}执行失败:${JSON.stringify(result)}`);
                await queryRunner.rollbackTransaction();
            } else {
                await queryRunner.commitTransaction();
            }
            r.assignFrom(result);
        } catch (e) {
            r.setError(-1, `事物异常:${String(e)}`);
            log.warn(`事物${transTag}异常:${JSON.stringify(r)}`);
            await queryRunner.rollbackTransaction();
        }
        await queryRunner.release();
        return r;
    }
}
```
## 5. 其它
### 别名
- 很奇怪typeorm的SQL语句，都会重新命名，结查SQL事句很长，所以我这里都会使用别名, createQueryBuilder的参数可以传入别名， 一般情况下，我传入字终a

### 使用createQueryBuilder不能指定返回字段
- 使用createQueryBuilder查询返回的结果，好像都会返回查询记录的所有字段，很多时间，我仅需要几个字段就可以了。 这个时候可以使用FindOptionsSelect。设置完成后，这个builder一个方法，叫setFindOptions可以用
- 如下代码：
```typescript
    const fields: FindOptionsSelect<Account> = {
        accountType: true
    };
    const list: Account[] = await this.repo.createQueryBuilder('a').setFindOptions({select: fields}).getMany();
    // 这样listt每个记录，只有一个accountType字段
```
- 还有一种情况是，你不管怎么设置，都会返回一些字段，仔细观查后，发现这些字段都是主键。

### 打印耗时
- typeorm初始化的时候，将logging设为true， 就可以打印出SQL语句了。但是每个SQL语句的耗时却没有，这个耗时的功能可以帮我们发现问题SQL，并优化。 其实，只要设置maxQueryExecutionTime的值就可以了，我这里将它设为1，就可以打印出来了。

## 最后，喜欢的话就收藏点个赞，希望对你使用有所帮助
