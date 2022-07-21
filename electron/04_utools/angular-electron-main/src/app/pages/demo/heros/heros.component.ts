import { Component, OnInit } from '@angular/core';
import { HEROES, IHero } from '../../../mock';

@Component({
    selector: 'app-heros',
    templateUrl: './heros.component.html',
    styleUrls: ['./heros.component.scss']
})
export class HerosComponent implements OnInit {
    private heros = HEROES;
    private selectedHero?: IHero;


    constructor() { }

    ngOnInit(): void {
    }

    onSelect(hero: IHero): void {
        this.selectedHero = hero;
    }

}
