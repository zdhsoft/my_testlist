import { NgModule } from "@angular/core"; //angular模心模块
import { BrowserModule } from "@angular/platform-browser"; // 浏览器解析的模板
import { AppComponent } from "./app.component";
import { StoreModule } from "./store/store.module"; // 根组件
import { StoreComponent } from "./store/store.component";
import { CheckoutComponent } from "./store/checkout.component";
import { CartDetailComponent } from "./store/cartDetail.component";
import { RouterModule } from "@angular/router";
import { StoreFirstGuard } from "./storeFirst.guard";
// 默认的module
@NgModule({ //NgModule装饰器 接受一个元数据对象，告诉angular如何编译和启动应用
    imports: [ // 配置当前模块运行依赖的其它模块
        BrowserModule,
        StoreModule, // 商城模块
        RouterModule.forRoot([ // 路由模块
            {
                path: "store", component: StoreComponent,
                canActivate: [StoreFirstGuard]
            },
            {
                path: "cart", component: CartDetailComponent,
                canActivate: [StoreFirstGuard]
            },
            {
                path: "checkout", component: CheckoutComponent,
                canActivate: [StoreFirstGuard]
            },
            {
                path: "admin",
                loadChildren: () => import("./admin/admin.module")
                    .then(m => m.AdminModule),
                canActivate: [StoreFirstGuard]
            },
            { path: "**", redirectTo: "/store" }
        ])],
    providers: [StoreFirstGuard], // 配置项目所需要的服务
    declarations: [AppComponent],// 配置当前项目运行的组件
    bootstrap: [AppComponent] // 指定应用的主视图（称为根组件）通过引导appModule来启动应用，这里一般写的是根组件
})
export class AppModule { }
