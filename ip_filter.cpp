#include "ip_filter.h"

void print_ip(const IP &ip)
{
    for(auto ip_part = ip.cbegin(); ip_part != ip.cend(); ++ip_part) {

        if (ip_part != ip.cbegin())
            std::cout << ".";

        std::cout << *ip_part;
    }
    std::cout << std::endl;
}
