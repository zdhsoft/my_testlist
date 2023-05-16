import { Component, Input } from '@angular/core';
import { Hero } from '../heroes/hero';
import { ActivatedRoute } from '@angular/router';
import { Location } from '@angular/common';
import { HeroService } from '../hero.service';

@Component({
    selector: 'app-hero-detail',
    templateUrl: './hero-detail.component.html',
    styleUrls: ['./hero-detail.component.css']
})
export class HeroDetailComponent {
    @Input() hero?: Hero;

    constructor(
        private route: ActivatedRoute,
        private heroService: HeroService,
        private location: Location
    ) {

    }

    ngOnInit(): void {
        this.getHero();
    }
    getHero(): void {
        const id = Number(this.route.snapshot.paramMap.get('id'));
        this.heroService.getHero(id)
            .subscribe(paramRet => this.hero = paramRet.ret === 0 ? paramRet.data as Hero : {id: -1, name: ''});
    }
    goBack(): void {
        this.location.back();
    }

    save(): void {
        console.log('--->save???' + JSON.stringify(this.hero));
        this.heroService.updateHero(this.hero!.id, this.hero!.name).subscribe(() => this.goBack());
    }

    deleteHero(): void {
        this.heroService.delHero(this.hero!.id).subscribe(() => this.goBack());
    }
}
