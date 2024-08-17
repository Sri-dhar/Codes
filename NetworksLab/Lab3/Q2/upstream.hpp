#ifndef UPSTREAM_HPP
#define UPSTREAM_HPP

#include <bits/stdc++.h>
#include "constants.hpp"

using namespace std;

string decrypt_presentation_layer(string s)
{
    string res = "";
    for (size_t i = 0; i < s.length(); i++)
    {
        int shift = (ENCRYPTION_KEY >> (8 * (i % 4))) & 0xFF;
        res += char((s[i] - shift + 256) % 256);
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

#endif  
