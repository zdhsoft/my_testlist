"use strict";
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var __metadata = (this && this.__metadata) || function (k, v) {
    if (typeof Reflect === "object" && typeof Reflect.metadata === "function") return Reflect.metadata(k, v);
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.Controller = exports.Module = exports.Injectable = void 0;
/* eslint-disable @typescript-eslint/no-explicit-any */
require("reflect-metadata");
var EnumMD;
(function (EnumMD) {
    EnumMD["type"] = "design:type";
    EnumMD["paramTypes"] = "design:paramtypes";
    EnumMD["returnType"] = "design:returntype";
    EnumMD["injectable"] = "__injectable__";
    EnumMD["module"] = "__module__";
    EnumMD["controller"] = "__controller__";
})(EnumMD || (EnumMD = {}));
const serviceList = [];
const controllerList = [];
function classFactory(_constructor) {
    const paramTypes = Reflect.getMetadata(EnumMD.paramTypes, _constructor);
    const OOO = {};
    const _oo = Object.getPrototypeOf(OOO);
    const args = [];
    for (const p of paramTypes) {
        let found = false;
        const _op = p.prototype;
        for (const s of serviceList) {
            const _os = Object.getPrototypeOf(s);
            if (_op === _os) {
                args.push(s);
                found = true;
                break;
            }
        }
        if (!found) {
            if (_oo === _op) {
                console.log("------", p.toString());
                args.push(p);
            }
            else {
                console.log('... not found!');
            }
        }
    }
    const result = new _constructor(...args);
    return result;
}
function Injectable(paramOpts = {}) {
    return (target) => {
        Reflect.defineMetadata(EnumMD.injectable, paramOpts, target);
    };
}
exports.Injectable = Injectable;
function Module(paramOpts) {
    return (target) => {
        Reflect.defineMetadata(EnumMD.module, paramOpts, target);
    };
}
exports.Module = Module;
function Controller(paramPath) {
    return (target) => {
        Reflect.defineMetadata(EnumMD.controller, paramPath, target);
    };
}
exports.Controller = Controller;
let XChatService = class XChatService {
    constructor() {
        //
        console.log('XChatService create');
    }
    getName() {
        return 'name';
    }
};
XChatService = __decorate([
    Injectable(),
    __metadata("design:paramtypes", [])
], XChatService);
let XTestService = class XTestService {
    constructor() {
        //
        console.log('XTestService create');
    }
    getName() {
        return 'hahahahaha';
    }
};
XTestService = __decorate([
    Injectable(),
    __metadata("design:paramtypes", [])
], XTestService);
let XTestController = class XTestController {
    constructor(chatService, testService) {
        this.chatService = chatService;
        this.testService = testService;
        console.log('XTestController:chatService', chatService.getName());
        console.log('XTestController:testService', testService.getName());
    }
};
XTestController = __decorate([
    Controller('/'),
    __metadata("design:paramtypes", [XChatService, XTestService])
], XTestController);
let XKKKController = class XKKKController {
    constructor(chatService) {
        this.chatService = chatService;
        console.log('XKKKController:chatService', chatService.getName());
    }
};
XKKKController = __decorate([
    Controller('/kkk'),
    __metadata("design:paramtypes", [XChatService])
], XKKKController);
let AppModule = class AppModule {
};
AppModule = __decorate([
    Module({
        service: [XChatService, XTestService],
        controller: [XTestController, XKKKController]
    })
], AppModule);
function init(appModule) {
    const v = Reflect.getMetadata(EnumMD.module, appModule);
    console.log(JSON.stringify(v));
    v.service?.forEach((s) => {
        const r = classFactory(s);
        serviceList.push(r);
    });
    v.controller?.forEach((s) => {
        const r = classFactory(s);
        serviceList.push(r);
        const path = Reflect.getMetadata(EnumMD.controller, s);
        console.log('----path:' + path);
    });
}
function main() {
    init(AppModule);
}
main();
//# sourceMappingURL=http.js.map