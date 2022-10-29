import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';

import { AppComponent } from './app.component';
import { ModelComponent } from './model/model.component';
import { AdminComponent } from './admin/admin.component';
import { StoreComponent } from './store/store.component';

@NgModule({
  declarations: [
    AppComponent,
    ModelComponent,
    AdminComponent,
    StoreComponent
  ],
  imports: [
    BrowserModule
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }
