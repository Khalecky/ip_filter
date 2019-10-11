#ifndef IP_FILTER_H_INCLUDED
#define IP_FILTER_H_INCLUDED

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using IP = std::vector<std::string>;
using listIP = std::vector<IP>;
using rangeIP = std::vector<listIP::const_iterator>;

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
IP split(const std::string &, char);

void print_ip(const IP &ip);

bool cmp_ip(const IP &ip1, const IP &ip2);  //lexicographical comparator for std::sort

//search first random IP
listIP::const_iterator find_first_ip(listIP::const_iterator iter_from, listIP::const_iterator iter_to, int search_value, int index_part_search = 0);

rangeIP search_in_ip(const listIP &ip_pool, int search_value, int index_part_search = 0);


template<typename ...Args>
void filter(const listIP &ip_pool, Args... ip_parts)
{
    //printf("iterate1 = %s\nsizeof = %lu\nargs = %s\n", __PRETTY_FUNCTION__, sizeof...(ip_parts), ip_parts ...);
    int count_args = sizeof...(ip_parts);
    int arr[sizeof...(ip_parts)] = {ip_parts ... };


    auto ip_range = search_in_ip(ip_pool, arr[0], 0);
    if (ip_range.empty())
        return;


    auto is_match = [&](const IP& ip) {
        //std::cout << "check match "; print_ip(ip);

        bool result = true;
        for (int i = 0; i < count_args; ++i)
        {
            int val = std::stoi(ip[i]);
            result = result && (val == arr[i]);
            //std::cout << arr[i] << " ==== " << val << "\t";
            if (!result)
                break;
        }
        //std::cout << (result? "IS MATCH": "FAIL") << std::endl;
        return result;
    };

    for(auto iter = ip_range[0]; iter != ip_range[1]; ++iter)
    {
        if(is_match(*iter))
            print_ip(*iter);
    }

    //std::cout << n << std::endl;
}




#endif // IP_FILTER_H_INCLUDED
