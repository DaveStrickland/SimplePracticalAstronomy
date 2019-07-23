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
 * @file DateAndTime.cc
 * @brief Definitions of the DateAndTime class
 * @ingroup group_time
 *
 * @author Dave Strickland, <dave.strickland@gmail.com>
 *
 * @version Sep 1, 2018 dks : Initial coding 
 */

#include "DateAndTime.h"
#include "SpaTimeConstants.h"

namespace SPA
{

DateAndTime::DateAndTime() : theYear(0),
                theMonth(0),
                theDay(0),
                theHours(0),
                theMinutes(0),
                theSeconds(0),
                theUTC_OffsetHours(0)
{
}

DateAndTime::DateAndTime(int aYear,
                         int aMonth,
                         int aDay,
                         int anHours,
                         int aMinutes,
                         double aSeconds,
                         double aUTC_OffsetHours) : theYear(aYear),
                                         theMonth(aMonth),
                                         theDay(aDay),
                                         theHours(anHours),
                                         theMinutes(aMinutes),
                                         theSeconds(aSeconds),
                                         theUTC_OffsetHours(aUTC_OffsetHours)

{
}

void DateAndTime::setDay(int aDay)
{
    theDay = aDay;
}

void DateAndTime::setHours(int anHours)
{
    theHours = anHours;
}

void DateAndTime::setMinutes(int aMinutes)
{
    theMinutes = aMinutes;
}

void DateAndTime::setMonth(int aMonth)
{
    theMonth = aMonth;
}

void DateAndTime::setSeconds(double aSeconds)
{
    theSeconds = aSeconds;
}

void DateAndTime::setUtcOffsetHours(double aUTC_OffsetHours)
{
    theUTC_OffsetHours = aUTC_OffsetHours;
}

void DateAndTime::setYear(int aYear)
{
    theYear = aYear;
}

double DateAndTime::getDayFraction() const
{
    double dayFraction = double(theHours) / double(SPA_HOURS_IN_DAY)
                    + double(theMinutes) / double(SPA_MINUTES_IN_DAY)
                    + theSeconds / double(SPA_SECONDS_IN_DAY);
    // Now offset by UTC correction
    dayFraction += theUTC_OffsetHours / double(SPA_HOURS_IN_DAY);
    return dayFraction;
}

bool operator==(const DateAndTime& aLHS,
                const DateAndTime& aRHS)
{
    if (aLHS.theYear != aRHS.theYear)
    {
        return false;
    }
    if (aLHS.theMonth != aRHS.theMonth)
    {
        return false;
    }

    if (aLHS.theDay != aRHS.theDay)
    {
        return false;
    }

    if (aLHS.theHours != aRHS.theHours)
    {
        return false;
    }

    if (aLHS.theMinutes != aRHS.theMinutes)
    {
        return false;
    }

    if (aLHS.theSeconds != aRHS.theSeconds)
    {
        return false;
    }

    if (aLHS.theUTC_OffsetHours != aRHS.theUTC_OffsetHours)
    {
        return false;
    }

    return true;
}

bool operator<(const DateAndTime& aLHS,
               const DateAndTime& aRHS)
{
    // Year comparison
    if (aLHS.theYear < aRHS.theYear)
    {
        return true;
    }
    else if (aLHS.theYear > aRHS.theYear)
    {
        return false;
    }
    else
    {
        // Same year, check month
        if (aLHS.theMonth < aRHS.theMonth)
        {
            return true;
        }
        else if (aLHS.theMonth > aRHS.theMonth)
        {
            return false;
        }
        else
        {
            // Same month, check day
            if (aLHS.theDay < aRHS.theDay)
            {
                return true;
            }
            else if (aLHS.theDay > aRHS.theDay)
            {
                return false;
            }
            else
            {
                // Same day, check day fraction which is UTC corrected
                double lhsDayFrac = aLHS.getDayFraction();
                double rhsDayFrac = aRHS.getDayFraction();
                if (lhsDayFrac < rhsDayFrac)
                {
                    return true;
                }
                else
                {
                    return false;
                } // end if dayFrac
            } // end if day
        } // end if month
    } // end if year

    return true;
}

} /* namespace SPA */

std::ostream& operator<<(std::ostream& os,
                         const SPA::DateAndTime& aDateAndTime)
{
    os << "DateAndTime{";
    os << " theYear=" << aDateAndTime.getYear()
       << " theMonth=" <<  aDateAndTime.getMonth()
       << " theDay=" <<  aDateAndTime.getDay()
       << " theHours=" <<  aDateAndTime.getHours()
       << " theMinutes=" <<  aDateAndTime.getMinutes()
       << " theSeconds=" << std::fixed << std::setprecision(6) << aDateAndTime.getSeconds()
       << " theUTC_OffsetHours=" << std::setprecision(4) << aDateAndTime.getUtcOffsetHours();
    os << " }";
    return os;
}
