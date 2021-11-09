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
exports.PedantsTypeController = void 0;
const common_1 = require("@nestjs/common");
let PedantsTypeController = class PedantsTypeController {
    getPedantsType() {
        return '获取所有的挂件类型';
    }
};
__decorate([
    (0, common_1.Get)('test'),
    __metadata("design:type", Function),
    __metadata("design:paramtypes", []),
    __metadata("design:returntype", String)
], PedantsTypeController.prototype, "getPedantsType", null);
PedantsTypeController = __decorate([
    (0, common_1.Controller)('pedants-type')
], PedantsTypeController);
exports.PedantsTypeController = PedantsTypeController;
//# sourceMappingURL=pedants-type.controller.js.map