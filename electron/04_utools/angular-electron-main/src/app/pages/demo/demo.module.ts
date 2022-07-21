import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { HerosComponent } from './heros/heros.component';
import { DemoRoutingModule } from './heros/demo-routing.module';



@NgModule({
    declarations: [
        HerosComponent
    ],
    imports: [
        CommonModule, DemoRoutingModule
    ],
    exports: [
        DemoRoutingModule
    ]
})
export class DemoModule { }
