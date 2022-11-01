import { Injectable } from "@angular/core";
import { Cart } from "./cart.model";
@Injectable()
export class Order {
    public id: number | null;
    public name: string | null;
    public address: string | null;
    public city: string | null;
    public state: string | null;
    public zip: string | null;
    public country: string | null;
    public shipped: boolean = false;
    constructor(public cart: Cart) {
        this.id = null;
        this.name = null;
        this.address = null;
        this.city = null;
        this.state = null;
        this.zip = null;
        this.country = null;
        this.shipped = false;
    }
    clear() {
        this.id = null;
        this.name = null;
        this.address = null;
        this.city = null;
        this.state = null;
        this.zip = null;
        this.country = null;
        this.shipped = false;
        this.cart.clear();
    }
}
