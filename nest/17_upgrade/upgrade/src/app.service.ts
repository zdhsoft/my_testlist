import { Injectable } from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { MockEnv, WhereMockEnv } from './db/mock_env';
import { Repository } from 'typeorm';

@Injectable()
export class XAppService {
    public constructor(@InjectRepository(MockEnv) private m_MockRepo: Repository<MockEnv>) {}
    async getHello() {
        const w: WhereMockEnv = {
            id: 1,
        };
        const recList = await this.m_MockRepo.find({ where: w });
        if (recList.length > 0) {
            return recList[0].env;
        } else {
            return '没有找到记录';
        }
    }
}
