import { Controller, Get, Post } from './global_list';
import { Request, Response } from 'express';

@Controller('/test')
class Test {
    constructor() {
        console.log('----------------------------->');
    }

    @Get('/hello')
    Hello(req: Request, res: Response) {
        console.log('*************************');
        return 'hello test!';
    }

    @Get('/test')
    Test() {
        console.log('*************************');
        return 'this is test!!!';
    }
}
