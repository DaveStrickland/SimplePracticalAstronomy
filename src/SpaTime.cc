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
 * @file SpaTime.cc
 * @brief Definitions of the SpaTime class
 * @ingroup group_time
 *
 * @author Dave Strickland, <dave.strickland@gmail.com>
 *
 * @version Jan 28, 2020 dks : Initial coding 
 */

#include "SpaTime.h"
#include "SpaTimeConstants.h"

namespace SPA
{

//SpaTime::SpaTime() : theHours(0),
               //theMinutes(0),
               //theSeconds(0),
               //theUTC_OffsetHours(0)
//{
//}

SpaTime::SpaTime(int anHours,
                 int aMinutes,
                 double aSeconds,
                 double aUTC_OffsetHours) : theHours(anHours),
                                            theMinutes(aMinutes),
                                            theSeconds(aSeconds),
                                            theUTC_OffsetHours(aUTC_OffsetHours)
{
}

void SpaTime::setHours(int anHours)
{
    theHours = anHours;
}

void SpaTime::setMinutes(int aMinutes)
{
    theMinutes = aMinutes;
}

void SpaTime::setSeconds(double aSeconds)
{
    theSeconds = aSeconds;
}

void SpaTime::setUtcOffsetHours(double aUTC_OffsetHours)
{
    theUTC_OffsetHours = aUTC_OffsetHours;
}

double SpaTime::getDayFraction() const
{
    double dayFraction = double(theHours) / double(SPA_HOURS_IN_DAY)
                    + double(theMinutes) / double(SPA_MINUTES_IN_DAY)
                    + theSeconds / double(SPA_SECONDS_IN_DAY);
    // Now offset by UTC correction
    dayFraction += theUTC_OffsetHours / double(SPA_HOURS_IN_DAY);
    return dayFraction;
}

bool operator==(const SpaTime& aLHS,
                const SpaTime& aRHS)
{
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

bool operator<(const SpaTime& aLHS,
               const SpaTime& aRHS)
{
    // Check day fraction which is UTC corrected
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
    return true;
}

} /* namespace SPA */

std::ostream& operator<<(std::ostream& os,
                         const SPA::SpaTime& aSpaTime)
{
    os << "SpaTime{";
    os << " theHours="   <<  aSpaTime.getHours()
       << " theMinutes=" <<  aSpaTime.getMinutes()
       << " theSeconds=" << std::fixed << std::setprecision(6) << aSpaTime.getSeconds()
       << " theUTC_OffsetHours="       << std::setprecision(4) << aSpaTime.getUtcOffsetHours();
    os << " }";
    return os;
}
