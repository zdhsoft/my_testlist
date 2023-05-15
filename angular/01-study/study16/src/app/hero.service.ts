import { Injectable } from '@angular/core';
import { Hero } from './heroes/hero';
import { HEROES } from './heroes/mock-heroes';
import { Observable, of } from 'rxjs';
import { MessageService } from './message.service';
import { HttpClient, HttpHeaders } from '@angular/common/http';
import { catchError, map, tap } from 'rxjs/operators';

const heroesUrl = 'api/heroes';
const heroUrl = 'api/hero';
const heroSaveUrl = 'api/hero_save';
@Injectable({
  providedIn: 'root'
})
export class HeroService {
  constructor(
    private http: HttpClient,
    private messageService: MessageService) {
    //
  }

  getHeroes(): Observable<Hero[]> {
    return this.http.get<Hero[]>(heroesUrl).pipe(
        tap(_ => this.log('fetched heroes' + JSON.stringify(_))),
        catchError(this.handlerError<Hero[]>('getHeroes', []))
    );
  }

  getHero(id: number): Observable<Hero> {
    return this.http.get<Hero>(`${heroUrl}/${id}`).pipe(
        tap(_ => this.log('fetched hero' + JSON.stringify(_))),
        catchError(this.handlerError<Hero>('getHero', {id: -1, name: 'aaa'}))
    );
  }

  private handlerError<T>(operation = 'operation', result?: T) {
    return (error: any): Observable<T> => {
        // TODO: send the error to remote logging infrastructure
        console.error(error); // log to console instead

        // TODO: better job of transforming error for user consumption
        this.log(`${operation} failed: ${error.message}`);

        // Let the app keep running by returning an empty result.
        return of(result as T);
    }
}
/** PUT: update the hero on the server */
updateHero(hero: Hero): Observable<any> {
    return this.http.put(heroSaveUrl, hero, this.httpOptions).pipe(
      tap(_ => this.log(`updated hero id=${hero.id}`)),
      catchError(this.handleError<any>('updateHero'))
    );
  }

//   getHero(paramId: number) {
//     const hero = HEROES.find(h => h.id === paramId)!;
//     this.log(`HeroService: fetched hero id=${paramId}`);
//     return of(hero);
//   }

  private log(paramMsg: string) {
    this.messageService.add(paramMsg);
  }

}
