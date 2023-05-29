import { Component, OnInit } from '@angular/core';
import { XCommRet } from '@zdhsoft/commret';
@Component({
  selector: 'app-welcome',
  templateUrl: './welcome.component.html',
  styleUrls: ['./welcome.component.css']
})
export class WelcomeComponent implements OnInit {

  constructor() {
    const r = new XCommRet<number>();
    r.setError(-100);
    console.log(r);
  }

  ngOnInit() {
    //
  }

}
