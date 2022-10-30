import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { ProductRepository } from "./product.repository";
import { StaticDataSource } from "./static.datasource";


@NgModule({
  declarations: [],
  imports: [
    CommonModule
  ],
  providers: [ProductRepository, StaticDataSource],
})
export class ModelModule { }
