// #include <unistd.h>

// int main() {
//     execl("/bin/ls", "ls", "-l", NULL);
//     // This line will not be executed if execl is successful
//     perror("execl");
//     return 1;
// }
#include <unistd.h>

int main() {
    char *args[] = {"ls", "-l", NULL};
    execv("/bin/ls", args);
    // This line will not be executed if execv is successful
    perror("execv");
    return 1;
}
