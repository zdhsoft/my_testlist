import { Injectable } from '@angular/core';
import { Hero } from './heroes/hero';
import { HEROES } from './heroes/mock-heroes';
import { Observable, of } from 'rxjs';
import { MessageService } from './message.service';
import { HttpClient, HttpContext, HttpHeaders, HttpParams } from '@angular/common/http';
import { catchError, map, tap } from 'rxjs/operators';

enum EnumAPI {
    heroes = '/api/heroes',
    hero = '/api/hero',  // /api/hero/:id
    add = '/api/add',
    del = '/api/del', // /api/del/:id
    update = '/api/update',
    search = '/api/search'
}

export interface IRet<T = any> {
    ret: number;
    msg?: string;
    data?: T;
}

export interface IOptions {
    headers?: HttpHeaders | { [header: string]: string | string[]; };
    responseType?: 'arraybuffer'|'blob'|'json'|'text';
}
// options: {
//     headers?: HttpHeaders | {
//         [header: string]: string | string[];
//     };
//     context?: HttpContext;
//     observe?: 'body';
//     params?: HttpParams | {
//         [param: string]: string | number | boolean | ReadonlyArray<string | number | boolean>;
//     };
//     reportProgress?: boolean;
//     responseType: 'arraybuffer';
//     withCredentials?: boolean;
// }
@Injectable({
    providedIn: 'root'
})
export class HeroService {
    constructor(
        private http: HttpClient,
        private msgService: MessageService,
    ) {
        //
    }
    private log(paramMsg: string) {
        console.log(paramMsg);
        this.msgService.add(paramMsg);
    }
    public getHeroes(): Observable<IRet<Hero[]>> {
        const err: IRet<Hero[]> = {
            ret: -1,
            msg: '发生错误',
        };
        return this.http.get<IRet<Hero[]>>(EnumAPI.heroes).pipe(
            tap(_ => this.log('fetched heroes' + JSON.stringify(_))),
            catchError(this.handlerError<IRet<Hero[]>>('getHeroes', err))
        );
    }

    public searchHeroes(paramName: string): Observable<IRet<Hero[]>> {
        const name = paramName.trim();
        if (name === '') {
            const empty: IRet<Hero[]> = {
                ret: 0,
                data: []
            };

            return of(empty);
        }
        const err: IRet<Hero[]> = {
            ret: -1,
            msg: '发生错误',
        };
        return this.http.post<IRet<Hero[]>>(EnumAPI.search, { name: paramName }).pipe(
            tap(_ => this.log('search heroes' + JSON.stringify(_))),
            catchError(this.handlerError<IRet<Hero[]>>('searchHeroes', err))
        );
    }

    public searchHeroesArray(paramName: string): Observable<Hero[]> {
        return this.searchHeroes(paramName).pipe(map((paramRet) => paramRet.ret === 0 ? paramRet.data as Hero[] : []));
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
    getHero(id: number): Observable<IRet<Hero>> {
        const err: IRet<Hero> = {
            ret: -1,
            msg: '发生错误',
        };
        return this.http.get<IRet<Hero>>(`${EnumAPI.hero}/${id}`).pipe(
            tap(_ => this.log('fetched hero' + JSON.stringify(_))),
            catchError(this.handlerError<IRet<Hero>>('getHero', err))
        );
    }

    addHero(name: string): Observable<IRet<number>> {
        const err: IRet<number> = {
            ret: -1,
            msg: '发生错误',
        };
        return this.http.post<IRet<number>>(EnumAPI.add, {name}).pipe(
            tap(_ => this.log('add hero' + JSON.stringify(_))),
            catchError(this.handlerError<IRet<number>>('addHero', err))
        );
    }
    delHero(id: number): Observable<IRet> {
        const err: IRet<number> = {
            ret: -1,
            msg: '发生错误',
        };
        return this.http.get<IRet>(`${EnumAPI.del}/${id}`).pipe(
            tap(_ => this.log('del hero' + JSON.stringify(_))),
            catchError(this.handlerError<IRet>('delHero', err))
        );
    }
    updateHero(id: number, newName: string): Observable<IRet> {
        const err: IRet<number> = {
            ret: -1,
            msg: '发生错误',
        };
        console.log('update hero');
        return this.http.post<IRet>(EnumAPI.update, {id, newName}).pipe(
            tap(_ => this.log('updateHero' + JSON.stringify(_))),
            catchError(this.handlerError<IRet>('updateHero', err))
        );
    }
}
