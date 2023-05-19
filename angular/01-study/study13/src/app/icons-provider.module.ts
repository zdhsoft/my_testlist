import { NgModule } from '@angular/core';
import { NZ_ICONS, NzIconModule } from 'ng-zorro-antd/icon';
// import * as AllIcons from '@ant-design/icons-angular/icons'
import { IconDefinition } from '@ant-design/icons-angular';


import {
  MenuFoldOutline,
  MenuUnfoldOutline,
  FormOutline,
  DashboardOutline,
  LockOutline,
  CopyOutline,
} from '@ant-design/icons-angular/icons';

// const antDesignIcons = AllIcons as {
//   [key: string]: IconDefinition;
// };
// const icons: IconDefinition[] = Object.keys(antDesignIcons).map(key => antDesignIcons[key])

const icons = [MenuFoldOutline, MenuUnfoldOutline, DashboardOutline, FormOutline, LockOutline, CopyOutline];

@NgModule({
  imports: [NzIconModule.forRoot(icons)],
  exports: [NzIconModule],
  providers: [
    { provide: NZ_ICONS, useValue: icons }
  ]
})
export class IconsProviderModule {
}
