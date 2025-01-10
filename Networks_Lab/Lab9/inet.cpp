#include <arpa/inet.h>
#include <iostream>
using namespace std;

int main()
{
    const char *ip_address = "192.168.1.1";
    struct in_addr addr;

    int result = inet_pton(AF_INET, ip_address, &addr);
    if (result == 1)
    {
        std::cout << "The IP address was successfully converted." << std::endl;
    }
    else if (result == 0)
    {
        std::cerr << "The input is not a valid IP address." << std::endl;
    }
    else
    {
        std::cerr << "An error occurred during conversion." << std::endl;
    }

    cout << "Result : " << result << endl;
    cout << "IP Address : " << addr.s_addr << endl;
    cout << "IP Address : " << inet_ntoa(addr) << endl;

    return 0;
}