import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { ProductRepository } from "./product.repository";
import { StaticDataSource } from "./static.datasource";
import { Cart } from "./cart.model";
import { Order } from './order.model';
import { OrderRepository } from './order.repository';
import { HttpClientModule } from "@angular/common/http";
import { RestDataSource } from './rest.datasource';
@NgModule({
  declarations: [],
  imports: [
    CommonModule,
    HttpClientModule
  ],
  providers: [ProductRepository, StaticDataSource, Cart, Order, OrderRepository,
    { provide: StaticDataSource, useClass: RestDataSource }
  ],
})
export class ModelModule { }
