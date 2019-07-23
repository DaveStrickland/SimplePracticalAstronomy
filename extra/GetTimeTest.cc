#include <iostream>
#include <string>
#include <ctime>
#include <cstring>
#include <iomanip> // put_time and get_time
#include <sstream>
#include <list>
// To compile:
// c++ -std=c++11 -O2 -g -Wall   -c -o GetTimeTest.o GetTimeTest.cc
// c++ -o GetTimeTest GetTimeTest
int main()
{
    // Test std::get_time can handle strings std::put_time produces
    std::tm tm1 = {45, 23, 12, 2, 0, 108, 3, 2, 0};
    std::list<std::string> fmt_list = {std::string("%F %T"),
        std::string("%Y-%m-%d %H:%M:%S"),
        std::string("%a %b %e %T %Z %Y")}; // US linux/OSX 'date' format
    for (std::list<std::string>::iterator it = fmt_list.begin();
        it != fmt_list.end(); ++it)
    {
        std::string date_format = *it;;
        std::cout << "Testing format: " << date_format << std::endl;
        std::stringstream ss;
        ss << std::put_time(&tm1, date_format.c_str());
        std::string put_time_str = ss.str();
        std::cout << "  Result of put_time on tm1: " << put_time_str << std::endl;

        // Parse string representation using get_time into tm2, compare to tm1
        std::tm tm2 = {0, 0, 0, 0, 0, 0, 0, 0, 0};    
        ss >> std::get_time(&tm2, date_format.c_str());
        if ( std::memcmp(&tm1, &tm2, sizeof(tm1)) != 0 )
        {
            std::cout << "  WARN: Struct from get_time, tm2!=tm1. Possible BUG?." << std::endl;
        }
        else
        {
            std::cout << "  Struct from get_time, tm2==tm1. OK." << std::endl;
        }

        // Comparse string representation of tm2 to that of tm1
        std::ostringstream oss;
        oss << std::put_time(&tm2, date_format.c_str());
        std::string get_time_str = oss.str();
        std::cout << "  Result of put_time on tm2: " << get_time_str << std::endl;
        if (put_time_str.compare(get_time_str) != 0)
        {
            std::cout << "  ERROR: String repr of get_time tm2 != string repr of tm1. PROBLEM." << std::endl;
        }
        else
        {
            std::cout << "  OK: String repr of get_time tm2 == string repr of tm1." << std::endl;
        }
    }
    return 0;
}
