import 'reflect-metadata';


export function Injectable(options = 'bbbbbbbbbbbbbbbbbb'): ClassDecorator {
    return (target: object) => {
        Reflect.defineMetadata('____OPTS___', options, target);
    };
}
@Injectable()
@Reflect.metadata('aaa','bbb')
class k {
    @Reflect.metadata('inMethod', 'B')
    public hello(): string {
        return 'hello world';
    }
}

Reflect.defineMetadata('mmmmmm', 'sssssssssssssssssssssss', k);

console.log(Reflect.getMetadata('aaa', k)); // 'A'
console.log(Reflect.getMetadata('____OPTS___', k)); // 'A'
console.log(Reflect.getMetadata('mmmmmm', k)); // 'A'
console.log(Reflect.getMetadata('inMethod', new k(), 'hello')); // 'B'


@Reflect.metadata('name', 'A')
class A {
  @Reflect.metadata('name', 'hello')
  hello() {
      //
  }
}

const objs = [A, new A(), A.prototype]
const res = objs.map(obj => [
  Reflect.getMetadata('name', obj),
  Reflect.getMetadata('name', obj, 'hello'),
  Reflect.getOwnMetadata('name', obj),
  Reflect.getOwnMetadata('name', obj ,'hello')
])

console.log(JSON.stringify(res, null, 2));
