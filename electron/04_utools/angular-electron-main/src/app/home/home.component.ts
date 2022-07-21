import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';
import { EnumRouterPath } from '../routes.path';

@Component({
    selector: 'app-home',
    templateUrl: './home.component.html',
    styleUrls: ['./home.component.scss']
})
export class HomeComponent implements OnInit {
    private home = EnumRouterPath.home;
    private heros = EnumRouterPath.heros;
    private admin = EnumRouterPath.admin;
    private login = EnumRouterPath.login;
    private detail = EnumRouterPath.detail;

    constructor(private router: Router) { }



    ngOnInit(): void {
        console.log('HomeComponent INIT');
    }

}
