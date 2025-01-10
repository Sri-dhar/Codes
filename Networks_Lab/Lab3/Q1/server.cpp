#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <thread>
#include <vector>
#include <mutex>
#include <algorithm>

using namespace std;

mutex cout_mutex;  
mutex clients_mutex; 

vector<int> clients; 


void broadcast_message(const string &message, int sender_socket) {
    lock_guard<mutex> lock(clients_mutex);
    for (int client_socket : clients) {
        if (client_socket != sender_socket) { 
            if (send(client_socket, message.c_str(), message.length(), 0) < 0) {
                cerr << "Error sending message to client socket " << client_socket << endl;
            }
        }
    }
}

void handle_client(int client_socket, int client_id) {
    char buffer[1024];
    while (true) {
        memset(buffer, 0, sizeof(buffer)); 
        int bytes_received =    (client_socket, buffer, sizeof(buffer) - 1, 0); 
        if (bytes_received <= 0) {
            break; 
        }
        buffer[bytes_received] = '\0'; 

        {
            lock_guard<mutex> lock(cout_mutex);
            cout << "Client ID " << client_id << " sent message: " << buffer << endl;
        }

        string message = "Client ID " + to_string(client_id) + ": " + buffer;
        broadcast_message(message, client_socket);

        {
            lock_guard<mutex> lock(cout_mutex);
            cout << "Broadcasting message: " << message << endl;
        }
    }

    {
        lock_guard<mutex> lock(clients_mutex);
        auto it = find(clients.begin(), clients.end(), client_socket);
        if (it != clients.end()) {
            clients.erase(it);
        }
    }

    close(client_socket);
}

void server_input_thread() {
    while (true) {
        
        cout << "Enter message to broadcast to all clients: ";
        string server_message;
        getline(cin, server_message);

        if (!server_message.empty()) {
            broadcast_message("Server: " + server_message, -1);
        }
    }
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

    vector<thread> threads;
    int client_id = 1;

    thread input_thread(server_input_thread);

    while (true) {
        int client_socket = accept(server_socket, NULL, NULL);
        if (client_socket < 0) {
            cerr << "Error accepting connection" << endl;
            continue;
        }

        {
            lock_guard<mutex> lock(clients_mutex);
            clients.push_back(client_socket);
        }

        cout << "Connected with client ID " << client_id << endl;

        threads.emplace_back(handle_client, client_socket, client_id++);
    }

    close(server_socket);
    input_thread.join();
    for (auto &t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }
    return 0;
}
