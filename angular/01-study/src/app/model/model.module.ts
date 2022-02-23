import {NgModule} from "@angular/core";
import {ProductRepository} from "./product.repository";
import {StaticDataSource} from "./static.datasources";

@NgModule({
  providers: [ProductRepository, StaticDataSource]
})
export class ModelModule{}
