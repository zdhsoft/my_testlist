import { NgModule } from '@angular/core';
import { Routes, RouterModule } from '@angular/router';
import { AuthGuardService } from './shared/auth/auth.guard.service';
import { LoginComponent } from './simple/login/login.component';
import { WelcomeComponent } from './simple/welcome/welcome.component';


// const routes: Routes = [
//   {
//     path: 'user',
//     children: [
//       {
//         path: 'login',
//         data: { name: '' },
//         loadChildren: () =>
//           import('./pages/login/login.module').then((m) => m.LoginModule),
//       },
//     ],
//   },
//   {
//       path: 'welcome',
//       canActivate: [AuthGuardService],
//       canActivateChild: [AuthGuardService],
//       loadChildren: () => import('./pages/welcome/welcome.module').then(m => m.WelcomeModule)
//   },
//   {
//       path: '',
//       pathMatch: 'full',
//       redirectTo: '/welcome'
//   },
// ];

// const routes: Routes = [
//   {
//       path: 'welcome',
//       component: LoginComponent,
//       loadChildren: () => import('./pages/welcome/welcome.module').then(m => m.WelcomeModule)
//   },
//   {
//     path: 'user',
//     children: [
//       {
//         path: 'login',
//         data: { name: '' },
//         loadChildren: () =>
//           import('./pages/login/login.module').then((m) => m.LoginModule),
//       },
//     ],
//   },
//   {
//       path: '',
//       pathMatch: 'full',
//       redirectTo: '/user/login'
//   },
// ];

const routes: Routes = [
    {
      path: 'simple',
      children: [
        {
          path: 'login',
          component: LoginComponent,
        },
        {
          path: 'welcome',
          canActivate: [AuthGuardService],
          canActivateChild: [AuthGuardService],
          component: WelcomeComponent,
        }
      ]
    },
    {
      path: '',
      pathMatch: 'full',
      redirectTo: '/simple/welcome'
    },
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
