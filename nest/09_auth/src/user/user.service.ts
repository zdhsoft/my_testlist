import { Injectable } from '@nestjs/common';
import { User } from 'src/entity/User';
import { Repository } from 'typeorm';

@Injectable()
export class UserService {
    constructor(private userRepo: Repository<User>) {}
    public async findOne(paramName: string) {
        return this.userRepo.findOne({ name: paramName });
    }
}
