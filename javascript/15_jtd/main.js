/** @format */

//bimport { Schema, validate } from "jtd";
const { Schema, validate } = require('jtd');

// You can leave out the "as Schema" part at the end if you're using JavaScript
// and not TypeScript.
const schema = {
    properties: {
        name: { type: 'string' },
        age: { type: 'uint32' },
        phones: {
            elements: { type: 'string' },
        },
    },
};

const result = validate(schema, {
    name: 'John Doe',
    age: -43,
    i:99,
    phones: ['+44 1234567', '+44 2345678'],
});

// jtd.validate returns an array of validation errors. If there were no problems
// with the input, it returns an empty array.

// Outputs: []
console.log(JSON.stringify(result, null, 2));
