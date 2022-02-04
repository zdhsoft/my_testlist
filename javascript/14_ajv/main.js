const Ajv = require('ajv');
const ajv = new Ajv();

const schema = {
    type: 'array',
    properties: {
        foo: { type: 'object',
            properties: {
                a: 'string',
                b: 'int8',
                c: {
                    type: 'array', items: {type: 'integer'}
                }
            },
            required:['a','c'],
        },
        bar: { type: 'string' },
    },
    required: ['foo'],
    additionalProperties: false,
};

const data = { foo: 1, bar: 'abc', c:199 };
const valid = ajv.validate(schema, data);
if (!valid) console.log(JSON.stringify(ajv.errors, null, 2));
