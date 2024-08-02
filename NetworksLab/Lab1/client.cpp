#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

using namespace std;

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
    server_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, server_ip, &server_addr.sin_addr) <= 0) {
        cerr << "Invalid IP address" << endl;
        return 1;
    }

    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        cerr << "Error connecting to server" << endl;
        return 1;
    }

    cout << "Connected to server" << endl;

    char buffer[1024];
    while (true) {
        cout << "Please enter the message to the server: ";
        cin.getline(buffer, sizeof(buffer));
        send(client_socket, buffer, strlen(buffer), 0);
        memset(buffer, 0, sizeof(buffer));
        recv(client_socket, buffer, sizeof(buffer), 0);
        cout << "Server reply: " << buffer << endl;
    }

    close(client_socket);
    return 0;
}