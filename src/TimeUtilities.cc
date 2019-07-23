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
 * @file TimeUtilities.cc
 * @brief Definitions of TimeUtilities function
 * @ingroup group_time
 *
 * @author Dave Strickland, <dave.strickland@gmail.com>
 *
 * @version Sep 2, 2018 dks : Initial coding 
 */

#include "TimeUtilities.h"
#include "SpaTimeConstants.h"
#include "DateAndTime.h"
#include "JulianDate.h"

#include <cmath>
#include <iostream>

namespace SPA
{
namespace TIME_UTIL
{

void integerAndFraction(double aRealNumber,
                        double& anIntegerPart,
                        double& aFractionalPart)
{
    anIntegerPart = std::floor(aRealNumber);
    aFractionalPart = aRealNumber - anIntegerPart;
    return;
}

void quotientAndRemainder(int aDividend,
                          int aDivisor,
                          int& aQuotient,
                          int& aRemainder)
{
    /*
     * Implementation note: std::ldiv in cstdlib performs
     * the same calculation, potentially using a single CPU
     * operation. Unpacking a std::div_t object is a bit of
     * a pain, so I've chosen to both use my own function
     * and expose the logic here.
     */
    aQuotient = aDividend / aDivisor;
    aRemainder = aDividend % aDivisor;
}

void calculateEaster(int aYear,
                     int &aMonth,
                     int &aDay)
{
    aMonth = 0;
    aDay = 0;

    // There are so many unexplained magic numbers in this algorithm
    // that I only bothered declaring two...
    constexpr int YEAR_DIVISOR = 19;
    constexpr int YEARS_IN_CENTURY = 100;

    int dummy_value; // Not used
    int a_const = 0;
    int b_const = 0;
    int c_const = 0;
    int d_const = 0;
    int e_const = 0;
    int f_const = 0;
    int g_const = 0;
    int h_const = 0;
    int i_const = 0;
    int k_const = 0;
    int l_const = 0;
    int m_const = 0;
    int n_const = 0;
    int p_const = 0;

    // Step 1
    quotientAndRemainder(aYear, YEAR_DIVISOR,
                         dummy_value, a_const);

    // Step 2
    quotientAndRemainder(aYear, YEARS_IN_CENTURY,
                         b_const, c_const);

    // Step 3
    quotientAndRemainder(b_const, 4,
                         d_const, e_const);

    // Step 4
    int step4_input = (b_const + 8);
    quotientAndRemainder(step4_input, 25,
                         f_const, dummy_value);

    // Step 5
    int step5_input = b_const  - f_const + 1;
    quotientAndRemainder(step5_input, 3,
                         g_const, dummy_value);

    // Step 6.
    int step6_input = (19 * a_const) + b_const - d_const - g_const + 15;
    quotientAndRemainder(step6_input, 30,
                         dummy_value, h_const);

    // Step 7.
    quotientAndRemainder(c_const, 4,
                         i_const, k_const);

    // Step 8.
    int step8_input = 32 + 2*(e_const + i_const) - h_const - k_const;
    quotientAndRemainder(step8_input, 7,
                         dummy_value, l_const);

    // Step 9
    int step9_input = a_const + (11 * h_const) + (22 * l_const);
    quotientAndRemainder(step9_input, 451,
                         m_const, dummy_value);

    // Step 10
    int step10_input = h_const + l_const - (7 * m_const) + 114;
    quotientAndRemainder(step10_input, 31,
                         n_const, p_const);

    aMonth = n_const;
    aDay = p_const + 1;
    return;
}

int calculateDayNumber(int aYear,
                       int aMonth,
                       int aDay)
{
    int multiplicand = 63; // Magic number?
    int dayNumber = 0;
    if ( isLeapYear(aYear) )
    {
        multiplicand -= 1;
    }

    if (aMonth > FEB)
    {
        dayNumber = int(SPA_AVG_DAYS_PER_MONTH * (aMonth + 1));
        dayNumber -= multiplicand;
    }
    else
    {
        dayNumber = int((aMonth - 1) * multiplicand / 2);
    }
    return dayNumber + aDay;
}

bool isLeapYear(int aYear)
{
    return ((aYear % 4) == 0) &&
           ( ((aYear % 100) != 0) ||
             ((aYear % 400) == 0) );
}

WeekDays calculateDayInTheWeek(const JulianDate& aJulianDate)
{
    // TODO
    WeekDays wd = MON;
    return wd;
}

WeekDays calculateDayInTheWeek(const DateAndTime& aDateAndTime)
{
    JulianDate jd(aDateAndTime);
    return calculateDayInTheWeek(jd);
}

WeekDays calculateDayInTheWeek(int aYear,
                               int aMonth,
                               int aDay)
{
    DateAndTime date(aYear, aMonth, aDay);
    return calculateDayInTheWeek(date);
}

int daysInYear(int aYear)
{
    if (isLeapYear(aYear))
    {
        return SPA::SPA_DAYS_IN_NONLEAP_YEAR + 1;
    }
    else
    {
        return SPA::SPA_DAYS_IN_NONLEAP_YEAR;
    }
}

double calculateDecimalHours(int anHour,
                             int aMinute,
                             double aSeconds)
{
    double decimalHours = double(anHour) + 
                          double(aMinute)/double(SPA_MINUTES_IN_HOUR) +
                          double(aSeconds)/double(SPA_SECONDS_IN_HOUR);
    return decimalHours;
}

void calculateHoursMinutesAndSeconds(double aDecimalHours,
                                     int& anHours,
                                     int& aMinutes,
                                     double& aSeconds)
{
    double int_hours = std::trunc(aDecimalHours); // trunctated to lowest int
    double mins = double(SPA_MINUTES_IN_HOUR) * (aDecimalHours - int_hours);
    double int_min = std::trunc(mins);
    aSeconds = double(SPA_SECONDS_IN_MINUTE) * (mins - int_min);
    aMinutes = int(int_min);
    anHours  = int(int_hours);
    return;
}

} // end namespace TIME_UTIL
} /* namespace SPA */
