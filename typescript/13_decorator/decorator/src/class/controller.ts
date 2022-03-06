import { Controller, Get, Post } from './global_list';
import { Request, Response } from 'express';

@Controller('/test')
class Test {
    private m_name = 100;
    constructor() {
        console.log('----------------------------->');
    }

    @Get('/hello')
    Hello(req: Request, res: Response) {
        console.log('*************************' + this.m_name);
        return 'hello test!';
    }

    @Get('/test')
    Test() {
        console.log('*************************');
        return 'this is test!!!';
    }
}
