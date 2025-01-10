#ifndef DOWNSTREAM_HPP
#define DOWNSTREAM_HPP

#include <bits/stdc++.h>
#include "constants.hpp"

using namespace std;

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
        int shift = (ENCRYPTION_KEY >> (8 * (i % 4))) & 0xFF;
        res += char((s[i] + shift) % 256);
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
    data = IP_HEADER_SOURCE + " " + IP_HEADER_DESTINATION + " " + data;
    cout << "Network Layer Sent: " << data << endl;
    return data;
}

string downStream_dataLinkLayer(string data)
{
    WAIT;
    data = MAC_HEADER_SOURCE + " " + MAC_HEADER_DEST + " " + data + " " + MAC_TRAILER;
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

#endif 
