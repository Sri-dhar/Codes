#include<bits/stdc++.h>
using namespace std;

//DATA LINK LAYER
#define MAC_HEADER_SOURCE "e4:g8:df:t6:03:0e"
#define MAC_HEADER_DEST "00:1A:2B:3C:4D:5E"
#define MAC_TRAILER "\xFA\xCE\xB0\x0C"
#define MAC_DATA "\x48\x65\x6C\x6C\x6F\x20\x57\x6F\x72\x6C\x64"

//NETWORK LAYER
#define IP_HEADER_SOURCE "172.16.0.13"
#define IP_HEADER_DESTINATION "183.44.113.3"

//TRANSPORT LAYER
#define TCP_UDP_HEADER "1F900050A1B2C3D40000000050027210FFFF0000"

//SESSION LAYER
#define SESSION_ID "325"


string StringToBitStream(string s) {
    string res = "";
    for (auto x : s) {
        res += bitset<8>(x).to_string();
    }
    return res;
}

string BitStreamToString(string b) {
    string res = "";
    for (size_t i = 0; i < b.size(); i += 8) {
        res += char(bitset<8>(b.substr(i, 8)).to_ulong());
    }
    return res;
}

int main(){

}