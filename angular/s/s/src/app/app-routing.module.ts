
import { NgModule } from '@angular/core';
import { Routes, RouterModule, PreloadAllModules } from '@angular/router';

// import { AuthGuardService } from './shared/auth';
// import { BasicLayoutComponent } from './layout/basic-layout/basic-layout.component';
// import { UserLayoutComponent } from './layout/user-layout/user-layout.component';

const routes: Routes = [
//   {
//     path: '',
//     component: BasicLayoutComponent,
//     canActivate: [AuthGuardService],
//     canActivateChild: [AuthGuardService],
//     children: [
//       // { path: '', redirectTo: 'home', pathMatch: 'full' },
//       {
//         path: 'home',
//         data: { name: '首页' },
//         loadChildren: () =>
//           import('./pages/home/home.module').then((m) => m.HomeModule),
//       },
//       {
//         path: 'invoice-manage',
//         data: { name: '发票查验管理' },
//         loadChildren: () =>
//           import('./pages/invoice-manage/invoice-manage.module').then(
//             (m) => m.InvoiceManageModule
//           ),
//       },
//       {
//         path: 'input-invoices',
//         data: { name: '进项发票管理' },
//         loadChildren: () =>
//           import('./pages/input-invoices/input-invoices.module').then(
//             (m) => m.InputInvoicesModule
//           ),
//       },
//       {
//         path: 'output-invoices',
//         data: { name: '销项发票管理' },
//         loadChildren: () =>
//           import('./pages/output-invoices/output-invoices.module').then(
//             (m) => m.OutputInvoicesModule
//           ),
//       },
//       {
//         path: 'statistics',
//         data: { name: '' },
//         loadChildren: () =>
//           import('./pages/statistics/statistics.module').then(
//             (m) => m.StatisticsManageModule
//           ),
//       },
//       {
//         path: 'organization-manage',
//         data: { name: '机构管理' },
//         loadChildren: () =>
//           import('./pages/organization-manage/organization-manage.module').then(
//             (m) => m.OrganizationManageModule
//           ),
//       },
//       {
//         path: 'user-manage',
//         data: { name: '用户管理' },
//         loadChildren: () =>
//           import('./pages/user-manage/user-manage.module').then(
//             (m) => m.UserManageModule
//           ),
//       },
//     ],
//   },
//   {
//     path: 'dashboard',
//     component: UserLayoutComponent,
//     canActivate: [AuthGuardService],
//     canActivateChild: [AuthGuardService],
//     children: [
//       {
//         path: 'index',
//         data: { name: '' },
//         loadChildren: () =>
//           import('./pages/dashboard/dashboard.module').then((m) => m.DashboardModule),
//       },
//     ],
//   },
//   {
//     path: 'user',
//     component: UserLayoutComponent,
//     children: [
//       {
//         path: 'login',
//         data: { name: '' },
//         loadChildren: () =>
//           import('./pages/login/login.module').then((m) => m.LoginModule),
//       },
//     ],
//   },
  { path: '**', redirectTo: 'exception/404' },
];

@NgModule({
  imports: [
    RouterModule.forRoot(routes, {
      enableTracing: false,
      scrollPositionRestoration: 'enabled',
      onSameUrlNavigation: 'reload',
      preloadingStrategy: PreloadAllModules,
    }),
  ],
  exports: [RouterModule],
})
export class AppRoutingModule {}
