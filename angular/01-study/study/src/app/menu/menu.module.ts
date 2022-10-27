import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { MenuComponent } from './menu.component';

import { NzMenuModule } from 'ng-zorro-antd/menu';

import {
  StepBackwardOutline,
  CaretLeftOutline,
  SettingOutline,
  DownloadOutline,
  UserOutline,
  LockOutline,
  MailOutline,
  AppstoreOutline,
} from '@ant-design/icons-angular/icons';
import {NzIconModule} from "ng-zorro-antd/icon";
import {IconDefinition} from "@ant-design/icons-angular";

const icons: IconDefinition[] = [
  StepBackwardOutline,
  CaretLeftOutline,
  SettingOutline,
  UserOutline,
  LockOutline,
  MailOutline,
  AppstoreOutline,
  DownloadOutline
];
@NgModule({
  declarations: [
    MenuComponent
  ],
  exports: [
    MenuComponent
  ],
  imports: [
    CommonModule,
    NzMenuModule,
    NzIconModule,
    NzIconModule.forChild(icons),
  ]
})
export class MenuModule { }
