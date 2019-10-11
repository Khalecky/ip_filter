#include "ip_filter.h"


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


void print_ip(const IP &ip)
{
    for(auto ip_part = ip.cbegin(); ip_part != ip.cend(); ++ip_part) {

        if (ip_part != ip.cbegin())
            std::cout << ".";

        std::cout << *ip_part;
    }
    std::cout << std::endl;
}


bool cmp_ip(const IP &ip1, const IP &ip2)
{
    for (int i = 0; i < ip1.size(); ++i)
    {
        int part1 = std::stoi(ip1[i]);
        int part2 = std::stoi(ip2[i]);

        if (part1 != part2)
            return part1 > part2;
    }

    return true;
}


listIP::const_iterator find_first_ip(listIP::const_iterator iter_from, listIP::const_iterator iter_to, int search_value, int index_part_search)
{
    auto iter_result = iter_to;

    auto left = iter_from;
    auto right = iter_to;

    auto iter_mid = left;

    while(true)
    {
        int d = std::distance(left, right)/2;
        //std::cout << "distance" << " " << d << std::endl;

        if (d < 1)
            break;

        iter_mid = left + d;

        int mid_val = std::stoi(iter_mid->at(index_part_search));

        if (mid_val == search_value) {
            //std::cout << "------ index of = " << (iter_mid - iter_from) << "\n";
            iter_result = iter_mid;

            break;
        }

        if (mid_val < search_value)
            right = iter_mid + 1;
        else
            left = iter_mid - 1;
    }
    return iter_result;
}


rangeIP search_in_ip(const listIP &ip_pool, int search_value, int index_part_search)
{
    rangeIP ip_range;

    auto iter_result = find_first_ip( ip_pool.cbegin(), ip_pool.cend(), search_value, index_part_search);


    if (iter_result == ip_pool.cend())
        return ip_range;

    auto left = iter_result;



    //find first occurence in sorted list ip starting from iter_result
    while (true) {

        if (left == ip_pool.cbegin())
            break;

        auto iter = left - 1;


        int val = std::stoi(iter->at(index_part_search));
        if (val != search_value)
            break;

        left = iter;

        //print_ip(*left);
    }


    ip_range.push_back(left);

    auto right = std::find_if(iter_result, ip_pool.cend(),
        [&](auto ip) {
            return std::stoi(ip[index_part_search]) != search_value;
        }
    );
    right--;

    ip_range.push_back(right);

    //std::cout << "left= "; print_ip(*left);
    //std::cout << "right= "; print_ip(*right);
    return ip_range;
}

