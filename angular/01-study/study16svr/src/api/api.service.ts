import { Injectable } from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { Heroes } from '../db/heroes';
import { Repository } from 'typeorm';

@Injectable()
export class XApiService {
    public constructor(@InjectRepository(Heroes) private m_HeroesRepo: Repository<Heroes>) {}

    public async getHeros() {
        return this.m_HeroesRepo.find();
    }

    public async getHero(paramId: number) {
        return this.m_HeroesRepo.findOne({ where: { id: paramId } });
    }
}
