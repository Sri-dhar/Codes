#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <thread>

using namespace std;

void receive_messages(int client_socket) {
    char buffer[1024];
    while (true) {
        memset(buffer, 0, sizeof(buffer)); // Clear buffer
        int bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
        if (bytes_received <= 0) {
            cerr << "Error receiving message or server disconnected" << endl;
            break;
        }
        buffer[bytes_received] = '\0'; // Null-terminate the received data
        cout << "Server reply: " << buffer << endl;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <server_ip> <port>" << endl;
        return 1;
    }

    const char *server_ip = argv[1];
    int port = atoi(argv[2]);

    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        cerr << "Error creating socket" << endl;
        return 1;
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(server_ip);
    server_addr.sin_port = htons(port);

    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        cerr << "Error connecting to server" << endl;
        return 1;
    }

    // Start a thread to receive messages from the server
    thread receiver(receive_messages, client_socket);

    while (true) {
        // Prompt client user for input
        cout << "Enter message: ";
        string user_message;
        getline(cin, user_message);

        if (send(client_socket, user_message.c_str(), user_message.length(), 0) < 0) {
            cerr << "Error sending message" << endl;
            break;
        }
    }

    receiver.join(); // Wait for the receiver thread to finish
    close(client_socket);
    return 0;
}
            