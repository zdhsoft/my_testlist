// const { testA } = require('../dist/a');
import { testA } from './a';
test('a', ()=> {
    expect(testA()).toBe(100);
});
