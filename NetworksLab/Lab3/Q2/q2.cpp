#include <bits/stdc++.h>
using namespace std;

// DATA LINK LAYER
#define MAC_HEADER_SOURCE "e4:g8:df:t6:03:0e"
#define MAC_HEADER_DEST "00:1A:2B:3C:4D:5E"
#define MAC_TRAILER "\xFA\xCE\xB0\x0C"
#define MAC_DATA "\x48\x65\x6C\x6C\x6F\x20\x57\x6F\x72\x6C\x64"

// NETWORK LAYER
#define IP_HEADER_SOURCE "172.16.0.13"
#define IP_HEADER_DESTINATION "183.44.113.3"

// TRANSPORT LAYER
#define TCP_HEADER "1F900050A1B2C3D40000000050027210FFFF0000"
#define UDP_HEADER "1A3B0000B3D8A5A90000000050027210FADD0000"

// SESSION LAYER
#define SESSION_ID "325"

#define WAIT this_thread::sleep_for(chrono::milliseconds(300))

// PRESENTATION LAYER ENCRYPTION and DECRYPTION
// APPLICATION LAYER PRINT THE DATA

int encryption_key = 0x0FA9834B;
int encryption_key2 = 0x0FA9834B;

string convert_to_8_length(int n)
{
    string s = to_string(n);
    while (s.size() < 8)
    {
        s = "0" + s;
    }
    return s;
}

string encrypt_presentation_layer(string s)
{
    string res = "";
    for (size_t i = 0; i < s.length(); i++)
    {
        int shift = (encryption_key >> (8 * (i % 4))) & 0xFF;
        res += char((s[i] + shift) % 256);
    }
    return res;
}

string decrypt_presentation_layer(string s)
{
    string res = "";
    for (size_t i = 0; i < s.length(); i++)
    {
        int shift = (encryption_key >> (8 * (i % 4))) & 0xFF;
        res += char((s[i] - shift + 256) % 256);
    }
    return res;
}

string StringToBitStream(string s)
{
    string res = "";
    for (auto x : s)
    {
        res += bitset<8>(x).to_string();
    }
    return res;
}

string BitStreamToString(string b)
{
    string res = "";
    for (size_t i = 0; i < b.size(); i += 8)
    {
        res += char(bitset<8>(b.substr(i, 8)).to_ulong());
    }
    return res;
}

string downStream_applicationLayer(string data)
{
    cout << "Application Layer Sent: " << data << endl;
    return data;
}

string downStream_presentationLayer(string data)
{
    data = encrypt_presentation_layer(data);
    cout << "Presentation Layer Sent: " << data << endl;
    return data;
}

string downStream_sessionLayer(string data)
{
    WAIT;
    int id = stoi(SESSION_ID);
    string id_string = convert_to_8_length(id);
    data = id_string + data;
    cout << "Session Layer Sent: " << data << endl;
    return data;
}

string downStream_transportLayer(string data, int protocol)
{
    WAIT;
    if (protocol == 0)
        data = UDP_HEADER + data;
    else
        data = TCP_HEADER + data;
    cout << "Transport Layer Sent: " << data << endl;
    return data;
}

string downStream_networkLayer(string data)
{
    WAIT;
    string ip_header_source = IP_HEADER_SOURCE;
    string ip_header_destination = IP_HEADER_DESTINATION;
    data = ip_header_source + " " + ip_header_destination + " " + data;
    cout << "Network Layer Sent: " << data << endl;
    return data;
}

string downStream_dataLinkLayer(string data)
{
    WAIT;
    string mac_header_source = MAC_HEADER_SOURCE;
    string mac_header_dest = MAC_HEADER_DEST;
    data = mac_header_source + " " + mac_header_dest + " " + data + " " + MAC_TRAILER;
    cout << "Data Link Layer Sent: " << data << endl;
    return data;
}

string downStream_physicalLayer(string data)
{
    WAIT;
    data = StringToBitStream(data);
    cout << "Physical Layer Sent: " << data << endl;
    return data;
}

string upStream_physicalLayer(string data)
{
    WAIT;
    cout << "Physical Layer Received: " << data << endl;
    data = BitStreamToString(data);
    return data;
}

string upStream_dataLinkLayer(string data)
{
    WAIT;
    cout << "Data Link Layer Received: " << data << endl;
    data = data.substr(36, data.size() - 36 - 4);
    return data;
}

string upStream_networkLayer(string data)
{
    WAIT;
    cout << "Network Layer Received: " << data << endl;
    data = data.substr(25, data.size() - 25);

    return data;
}

string upStream_transportLayer(string data)
{
    WAIT;
    cout << "Transport Layer Received: " << data << endl;
    data = data.substr(40, data.size() - 40);
    return data;
}

string upStream_sessionLayer(string data)
{
    WAIT;
    cout << "Session Layer Received: " << data << endl;
    data = data.substr(8, data.size() - 8);
    return data;
}

string upStream_presentationLayer(string data)
{
    WAIT;
    cout << "Presentation Layer Received: " << data << endl;
    data = decrypt_presentation_layer(data);
    return data;
}

string upStream_applicationLayer(string data)
{
    cout << "Application Layer Received: " << data << endl;
    return data;
}

string simulateApplicationToPhysicalLayer(string data)
{
    cout << "----------------------------------------------" << endl;
    cout << "\nSimulating Application to Physical Layer\n"
         << endl;
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
    cout << "\nSimulating Physical to Application Layer\n"
         << endl;
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
