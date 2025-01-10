#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <algorithm>
#include <sys/wait.h>
#include <atomic>

using namespace std;

atomic<int> connection_id_counter(0);

void reverse(char *str) {
    std::reverse(str, str + strlen(str));
}

void handle_client(int client_socket, int connection_id) {
    char buffer[1024];
    while (true) {
        memset(buffer, 0, sizeof(buffer)); 
        int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
        if (bytes_received <= 0) {
            break;
        }
        cout << "Client ID " << connection_id << " sent message: " << buffer << endl;

        reverse(buffer);

        send(client_socket, buffer, strlen(buffer), 0);
        cout << "Sending reply to Client ID " << connection_id << ": " << buffer << endl;
    }
    close(client_socket);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <port>" << endl;
        return 1;
    }

    int port = atoi(argv[1]);

    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        cerr << "Error creating socket" << endl;
        return 1;
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        cerr << "Error binding socket" << endl;
        return 1;
    }

    listen(server_socket, 5);

    cout << "Server listening on port " << port << endl;

    while (true) {
        int client_socket = accept(server_socket, NULL, NULL);
        if (client_socket < 0) {
            cerr << "Error accepting connection" << endl;
            continue;
        }

        int connection_id = connection_id_counter.fetch_add(1);

        cout << "Connected with Client ID " << connection_id << endl;

        pid_t pid = fork();
        if (pid < 0) {
            cerr << "Error forking child process" << endl;
            close(client_socket);
            continue;
        } else if (pid == 0) {
            close(server_socket);
            handle_client(client_socket, connection_id);
            exit(0);
        } else {
            close(client_socket);
        }
    }

    close(server_socket);
    return 0;
}
