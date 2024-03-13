#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstring>

#define LSH_RL_BUFSIZE 1024

// Function declarations
std::string lsh_read_line();
std::vector<std::string> lsh_split_line(std::string line);
int lsh_execute(std::vector<std::string> args);
int lsh_launch(std::vector<std::string> args);
void lsh_loop();

// Built-in command declarations
int lsh_cd(std::vector<std::string> args);
int lsh_help(std::vector<std::string> args);
int lsh_exit(std::vector<std::string> args);

// Array of built-in command strings
std::vector<std::string> builtin_str = {
    "cd",
    "help",
    "exit"
};

// Array of built-in command functions
std::vector<int (*)(std::vector<std::string>)> builtin_func = {
    &lsh_cd,
    &lsh_help,
    &lsh_exit
};

int lsh_num_builtins() {
    return builtin_str.size();
}

std::string lsh_read_line() {
    std::string line;
    std::getline(std::cin, line);
    return line;
}

std::vector<std::string> lsh_split_line(std::string line) {
    std::istringstream iss(line);
    std::vector<std::string> tokens;
    std::string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

int lsh_cd(std::vector<std::string> args) {
    if (args.size() < 2) {
        std::cerr << "lsh: expected argument to \"cd\"\n";
    } else {
        if (chdir(args[1].c_str()) != 0) {
            perror("lsh");
        }
    }
    return 1;
}

int lsh_help(std::vector<std::string> args) {
    std::cout << "Simple Shell\n";
    std::cout << "Enter program names and arguments, and press enter.\n";
    std::cout << "Built-in commands:\n";
    std::cout << "  cd <directory>: Change the current working directory\n";
    std::cout << "  help: Display this help message\n";
    std::cout << "  exit: Exit the shell\n";
    return 1;
}

int lsh_exit(std::vector<std::string> args) {
    return 0;
}

int lsh_execute(std::vector<std::string> args) {
    if (args.empty()) {
        return 1;
    }

    for (size_t i = 0; i < lsh_num_builtins(); i++) {
        if (args[0] == builtin_str[i]) {
            return (*builtin_func[i])(args);
        }
    }

    return lsh_launch(args);
}

int lsh_launch(std::vector<std::string> args) {
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0) {
        // Child process
        std::vector<char*> cargs;
        for (auto &s : args) {
            cargs.push_back(&s[0]);
        }
        cargs.push_back(NULL);
        if (execvp(cargs[0], &cargs[0]) == -1) {
            perror("lsh");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        // Error forking
        perror("lsh");
    } else {
        // Parent process
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}

void lsh_loop() {
    std::string line;
    std::vector<std::string> args;
    int status;

    do {
        std::cout << "CppTerm >> ";
        line = lsh_read_line();
        if(line == "hi") {
            std::cout << "Hello, World!" << std::endl;
            continue;
        }
        args = lsh_split_line(line);
        status = lsh_execute(args);
    } while (status);
}

int main(int argc, char **argv) {
    lsh_loop();
    return EXIT_SUCCESS;
}