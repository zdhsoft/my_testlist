import { Injectable } from "@angular/core";
import { Product } from "./product.model";
//import { StaticDataSource } from "./static.datasource";
import { RestDataSource } from "./rest.datasource";

@Injectable()
export class ProductRepository {
    private products: Product[] = [];
    private categories: string[] = [];

    constructor(private dataSource: RestDataSource) {
        dataSource.getProducts().subscribe(data => {
            this.products = data;
            // console.log(JSON.stringify(data, null, 2));
            const categorieSet = new Set<string>();
            let idx = 0;
            data.forEach((p) => {
                if(p.category) {
                    console.log('-----' + idx + ':' + p.category);
                    idx++;
                    categorieSet.add(p.category);
                }
            });
            this.categories = [];
            categorieSet.forEach(v=>this.categories.push(v));
            this.categories.sort();

            // this.categories = data.map(p => p.category || '')
            //     .filter((c, index, array) => c !== '' && (array.indexOf(c) == index)).sort();
        });
    }

    getProducts(category: string | null | undefined = null): Product[] {
        return this.products
            .filter(p => category == null || category == p.category);
    }

    getProduct(id: number): Product {
        return this.products.find(p => p.id == id) as Product;
    }

    getCategories(): string[] {
        return this.categories;
    }

    saveProduct(product: Product) {
        if (product.id == null || product.id == 0) {
            this.dataSource.saveProduct(product)
                .subscribe(p => this.products.push(p));
        } else {
            this.dataSource.updateProduct(product)
                .subscribe(p => {
                    this.products.splice(this.products.
                        findIndex(p => p.id == product.id), 1, product);
                });
        }
    }

    deleteProduct(id: number) {
        this.dataSource.deleteProduct(id).subscribe(p => {
            this.products.splice(this.products.
                findIndex(p => p.id == id), 1);
        })
    }
}
