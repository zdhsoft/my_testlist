import { NgModule } from '@angular/core';
import { Routes, RouterModule } from '@angular/router';
import { HeroesComponent } from './heroes/heroes.component';
import { AuthGuard } from './shared/auth/auth.guard.service';

const routes: Routes = [
  { path: '', pathMatch: 'full', redirectTo: '/welcome' },
  // { path: 'heroes', component: HeroesComponent },
  { path: 'login', loadChildren: () => import('./pages/login/login.module').then(m => m.LoginModule) },
  { path: 'heroes', canActivate: [AuthGuard], loadChildren: () => import('./pages/heroes/heroes.module').then(m => m.HeroesModule) },
  { path: 'home', canActivate: [AuthGuard], loadChildren: () => import('./pages/home/home.module').then(m => m.HomeModule) },
  { path: 'welcome', canActivate: [AuthGuard], loadChildren: () => import('./pages/welcome/welcome.module').then(m => m.WelcomeModule) },
  { path: '**', redirectTo: 'exception/404' },

];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
