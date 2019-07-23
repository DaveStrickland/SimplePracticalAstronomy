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
 * @file JulianDate.cc
 * @brief Definition of JulianDate class.
 * @ingroup group_time
 *
 * @author Dave Strickland <dstrickland@gmail.com>
 *
 * @version Aug 25, 2018 dks : Initial coding
 */

#include "JulianDate.h"
#include "DateAndTime.h"
#include "TimeUtilities.h"
#include "SpaTimeConstants.h"
#include "TimeDifference.h"

namespace SPA
{

JulianDate::JulianDate() : theJulianDays(0)
{
}

JulianDate::JulianDate(double aDecimalDays) : theJulianDays(aDecimalDays)
{
}

JulianDate::JulianDate(int aYear,
                       int aMonth,
                       int aDay,
                       int anHours,
                       int aMinutes,
                       double aSeconds,
                       double aUTC_OffsetHours)
{
    SPA::DateAndTime dateAndTime(aYear,
                                 aMonth,
                                 aDay,
                                 anHours,
                                 aMinutes,
                                 aSeconds,
                                 aUTC_OffsetHours);
    theJulianDays = convertDateAndTimeToJulianDate(dateAndTime);
}

JulianDate::JulianDate(const SPA::DateAndTime& aDateAndTime)
{
    theJulianDays = convertDateAndTimeToJulianDate(aDateAndTime);
}

double JulianDate::convertDateAndTimeToJulianDate(const SPA::DateAndTime& aDateAndTime)
{
    double jd = 0;
    DateAndTime dateAndTime(aDateAndTime); // need a modifiable copy

    // Is date >= 1582-10-15 (i.e. Gregorian calendar)?
    // Do this first as we mess with the year/month...
    DateAndTime gregorian(1582, 10, 15, 0, 0, 0, 0);
    bool isGregorian = dateAndTime > gregorian;

    if (dateAndTime.getMonth() < MAR)
    {
        dateAndTime.setYear(dateAndTime.getYear() - 1);
        dateAndTime.setMonth(dateAndTime.getMonth() + 12);
    }

    int b_const = 0;
    if (isGregorian)
    {
        const int CENTURY = 100;
        int a_const = int(dateAndTime.getYear() / CENTURY);
        b_const = 2 - a_const + int(a_const / 4); // Why 4?
    }

    const double MYSTERIOUS_CONSTANT_1 = 0.75;
    double c_tmp = SPA_DAYS_IN_JULIAN_YEAR * dateAndTime.getYear();
    int c_const = 0;
    if (dateAndTime.getYear() < 0)
    {
        c_const = int(c_tmp - MYSTERIOUS_CONSTANT_1);
    }
    else
    {
        c_const = int(c_tmp);
    }

    int d_const = int(SPA_AVG_DAYS_PER_MONTH * (dateAndTime.getMonth() + 1));

    const double BASE_JD = 1720994.5; // where does this come from?
    jd = double(b_const + c_const + d_const + dateAndTime.getDay()) + dateAndTime.getDayFraction() + BASE_JD;
    return jd;
}

JulianDate& JulianDate::operator-=(const TimeDifference& aTimeDifference)
{
    theJulianDays -= aTimeDifference.getDecimalDayDifference();
    return *this;
}

JulianDate& JulianDate::operator+=(const TimeDifference& aTimeDifference)
{
    theJulianDays += aTimeDifference.getDecimalDayDifference();
    return *this;
}

JulianDate JulianDate::operator-(const TimeDifference& aTimeDifference)
{
    return JulianDate(theJulianDays - aTimeDifference.getDecimalDayDifference());
}

JulianDate JulianDate::operator+(const TimeDifference& aTimeDifference)
{
    return JulianDate(theJulianDays + aTimeDifference.getDecimalDayDifference());
}

TimeDifference operator-(const JulianDate& aLHS_JulianDate, const JulianDate& aRHS_JulianDate)
{
    return TimeDifference(aLHS_JulianDate.getDecimalDays() - aRHS_JulianDate.getDecimalDays());
}

double JulianDate::getModifiedJulianDate() const
{
    return theJulianDays - SPA_MJD_EPOCH;
}

DateAndTime JulianDate::getDateAndTime() const
{
    /*
     * Note: SPA_AVG_DAYS_PER_MONTH is used instead of 30.6001 because
     * that value was a workaround for the floating point math
     * limitations of older calculators. The algorithm works correctly
     * with SPA_AVG_DAYS_PER_MONTH on computers with ieee754 math.
     */

    // onstants of unknown origin used in this routine.
    const double constantC = 1524;
    const double constantD = 122.1;
    const double constantMonth = 13.5;
    const double constantYear = 2.5;

    double valueI; // I to start off with
    double valueF; // F.
    TIME_UTIL::integerAndFraction(theJulianDays + 0.5,
                                  valueI,
                                  valueF);

    double intPart;
    double fracPart;
    double tempVal;

    double valueA;
    double valueB;
    if (valueI >= SPA_LAST_DAY_OF_JULIAN_CALENDAR) // Assume >= not >
    {
        tempVal = (valueI - SPA_JULIAN_CONVERSION_CONVERSION_CONST)
                        / SPA_DAYS_IN_GREGORIAN_CENTURY;
        TIME_UTIL::integerAndFraction(tempVal, valueA, fracPart); // A
        tempVal = 0.25 * valueA; // 0.25*A
        TIME_UTIL::integerAndFraction(tempVal, intPart, fracPart);
        valueB = valueI + 1 + valueA - intPart; // B
    }
    else
    {
        valueB = valueI;
    }

    double valueC = valueB + constantC;

    double valueD;
    tempVal  = (valueC - constantD) / SPA_DAYS_IN_JULIAN_YEAR;
    TIME_UTIL::integerAndFraction(tempVal, valueD, fracPart);

    double valueE;
    tempVal = SPA_DAYS_IN_JULIAN_YEAR  * valueD;
    TIME_UTIL::integerAndFraction(tempVal, valueE, fracPart);

    double valueG;
    tempVal = (valueC - valueE) / SPA_AVG_DAYS_PER_MONTH;
    TIME_UTIL::integerAndFraction(tempVal, valueG, fracPart);

    // Calculate the decimal days "d"
    double decimalDays;
    tempVal = SPA_AVG_DAYS_PER_MONTH * valueG;
    TIME_UTIL::integerAndFraction(tempVal, intPart, fracPart);
    decimalDays = valueC - valueE + valueF - intPart;

    // Conversion to days, hours, minutes, seconds.
    TIME_UTIL::integerAndFraction(decimalDays, intPart, fracPart);
    int days = int(intPart);
    double decimalHours = fracPart * SPA_HOURS_IN_DAY;
    int hours;
    int minutes;
    double seconds;
    TIME_UTIL::calculateHoursMinutesAndSeconds(decimalHours,
                                               hours,
                                               minutes,
                                               seconds);

    int month;
    if (valueG < constantMonth)
    {
        month = int(valueG) - 1;
    }
    else
    {
        month = int(valueG) - 13;
    }

    int year;
    if (month > constantYear)
    {
        year = int(valueD) - 4716;
    }
    else
    {
        year = int(valueD) - 4715;
    }

    return SPA::DateAndTime(year, month, days, hours, minutes, seconds, 0);
}

} /* namespace SPA */

