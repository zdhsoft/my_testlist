import { Injectable } from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { Heroes, WhereHeroes } from '../db/heroes';
import { Repository } from 'typeorm';
import { getLogger } from 'xmcommon';
import { XTypeormUtils } from '../common/typeorm_utils';
const log = getLogger(__filename);

@Injectable()
export class XApiService {
    public constructor(@InjectRepository(Heroes) private m_HeroesRepo: Repository<Heroes>) {}

    public async getHeros() {
        return this.m_HeroesRepo.find();
    }

    public async getHero(paramId: number) {
        return this.m_HeroesRepo.findOne({ where: { id: paramId } });
    }

    public async delHero(paramId: number) {
        return this.m_HeroesRepo.delete({ id: paramId });
    }

    public async addHero(paramName: string) {
        const result = await this.m_HeroesRepo.insert({ name: paramName });
        log.info('--->add hero:' + JSON.stringify(result, null, 2));
        return result.identifiers[0].id as number;
    }

    public async updateHero(paramId: number, paramNewName: string) {
        const result = await this.m_HeroesRepo.update({ id: paramId }, { name: paramNewName });
        log.info('--->update hero:' + JSON.stringify(result, null, 2));
        return result.affected;
    }

    public async searchHero(paramName: string) {
        const w: WhereHeroes = {
            name: XTypeormUtils.like(paramName),
        };
        return this.m_HeroesRepo.find({ where: w });
    }
}
