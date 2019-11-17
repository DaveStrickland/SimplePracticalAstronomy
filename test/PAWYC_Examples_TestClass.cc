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
 * @file PAWYC_Examples_TestClass.cc
 * @brief Definition of the example functions
 * @ingroup group_examples
 *
 * @author Dave Strickland, <dave.strickland@gmail.com>
 *
 * @version Sep 2, 2018 dks : Initial coding 
 */

#include "PAWYC_Examples_TestClass.h"
#include "SpaTestUtilities.h"
#include "TimeUtilities.h"
#include "JulianDate.h"
#include "DateAndTime.h"
#include "TimeDifference.h"

namespace SPA
{
namespace TEST
{

PAWYC_Examples_TestClass::PAWYC_Examples_TestClass()
{
}

PAWYC_Examples_TestClass::~PAWYC_Examples_TestClass()
{
}

void PAWYC_Examples_TestClass::example2_DateOfEaster()
{
    int year = 2000;
    int month = 0;
    int day = 0;
    int expectedMonth = 4; // April
    int expectedDay = 23;
    SPA::TIME_UTIL::calculateEaster(year, month, day);
    ASSERT_EQUALM("Month for Easter in year 2000 does not match",
                  expectedMonth,
                  month);
    ASSERT_EQUALM("Day for Easter in year 2000 does not match",
                  expectedDay,
                  day);
}

void PAWYC_Examples_TestClass::example3_DayNumber()
{
    // Part 1: day of year for input day
    int year = 1985;
    int month = 2;
    int day = 17;
    int dayNumber = SPA::TIME_UTIL::calculateDayNumber(year, month, day);
    int expectedDayNumber = 48;
    ASSERT_EQUALM("Day number for 1985 Feb 17",
                  expectedDayNumber,
                  dayNumber);

    /* Part 2: elapsed days since epoch 1990 Jan 0.0
     *
     * This part is more difficult to do with DateAndTime,
     * as the intention is for users to use JulianDate for
     * time differences (because it works better). but we don't
     * want DateAndTime to depend on JulianDate, and re-implementing
     * a DateAndTime specific time difference function seems
     * wasteful (although certainly possible). It would also
     * be possible to come up with a clearer algorithm to
     * do it, but that is outside the scope of PAWYC.
     *
     * So instead I've chosen to illustrate a simple brute
     * force approach that should work but is clearly ugly
     * to use in practice. The point is that its just so
     * much easier to do with Julian Dates because they're
     * already a consecutive count of the number of days.
     */
    SPA::DateAndTime epoch1990(1990, 1, 0);
    SPA::DateAndTime date(year, month, day);

    double expectedDaysElapsed = -1778;
    double tolerance = 1.0e-9;
    double elapsed = 0;

    int startYear = date.getYear();
    int endYear = epoch1990.getYear();
    // Ignore general use, because we know endYear > startYear and
    // we're counting backwards...
    elapsed -= SPA::TIME_UTIL::calculateDayNumber(epoch1990.getYear(),
                                                  epoch1990.getMonth(),
                                                  epoch1990.getDay());
    for (int iYear = endYear - 1; iYear >= startYear; iYear--)
    {
        elapsed -= SPA::TIME_UTIL::daysInYear(iYear);
    }
    // Now correct for the number of days into startYear
    elapsed += SPA::TIME_UTIL::calculateDayNumber(date.getYear(),
                                                  date.getMonth(),
                                                  date.getDay());

    ASSERT_EQUAL_DELTAM("Days since epoch 1990 Jan 0.0 differs from expectation",
                        expectedDaysElapsed,
                        elapsed,
                        tolerance);
}

void PAWYC_Examples_TestClass::example4_JulianDate()
{
    double tolerance = 1.0e-6;
    int digits = 6;
    double expectedJulianDate = 2446113.75;
    SPA::JulianDate jd(1985, 2, 17, 6, 0, 0, 0);
    spaTestFloatingPointEqual("JulianDate for 1985-02-16 06:00:00 UT",
                              expectedJulianDate,
                              jd.getDecimalDays(),
                              tolerance,
                              digits);

    // Part 2: elapsed days since epoch 1990 Jan 0.0
    SPA::DateAndTime epoch1990(1990, 1, 0); // NB 00:00:00 UT
    SPA::DateAndTime date(1985, 2, 17); // NB 00:00:00 UT
    SPA::TimeDifference timeDifference = date - epoch1990;

    double expectedDaysElapsed = -1778;
    ASSERT_EQUAL_DELTAM("Days since epoch 1990 Jan 0.0 differs from expectation",
                        expectedDaysElapsed,
                        timeDifference.getDecimalDayDifference(),
                        tolerance);

}

void PAWYC_Examples_TestClass::example5_JulianDateToCalendarDate()
{
    double jdTolerance = 1.0e-4; // tolerance in fractional days

    /*
    * The Gregorian date corresponding to JD=2446113.75 is
    * 1985 February 17.25, i.e. 1985 02 17 06:00:00 UTC.
    */
    DateAndTime expectedDate(1985, 2, 17, 6, 0, 0, 0);
    JulianDate jd(2446113.75);
    DateAndTime outputDate = jd.getDateAndTime();

    // To check for approximate equivalence, we use Julian Dates
    // and time differences. This is non-circular because the
    // conversion to JD is independent of the conversion from JD
    // to DateAndTime.
    TimeDifference td = jd - JulianDate(outputDate);
    if ( std::fabs(td.getDecimalDayDifference()) > jdTolerance)
    {
        std::ostringstream ss;
        ss << "1b. Conversion from JD to DateAndTime incorrect: ";
        ss << " Input date=" << expectedDate
           << ", Output date=" << outputDate
           << ", difference=" << td.getDecimalDayDifference()
           << " days, which exceeds test tolerance=" << jdTolerance;
        FAILM(ss.str());
    }
    return;
}

void PAWYC_Examples_TestClass::example6_DayOfWeek()
{
    // This is a much simpler version of the better tests in
    // TimeUtilities_TestClass::testCalculateDayInTheWeek().
    
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
    return;
}

} /* namespace TEST */
} /* namespace SPA */
