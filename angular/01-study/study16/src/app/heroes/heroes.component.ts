import { Component } from '@angular/core';
import { Hero } from './hero';
import { HEROES } from './mock-heroes';
@Component({
  selector: 'app-heroes',
  templateUrl: './heroes.component.html',
  styleUrls: ['./heroes.component.css']
})
export class HeroesComponent {
    hero: Hero = {
        name: '刘德华 andy',
        id: 1,
    }
    heroes = HEROES;
    selectedHero?: Hero;
    public onSelect(hero: Hero): void {
        this.selectedHero = hero;
    }
}
