#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <algorithm>
#include <sys/wait.h>

using namespace std;

void reverse(char *str) {
    reverse(str, str + strlen(str));
}

void handle_client(int client_socket) {
    char buffer[1024];
    while (true) {
        // Receive message from client
                    (buffer, 0, sizeof(buffer));
        int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
        if (bytes_received <= 0) {
            break; // Client disconnected
        }
        cout << "Client socket " << client_socket << " sent message: " << buffer << endl;

        // Reverse string
        reverse(buffer, buffer + strlen(buffer));

        // Send message to client
        send(client_socket, buffer, strlen(buffer), 0);
        cout << "Sending reply: " << buffer << endl;
    }
    close(client_socket);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <port>" << endl;
        return 1;
    }

    int port = atoi(argv[1]);

    // Create socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        cerr << "Error creating socket" << endl;
        return 1;
    }

    // Bind socket
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        cerr << "Error binding socket" << endl;
        return 1;
    }

    // Listen for connections
    listen(server_socket, 5); // Backlog of 5 connections

    cout << "Server listening on port " << port << endl;

    while (true) {
        // Accept connection
        int client_socket = accept(server_socket, NULL, NULL);
        if (client_socket < 0) {
            cerr << "Error accepting connection" << endl;
            continue;
        }

        cout << "Connected with client socket number " << client_socket << endl;

        // Fork a child process to handle the client
        pid_t pid = fork();
        if (pid < 0) {
            cerr << "Error forking child process" << endl;
            close(client_socket);
            continue;
        } else if (pid == 0) { // Child process
            close(server_socket); // Close listening socket in child
            handle_client(client_socket);
            exit(0);
        } else { // Parent process
            close(client_socket); // Close client socket in parent
        }
    }

    close(server_socket);
    return 0;
}
