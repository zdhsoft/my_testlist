import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { Routes, RouterModule } from '@angular/router';
import { HerosComponent } from './heros.component';
import { EnumRouterPath } from '../../../routes.path';

const routes: Routes = [
    {
        path: EnumRouterPath.heros,
        component: HerosComponent
    }
];

@NgModule({
    declarations: [],
    imports: [CommonModule, RouterModule.forChild(routes)],
    exports: [RouterModule]
})
export class DemoRoutingModule { }
