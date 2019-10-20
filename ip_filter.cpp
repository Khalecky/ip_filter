#include "ip_filter.h"



std::vector<std::string> split(const std::string &str, char sep)
{
    std::vector<std::string> r;

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

void filter_any(const ip_pool_t &ip_pool, int ip_part)
{
    std::for_each(ip_pool.cbegin(), ip_pool.cend(),
        [&](const IP& ip) {
            if(ip.contains(ip_part))
                ip.print();
        }
    );
}



////
IP::IP(const std::string &_ip_str) : ip_str(_ip_str)
{
    auto str_list = split(ip_str, '.');

    for (const auto&str: str_list)
    {
        unsigned char byte = std::stoi(str);
        ip = ip << 8;
        ip = ip | byte;
        bytes.push_back(byte);
    }
}

IP::IP(const int *p_bytes, size_t bytes_count)
{
    for (int i = 0; i < 4; ++i)
    {
        bytes.push_back( (bytes_count > i ? static_cast<unsigned char>(p_bytes[i]) : 0) );
        //
        ip = ip << 8;
        ip = ip | bytes.back();
        //
        if (i > 0)
            ip_str.append(".");
        ip_str.append(std::to_string(bytes.back()) );
    }
}

bool IP::contains(int val) const
{
    return std::find(bytes.cbegin(), bytes.cend(), val) != bytes.cend();
}


void IP::print() const
{
    using namespace std;
    print<ostream>(cout);
}


IP::operator int() const
{
    return ip;
}

int IP::operator[](size_t i) const
{
    //TODO check i < 4
    return bytes[i];
}
