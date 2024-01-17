// use std::io;

// fn main() {
//     println!("Guess the number!");

//     // println!("Please input your guess.");

//     // let mut guess = String::new();
//     // let mut guesss = String::new();

//     // io::stdin()
//     //     .read_line(&mut guess)
//     //     .expect("Failed to read line");
//     //     // .read_line(&mut guesss)
    
//     //typecast guess as integer
//     let guess: u32 = guess.trim().parse().expect("Please type a number!");

//     if guess%2 == 0
//     {
//         println!("Even");
//     }
//     else
//     {
//         println!("Odd");
//     }

//     println!("You guessed: {guess}");
// }

use std::io;

fn main() {
    println!("Guess the number!");

    println!("Please input your guess.");

    let mut guess = String::new();

    io::stdin()
        .read_line(&mut guess)
        .expect("Failed to read line");

    println!("You guessed: {guess}");
}