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
require("reflect-metadata");
let k = class k {
    hello() {
        return 'hello world';
    }
};
__decorate([
    Reflect.metadata('inMethod', 'B'),
    __metadata("design:type", Function),
    __metadata("design:paramtypes", []),
    __metadata("design:returntype", String)
], k.prototype, "hello", null);
k = __decorate([
    Reflect.metadata('aaa', 'bbb')
], k);
console.log(Reflect.getMetadata('aaa', k)); // 'A'
console.log(Reflect.getMetadata('inMethod', new k(), 'hello')); // 'B'
let A = class A {
    hello() {
        //
    }
};
__decorate([
    Reflect.metadata('name', 'hello'),
    __metadata("design:type", Function),
    __metadata("design:paramtypes", []),
    __metadata("design:returntype", void 0)
], A.prototype, "hello", null);
A = __decorate([
    Reflect.metadata('name', 'A')
], A);
const objs = [A, new A, A.prototype];
const res = objs.map(obj => [
    Reflect.getMetadata('name', obj),
    Reflect.getMetadata('name', obj, 'hello'),
    Reflect.getOwnMetadata('name', obj),
    Reflect.getOwnMetadata('name', obj, 'hello')
]);
console.log(res);
