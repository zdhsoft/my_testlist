import { Component, OnInit, Input } from '@angular/core';
import { IHero } from '../../../../mock';

@Component({
    selector: 'app-hero-detail',
    templateUrl: './hero-detail.component.html',
    styleUrls: ['./hero-detail.component.scss']
})
export class HeroDetailComponent implements OnInit {

    @Input() hero?: IHero;
    constructor() { }

    ngOnInit(): void {
    }

}
