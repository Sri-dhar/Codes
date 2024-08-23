#include "upstream.hpp"
#include "downstream.hpp"

string simulateApplicationToPhysicalLayer(string data)
{
    cout << "----------------------------------------------" << endl;
    cout << "\nSimulating Application to Physical Layer\n" << endl;
    cout << "----------------------------------------------" << endl;
    data = downStream_applicationLayer(data);
    data = downStream_presentationLayer(data);
    data = downStream_sessionLayer(data);
    data = downStream_transportLayer(data, 1); // 1 for tcp and 0 for udp
    data = downStream_networkLayer(data);
    data = downStream_dataLinkLayer(data);
    data = downStream_physicalLayer(data);
    return data;
}


string simulatePhysicalToApplicationLayer(string data)
{
    cout << "----------------------------------------------" << endl;
    cout << "\nSimulating Physical to Application Layer\n" << endl;
    cout << "----------------------------------------------" << endl;
    data = upStream_physicalLayer(data);
    data = upStream_dataLinkLayer(data);
    data = upStream_networkLayer(data);
    data = upStream_transportLayer(data);
    data = upStream_sessionLayer(data);
    data = upStream_presentationLayer(data);
    data = upStream_applicationLayer(data);
    return data;
}

int main()
{
    string data = "Hello World";
    string BitsStream = simulateApplicationToPhysicalLayer(data);
    string decryptedData = simulatePhysicalToApplicationLayer(BitsStream);
}   
