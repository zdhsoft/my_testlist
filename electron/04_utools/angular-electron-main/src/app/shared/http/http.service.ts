import { Injectable } from '@angular/core';
import { HttpHeaders, HttpClient } from '@angular/common/http';
import { Observable } from 'rxjs';
@Injectable({
    providedIn: 'root'
})
export interface IHeaderParam {
    key: string;
    value: string;
}
export class HttpService {

    private constructor() { }
}
