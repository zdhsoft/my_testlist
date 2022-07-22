import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { HerosComponent } from './heros/heros.component';
import { DemoRoutingModule } from './heros/demo-routing.module';
import { HeroDetailComponent } from './heros/hero-detail/hero-detail.component';
import { MessagesComponent } from './heros/messages/messages.component';
import { FormsModule, ReactiveFormsModule } from '@angular/forms';



@NgModule({
    declarations: [
        HerosComponent,
        HeroDetailComponent,
        MessagesComponent
    ],
    imports: [
        CommonModule, ReactiveFormsModule, FormsModule, DemoRoutingModule
    ],
    exports: [
        DemoRoutingModule
    ]
})
export class DemoModule { }
