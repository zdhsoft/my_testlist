import { Injectable } from "@angular/core";
import { ActivatedRouteSnapshot, CanActivate, RouterStateSnapshot, UrlTree } from "@angular/router";
import { Observable } from "rxjs";
import { ProjectConst } from "src/app/common/constant";

@Injectable({providedIn: 'root'})
export class AuthGuardService implements CanActivate {
  constructor() {

  }
  private static unverified() {
    const url = `${ProjectConst.HOME_URL}/simple/login`;
    window.open(url, '_self');

    return false;
  }
  /** 获取路由上的参数 */
  getRouteParams(activatedRoute: ActivatedRouteSnapshot) {
    console.log('auth-guard.service 请求参数', activatedRoute.queryParams);
  }
  canActivate(route: ActivatedRouteSnapshot, state: RouterStateSnapshot): boolean | UrlTree | Observable<boolean | UrlTree> | Promise<boolean | UrlTree> {
    return AuthGuardService.unverified();
    // // this.getRouteParams(route);
    // // const r = AuthGuardService.unverified();
    // // console.log('canActivate:' + JSON.stringify(r));
    // // return r;
  }
}
