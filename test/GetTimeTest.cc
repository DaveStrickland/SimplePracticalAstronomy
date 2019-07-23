// Test whether get_time can correctly parse std::put_time's output.
// Also compares against POSIX strptime for sanity checking.
// GCC compilation used:
// g++ -std=c++11 -O2 -g -Wall -c -o GetTimeTest.o GetTimeTest.cc
// g++ -o GetTimeTest GetTimeTest.o
//  
// Dave Strickland <dkstrickland2@gmail.com>, Feb 07, 2018.
#include <iostream>
#include <string>
#include <ctime>
#include <cstring>
#include <iomanip> // put_time and get_time, c++11 and later
#include <sstream>
#include <list>

#include "GetTimeTest.h"

#ifdef GETTIME_STANDALONE
/**
 * Provided to allow a stand-alone compilation outside of the unit test main
 */
int main()
{
    runMainGetTimeTest();
    return 0;
}
#endif // GETTIME_STANDALONE

namespace SPA
{
namespace TEST
{

void MakeTimeTestSuite(cute::suite& aSuite)
{
    // aSuite += CUTE(GetTimeTestWrapper); // disabled as known bugs: https://gcc.gnu.org/bugzilla/show_bug.cgi?id=84216
    aSuite += CUTE(StrpTimeTestWrapper);
}

void GetTimeTestWrapper()
{
    std::tm tm1;
    std::list<std::string> fmt_list;
    initializeGetTimeTest(tm1, fmt_list);

    int numFail = GetTimeTest(tm1, fmt_list);
    int expectedNumFail = 0;
    ASSERT_EQUALM("Non-zero number of std::get_time failures.", expectedNumFail, numFail);
    return;
}

void StrpTimeTestWrapper()
{
    std::tm tm1;
    std::list<std::string> fmt_list;
    initializeGetTimeTest(tm1, fmt_list);

    int numFail = StrpTimeTest(tm1, fmt_list);
    int expectedNumFail = 0;
    ASSERT_EQUALM("Non-zero number of std::strptime failures.", expectedNumFail, numFail);
    return;
}


void initializeGetTimeTest(std::tm& aTmStruct,
                           std::list<std::string>& aFormatList)
{
    // tm1 content is exactly equivalent to std::localtime(&now) when std::time_t now = 1199294625;
    aTmStruct = {45, 23, 13, 2, 0, 108, 3, 1, 0};

    aFormatList.clear();

    std::list<std::string> fmt_list = {std::string("%Y %m %d %T"),
        std::string("%F %T"),
        std::string("%Y-%j %X %z"),
        std::string("%c %Z"),
        std::string("%x %r"),
        std::string("%Y-%m-%d %H:%M:%S"),
        std::string("%y-%m-%d %T"),
        std::string("%a %b %e %T %Z %Y")}; // US linux/OSX 'date' format
    aFormatList = fmt_list;
    return;
}

void runMainGetTimeTest()
{
    std::tm tm1;
    std::list<std::string> fmt_list;
    initializeGetTimeTest(tm1, fmt_list);

    std::cout << "Testing std::get_time() ---------------------------" << std::endl;
    int gettime_nfail = GetTimeTest(tm1, fmt_list);
    std::cout << "Testing strptime() --------------------------------" << std::endl;
    int strptime_nfail = StrpTimeTest(tm1, fmt_list);
    std::cout << "Results -------------------------------------------" << std::endl;
    std::cout << "  get_time fails to parse put_time output " << gettime_nfail << " times." << std::endl;
    std::cout << "  strptime fails to parse put_time output " << strptime_nfail << " times." << std::endl;
}

int GetTimeTest(const std::tm& tm1, const std::list<std::string>& fmt_list)
{
    // Test std::get_time can handle strings std::put_time produces
    int num_passes = 0;
    int num_fails = 0;
    int num_tm_inconsistencies = 0;
    std::list<std::string> fail_fmt_list; // List of failing formats
    std::list<std::string> pass_fmt_list; // List of passing formats
    int testNumber = 0;
    for (std::list<std::string>::const_iterator it = fmt_list.cbegin();
        it != fmt_list.cend(); ++it)
    {
        std::string date_format = *it;;
        std::cout << "#" << testNumber++ <<  ": Testing format: " << date_format << std::endl;
        std::stringstream ss;
        ss << std::put_time(&tm1, date_format.c_str());
        if (ss.fail())
        {
            std::cout << "  WARN: put_time parse sets stream fail bit." << std::endl;
            ss.clear();
        }
        std::string put_time_str = ss.str();
        std::cout << "  Result of put_time on tm1: " << put_time_str << std::endl;

        // Parse string representation using get_time into tm2, compare to tm1
        std::tm tm2 = {0, 0, 0, 0, 0, 0, 0, 0, 0};    
        ss >> std::get_time(&tm2, date_format.c_str());
        if (ss.fail())
        {
            std::cout << "  WARN: get_time parse sets stream fail bit." << std::endl;
        }
        if ( std::memcmp(&tm1, &tm2, sizeof(tm1)) != 0 )
        {
            std::cout << "  WARN: Struct from get_time, tm2!=tm1: " << TmDiff(tm1, tm2) << " Possible BUG?." << std::endl;
            num_tm_inconsistencies++;
        }
        else
        {
            std::cout << "  Struct from get_time, tm2==tm1. OK." << std::endl;
        }

        // Compare string representation of tm2 to that of tm1
        std::ostringstream oss;
        oss << std::put_time(&tm2, date_format.c_str());
        if (oss.fail())
        {
            std::cout << "  WARN: put_time parse sets stream fail bit." << std::endl;
        }
        std::string get_time_str = oss.str();
        std::cout << "  Result of put_time on tm2: " << get_time_str << std::endl;
        if (put_time_str.compare(get_time_str) != 0)
        {
            num_fails++;
            fail_fmt_list.push_back(date_format);
            std::cout << "  ERROR: String repr of get_time tm2 != string repr of tm1. BUG?." << std::endl;
        }
        else
        {
            num_passes++;
            pass_fmt_list.push_back(date_format);
            std::cout << "  OK: String repr of get_time tm2 == string repr of tm1." << std::endl;
        }
    }
    
    // Summary info
    std::cout << num_fails << " string comparison tests fail and " << num_passes << " pass." << std::endl;
    std::cout << "Input/output std::tm structs were inconsistent " << num_tm_inconsistencies << " times." << std::endl;
    std::cout << "Passing format strings:" << std::endl;
    for (std::list<std::string>::iterator it = pass_fmt_list.begin();
        it != pass_fmt_list.end(); ++it)
    {
        std::cout << *it << std::endl;
    }   
    if (num_fails)
    {
        std::cout << "Definitely failing format strings:" << std::endl;
        for (std::list<std::string>::iterator it = fail_fmt_list.begin();
            it != fail_fmt_list.end(); ++it)
        {
            std::cout << *it << std::endl;
        }   
    }
    return num_fails;
}


int StrpTimeTest(const std::tm& tm1, const std::list<std::string>& fmt_list)
{
    // Test if strptime can handle strings std::put_time produces
    int num_passes = 0;
    int num_fails = 0;
    int num_tm_inconsistencies = 0;
    std::list<std::string> fail_fmt_list; // List of failing formats
    std::list<std::string> pass_fmt_list; // List of passing formats
    int testNumber = 0;
    for (std::list<std::string>::const_iterator it = fmt_list.cbegin();
        it != fmt_list.cend(); ++it)
    {
        std::string date_format = *it;;
         std::cout << "#" << testNumber++ <<  ": Testing format: " << date_format << std::endl;
        std::stringstream ss;
        ss << std::put_time(&tm1, date_format.c_str());
        if (ss.fail())
        {
            std::cout << "  WARN: put_time parse sets stream fail bit." << std::endl;
            ss.clear();
        }
        std::string put_time_str = ss.str();
        std::cout << "  Result of put_time on tm1: " << put_time_str << std::endl;

        // Parse string representation using get_time into tm2, compare to tm1
        std::tm tm2 = {0, 0, 0, 0, 0, 0, 0, 0, 0};
        if (!strptime(put_time_str.c_str(),
                 date_format.c_str(),
                 &tm2))
        {
            std::cout << "  WARN: strptime parse yields non-zero return value." << std::endl;
        }
        if ( std::memcmp(&tm1, &tm2, sizeof(tm1)) != 0 )
        {
            std::cout << "  WARN: Struct from strptime, tm2!=tm1: " << TmDiff(tm1, tm2) << " Possible BUG?." << std::endl;
            num_tm_inconsistencies++;
        }
        else
        {
            std::cout << "  Struct from strptime, tm2==tm1. OK." << std::endl;
        }

        // Comparse string representation of tm2 to that of tm1
        std::ostringstream oss;
        oss << std::put_time(&tm2, date_format.c_str());
        if (oss.fail())
        {
            std::cout << "  WARN: put_time parse sets stream fail bit." << std::endl;
        }
        std::string get_time_str = oss.str();
        std::cout << "  Result of put_time on tm2: " << get_time_str << std::endl;
        if (put_time_str.compare(get_time_str) != 0)
        {
            num_fails++;
            fail_fmt_list.push_back(date_format);
            std::cout << "  ERROR: String repr of strptime tm2 != string repr of tm1. BUG?." << std::endl;
        }
        else
        {
            num_passes++;
            pass_fmt_list.push_back(date_format);
            std::cout << "  OK: String repr of strptime tm2 == string repr of tm1." << std::endl;
        }
    }
    
    // Summary info
    std::cout << num_fails << " string comparison tests fail and " << num_passes << " pass." << std::endl;
    std::cout << "Input/output std::tm structs were inconsistent " << num_tm_inconsistencies << " times." << std::endl;
    std::cout << "Passing format strings:" << std::endl;
    for (std::list<std::string>::iterator it = pass_fmt_list.begin();
        it != pass_fmt_list.end(); ++it)
    {
        std::cout << *it << std::endl;
    }   
    if (num_fails)
    {
        std::cout << "Definitely failing format strings:" << std::endl;
        for (std::list<std::string>::iterator it = fail_fmt_list.begin();
            it != fail_fmt_list.end(); ++it)
        {
            std::cout << *it << std::endl;
        }   
    }
    return num_fails;
}

std::string TmDiff(const std::tm& tm1, const std::tm& tm2)
{
    std::ostringstream ss;
    if ( std::memcmp(&tm1, &tm2, sizeof(tm1)) == 0 )
    {
        ss << "No differences between tm1 and tm2.";
    }
    else
    {
        if (tm1.tm_sec != tm2.tm_sec)
        {
            ss << "tm_sec{" << tm1.tm_sec << "," << tm2.tm_sec << "} ";
        }
        if (tm1.tm_min != tm2.tm_min)
        {
            ss << "tm_min{" << tm1.tm_min << "," << tm2.tm_min << "} ";
        }
        if (tm1.tm_hour != tm2.tm_hour)
        {
            ss << "tm_hour{" << tm1.tm_hour << "," << tm2.tm_hour << "} ";
        }
        if (tm1.tm_mday != tm2.tm_mday)
        {
            ss << "tm_mday{" << tm1.tm_mday << "," << tm2.tm_mday << "} ";
        }
        if (tm1.tm_mon != tm2.tm_mon)
        {
            ss << "tm_mon{" << tm1.tm_mon << "," << tm2.tm_mon << "} ";
        }
        if (tm1.tm_year != tm2.tm_year)
        {
            ss << "tm_year{" << tm1.tm_year << "," << tm2.tm_year << "} ";
        }
        if (tm1.tm_wday != tm2.tm_wday)
        {
            ss << "tm_wday{" << tm1.tm_wday << "," << tm2.tm_wday << "} ";
        }    
        if (tm1.tm_yday != tm2.tm_yday)
        {
            ss << "tm_yday{" << tm1.tm_yday << "," << tm2.tm_yday << "} ";
        }
        if (tm1.tm_isdst != tm2.tm_isdst)
        {
            ss << "tm_isdst{" << tm1.tm_isdst << "," << tm2.tm_isdst << "} ";
        }
    }
    return ss.str();
}

} // end namespace TEST
} // end namespace SPA
