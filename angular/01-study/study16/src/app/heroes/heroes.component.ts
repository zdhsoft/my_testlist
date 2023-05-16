import { Component } from '@angular/core';
import { Hero } from './hero';
import { HEROES } from './mock-heroes';
import { HeroService } from '../hero.service';
import { MessageService } from '../message.service';
@Component({
    selector: 'app-heroes',
    templateUrl: './heroes.component.html',
    styleUrls: ['./heroes.component.css']
})
export class HeroesComponent {

    heroes: Hero[] = [];
//    selectedHero?: Hero;

    public constructor(
        private heroService: HeroService,
        private messageService: MessageService
        ) {
        //
    }
    ngOnInit(): void {
        this.getHeroes();
    }
    getHeroes(): void {
        this.heroService.getHeroes().subscribe(
            (paramRet) => {
                this.heroes = paramRet.ret === 0? paramRet.data as Hero[] : [];
            }
        );
    }
    deleteHero(paramId: number): void {
        this.heroService.delHero(paramId).subscribe((ret) => {
            if (ret.ret === 0) {
                this.getHeroes();
            }
        });
    }
    addHero(paramName: string): void {
        this.heroService.addHero(paramName).subscribe((paramRet) => {
            if (paramRet.ret === 0) {
                this.getHeroes();
            }
        });
    }

    // public onSelect(hero: Hero): void {
    //     this.selectedHero = hero;
    //     this.messageService.add(`HeroesComponent: Selected hero id=${hero.id}`);
    // }
}
