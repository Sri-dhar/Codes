#include <iostream>
#include <fstream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstdlib>

#define FRAME_SIZE 32

using namespace std;

struct Frame {
    int sequenceNumber;
    char data[FRAME_SIZE];
};

void receiveFrame(int serverSocket, ofstream &outputFile) {
    Frame frame;
    int bytesReceived = recv(serverSocket, &frame, sizeof(frame), 0);
    if (bytesReceived > 0) {
        cout << "Frame no: " << frame.sequenceNumber << ", Data: " << frame.data << endl;
        outputFile.write(frame.data, bytesReceived - sizeof(int));
        outputFile.flush();
        
        if (!outputFile.good()) {
            cerr << "Error writing to file." << endl;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <port>" << endl;
        return 1;
    }

    ofstream outputFile("/home/solomons/Codes/NetworksLab/Lab4/Q1/client.txt");
    
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

    if (!outputFile.is_open()) {
        cerr << "Failed to open output file." << endl;
        close(clientSocket);
        return 1;
    }

    while (true) {
        receiveFrame(clientSocket, outputFile);
    }

    outputFile.close();
    close(clientSocket);
    return 0;
}                               