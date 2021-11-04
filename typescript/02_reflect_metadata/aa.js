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
exports.HTTP_CODE_METADATA = void 0;
require("reflect-metadata");
exports.HTTP_CODE_METADATA = '__httpCode__';
function HttpCode(statusCode) {
    return (target, key, descriptor) => {
        Reflect.defineMetadata(exports.HTTP_CODE_METADATA, statusCode, descriptor.value);
        return descriptor;
    };
}
class aaa {
    callWithClientUseFactory() {
        return 100;
    }
    static mmm() {
        return 999;
    }
}
__decorate([
    HttpCode(200),
    __metadata("design:type", Function),
    __metadata("design:paramtypes", []),
    __metadata("design:returntype", Number)
], aaa.prototype, "callWithClientUseFactory", null);
__decorate([
    HttpCode(345),
    __metadata("design:type", Function),
    __metadata("design:paramtypes", []),
    __metadata("design:returntype", Number)
], aaa, "mmm", null);
const b = new aaa();
const code = Reflect.getMetadata(exports.HTTP_CODE_METADATA, b.callWithClientUseFactory);
console.log(code);
const ccc = Reflect.getMetadata(exports.HTTP_CODE_METADATA, aaa.mmm);
console.log(ccc);
b.callWithClientUseFactory();
//# sourceMappingURL=aa.js.map