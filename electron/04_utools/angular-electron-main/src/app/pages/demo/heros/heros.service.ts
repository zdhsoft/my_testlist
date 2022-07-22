import { Injectable } from '@angular/core';
import { HEROES, IHero } from '../../../mock';
import {Observable, of} from 'rxjs';
import { MessagesService } from './messages.service';

@Injectable({
    providedIn: 'root'
})
export class HerosService {

    constructor(private msgServices: MessagesService) { }

    public getHeros(): Observable<IHero[]>  {
        const heroes = of(HEROES);
        this.msgServices.add('HeroService: fetched heroes!');
        return heroes;
    }
}
