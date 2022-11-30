
function test(js_fn, done) {
    var args = Array.prototype.slice
        .call(arguments)
        .slice(2)
        .map(a => {
            return { argument: JSON.stringify(a) }
        })
    console.log(JSON.stringify(args, null, 2));
}

test(() => { }, () => { }, 1, 2, 3, 4, 5);


// Nightmare.prototype.evaluate_now = function(js_fn, done) {
//     var args = Array.prototype.slice
//       .call(arguments)
//       .slice(2)
//       .map(a => {
//         return { argument: JSON.stringify(a) }
//       })
//     var source = template.execute({ src: String(js_fn), args: args })
//     this.child.call('javascript', source, done)
//     return this
//   }
