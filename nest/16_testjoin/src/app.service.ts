import { Injectable } from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { DataSource, Repository } from 'typeorm';
import { Account, SelectAccount } from './db/account';
import { App, SelectApp } from './db/app';
import { User } from './db/user';

@Injectable()
export class XAppService {
    getHello(): string {
        return 'Hello World!';
    }

    public async t() {
        const r = await this.accountRepo
            .createQueryBuilder('a')
            .leftJoinAndSelect('a.app', 'app')
            .where({ appId: 'platform' })
            .getOne();
        return r;
    }

    public async t2() {
        // 要置要返回的字段
        const k: SelectApp = {
            appName: true,
            status: true,
            orgAddress: true,
        };
        const a: SelectAccount = {
            accountId: true,
            appId: true,
            app: k, // 目前测试这个字段不生效
        };
        const r = await this.accountRepo
            .createQueryBuilder('a')
            .setFindOptions({ select: a })
            .leftJoinAndSelect('a.app', 'b')
            .where({ appId: 'platform' })
            .getOne();
        return r;
    }
    public async t3() {
        // 要置要返回的字段
        const k: SelectApp = {
            appName: true,
            status: true,
            orgAddress: true,
        };
        const a: SelectAccount = {
            accountId: true,
            appId: true,
            app: k, // 目前测试这个字段不生效
        };
        const r = await this.accountRepo
            .createQueryBuilder('a')
            // .setFindOptions({ select: a })
            .leftJoin('a.app', 'b')
            .select('appName, status, orgAddress, app')
            .where({ appId: 'platform' })
            .getOne();
        return r;
    }

    public async getUserList() {
        const r1 = await this.dataSource.query(
            "select c.accountId, a.appId, a.appName, c.accountType from App as a left join Account as c on(a.appId = c.appId) where a.appId = 'platform'",
        );

        // const r = this.dataSource.createQueryRunner();
        const r2 = '';

        // const r2 = await this.accountRepo
        //     .createQueryBuilder('a')
        //     .leftJoinAndSelect(App, 'b', 'a.appId = b.appId')
        //     .skip(20)
        //     .take(10)
        //     .select(['a.appId as appId, b.appName as appName'])
        //     .getRawAndEntities<App>();

        return { r1, r2 };
    }
    constructor(
        @InjectRepository(Account) private accountRepo: Repository<Account>,
        @InjectRepository(App) private appRepo: Repository<App>,
        @InjectRepository(User) private userRepo: Repository<User>,
        private dataSource: DataSource,
    ) {
        //
    }
}
