import 'reflect-metadata';
@Reflect.metadata('aaa','bbb')
class k {
    @Reflect.metadata('inMethod', 'B')
    public hello(): string {
        return 'hello world';
    }
}


console.log(Reflect.getMetadata('aaa', k)); // 'A'
console.log(Reflect.getMetadata('inMethod', new k(), 'hello')); // 'B'


@Reflect.metadata('name', 'A')
class A {
  @Reflect.metadata('name', 'hello')
  hello() {
      //
  }
}

const objs = [A, new A, A.prototype]
const res = objs.map(obj => [
  Reflect.getMetadata('name', obj),
  Reflect.getMetadata('name', obj, 'hello'),
  Reflect.getOwnMetadata('name', obj),
  Reflect.getOwnMetadata('name', obj ,'hello')
])

console.log(JSON.stringify(res, null, 2));
