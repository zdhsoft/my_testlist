import { controllerList, routeList, paramList, parseList } from './global_list';
import { Express, Router } from 'express';
import { handlerFactory } from './ut';

function register(rootPath: string, app: Express) {
    const router = Router();

    controllerList.forEach((controller) => {
        const { path: basePath, target: cTarget } = controller;

        const f = routeList.filter(({ target, loaded }) => !loaded && target === (cTarget as any).prototype);
        f.forEach((route) => {
            route.loaded = true;
            const { name: funcName, type, path, func, target } = route;
            const handler = handlerFactory(
                target,
                funcName as string,
                func,
                paramList.filter((param) => param.name === funcName),
                parseList.filter((parse) => parse.name === funcName),
            );

            router[type](basePath + path, handler);
        });
    });
    app.use(rootPath, router);
}

export default register;
