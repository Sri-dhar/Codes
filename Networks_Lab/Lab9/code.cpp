#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <arpa/inet.h>
#include <algorithm>

using namespace std;

struct RouteEntry
{
    string cidr;
    string line;
};

void cidrToNetworkAndMask(const string &cidr, in_addr &network, in_addr &mask)
{
    size_t pos = cidr.find('/');
    string ip = cidr.substr(0, pos);
    int prefixLength = stoi(cidr.substr(pos + 1));

    stringstream ss(ip);
    string segment;
    string decimalIp;

    // cout << "Converting CIDR IP from hex to decimal: " << ip << endl;
    while (getline(ss, segment, '.'))
    {
        unsigned int decimalSegment;
        stringstream converter(segment);
        converter >> hex >> decimalSegment;
        decimalIp += to_string(decimalSegment) + ".";
    }

    if (!decimalIp.empty())
    {
        decimalIp.pop_back();
    }

    // cout << "Converted CIDR IP to decimal: " << decimalIp << endl;

    inet_pton(AF_INET, decimalIp.c_str(), &network);
    mask.s_addr = htonl(~((1 << (32 - prefixLength)) - 1));

    // cout << "Generated mask for CIDR /" << prefixLength << ": " << inet_ntoa(mask) << endl;
}

bool isInNetwork(const in_addr &ip, const in_addr &network, const in_addr &mask)
{
    return (ip.s_addr & mask.s_addr) == (network.s_addr & mask.s_addr);
}

string forward(const string &ipAddress, const vector<RouteEntry> &routingTable)
{
    in_addr ip;
    inet_pton(AF_INET, ipAddress.c_str(), &ip);

    string bestMatch;
    int bestPrefixLength = -1;

    // cout << "Processing IP address: " << ipAddress << endl;

    for (const auto &entry : routingTable)
    {
        in_addr network, mask;
        cidrToNetworkAndMask(entry.cidr, network, mask);

        if (isInNetwork(ip, network, mask))
        {
            // cout <<"IP "<< ipAddress << " is in network: " << entry.cidr << endl;
            int prefixLength = stoi(entry.cidr.substr(entry.cidr.find('/') + 1));

            // cout << "Matching CIDR: " << entry.cidr << " with line: " << entry.line << endl;

            if (prefixLength > bestPrefixLength)
            {
                bestPrefixLength = prefixLength;
                bestMatch = entry.line;
                // cout << "Best match so far: " << entry.cidr << " on line " << entry.line << endl;
            }
        }
    }

    if (bestMatch.empty())
    {
        // cout << "No matching route found for IP: " << ipAddress << endl;
        return "No match found";
    }
    else
    {
        // cout << "Forwarding IP: " << ipAddress << " using line: " << bestMatch << endl;
        return bestMatch;
    }
}

string process(const string &ip)
{
    if (ip.find('.') != string::npos)
    {
        stringstream ss(ip);
        string segment;
        string decimalIp;

        // cout << "Processing input IP in hexadecimal format: " << ip << endl;

        while (getline(ss, segment, '.'))
        {
            unsigned int decimalSegment;
            stringstream converter(segment);
            converter >> hex >> decimalSegment;
            decimalIp += to_string(decimalSegment) + ".";
        }

        if (!decimalIp.empty())
        {
            decimalIp.pop_back();
        }

        // cout << "Converted IP to decimal format: " << decimalIp << endl;
        return decimalIp;
    }

    return ip;
}

int main()
{
    vector<RouteEntry> routingTable = {
        {"C4.5E.2.0/23", "A"},
        {"C4.5E.4.0/22", "B"},
        {"C4.5E.C0.0/19", "C"},
        {"C4.5E.40.0/18", "D"},
        {"C4.4C.0.0/14", "E"},
        {"C0.0.0.0/2", "F"},
        {"80.0.0.0/1", "G"},
    };

    vector<string> ips = {"C4.4B.31.2E", "C4.5E.05.09", "C4.4D.31.2E", "C4.5E.03.87", "C4.5E.7F.12", "C4.5E.D1.02"};
    for (const auto &ip : ips)
    {
        cout << "Given IP: " << ip << " is processed as: " << process(ip) << endl;
        string result = forward(process(ip), routingTable);
        cout << "The line to use for IP: " << ip << " is: " << result << endl;
    }

    while (1)
    {
        cout << "\nEnter an IP to know its forwarding line and -1 to exit: " << endl;
        string ip;
        cin >> ip;
        if (ip == "-1")
            return 0;

        cout << "Given IP: " << ip << " is processed as: " << process(ip) << endl;
        string result = forward(process(ip), routingTable);
        cout << "The line to use for IP: " << ip << " is: " << result << endl;
    }

    return 0;
}
