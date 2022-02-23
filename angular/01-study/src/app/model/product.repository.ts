import {Injectable} from "@angular/core";
import {Product} from "./product.model";
import {StaticDataSource} from "./static.datasources";
import {XUtils} from "../../common/utils";

@Injectable()
export class ProductRepository {
  private products: Product[] = [];
  private categories: string[] = [];

  constructor(private dataSource: StaticDataSource) {
    dataSource.getProducts().subscribe(data => {
      this.products = data;
      const s = new Set<string>();
      data.forEach((v) => {
        if (XUtils.isNotNull(v.category)) {
          s.add(v.category as string);
        }
      });
      s.forEach((k) => this.categories.push(k));
      this.categories.sort();
    });
  }

  getProducts(category?: string): Product[] {
    const ret: Product[] = [];
    if (XUtils.isNull(category)) {
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
