/*
 * Copyright (C) 2018 David Strickland, <dave.strickland@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file TimeUtilities_TestClass.cc
 * @brief Definition of TimeUtilities_TestClass functions
 * @ingroup group_test
 *
 * @author Dave Strickland, <dave.strickland@gmail.com>
 *
 * @version Sep 2, 2018 dks : Initial coding 
 */

#include "TimeUtilities_TestClass.h"
#include "TimeUtilities.h"
#include "DateAndTime.h"
#include "JulianDate.h"

#include <array>
#include <sstream>
#include <iostream>
#include <string>
#include <map>
#include <utility>

namespace SPA
{
namespace TEST
{

void TimeUtilities_TestClass::testCalculateEaster()
{
    /*
     * These tests include the earliest (in the year) and latest dates of Easter,
     * and are taken from https://en.wikipedia.org/wiki/List_of_dates_for_Easter
     */
    const int NTESTS = 7;
    constexpr std::array<int, NTESTS> inputYears =  {1818, 1943, 1998, 2000, 2009, 2016, 2029};
    constexpr std::array<int, NTESTS> easterMonth = {3,    4,    4,    4,    4,    3,    4};
    constexpr std::array<int, NTESTS> easterDay =   {22,   25,   12,   23,   12,   27,   1};

    std::ostringstream ss;
    int month = 0;
    int day = 0;
    for (int iTest = 0; iTest < NTESTS; iTest++)
    {
        SPA::TIME_UTIL::calculateEaster(inputYears[iTest], month, day);

        if ( (easterMonth[iTest] != month) || (easterDay[iTest] != day) )
        {
            ss << "  Test " << iTest << " for year=" << inputYears[iTest]
               << " expect Easter on " << easterMonth[iTest] << "/" << easterDay[iTest]
               << " but got " << month << "/" << day;
            FAILM(ss.str());
            ss.str(std::string());
        } // end if
    } // end for iTest
}

void TimeUtilities_TestClass::testIntegerAndFraction()
{
    double tolerance = 1.0e-16; // Test tolerance.

    // 1. 1.5 => 1.0, 0.5
    double real1 = 1.5;
    double expectedIntPart1 = 1.0;
    double expectedFracPart1 = 0.5;
    double intPart1;
    double fracPart1;
    SPA::TIME_UTIL::integerAndFraction(real1,
                                       intPart1,
                                       fracPart1);
    ASSERT_EQUAL_DELTAM("1. Incorrect integer part.",
                        expectedIntPart1,
                        intPart1,
                        tolerance);
    ASSERT_EQUAL_DELTAM("1. Incorrect fractional part.",
                            expectedFracPart1,
                            fracPart1,
                            tolerance);

    // 2. -3.25 => -4.0, 0.75
    double real2 = -3.25;
    double expectedIntPart2 = -4.0;
    double expectedFracPart2 = 0.75;
    double intPart2;
    double fracPart2;
    SPA::TIME_UTIL::integerAndFraction(real2,
                                       intPart2,
                                       fracPart2);
    ASSERT_EQUAL_DELTAM("2. Incorrect integer part.",
                        expectedIntPart2,
                        intPart2,
                        tolerance);
    ASSERT_EQUAL_DELTAM("2. Incorrect fractional part.",
                            expectedFracPart2,
                            fracPart2,
                            tolerance);
    return;
}

void TimeUtilities_TestClass::testIsLeapYear()
{
    std::ostringstream ss;
    const int NUM_TESTS = 6;
    std::array<int, NUM_TESTS> inputYears = {1900, 1999, 2000, 2001, 2004, 2100};
    std::array<bool, NUM_TESTS> expected = {false, false, true, false, true, false};
    for (int iTest = 0; iTest < NUM_TESTS; iTest++)
    {
        bool isLeap = SPA::TIME_UTIL::isLeapYear(inputYears[iTest]);
        ss << "  Test " << iTest << " year=" << inputYears[iTest]
           << " expectedIsLeapYear=" << expected[iTest]
           << ", got isLeapYear=" << isLeap;
        if (isLeap !=  expected[iTest])
        {
            FAILM(ss.str());
        }
        ss.str(std::string()); // clear ss
    }
    return;
}

void TimeUtilities_TestClass::testCalculateDayNumber()
{
    std::ostringstream ss;
    const int NUM_TESTS = 2;
    std::array<int, NUM_TESTS> iYears = {1985, 2018};
    std::array<int, NUM_TESTS> iMonth = {2, 9};
    std::array<int, NUM_TESTS> iDay   = {17, 2};
    std::array<int, NUM_TESTS> expectedDayNumber = {48, 245};
    for (int iTest = 0; iTest < NUM_TESTS; iTest++)
    {
        int year  = iYears[iTest];
        int month = iMonth[iTest];
        int day   = iDay[iTest];
        int expected = expectedDayNumber[iTest];

        int oDayNum = SPA::TIME_UTIL::calculateDayNumber(year, month, day);
        ss << "  Test " << iTest << " year=" << year
           << " month=" << month
           << " day=" << day
           << " expectedDayNumber=" << expected
           << ", got dayNumber=" << oDayNum;
        if (oDayNum !=  expected)
        {
            FAILM(ss.str());
        }
        ss.str(std::string()); // clear ss
    }
    return;
}

void TimeUtilities_TestClass::testCalculateBCE_Year()
{
    std::ostringstream ss;
    const int NUM_TESTS = 4;
    std::array<int, NUM_TESTS> iBCE_Years = {-10, 1, 10, 4713};
    std::array<int, NUM_TESTS> expectedYears = {0, 0, -9, -4712};
    for (int iTest = 0; iTest < NUM_TESTS; iTest++)
    {
        int bce_year = iBCE_Years[iTest];
        int expected = expectedYears[iTest];

        int oYear = SPA::TIME_UTIL::convertBCE_Year(bce_year);
        ss << "  Test " << iTest << " bce_year=" << bce_year
           << " expectedYear=" << expected
           << ", got year=" << oYear;
        if (oYear !=  expected)
        {
            FAILM(ss.str());
        }
        ss.str(std::string()); // clear ss
    }
    return;
}


void TimeUtilities_TestClass::testCalculateDayInTheWeek()
{
    // 1. Example from Section 6 of PAWYC, using all three
    // overloaded functions.
    int year = 1985;
    int month = 2;
    int day = 17;
    WeekDays expectedWeekDay1 = SUN;
    DateAndTime dt1(year, month, day);
    JulianDate jd1(dt1);
    WeekDays wd_jd1 = SPA::TIME_UTIL::calculateDayInTheWeek(jd1);
    WeekDays wd_dt1 = SPA::TIME_UTIL::calculateDayInTheWeek(dt1);
    WeekDays wd_ymd1 = SPA::TIME_UTIL::calculateDayInTheWeek(year, month, day);

    double expectedJulianDate = 2446113.5;
    double tolerance = 1.0e-6;
    ASSERT_EQUAL_DELTAM("1a. JulianDate from DateAndTime is incorrect",
                        expectedJulianDate,
                        jd1.getDecimalDays(),
                        tolerance);
    ASSERT_EQUALM("1b. calculateDayInTheWeek failed with JulianDate input",
                  static_cast<int>(expectedWeekDay1),
                  static_cast<int>(wd_jd1));
    ASSERT_EQUALM("1c. calculateDayInTheWeek failed with DateAndTime input",
                  static_cast<int>(expectedWeekDay1),
                  static_cast<int>(wd_dt1));
    ASSERT_EQUALM("1d. calculateDayInTheWeek failed with year/month/day input",
                  static_cast<int>(expectedWeekDay1),
                  static_cast<int>(wd_ymd1));

    // 2. Test a full (contiguous) week.
    year = 1933;
    month = 11;
    day = 19;
    int expectedWeekDay2 = 0; // SUN
    for (; expectedWeekDay2 < 7; expectedWeekDay2++)
    {
        WeekDays wd2 = SPA::TIME_UTIL::calculateDayInTheWeek(year, month, day);
        int intWeekDay = static_cast<int>(wd2);
        if (expectedWeekDay2 != intWeekDay)
        {
            std::ostringstream ss;
            ss << "For " << year << "-" << month << "-" << day
               << " calculateDayInTheWeek returns " << wd2
               << " instead of " << static_cast<WeekDays>(expectedWeekDay2);
            FAILM(ss.str());
        }
        day++;
    }

    // Example 3, fractions of a day.
    // 3a. Monday 2018-09-24 14:24:16 utc is JD=2458386.10018519
    // 3b. Tuesday 2018-09-24 02:24:16 UTC is 2458386.60018519
    WeekDays expectedWeekDay3a = MON;
    JulianDate jd3a(2458386.10018519);
    WeekDays wd_jd3a = SPA::TIME_UTIL::calculateDayInTheWeek(jd3a);
    ASSERT_EQUALM("3a. calculateDayInTheWeek failed with JulianDate input",
                   static_cast<int>(expectedWeekDay3a),
                   static_cast<int>(wd_jd3a));
    WeekDays expectedWeekDay3b = TUE;
    JulianDate jd3b(2458386.60018519);
    WeekDays wd_jd3b = SPA::TIME_UTIL::calculateDayInTheWeek(jd3b);
    ASSERT_EQUALM("3b. calculateDayInTheWeek failed with JulianDate input",
                   static_cast<int>(expectedWeekDay3b),
                   static_cast<int>(wd_jd3b));
    return;
}

void TimeUtilities_TestClass::testQuotientAndRemainder()
{
    // 1a. 100/20 = 5,0
    int dividend1 = 100;
    int divisor1 = 20;
    int expectedQuotient1 = 5;
    int expectedRemainder1 = 0;
    int quotient1;
    int remainder1;
    SPA::TIME_UTIL::quotientAndRemainder(dividend1,
                                         divisor1,
                                         quotient1,
                                         remainder1);
    ASSERT_EQUALM("1a. Incorrect quotient",
                  expectedQuotient1,
                  quotient1);
    ASSERT_EQUALM("1a. Incorrect remainder",
                      expectedRemainder1,
                      remainder1);

    // 1b. 103/20 = 5,3
    dividend1 = 103;
    expectedRemainder1 = 3;
    SPA::TIME_UTIL::quotientAndRemainder(dividend1,
                                         divisor1,
                                         quotient1,
                                         remainder1);
    ASSERT_EQUALM("1b. Incorrect quotient",
                  expectedQuotient1,
                  quotient1);
    ASSERT_EQUALM("1b. Incorrect remainder",
                      expectedRemainder1,
                      remainder1);

    // 2. -23/4 = -5,-3
    int dividend2 = -23;
    int divisor2 = 4;
    int expectedQuotient2 = -5;
    int expectedRemainder2 = -3;
    int quotient2;
    int remainder2;
    SPA::TIME_UTIL::quotientAndRemainder(dividend2,
                                         divisor2,
                                         quotient2,
                                         remainder2);
    ASSERT_EQUALM("2. Incorrect quotient",
                  expectedQuotient2,
                  quotient2);
    ASSERT_EQUALM("2. Incorrect remainder",
                      expectedRemainder2,
                      remainder2);

    // 3. -17/-4 = 4,-1
    int dividend3 = -17;
    int divisor3 = -4;
    int expectedQuotient3 = 4;
    int expectedRemainder3 = -1;
    int quotient3;
    int remainder3;
    SPA::TIME_UTIL::quotientAndRemainder(dividend3,
                                         divisor3,
                                         quotient3,
                                         remainder3);
    ASSERT_EQUALM("3. Incorrect quotient",
                  expectedQuotient3,
                  quotient3);
    ASSERT_EQUALM("3. Incorrect remainder",
                      expectedRemainder3,
                      remainder3);

    return;
}

void TimeUtilities_TestClass::testCalculateDecimalHours()
{
    using namespace TIME_UTIL;
    double tolerance = 1.0e-12;
    
    // 1. 1h 30m 00s -> 1.5
    int hours = 1;
    int minutes = 30;
    double seconds = 0;
    double expectedDecimalHours = 1.5;
    double decimalHours = calculateDecimalHours(hours, minutes, seconds);
    ASSERT_EQUAL_DELTAM("1. Decimal hours incorrect.",
                         expectedDecimalHours,
                         decimalHours,
                         tolerance);
                         
    // 2. 3h -50m 300s -> 2.25
    hours = 3;
    minutes = -50;
    seconds = 300;
    expectedDecimalHours = 2.25;
    decimalHours = calculateDecimalHours(hours, minutes, seconds);
    ASSERT_EQUAL_DELTAM("2. Decimal hours incorrect.",
                         expectedDecimalHours,
                         decimalHours,
                         tolerance);
        
    // 3. -4h -30m -1800s -> -5.00
    hours = -4;
    minutes = -30;
    seconds = -1800;
    expectedDecimalHours = -5;
    decimalHours = calculateDecimalHours(hours, minutes, seconds);
    ASSERT_EQUAL_DELTAM("3. Decimal hours incorrect.",
                         expectedDecimalHours,
                         decimalHours,
                         tolerance);
    return;
}

void TimeUtilities_TestClass::testCalculateHoursMinutesAndSeconds()
{
    using namespace TIME_UTIL;
    double tolerance = 1.0e-9; // 1ns
    int precision = 9;
    int outputHours;
    int outputMinutes;
    double outputSeconds;
    
    // 1. 1.5 hours-> 1h30m00s
    int expectedHours = 1;
    int expectedMinutes = 30;
    double expectedSeconds = 0;
    double inputDecimalHours = 1.5;
    calculateHoursMinutesAndSeconds(inputDecimalHours, 
                                    outputHours, 
                                    outputMinutes, 
                                    outputSeconds);
    if ( ! hoursMinutesSecondsMatch(expectedHours,
                                    expectedMinutes,
                                    expectedSeconds,
                                    outputHours,
                                    outputMinutes,
                                    outputSeconds,
                                    tolerance) )
    {
        std::ostringstream ss;
        ss << "HMS differ: expected={" 
           << expectedHours << ":" << expectedMinutes 
           << ":" << std::fixed<< std::setprecision(precision) << expectedSeconds << "}"
           << " actual={" << outputHours << ":" << outputMinutes 
           << ":" << std::fixed<< std::setprecision(precision) << outputSeconds << "}";
        FAILM(ss.str());
    }
                         
    // 2. 2.25 hours -> 2h15m00s
    expectedHours = 2;
    expectedMinutes = 15;
    expectedSeconds = 0;
    inputDecimalHours = 2.25;
    calculateHoursMinutesAndSeconds(inputDecimalHours, 
                                    outputHours, 
                                    outputMinutes, 
                                    outputSeconds);
    if ( ! hoursMinutesSecondsMatch(expectedHours,
                                    expectedMinutes,
                                    expectedSeconds,
                                    outputHours,
                                    outputMinutes,
                                    outputSeconds,
                                    tolerance) )
    {
        std::ostringstream ss;
        ss << "HMS differ: expected={" 
           << expectedHours << ":" << expectedMinutes 
           << ":" << std::fixed<< std::setprecision(precision) << expectedSeconds << "}"
           << " actual={" << outputHours << ":" << outputMinutes 
           << ":" << std::fixed<< std::setprecision(precision) << outputSeconds << "}";
        FAILM(ss.str());
    }
        
    // 3. -5.11 hours -> -5h06m36s
    expectedHours = -5;
    expectedMinutes = -6;
    expectedSeconds = -36;
    inputDecimalHours = -5.11;
    calculateHoursMinutesAndSeconds(inputDecimalHours, 
                                    outputHours, 
                                    outputMinutes, 
                                    outputSeconds);
    if ( ! hoursMinutesSecondsMatch(expectedHours,
                                    expectedMinutes,
                                    expectedSeconds,
                                    outputHours,
                                    outputMinutes,
                                    outputSeconds,
                                    tolerance) )
    {
        std::ostringstream ss;
        ss << "HMS differ: expected={" 
           << expectedHours << ":" << expectedMinutes 
           << ":" << std::fixed<< std::setprecision(precision) << expectedSeconds << "}"
           << " actual={" << outputHours << ":" << outputMinutes 
           << ":" << std::fixed<< std::setprecision(precision) << outputSeconds << "}";
        FAILM(ss.str());
    }
    
    return;
}

bool TimeUtilities_TestClass::hoursMinutesSecondsMatch(int anHoursA,
                                                       int aMinutesA,
                                                       double aSecondsA,
                                                       int anHoursB,
                                                       int aMinutesB,
                                                       double aSecondsB,
                                                       double aSecondsTolerance)
{
    if (anHoursA != anHoursB)
    {
        return false;
    }
    if (aMinutesA != aMinutesB)
    {
        return false;
    }
    double absDiff = std::fabs(aSecondsA - aSecondsB);
    if (absDiff > aSecondsTolerance)
    {
        return false;
    }
    return true;
}

void TimeUtilities_TestClass::testTimeEnumerationOstream()
{
    // Construct map of values and expected outputs.
    std::map<SPA::WeekDays, std::string> weekDayMap;
    weekDayMap.insert( std::make_pair(SUN, std::string("SUN")) );
    weekDayMap.insert( std::make_pair(SUN, std::string("MON")) );
    weekDayMap.insert( std::make_pair(SUN, std::string("TUE")) );
    weekDayMap.insert( std::make_pair(SUN, std::string("WED")) );
    weekDayMap.insert( std::make_pair(SUN, std::string("THU")) );
    weekDayMap.insert( std::make_pair(SUN, std::string("FRI")) );
    weekDayMap.insert( std::make_pair(SUN, std::string("SAT")) );
    
    // Iterate over map
    std::ostringstream ss;
    for (auto itr = weekDayMap.cbegin(); itr != weekDayMap.cend(); itr++)
    {
        SPA::WeekDays wd = itr->first;
        std::string expected = itr->second;
        ss << wd; // TODO: Find why this is mot working
        std::string output = ss.str();
        ss.str(std::string());
        ASSERT_EQUALM("Stream output for input weekday is incorrect.",
            expected,
            output);
    }
    return;
}


} /* namespace TEST */
} /* namespace SPA */
