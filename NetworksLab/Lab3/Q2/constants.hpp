#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <string>
using namespace std;

// DATA LINK LAYER
const string MAC_HEADER_SOURCE = "e4:g8:df:t6:03:0e";
const string MAC_HEADER_DEST = "00:1A:2B:3C:4D:5E";
const string MAC_TRAILER = "\xFA\xCE\xB0\x0C";

// NETWORK LAYER
const string IP_HEADER_SOURCE = "172.16.0.13";
const string IP_HEADER_DESTINATION = "183.44.113.3";

// TRANSPORT LAYER
const string TCP_HEADER = "1F900050A1B2C3D40000000050027210FFFF0000";
const string UDP_HEADER = "1A3B0000B3D8A5A90000000050027210FADD0000";

// SESSION LAYER
const string SESSION_ID = "325";

// PRESENTATION LAYER ENCRYPTION
const int ENCRYPTION_KEY = 0x0FA9834B;
const int ENCRYPTION_KEY2 = 0x0FA9834B;

#define WAIT this_thread::sleep_for(chrono::milliseconds(300))

#endif // CONSTANTS_HPP
