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
 * @file TimeDifference.h
 * @brief Contains the declaration of the TimeDifference class
 * @ingroup group_time
 *
 * @author Dave Strickland, <dave.strickland@gmail.com>
 *
 * @version Sep 15, 2018 dks : Initial coding 
 */

#ifndef INC_TIMEDIFFERENCE_H_
#define INC_TIMEDIFFERENCE_H_

namespace SPA
{

/**
 * @brief Represents the time elapsed between two time points
 * @ingroup group_time
 *
 * Internally time differences are stored as decimal days
 * for simplicity. For input JulianDates this limits the
 * time precision to approximately 1.0e-9 days, or 100 ms.
 */
class TimeDifference
{
    public:
        /**
         * @brief Default constructor for TimeDifference
         * @param[in] aDecimalDayDifference
         */
        TimeDifference(double aDecimalDayDifference = 0);

        /// Default TimeDifference destructor
        ~TimeDifference() = default;

        /**
         * @brief Gets the time difference represented by this
         *   object in decimal Julian days.
         *
         * @return The time difference represented by this
         *   object in decimal Julian days.
         */
        double getDecimalDayDifference() const
        {
            return theDecimalDayDifference;
        }

        /**
         * @brief Resets the decimal day difference stored in this
         *   TimeDifference object.
         *
         * @param[in] aDecimalDayDifference The value to set the
         *   decimal day difference in this object to.
         */
        void setDecimalDayDifference(double aDecimalDayDifference)
        {
            theDecimalDayDifference = aDecimalDayDifference;
        }

    private:
        /**
         *  Decimal number of Solar days that is the difference between
         *  two JulianDates
         */
        double theDecimalDayDifference;
};

} /* namespace SPA */

#endif /* INC_TIMEDIFFERENCE_H_ */
