import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';

import { AppComponent } from './app.component';
import { NZ_I18N, zh_CN } from 'ng-zorro-antd/i18n';
import { registerLocaleData } from '@angular/common';
import zh from '@angular/common/locales/zh';
import { FormsModule } from '@angular/forms';
import { HttpClientModule } from '@angular/common/http';
import { BrowserAnimationsModule } from '@angular/platform-browser/animations';
import { NzIconService, NZ_ICONS } from 'ng-zorro-antd/icon';
import * as AllIcons from '@ant-design/icons-angular/icons';
import { IconDefinition } from '@ant-design/icons-angular';

registerLocaleData(zh);
const antDesignIcons = AllIcons as {
    [key: string]: IconDefinition;
};
const icons = Object.keys(antDesignIcons).map((key) => antDesignIcons[key]);

@NgModule({
  declarations: [
    AppComponent
  ],
  imports: [
    BrowserModule,
    FormsModule,
    HttpClientModule,
    BrowserAnimationsModule
  ],
  providers: [
    { provide: NZ_I18N, useValue: zh_CN },
    { provide: NZ_ICONS, useValue: icons },
  ],
  bootstrap: [AppComponent]
})
export class AppModule {
    constructor(private iconService: NzIconService) {
        this.iconService.fetchFromIconfont({
            scriptUrl: 'assets/iconfont/iconfont.js'
        })
    }
}
