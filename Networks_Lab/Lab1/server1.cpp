    #include <iostream>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <string.h>
    #include <unistd.h>
    #include <algorithm>

    using namespace std;

    void reverse(char *str) {
        std::reverse(str, str + strlen(str));
    }

    void handle_client(int client_socket) {
        char buffer[1024];
        while (true) {
            memset(buffer, 0, sizeof(buffer)); // Clear buffer
            int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0); // recieve message from client
            if (bytes_received <= 0) {
                break; // Client disconnect
            }
            cout << "Client socket " << client_socket << " sent message: " << buffer << endl;

            reverse(buffer);

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

        
        int server_socket = socket(AF_INET, SOCK_STREAM, 0);
        //socket function takes
        //AF_INET: address family, IPv4
        //SOCK_STREAM: type of socket, TCP
        //0: protocol, 0 means use default protocol for AF_INET and SOCK_STREAM

        if (server_socket < 0) {
            cerr << "Error creating socket" << endl;
            return 1;
        }

        struct sockaddr_in server_addr; //endpoint address in ipv4 socket
        memset(&server_addr, 0, sizeof(server_addr)); ///server_addr is the address of the server
        server_addr.sin_family = AF_INET; //address family is IPv4 || AF_INET6 for IPv6
        server_addr.sin_addr.s_addr = INADDR_ANY; // any ip address
        server_addr.sin_port = htons(port); // converts port to network byte order

        // bind     function takes 3 arguments
        // server socket, server address, size of server address                        
        if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
            cerr << "Error binding socket" << endl;
            return 1;
        }

        
        listen(server_socket, 1); 
        // maximum no. of clients that can be connected to the server and be waiting in the queue

        cout << "Server listening on port " << port << endl;

        while (true) {
            //message loop
            int client_socket = accept(server_socket, NULL, NULL);
            if (client_socket < 0) {
                cerr << "Error accepting connection" << endl;
                continue;
            }

            cout << "Connected with client socket number " << client_socket << endl;

            // Handle the client
            handle_client(client_socket);
        }

        close(server_socket);
        return 0;
    }
