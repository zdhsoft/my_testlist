import { Component } from "@angular/core";
import { NgForm } from "@angular/forms";
import { Order } from "../model/order.model";
import { OrderRepository } from "../model/order.repository";
@Component({
    template: "checkout.component.html"
})
export class CheckoutComponent {
    public orderSent: boolean = false;
    public submitted: boolean = false;
    constructor(public repository: OrderRepository,
        public order: Order) { }
    submitOrder(form: NgForm) {
        this.submitted = true;
        if (form.valid) {
            this.repository.saveOrder(this.order).subscribe(order => {
                this.order.clear();
                this.orderSent = true;
                this.submitted = false;
            });
        }
    }
}
