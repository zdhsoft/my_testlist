import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { ButtonComponent } from './button.component';
import {NzButtonModule} from "ng-zorro-antd/button";
import {FormsModule} from "@angular/forms";
import {NzRadioModule} from "ng-zorro-antd/radio";
import {
  StepBackwardOutline,
  CaretLeftOutline,
  SettingOutline,
  DownloadOutline,
  UserOutline,
  LockOutline,
} from '@ant-design/icons-angular/icons';
import {NzIconModule} from "ng-zorro-antd/icon";
import {IconDefinition} from "@ant-design/icons-angular";

const icons: IconDefinition[] = [
  StepBackwardOutline,
  CaretLeftOutline,
  SettingOutline,
  UserOutline,
  LockOutline,
  DownloadOutline
];
@NgModule({
  declarations: [
    ButtonComponent
  ],
  exports: [
    ButtonComponent
  ],
  imports: [
    CommonModule,
    NzButtonModule,
    FormsModule,
    NzIconModule.forChild(icons),
    NzRadioModule
  ]
})
export class ButtonModule { }
