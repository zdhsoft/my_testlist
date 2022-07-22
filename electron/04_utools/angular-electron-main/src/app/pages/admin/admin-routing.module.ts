import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { Routes, RouterModule } from '@angular/router';
import { AdminComponent } from './admin.component';
import { EnumRouterPath } from '../../routes.path';

const routes: Routes = [
    {
        path: EnumRouterPath.admin,
        component: AdminComponent
    }
];

@NgModule({
    declarations: [AdminComponent],
    imports: [CommonModule, RouterModule.forChild(routes)],
    exports: [RouterModule]
})
export class AdminRoutingModule { }
