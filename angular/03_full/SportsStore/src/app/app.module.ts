import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';

import { AppComponent } from './app.component';
import { StoreModule } from './store/store.module';
import { ModelModule } from './model/model.module';
import { AdminModule } from './admin/admin.module';


@NgModule({
  declarations: [
    AppComponent,
  ],
  imports: [
    BrowserModule, StoreModule, ModelModule, AdminModule
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }
