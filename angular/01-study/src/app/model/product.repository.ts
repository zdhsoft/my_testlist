import {Injectable} from "@angular/core";
import {Product} from "./product.model";
import {StaticDataSource} from "./static.datasources";
import {utils} from "xmcommon";

@Injectable()
export class ProductRepository {
  private products: Product[] = [];
  private categories: string[] = [];

  constructor(private dataSource: StaticDataSource) {
    dataSource.getProducts().subscribe(data => {
      this.products = data;
      this.categories = data.map(p => p.category || '')
        .filter((c, index, array) => array.indexOf(c) == index).sort();
    });
  }

  getProducts(category?: string): Product[] {
    const ret: Product[] = [];
    if (utils.isNull(category)) {
      ret.push(...this.products);
    } else {
      for(const p of this.products) {
        if (p.category === category) {
          ret.push(p);
        }
      }
    }
    return ret;
  }

  getProduct(id: number): Product | undefined {
    return this.products.find(
      (p) => {
        return p?.id === id;
      }
    );
  }

  getCategories(): string[] {
    return this.categories;
  }
}
