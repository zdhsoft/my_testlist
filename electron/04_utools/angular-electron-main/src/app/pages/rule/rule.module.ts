import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { TextComponent } from './text/text.component';
import { DateComponent } from './date/date.component';
import { MultfileComponent } from './multfile/multfile.component';
import { CurrencyComponent } from './currency/currency.component';
import { CheckboxComponent } from './checkbox/checkbox.component';
import { RadiobuttonComponent } from './radiobutton/radiobutton.component';
import { ComboboxComponent } from './combobox/combobox.component';

@NgModule({
    declarations: [
        TextComponent,
        DateComponent,
        MultfileComponent,
        CurrencyComponent,
        CheckboxComponent,
        RadiobuttonComponent,
        ComboboxComponent
    ],
    imports: [
        CommonModule
    ]
})
export class RuleModule { }
