import { ChangeDetectorRef, Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';
import { NzMessageService } from 'ng-zorro-antd/message';

@Component({
  selector: 'app-login',
  templateUrl: './login.component.html',
  styleUrls: ['./login.component.css']
})
export class LoginComponent implements OnInit {

  account = '';
  userAgent: any = null;
  password = ''; // 是否显示密码框
  style: any = {};
  loading = false;
  //footer = FOOTER;

  get isWebKit() {
    return this.userAgent.indexOf('applewebkit/') > 0 ? 'on' : 'off';
  }

  constructor(
    private cdr: ChangeDetectorRef,
    private router: Router,
    private msg: NzMessageService,
    //private userInfoService: UserInfoService
  ) {}

  onLogin(): void {
    if (this.loading) {
      return;
    }

    const account = this.account.trim();
    let password = this.password.trim();

    if (!account) {
      this.msg.error('请输入登录账号');
      return;
    }
    if (!password) {
      this.msg.error('请输入登录密码');
      return;
    }

    this.loading = true;
    // this.userInfoService.login({ account, password }).subscribe({
    //   next: (res) => {
    //     this.loading = false;
    //     this.router.navigate(['/']);
    //   },
    //   error: ({ msg }) => {
    //     this.msg.error(msg);
    //     this.loading = false;
    //     this.cdr.markForCheck();
    //   },
    // });
  }

  onKeyUp() {
    this.account = this.account.replace(/\W/g, '');
  }

  ngOnInit(): void {
    this.userAgent = navigator.userAgent.toLowerCase();
    // if (this.xn.user.isLogined()) {
    //   this.xn.user.redirectWhenLogin();
    //   return;
    // }

    // if (this.xn.user.hasCookie()) {
    //   this.xn.user.authRaw().subscribe(json => {
    //     if (json.ret === 0) {
    //       this.xn.user.redirectWhenLogin();
    //     }
    //   });
    // }
  }


}
