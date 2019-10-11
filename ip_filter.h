#ifndef IP_FILTER_H_INCLUDED
#define IP_FILTER_H_INCLUDED

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "version.h"

using IP = std::vector<std::string>;
using listIP = std::vector<IP>;
using rangeIP = std::vector<listIP::const_iterator>;


void print_ip(const IP &ip);


template<typename ...Args>
void filter(const listIP &ip_pool, Args... ip_parts)
{
    int count_args = sizeof...(ip_parts);
    int arr[sizeof...(ip_parts)] = {ip_parts ... };

    auto iter_from = ip_pool.cbegin();
    auto iter_to = ip_pool.cend();

    for (int i = 0; i < count_args; ++i)
    {
        iter_from = std::lower_bound( iter_from, iter_to, arr[i], [&](const IP &ip, int val) { return std::stoi(ip[i]) > val;});

        if (iter_from == iter_to)
            return;

        iter_to = std::upper_bound( iter_from, iter_to, arr[i], [&](int val, const IP &ip) { return std::stoi(ip[i]) < val;});
    }

    for(auto iter = iter_from; iter != iter_to; ++iter)
        print_ip(*iter);
}

#endif // IP_FILTER_H_INCLUDED
