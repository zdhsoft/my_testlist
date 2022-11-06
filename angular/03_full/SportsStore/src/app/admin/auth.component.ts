import { Component } from "@angular/core";
import { NgForm } from "@angular/forms";
import { Router } from "@angular/router";
@Component({
    templateUrl: "auth.component.html"
})
export class AuthComponent {
    public username: string = '';
    public password: string = '';
    public errorMessage: string = '';
    constructor(private router: Router) { }
    authenticate(form: NgForm) {
        if (form.valid) {
            // perform authentication
            this.router.navigateByUrl("/admin/main");
        } else {
            this.errorMessage = "Form Data Invalid";
        }
    }
}
