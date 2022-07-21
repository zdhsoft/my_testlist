import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';
import { FormsModule } from '@angular/forms';
import { HttpClientModule, HttpClient } from '@angular/common/http';
import { CoreModule } from './core/core.module';
import { SharedModule } from './shared/shared.module';

import { AppRoutingModule } from './app-routing.module';

// NG Translate
import { TranslateModule, TranslateLoader } from '@ngx-translate/core';
import { TranslateHttpLoader } from '@ngx-translate/http-loader';

import { HomeModule } from './home/home.module';
import { DetailModule } from './detail/detail.module';
import { LoginModule } from './pages/login/login.module';
import { AdminModule } from './pages/admin/admin.module';
import { RuleModule } from './pages/rule/rule.module';

import { AppComponent } from './app.component';
import { APP_CONFIG } from '../environments/environment';

// import { AdminComponent } from './pages/admin/admin.component';
// import { LoginComponent } from './pages/login/login.component';

// AoT requires an exported function for factories
const httpLoaderFactory = (http: HttpClient): TranslateHttpLoader => new TranslateHttpLoader(http, './assets/i18n/', '.json');

@NgModule({
    declarations: [AppComponent],
    imports: [
        BrowserModule,
        FormsModule,
        HttpClientModule,
        CoreModule,
        SharedModule,
        HomeModule,
        DetailModule,
        LoginModule,
        AdminModule,
        AppRoutingModule,
        RuleModule,
        TranslateModule.forRoot({
            loader: {
                provide: TranslateLoader,
                useFactory: httpLoaderFactory,
                deps: [HttpClient]
            }
        })
    ],
    providers: [{ provide: 'APP_CONFIG', useValue: APP_CONFIG }],
    bootstrap: [AppComponent]
})
export class AppModule { }
