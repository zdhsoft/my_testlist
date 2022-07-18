// const { testA } = require('../dist/a');
import { testA } from '../src/a';
test('a', ()=> {
    expect(testA()).toBe(100);
});
