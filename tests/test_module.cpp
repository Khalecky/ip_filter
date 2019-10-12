#define BOOST_TEST_MODULE app_tests

#include <boost/test/unit_test.hpp>
#include <boost/test/tools/output_test_stream.hpp>

#include <fstream>

#include "../version.h"
#include "../ip_filter.h"

using boost::test_tools::output_test_stream;

listIP ip_pool;

void fill_ip_pool()
{
    if (!ip_pool.empty())
        return;

    std::ifstream ifs ("ip_filter.tst");

    for(std::string line; std::getline(ifs, line);)
    {
        //std::cout << line << std::endl;
        auto v = split(line, '.');
        ip_pool.push_back(v);
    }

}

void print_ip_test(output_test_stream &output, const IP& ip)
{
    for(auto iter = ip.cbegin(); iter != ip.cend(); ++iter) {

        if (iter != ip.cbegin())
            output << ".";
        output << *iter;
    }
    output << std::endl;
}


BOOST_AUTO_TEST_SUITE(app_tests)

BOOST_AUTO_TEST_CASE(test_version)
{
    BOOST_CHECK(PROJECT_VERSION_PATCH > 0);
}

BOOST_AUTO_TEST_CASE(test_filter_first_byte)
{
    output_test_stream output( "ip_filter_first_byte.tst", true );
    fill_ip_pool();

    int first_byte = 46;

    rangeIP range = filter(ip_pool, first_byte);
    BOOST_REQUIRE_EQUAL(range.size(), 2);

    for(auto iter = range.front(); iter != range.back(); ++iter)
        print_ip_test(output, *iter);

    BOOST_REQUIRE (!output.is_empty(false));
    BOOST_CHECK( output.match_pattern() );
}

BOOST_AUTO_TEST_CASE(test_filter_two_bytes)
{
    output_test_stream output( "ip_filter_two_bytes.tst", true );
    fill_ip_pool();

    int first_byte = 46;
    int second_byte = 70;

    rangeIP range = filter(ip_pool, first_byte, second_byte);
    BOOST_REQUIRE_EQUAL(range.size(), 2);

    //output << __PRETTY_FUNCTION__<< std::endl;
    for(auto iter = range.front(); iter != range.back(); ++iter) {
        print_ip_test(output, *iter);
    }

    BOOST_REQUIRE (!output.is_empty(false));
    BOOST_CHECK( output.match_pattern() );
}


BOOST_AUTO_TEST_SUITE_END()
