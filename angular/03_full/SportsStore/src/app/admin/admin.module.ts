import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { AdminComponent } from './admin.component';
import { FormsModule } from '@angular/forms';
import { RouterModule } from '@angular/router';
import { AuthComponent } from './auth.component';
import { AuthGuard } from './auth.guard';
import { OrderTableComponent } from './orderTable.component';
import { ProductEditorComponent } from './productEditor.component';
import { ProductTableComponent } from './productTable.component';

const routing = RouterModule.forChild([
  { path: 'auth', component: AuthComponent },
  {
    path: 'main', component: AdminComponent, canActivate: [AuthGuard],
    children: [
      { path: "products/:mode/:id", component: ProductEditorComponent },
      { path: "products/:mode", component: ProductEditorComponent },
      { path: "products", component: ProductTableComponent },
      { path: "orders", component: OrderTableComponent },
      { path: "**", redirectTo: "products" }
    ]
  },
  { path: '**', redirectTo: 'auth' }
]);
@NgModule({
  declarations: [AdminComponent, AuthComponent, OrderTableComponent, ProductEditorComponent, ProductTableComponent],
  imports: [
    CommonModule,
    FormsModule,
    routing,
  ],
  providers: [AuthGuard],
  exports: [AdminComponent]
})
export class AdminModule { }
