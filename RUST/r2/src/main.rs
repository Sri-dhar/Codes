// fn main()
// {
//     println!("Hello how are you");
//     let mut world = "how are you";
//     println!("{}",world);
//     world = "hi i am sridhar";
//     println!("Hello, how are you");
//     println!("{}",world);
// }

fn foo(_x: &'static str) -> &'static str {
    "world"
}

fn main() {
    println!("Hello {}!", foo("how tao;je"));
}