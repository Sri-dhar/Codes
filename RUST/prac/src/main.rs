#[derive(Debug)]
enum IpAddrKind {
    V4(i32),
    V6(i32),
}

fn route(a : IpAddrKind) {
    println!("a is {:?}", a);
}

fn main() {
    // println!("Hello, world!");
    // let mut s : String = String::from("Hello, world!");
    // let y = s.clone();
    // println!("{}", y);
    // println!("{}", s);
    // s = String::from("Hello wsecsklaj");
    // println!("{}", s);
    let four = IpAddrKind::V4(127);
    let six =   IpAddrKind::V6(2344);

    route(four);
    route(six);

}
