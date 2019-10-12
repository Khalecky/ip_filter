#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>

#include "version.h"
#include "ip_filter.h"


int main()
{

    try
    {
        listIP ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            auto v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));

        }

        std::sort(ip_pool.begin(), ip_pool.end(),
            [](const IP &ip1, const IP &ip2) {
                for (unsigned int i = 0; i < ip1.size(); ++i) {
                    int part1 = std::stoi(ip1[i]);
                    int part2 = std::stoi(ip2[i]);

                    if (part1 != part2)
                        return part1 > part2;
                }
                return true;
            }
        );

        for(const auto &ip: ip_pool)
            print_ip(ip);

        print_ip_range(filter(ip_pool, 1));
        print_ip_range(filter(ip_pool, 46, 70));

        // TODO filter by any byte and output
        // ip = filter_any(46)

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
