fn main() {
    println!("Hello, world!");

    let c = 'z';
    let z = 'ℤ';
    let heart_eyed_cat = '😻';

    let tup: (i32, f64, u8) = (500, 6.4, 1);
    let (_x, y, _z) = tup;

    println!("The value of y is: {}", y);
}
