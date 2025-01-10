#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

using namespace std;

void handle_client(int client_socket) {
    char buffer[1024];
    while (true) {
        memset(buffer, 0, sizeof(buffer)); // Clear buffer
        int bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0); // Receive message from client
        if (bytes_received <= 0) {
            break; // Client disconnects
        }
        buffer[bytes_received] = '\0'; // Null-terminate the received data
        cout << "Client socket " << client_socket << " sent message: " << buffer << endl;

        // Prompt server user for a reply
        cout << "Enter your reply: ";
        string server_reply;
        getline(cin, server_reply);

        // Send the reply back to the client
        if (send(client_socket, server_reply.c_str(), server_reply.length(), 0) < 0) {
            cerr << "Error sending message" << endl;
            break;
        }
        cout << "Sending reply: " << server_reply << endl;
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

    listen(server_socket, 1);

    cout << "Server listening on port " << port << endl;

    while (true) {
        int client_socket = accept(server_socket, NULL, NULL);
        if (client_socket < 0) {
            cerr << "Error accepting connection" << endl;
            continue;
        }

        cout << "Connected with client socket number " << client_socket << endl;

        handle_client(client_socket);
    }

    close(server_socket);
    return 0;
}
