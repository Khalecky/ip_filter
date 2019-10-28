#include "ip_filter.h"


StringList split(const std::string &str, char sep)
{
    StringList r;

    std::string::size_type start = 0;

    std::string::size_type stop = str.find_first_of(sep);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(sep, start);
    }

    r.push_back(str.substr(start));

    return r;
}

void filter_any(const PoolIP &ip_pool, int ip_part)
{
    std::for_each(ip_pool.cbegin(), ip_pool.cend(),
        [&](const IP& ip) {
            if(ip.contains(ip_part))
                ip.print();
        }
    );
}
