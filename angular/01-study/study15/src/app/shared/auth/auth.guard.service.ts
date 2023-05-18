import { Injectable, inject } from "@angular/core";
import { Router, ActivatedRouteSnapshot, RouterStateSnapshot, CanActivateFn } from "@angular/router";

Injectable({
  providedIn: 'root'
})
class AuthenticationService {

  constructor(private router: Router) {}

  canActivate(next: ActivatedRouteSnapshot, state: RouterStateSnapshot): boolean {
      //your logic goes here
      return true;
  }
}

export const AuthGuard: CanActivateFn = (route: ActivatedRouteSnapshot, state: RouterStateSnapshot): boolean => {
  // // return inject(PermissionsService).canActivate(next, state);

  // const authService = inject(AuthenticationService);
  // const router = inject(Router);

  // return authService.checkLogin().pipe(
  //   map(() => true),
  //   catchError(() => {
  //     router.navigate(['route-to-fallback-page']);
  //     return of(false);
  //   })
  // );
}
