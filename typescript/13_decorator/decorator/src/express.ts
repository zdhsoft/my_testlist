import express, { Request, Response } from 'express';
import register from './class/register';
import './class/controller';
const app = express();
app.get('/', (req: Request, res: Response) => {
    res.send('hello world');
});

register('/', app);

const server = app.listen(8080, () => {
    console.log(`web 服务 => localhost: 8080`);
});
