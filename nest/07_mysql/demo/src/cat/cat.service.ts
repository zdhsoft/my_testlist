import { Injectable } from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { Repository } from 'typeorm';
import { Cat } from '../orm/entity/Cat';

@Injectable()
export class CatService {
    constructor(
        @InjectRepository(Cat) private readonly catRepository: Repository<Cat>,
    ) {}

    findAll(): Promise<Cat[]> {
        return this.catRepository.find();
    }

    findOne(id: number): Promise<Cat> {
        return this.catRepository.findOne(id);
    }

    async remove(id: number): Promise<void> {
        await this.catRepository.delete(id);
    }

    async create(cats: Cat): Promise<void> {
        await this.catRepository.save(cats);
    }
}
