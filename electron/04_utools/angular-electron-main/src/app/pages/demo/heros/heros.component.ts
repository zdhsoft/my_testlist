import { Component, OnInit } from '@angular/core';
import { IHero } from '../../../mock';
import { HerosService } from './heros.service';
import { MessagesService } from './messages.service';


@Component({
    selector: 'app-heros',
    templateUrl: './heros.component.html',
    styleUrls: ['./heros.component.scss']
})
export class HerosComponent implements OnInit {
    private heros: IHero[] = [];
    private selectedHero?: IHero;


    constructor(private heroService: HerosService, private msgService: MessagesService) { }

    ngOnInit(): void {
        this.getHeros();
    }

    onSelect(hero: IHero): void {
        this.selectedHero = hero;
        this.msgService.add(`HeroesComponent: Selected hero id=${hero.id}`);
    }

    getHeros(): void  {
        this.heroService.getHeros()
        .subscribe(list => this.heros = list);
    }
}
