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
function Injectable(paramOpts = {}) {
    return (target) => {
        Reflect.defineMetadata(EnumMD.injectable, paramOpts, target);
        Reflect.defineMetadata(EnumMD.type, target, target);
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
};
XTestService = __decorate([
    Injectable(),
    __metadata("design:paramtypes", [])
], XTestService);
let XTestController = class XTestController {
    constructor(chatService, testService) {
        this.chatService = chatService;
        this.testService = testService;
        //
    }
};
XTestController = __decorate([
    Controller('/'),
    __metadata("design:paramtypes", [XChatService, XTestService])
], XTestController);
let AppModule = class AppModule {
};
AppModule = __decorate([
    Module({
        service: [XChatService, XTestService],
        controller: [XTestController]
    })
], AppModule);
function init(appModule) {
    const v = Reflect.getMetadata(EnumMD.module, appModule);
    console.log(JSON.stringify(v));
    v.service?.forEach((s) => {
        const opts = Reflect.getMetadata(EnumMD.injectable, s);
        const type = Reflect.getMetadata(EnumMD.type, s);
        // const param = Reflect.getMetadata(EnumMD.paramTypes, s);
        // const ret = Reflect.getMetadata(EnumMD.returnType, s);
        if (typeof type === 'function') {
            const serviceObj = new type();
            Object.setPrototypeOf(serviceObj, type);
            serviceList.push(serviceObj);
        }
        console.log('service:****', JSON.stringify(opts));
    });
    v.controller?.forEach((s) => {
        const i = Reflect.getMetadata(EnumMD.controller, s);
        const m = Reflect.getMetadata(EnumMD.paramTypes, s);
        const type = Reflect.metadata(EnumMD.type, s);
        const params = [];
        m.forEach((p) => {
            let found = false;
            for (const pp of serviceList) {
                const ppp = Object.getPrototypeOf(pp);
                if (p === ppp) {
                    found = true;
                    params.push(pp);
                    break;
                }
            }
            if (!found) {
                params.push(null);
            }
        });
        const c = new type(...params);
        controllerList.push(c);
        console.log('controller:****', JSON.stringify(i), JSON.stringify(m));
    });
}
function main() {
    init(AppModule);
}
main();
//# sourceMappingURL=http.js.map