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

void sendFrame(int clientSocket, Frame frame) {
    send(clientSocket, &frame, sizeof(frame), 0);
    cout << "Sent Frame: Seq No: " << frame.sequenceNumber << ", Data: " << frame.data << endl;
    
    // Wait for ACK
    char ackBuffer[10];
    int bytesReceived = recv(clientSocket, ackBuffer, sizeof(ackBuffer), 0);
    if (bytesReceived > 0) {
        ackBuffer[bytesReceived] = '\0';  // Null-terminate the received string
        cout << "Received: " << ackBuffer << endl;
    } else {
        cout << "No ACK received" << endl;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <port>" << endl;
        return 1;
    }

    int port = atoi(argv[1]);
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addrLen = sizeof(clientAddr);

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        cerr << "Socket creation failed." << endl;
        return 1;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        cerr << "Bind failed." << endl;
        close(serverSocket);
        return 1;
    }

    if (listen(serverSocket, 3) < 0) {
        cerr << "Listen failed." << endl;
        close(serverSocket);
        return 1;
    }

    cout << "Server is listening on port " << port << endl;

    clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &addrLen);
    if (clientSocket < 0) {
        cerr << "Accept failed." << endl;
        close(serverSocket);
        return 1;
    }

    ifstream file("data.txt");
    if (!file.is_open()) {
        cerr << "Failed to open file." << endl;
        close(clientSocket);
        close(serverSocket);
        return 1;
    }

    int sequenceNumber = 0;
    char buffer[FRAME_SIZE];
    string input;

    while (file.read(buffer, FRAME_SIZE) || file.gcount()) {
        Frame frame;
        frame.sequenceNumber = sequenceNumber++;
        memset(frame.data, 0, FRAME_SIZE);
        memcpy(frame.data, buffer, file.gcount());

        cout << "Converting to Frame: Seq No: " << frame.sequenceNumber << ", Data: " << frame.data << endl;
        
        cout << "Send next frame? (y/n): ";
        cin >> input;
        
        if (input == "y" || input == "Y") {
            sendFrame(clientSocket, frame);
        } else {
            cout << "Frame not sent." << endl;
        }
    }

    file.close();
    close(clientSocket);
    close(serverSocket);
    return 0;
}                               