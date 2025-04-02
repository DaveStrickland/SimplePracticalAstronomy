/*
 * Copyright (C) 2020 David Strickland, <dave.strickland@gmail.com>
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
 * @file SpaDate.cc
 * @brief Definitions of the SpaDate class
 * @ingroup group_time
 *
 * @author Dave Strickland, <dave.strickland@gmail.com>
 *
 * @version Jan 28, 2020 dks : Initial coding 
 */

#include "SpaDate.h"
#include "SpaTimeConstants.h"
#include "TimeDifference.h"
#include "TimeUtilities.h"

namespace SPA
{

SpaDate::SpaDate() : theYear(0),
                theMonth(0),
                theDay(0)
{
}

SpaDate::SpaDate(int aYear,
           int aMonth,
           int aDay) : theYear(aYear),
                       theMonth(aMonth),
                       theDay(aDay)
{
}

void SpaDate::setDay(int aDay)
{
    theDay = aDay;
}

void SpaDate::setMonth(int aMonth)
{
    theMonth = aMonth;
}

void SpaDate::setYear(int aYear)
{
    theYear = aYear;
}

int SpaDate::getDayNumber() const
{
    return TIME_UTIL::calculateDayNumber(theYear, theMonth, theDay);
}

bool operator==(const SpaDate& aLHS,
                const SpaDate& aRHS)
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
    return true;
}

bool operator<(const SpaDate& aLHS,
               const SpaDate& aRHS)
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
            else 
            {
                return false;
            } // end if day
        } // end if month
    } // end if year

    return true;
}

TimeDifference operator-(const SpaDate& aLHS_Date, const SpaDate& aRHS_Date)
{
    double jd_lhs = TIME_UTIL::calculateJulianDayNumber(aLHS_Date.getYear(),
                                                        aLHS_Date.getMonth(), 
                                                        aLHS_Date.getDay());
    double jd_rhs = TIME_UTIL::calculateJulianDayNumber(aRHS_Date.getYear(),
                                                        aRHS_Date.getMonth(), 
                                                        aRHS_Date.getDay());
    return TimeDifference(jd_lhs - jd_rhs);
}

} /* namespace SPA */

std::ostream& operator<<(std::ostream& os,
                         const SPA::SpaDate& aSpaDate)
{
    os << "SpaDate{";
    os << " theYear="  << aSpaDate.getYear()
       << " theMonth=" <<  aSpaDate.getMonth()
       << " theDay="   <<  aSpaDate.getDay();
    os << " }";
    return os;
}
