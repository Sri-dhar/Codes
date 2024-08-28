#include <iostream>
#include <fstream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstdlib>
#include <vector>
#include <string>
#define FRAME_SIZE 32

using namespace std;

struct Frame {
    int sequenceNumber;
    char data[FRAME_SIZE];
};

vector<string> receivedData;

void updateFile(const string& filename) {
    ofstream outputFile(filename, ios::trunc);
    if (!outputFile.is_open()) {
        cerr << "Failed to open output file." << endl;
        return;
    }
    for (const auto& data : receivedData) {
        outputFile << data;
    }
    outputFile.close();
}

void receiveFrame(int serverSocket, const string& filename) {
    Frame frame;
    int bytesReceived = recv(serverSocket, &frame, sizeof(frame), 0);
    if (bytesReceived > 0) {
        cout << "Received Frame no: " << frame.sequenceNumber << ", Data: " << frame.data << endl;
        
        string input;
        cout << "1. Successfully receive and send ACK" << endl;
        cout << "2. Simulate corruption (don't send ACK)" << endl;
        cout << "3. Simulate ACK lost (send ACK but don't save frame)" << endl;
        cout << "Choose an option (1-3): ";
        cin >> input;
        
        if (input == "1") {
            // Add to vector
            receivedData.push_back(string(frame.data, bytesReceived - sizeof(int)));
            
            // Update file
            updateFile(filename);

            // Send ACK
            char ack[10];
            sprintf(ack, "ACK %d", frame.sequenceNumber);
            send(serverSocket, ack, strlen(ack), 0);
            cout << "ACK sent for frame " << frame.sequenceNumber << endl;
        } else if (input == "2") {
            cout << "Simulating corruption. No ACK sent." << endl;
        } else if (input == "3") {
            // Send ACK but don't save frame
            char ack[10];
            sprintf(ack, "ACK %d", frame.sequenceNumber);
            send(serverSocket, ack, strlen(ack), 0);
            cout << "ACK sent but frame not saved (simulating ACK lost)" << endl;
        } else {
            cout << "Invalid option. Frame discarded." << endl;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <port>" << endl;
        return 1;
    }

    string outputFilename = "client.txt";
    int port = atoi(argv[1]);
    int clientSocket;
    struct sockaddr_in serverAddr;

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        cerr << "Socket creation failed." << endl;
        return 1;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);

    if (inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr) <= 0) {
        cerr << "Invalid address/ Address not supported." << endl;
        close(clientSocket);
        return 1;
    }

    if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        cerr << "Connection failed." << endl;
        close(clientSocket);
        return 1;
    }

    while (true) {
        receiveFrame(clientSocket, outputFilename);
    }

    close(clientSocket);
    return 0;
}   