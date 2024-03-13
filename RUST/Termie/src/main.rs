use std::io::{self, Write};
use std::fs::OpenOptions;
use chrono::{DateTime, Local};
use std::collections::HashMap;
use std::process::Command;
use dirs;
use std::env;

struct CustomCommand {
    name: String,
    path: String,
}

#[macro_use]
extern crate lazy_static;

use std::sync::Mutex;

lazy_static! {
    static ref GLOBAL_VECTOR: Mutex<Vec<String>> = Mutex::new(vec![]);
    static ref GLOBAL_SAVED_COMMANDS: Mutex<Vec<String>> = Mutex::new(vec![]);
    static ref COMMANDS: Mutex<HashMap<String, CustomCommand>> = Mutex::new(HashMap::new());
}

fn add_function(name: &str, path: &str) {
    let mut commands = COMMANDS.lock().unwrap();
    commands.insert(name.to_string(), CustomCommand {
        name: name.to_string(),
        path: path.to_string(),
    });
}

fn execute_command(name: &str) {
    let commands = COMMANDS.lock().unwrap();
    if let Some(command) = commands.get(name) {
        let output = Command::new(&command.path)
            .output()
            .expect("Failed to execute command");

        let output = String::from_utf8_lossy(&output.stdout);
        println!("{}", output);
    } else {
        println!("Command not found");
    }
}

fn write_to_bashhistory(input: &str) {
    // let home_dir = dirs::home_dir().expect("Could not get home directory");
    // let home_bashhistory_path = home_dir.join(".bashhistory");

    let current_dir = env::current_dir().expect("Could not get current directory");
    let current_bashhistory_path = current_dir.join(".bashhistory");

    // write_to_file(&home_bashhistory_path, input);
    write_to_file(&current_bashhistory_path, input);
}

fn write_to_file(path: &std::path::Path, input: &str) {
    let file = OpenOptions::new()
        .write(true)
        .append(true)
        .open(path);

    let mut file = match file {
        Ok(file) => file,
        Err(e) => {
            eprintln!("Could not open {}: {}", path.display(), e);
            return;
        }
    };

    if let Err(e) = writeln!(file, "{}", input) {
        eprintln!("Couldn't write to file: {}", e);
    }

    file.flush().expect("Could not flush buffer");
}

fn temp(input: &str) {
    println!("the input was  {}", input);
    println!("hllo world");
}

fn loop_to_get_input() {
    let mut global_string_vector = GLOBAL_VECTOR.lock().unwrap();
    loop {
        print!("Termie >> ");
        io::stdout().flush().unwrap();
        let mut input = String::new();
        io::stdin().read_line(&mut input).unwrap();
        let input = input.trim();
        let now: DateTime<Local> = Local::now();
        let command_with_time = format!("{} - {}", now.to_string(), input);
        write_to_bashhistory(&command_with_time);
        let parts: Vec<&str> = input.split_whitespace().collect();
        match parts.as_slice() {
            ["exit"] => break,
            ["add_function", name, path] => add_function(name, path),
            ["temp", temp_input @ ..] => {
                let temp_input_str = temp_input.join(" ");
                temp(&temp_input_str);
            }
            ["history", "-a"] => {
                let history = std::fs::read_to_string(".bashhistory")
                    .expect("Could not read .bashhistory file");
                println!("{}", history);
            }
            ["history"] => {
                for command in global_string_vector.iter() {
                    println!("{}", command);
                }
            }
            ["history","-ac"] => {
                //empty the .bashhistory file
                // let home_dir = dirs::home_dir().expect("Could not get home directory");
                // let home_bashhistory_path = home_dir.join(".bashhistory");
                let current_dir = env::current_dir().expect("Could not get current directory");
                let current_bashhistory_path = current_dir.join(".bashhistory");
                // let mut file = OpenOptions::new()
                //     .write(true)
                //     .truncate(true)
                //     .open(home_bashhistory_path)
                //     .expect("Could not open file");
                // file.write_all(b"").expect("Could not write to file");
                let mut file = OpenOptions::new()
                    .write(true)
                    .truncate(true)
                    .open(current_bashhistory_path)
                    .expect("Could not open file");
                file.write_all(b"").expect("Could not write to file");

            }
            [command] => {
                execute_command(command);
                global_string_vector.push(command.to_string());
            }
            _ => println!("Invalid command"),
        }
    }
}

fn main() { 
    // write_to_bashhistory(now.to_string().as_str());
    loop_to_get_input();
    let _global_string_vector = GLOBAL_VECTOR.lock().unwrap();
    let mut global_command_vector = GLOBAL_SAVED_COMMANDS.lock().unwrap();
    //input values into global command vector like ls cd mkdir and exit
    global_command_vector.push("ls".to_string());
    global_command_vector.push("cd".to_string());
    global_command_vector.push("mkdir".to_string());
    global_command_vector.push("exit".to_string());
}


// trying to make the code remember the custom functions
//given by add_function
// add history function to print the .bashhistory 
// enable flags in history function such that history -c will clear the history