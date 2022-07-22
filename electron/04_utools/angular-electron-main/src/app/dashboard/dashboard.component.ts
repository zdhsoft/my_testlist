import { Component, OnInit } from '@angular/core';
import { IHero } from '../mock';
import { HerosService } from '../pages/demo/heros/heros.service';


@Component({
    selector: 'app-dashboard',
    templateUrl: './dashboard.component.html',
    styleUrls: ['./dashboard.component.scss']
})
export class DashboardComponent implements OnInit {
    private heroes: IHero[] = [];
    constructor(private heroService: HerosService) { }

    ngOnInit(): void {

    }

    public getHeroes() {
        this.heroService.getHeros().subscribe(list => this.heroes = list.slice(1,5));
    }

}
