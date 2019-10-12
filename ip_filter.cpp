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

void print_ip_range(const rangeIP &range)
{
    if (range.size() != 2)
        return;

    for(auto iter = range.front(); iter != range.back(); ++iter)
        print_ip(*iter);
}

IP split(const std::string &str, char d)
{
    IP r;

    std::string::size_type start = 0;

    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}
