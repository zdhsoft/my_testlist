import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { AdminComponent } from './admin.component';
import { FormsModule } from '@angular/forms';
import { RouterModule } from '@angular/router';
import { AuthComponent } from './auth.component';

const routing = RouterModule.forChild([
  {path: 'auth', component: AuthComponent},
  {path: 'main', component: AdminComponent},
  {path: '**', redirectTo:'auth'}
]);
@NgModule({
  declarations: [AdminComponent, AuthComponent],
  imports: [
    CommonModule,
    FormsModule,
    routing,
  ],
  exports: [AdminComponent]
})
export class AdminModule { }
