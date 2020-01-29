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
 * @file Time.cc
 * @brief Definitions of the Time class
 * @ingroup group_time
 *
 * @author Dave Strickland, <dave.strickland@gmail.com>
 *
 * @version Jan 28, 2020 dks : Initial coding 
 */

#include "Time.h"
#include "SpaTimeConstants.h"

namespace SPA
{

Time::Time() : theHours(0),
               theMinutes(0),
               theSeconds(0),
               theUTC_OffsetHours(0)
{
}

Time::Time(int anHours,
           int aMinutes,
           double aSeconds,
           double aUTC_OffsetHours) : theHours(anHours),
                                      theMinutes(aMinutes),
                                      theSeconds(aSeconds),
                                      theUTC_OffsetHours(aUTC_OffsetHours)
{
}

void Time::setHours(int anHours)
{
    theHours = anHours;
}

void Time::setMinutes(int aMinutes)
{
    theMinutes = aMinutes;
}

void Time::setSeconds(double aSeconds)
{
    theSeconds = aSeconds;
}

void Time::setUtcOffsetHours(double aUTC_OffsetHours)
{
    theUTC_OffsetHours = aUTC_OffsetHours;
}

double Time::getDayFraction() const
{
    double dayFraction = double(theHours) / double(SPA_HOURS_IN_DAY)
                    + double(theMinutes) / double(SPA_MINUTES_IN_DAY)
                    + theSeconds / double(SPA_SECONDS_IN_DAY);
    // Now offset by UTC correction
    dayFraction += theUTC_OffsetHours / double(SPA_HOURS_IN_DAY);
    return dayFraction;
}

bool operator==(const Time& aLHS,
                const Time& aRHS)
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

bool operator<(const Time& aLHS,
               const Time& aRHS)
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
                         const SPA::Time& aTime)
{
    os << "Time{";
    os << " theHours=" <<  aTime.getHours()
       << " theMinutes=" <<  aTime.getMinutes()
       << " theSeconds=" << std::fixed << std::setprecision(6) << aTime.getSeconds()
       << " theUTC_OffsetHours=" << std::setprecision(4) << aTime.getUtcOffsetHours();
    os << " }";
    return os;
}
