#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFSIZ 1024

int main()
{
    int f;
    char buffer[BUFSIZ];

    f = open("test.txt", O_RDONLY);
    if (f == -1) 
    {
        perror("Error opening file");
        exit(1);
    }

    ssize_t bytesRead;
    while ((bytesRead = read(f, buffer, BUFSIZ)) > 0) {
        if (write(STDOUT_FILENO, buffer, bytesRead) == -1) {
            perror("Error writing to stdout");
            exit(1);
        }
    }

    if (bytesRead == -1) {
        perror("Error reading file");
        exit(1);
    }

    close(f);

    return 0;
}



// O_RDONLY: Open for read-only access.
// O_WRONLY: Open for write-only access.
// O_RDWR: Open for both read and write access.
// O_CREAT: Create the file if it does not exist.
// O_TRUNC: Truncate the file to zero length if it exists.
// O_APPEND: Set the file offset to the end of the file before each write.
// O_EXCL: Ensure that this call creates the file exclusively (fails if the file already exists).
// O_SYNC: Perform synchronous writes.
// O_NONBLOCK: Open in non-blocking mode.
// O_CLOEXEC: Set the close-on-exec flag for the new file descriptor.