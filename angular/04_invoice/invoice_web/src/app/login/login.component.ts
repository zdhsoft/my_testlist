import { Component } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import {map} from "rxjs";

interface LoginResponse {
  success: boolean;
  token: string;
}

@Component({
  selector: 'app-login',
  templateUrl: './login.component.html',
  styleUrls: ['./login.component.css']
})
export class LoginComponent {
  public username: string;
  public password: string;

  constructor(private http: HttpClient) {
    this.username = '';
    this.password = '';
  }

  login() {
    const url = 'https://example.com/login'; // 替换成实际的登录接口地址
    const data = { username: this.username, password: this.password };
    const s = this.http.post(url, data).pipe(map(response => response as LoginResponse));
    s.subscribe()


    //   .subscribe(response => {
    //   console.log(response); // 处理登录成功的响应
    // }, error => {
    //   console.error(error); // 处理登录失败的响应
    // });
  }
}
