import { NgModule } from '@angular/core';
import { StoreComponent } from './store.component';
import {ModelModule} from "../model/model.module";
import {BrowserModule} from "@angular/platform-browser";
import {FormsModule} from "@angular/forms";



@NgModule({
  declarations: [
    StoreComponent
  ],
  imports: [
    ModelModule, BrowserModule, FormsModule
  ],
  exports: [StoreComponent]
})
export class StoreModule { }
