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
 * @file SpaTestUtilities.cc
 * @brief Definitions of test utility functions used for SPA testing
 * @ingroup group_test
 *
 * @author Dave Strickland, <dave.strickland@gmail.com>
 *
 * @version Sep 2, 2018 dks : Initial coding 
 */

#include "SpaTestUtilities.h"
#include <cute/cute.h>

#include <sstream>
#include <iomanip>

namespace SPA
{
namespace TEST
{

void spaTestFloatingPointEqual(const std::string& aMessage,
                               double anExpectedValue,
                               double anActualValue,
                               double aTolerance,
                               int aNumberOfDigitsOfPrecision)
{
    double absDiff = std::fabs(anActualValue - anExpectedValue);
    if (absDiff > aTolerance)
    {
        std::ostringstream ss;
        ss << aMessage
           << ": anExpectedValue=" << std::fixed << std::setprecision(aNumberOfDigitsOfPrecision) << anExpectedValue
           << " anActualValue=" << anActualValue
           << " aTolerance=" << aTolerance
           << " absDiff=" << absDiff;
        FAILM(ss.str());
    }
}

} /* namespace TEST */
} /* namespace SPA */
