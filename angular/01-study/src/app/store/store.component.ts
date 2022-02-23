import { Component, OnInit } from '@angular/core';
import {ProductRepository} from "../model/product.repository";
import {Product} from "../model/product.model";

@Component({
  selector: 'store',
  templateUrl: './store.component.html',
  styleUrls: ['./store.component.css']
})
export class StoreComponent implements OnInit {
  public selectedCategory?: string;
  public productsPerPage = 4;
  public selectedPage = 1;
  constructor(private repository: ProductRepository) { }

  ngOnInit(): void {
  }

  get products(): Product[] {
    const k = [];
    const pageIndex = (this.selectedPage - 1) * this.productsPerPage;
    k.push(pageIndex);
    const list = this.repository.getProducts(this.selectedCategory);
    k.push(list.length);
    const ret = list.splice(pageIndex, this.productsPerPage);
    k.push(ret.length);
    console.log("kkkk:" + JSON.stringify(k));
    return ret;
    // return this.repository.getProducts(this.selectedCategory).slice(pageIndex, this.productsPerPage);
  }

  get categories(): string[] {
    return this.repository.getCategories();
  }

  changeCategory(newCategory ?: string) {
    this.selectedCategory = newCategory;
  }

  changePage(newPage: number) {
    this.selectedPage = newPage;
  }

  changePageSize(newSize: number) {
    this.productsPerPage = newSize;
  }

  get pageNumbers(): number[] {
    const ret: number[] = [];
    const list = this.repository.getProducts(this.selectedCategory);
    const p = Math.ceil(list.length / this.productsPerPage);
    for(let i = 1; i <= p; i++) {
      ret.push(i);
    }
    // console.log('ret:' + JSON.stringify(ret));
    // const pp = Array(Math.ceil(this.repository.getProducts(this.selectedCategory).length/this.productsPerPage)).fill(0).map((x,i) => i+1);
    // console.log('p:' + JSON.stringify((pp)));
    return ret;
  }

}
