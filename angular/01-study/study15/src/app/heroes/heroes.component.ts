import { Component } from '@angular/core';
import { Hero } from '../data/hero';

@Component({
  selector: 'app-heroes',
  templateUrl: './heroes.component.html',
  styleUrls: ['./heroes.component.css']
})
export class HeroesComponent {
  hero: Hero = {
    id: 1,
    name: '我是英雄',
    url: 'www.zdhsoft.com'
  }
  constructor() {

  }
}
