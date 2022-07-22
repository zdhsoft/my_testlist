import { NgModule } from '@angular/core';
import { Routes, RouterModule } from '@angular/router';
import { PageNotFoundComponent } from './shared/components';

import { HomeRoutingModule } from './home/home-routing.module';
import { DetailRoutingModule } from './detail/detail-routing.module';
import { LoginRoutingModule } from './pages/login/login-routing.module';
import { DemoRoutingModule } from './pages/demo/heros/demo-routing.module';
import { AdminRoutingModule } from './pages/admin/admin-routing.module';
import { DashboardComponent } from './dashboard/dashboard.component';

const routes: Routes = [
    {
        path: '',
        redirectTo: '/dashboard',
        pathMatch: 'full'
    },
    {
        path: '**',
        component: PageNotFoundComponent
    },
    {
        path: 'dashboard',
        component: DashboardComponent
    }
];

@NgModule({
    imports: [
        RouterModule.forRoot(routes, { relativeLinkResolution: 'legacy' }),
        HomeRoutingModule,
        DetailRoutingModule,
        AdminRoutingModule,
        DemoRoutingModule,
        LoginRoutingModule
    ],
    exports: [RouterModule]
})
export class AppRoutingModule { }
