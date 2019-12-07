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
 * @file PolynomialTiming_TestClass.cc
 * @brief Definition of PolynomialTiming_TestClass functions
 * @ingroup group_test
 *
 * @author Dave Strickland dave.strickland@gmail.com
 * 
 * @version Jul 18, 2018 dks : Initial version
 */

#include "PolynomialTiming_TestClass.h"
#include <iostream>
#include <iomanip>
#include <array>
#include <cmath>

#include <chrono>
#include <thread>
#include "GoodTimer.h"

namespace SPA
{
namespace TEST
{

namespace POLY
{
    // Example polynomials

    /// A six coefficient polynomial used for testing.
    constexpr std::array<double, 6> SIX_COEFF = {{1, 0.1, 0.01, 0.001, 0.0001, 0.00001}};

    /**
     * A six coefficient polynomial with some coefficient values set to zero, equivalent
     * to a three coefficient polynomial.
     */
    constexpr std::array<double, 6> SIX_COEFF_ZERO = {{1, 0.1, 0.01, 0, 0, 0}};

    /// A three coefficient polynomial used for testing.
    constexpr std::array<double, 6> THREE_COEFF = {{1, 0.1, 0.01}};

    /**
     * Enumeration that names the coefficients of a polynomial and
     * gives the number of coefficients defined.
     */
    enum COEFF {ZERO, ONE, TWO, THREE, FOUR, FIVE, NUM_COEFF};
}

/**
 * 3-coefficient (2nd order) polynomial implemented with multiplication
 */
double SimpleThreeCoeff(const double aValue)
{
    using namespace POLY;
    double retval = THREE_COEFF[ZERO] +
        aValue * THREE_COEFF[ONE] +
        aValue * aValue * THREE_COEFF[TWO];
    return retval;
}

/**
 * 3-coefficient (2nd order) polynomial implemented with std::pow
 */
double PowThreeCoeff(const double aValue)
{
    using namespace POLY;
    double retval = THREE_COEFF[ZERO] +
        aValue * THREE_COEFF[ONE] +
        std::pow(aValue, 2) * THREE_COEFF[TWO];
    return retval;
}

/**
 * 6-coefficient (5th order) polynomial, skipping orders where the
 *  coefficient is zero.
 * 
 * Here the aim is to see of the performance is equivalent to
 * SimpleThreeCoeff, or if the if statements come with a cost.
 * We're avoiding the obvious loop-based implementation in this case.
 */
double ZeroThreeCoeff(const double aValue)
{
    using namespace POLY;
    double valSquared = aValue * aValue;
    double retval = 0;
    if ( SIX_COEFF_ZERO[ZERO] != 0 )
    {
        retval += SIX_COEFF_ZERO[ZERO];
    }   
    if ( SIX_COEFF[ONE] != 0 )
    {
        retval += aValue * SIX_COEFF_ZERO[ONE];
    }   
    if ( SIX_COEFF_ZERO[TWO] != 0 )
    {
        retval += valSquared * SIX_COEFF_ZERO[TWO];
    }   
    if ( SIX_COEFF_ZERO[THREE] != 0 )
    {
        retval += valSquared * aValue * SIX_COEFF_ZERO[THREE];
    }   
    if ( SIX_COEFF_ZERO[FOUR] != 0 )
    {
        retval += valSquared * valSquared * SIX_COEFF_ZERO[FOUR];
    }   
    if ( SIX_COEFF_ZERO[FIVE] != 0 )
    {
        retval += valSquared * valSquared * aValue * SIX_COEFF_ZERO[FIVE];
    }   
    return retval;
}

/**
 * 6-coefficient (5th order) polynomial implemented with multiplication
 */
double SimpleSixCoeff(const double aValue)
{
    using namespace POLY;
    double valSquared = aValue * aValue;
    double retval = SIX_COEFF[ZERO] +
        aValue * SIX_COEFF[ONE] +
        valSquared * SIX_COEFF[TWO] +
        valSquared * aValue * SIX_COEFF[THREE] +
        valSquared * valSquared * SIX_COEFF[FOUR] +
        valSquared * valSquared * aValue * SIX_COEFF[FIVE];
    return retval;
}

/**
 * 6-coefficient (5th order) polynomial implement with multiplication,
 * using the ones of forms suggested by Numerical Recipies
 */
double NumRecSixCoeff(const double aValue)
{
    using namespace POLY;
    double retval = (((( SIX_COEFF[FIVE] * aValue +  SIX_COEFF[FOUR] )
        * aValue + SIX_COEFF[THREE] )
        * aValue + SIX_COEFF[TWO] )
        * aValue + SIX_COEFF[ONE] )
        * aValue + SIX_COEFF[ZERO];
    return retval;
}

/**
 * 6-coefficient (5th order) polynomial implement with multiplication,
 * using the downward-counting loop form suggested by Numerical Recipies
 */
double NumRecLoopSixCoeff(const double aValue)
{
    using namespace POLY;
    double retval = SIX_COEFF[NUM_COEFF-1];
    for (int iIter = NUM_COEFF - 2; iIter >= 0; iIter--)
    {
        retval = retval*aValue + SIX_COEFF[iIter];
    }
    return retval;
}

/**
 * 6-coefficient (5th order) polynomial implemented with std::pow
 * 
 * This is amazingly expensive computationally.
 */
double PowSixCoeff(const double aValue)
{
    using namespace POLY;
    double retval = SIX_COEFF[ZERO] +
        aValue * SIX_COEFF[ONE] +
        std::pow(aValue, 2) * SIX_COEFF[TWO] +
        std::pow(aValue, 3) * SIX_COEFF[THREE] +
        std::pow(aValue, 4) * SIX_COEFF[FOUR] +
        std::pow(aValue, 5) * SIX_COEFF[FIVE];
    return retval;
}

/**
 * 6-coefficient (5th order) polynomial implemented with std::pow
 *  and a loop
 * 
 * This is amazingly expensive computationally.
 */
double LoopPowSixCoeff(const double aValue)
{
    using namespace POLY;
    double retval = SIX_COEFF[ZERO];
    for (int iOrder = ONE; iOrder < NUM_COEFF; iOrder++)
    {
        retval += std::pow(aValue, iOrder) * SIX_COEFF[iOrder];
    }
    return retval;
}

/**
 * 6-coefficient (5th order) polynomial implemented with multiplication
 * and a loop
 */
double LoopSimpleSixCoeff(const double aValue)
{
    using namespace POLY;
    double retval = SIX_COEFF[ZERO];
    double xval = 1.0;
    for (int iOrder = ONE; iOrder < NUM_COEFF; iOrder++)
    {
        xval *= aValue;
        retval += xval * SIX_COEFF[iOrder];
    }
    return retval;
}

/**
 * 6-coefficient (5th order) polynomial implemented with multiplication
 * and a loop, that ignores orders where the coefficient is zero.
 * 
 * The aim is to see if the cost of "if" statements outweighs
 * any gain from having to do less multiplications.
 */
double ZeroLoopSimpleSixCoeff(const double aValue)
{
    using namespace POLY;
    double retval = SIX_COEFF[ZERO];
    double xval = 1.0;
    for (int iOrder = ONE; iOrder < NUM_COEFF; iOrder++)
    {
        if (SIX_COEFF[iOrder] != 0)
        {
            xval *= aValue;
            retval += xval * SIX_COEFF[iOrder];
        }
    }
    return retval;
}



void PolynomialTiming_TestClass::printResult(const std::string& aTestName,
                                             double aTimeSeconds,
                                             const int aNumTests,
                                             double aTestValue)
{
    double usecPerTest = aTimeSeconds * 1.0e6 / double(aNumTests);
    std::cout << "method: " << aTestName << " "
        << std::scientific << std::setprecision(3) << double(aNumTests) << " tests, "
        << std::fixed << std::setprecision(6) << aTimeSeconds << " s, "
        << usecPerTest << " us/test,"
        << " final value=" << std::scientific << std::setprecision(4) << aTestValue 
        << std::endl;
}

void PolynomialTiming_TestClass::testTiming()
{
    SPA::GoodTimer timer;
    std::cout << "Timer resolution: " 
        << std::fixed << std::setprecision(9)
        << timer.resolution(SPA::TIMER_RES_OPTIONS::TIMER_RES_MEAN) << " seconds." << std::endl;
         
    std::cout << "Testing Timer..." << std::endl;
    SPA::GoodTimer timer2;
    timer.reset();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    double elapsed = timer.elapsed();
    std::cout << "  Slept for 0.5 seconds, Timer claims " 
        << elapsed << " seconds passed." << std::endl;
    std::cout << "  Timer2 claims " 
        << timer2.elapsed() << " seconds passed." << std::endl;

    timer2.pause();
    std::this_thread::sleep_for(std::chrono::milliseconds(750));
    elapsed = timer.elapsed();
    std::cout << "  Slept for another 0.75 seconds, Timer claims " 
        << elapsed << " seconds passed." << std::endl;
    std::cout << "  Timer2 claims " 
        << timer2.elapsed() << " seconds passed." << std::endl;
    timer2.start();

    std::this_thread::sleep_for(std::chrono::milliseconds(110));
    elapsed = timer.elapsed();
    std::cout << "  Slept for another 0.11 seconds, Timer claims " 
        << elapsed << " seconds passed." << std::endl;
    std::cout << "  Timer2 claims " 
        << timer2.elapsed() << " seconds passed." << std::endl;
                
    int NTESTS = 10000000;
    double coefficient = 1.0e-4;
    double oValue;

    //std::vector<std::function<double(const double)> > functionVector;

    std::cout << "---------------------------------------" << std::endl;
    
    timer.reset();
    oValue = runTestLoop(NTESTS, coefficient, SimpleThreeCoeff);
    elapsed = timer.elapsed();
    printResult("SimpleThreeCoeff", elapsed, NTESTS, oValue);

    timer.reset();
    oValue = runTestLoop(NTESTS, coefficient, ZeroThreeCoeff);
    elapsed = timer.elapsed();
    printResult("ZeroThreeCoeff", elapsed, NTESTS, oValue);

    timer.reset();
    oValue = runTestLoop(NTESTS, coefficient, PowThreeCoeff);
    elapsed = timer.elapsed();
    printResult("PowThreeCoeff", elapsed, NTESTS, oValue);

    timer.reset();
    oValue = runTestLoop(NTESTS, coefficient, SimpleSixCoeff);
    elapsed = timer.elapsed();
    printResult("SimpleSixCoeff", elapsed, NTESTS, oValue);        

    timer.reset();
    oValue = runTestLoop(NTESTS, coefficient, PowSixCoeff);
    elapsed = timer.elapsed();
    printResult("PowSixCoeff", elapsed, NTESTS, oValue);

    timer.reset();
    oValue = runTestLoop(NTESTS, coefficient, LoopPowSixCoeff);
    elapsed = timer.elapsed();
    printResult("LoopPowSixCoeff", elapsed, NTESTS, oValue);

    timer.reset();
    oValue = runTestLoop(NTESTS, coefficient, ZeroLoopSimpleSixCoeff);
    elapsed = timer.elapsed();
    printResult("ZeroLoopSimpleSixCoeff", elapsed, NTESTS, oValue);

    timer.reset();
    oValue = runTestLoop(NTESTS, coefficient, LoopSimpleSixCoeff);
    elapsed = timer.elapsed();
    printResult("LoopSimpleSixCoeff", elapsed, NTESTS, oValue);

    timer.reset();
    oValue = runTestLoop(NTESTS, coefficient, NumRecSixCoeff);
    elapsed = timer.elapsed();
    printResult("NumRecSixCoeff", elapsed, NTESTS, oValue);

    timer.reset();
    oValue = runTestLoop(NTESTS, coefficient, NumRecLoopSixCoeff);
    elapsed = timer.elapsed();
    printResult("NumRecLoopSixCoeff", elapsed, NTESTS, oValue);

    std::cout << "---------------------------------------" << std::endl;
    std::cout << "Rerunning tests in different order" << std::endl;
    coefficient = 3.13e-5;

    timer.reset();
    oValue = runTestLoop(NTESTS, coefficient, PowThreeCoeff);
    elapsed = timer.elapsed();
    printResult("PowThreeCoeff", elapsed, NTESTS, oValue);

    timer.reset();
    oValue = runTestLoop(NTESTS, coefficient, SimpleSixCoeff);
    elapsed = timer.elapsed();
    printResult("SimpleSixCoeff", elapsed, NTESTS, oValue);        

    timer.reset();
    oValue = runTestLoop(NTESTS, coefficient, NumRecSixCoeff);
    elapsed = timer.elapsed();
    printResult("NumRecSixCoeff", elapsed, NTESTS, oValue);

    timer.reset();
    oValue = runTestLoop(NTESTS, coefficient, LoopSimpleSixCoeff);
    elapsed = timer.elapsed();
    printResult("LoopSimpleSixCoeff", elapsed, NTESTS, oValue);

    timer.reset();
    oValue = runTestLoop(NTESTS, coefficient, NumRecLoopSixCoeff);
    elapsed = timer.elapsed();
    printResult("NumRecLoopSixCoeff", elapsed, NTESTS, oValue);

    timer.reset();
    oValue = runTestLoop(NTESTS, coefficient, ZeroThreeCoeff);
    elapsed = timer.elapsed();
    printResult("ZeroThreeCoeff", elapsed, NTESTS, oValue);

    timer.reset();
    oValue = runTestLoop(NTESTS, coefficient, PowSixCoeff);
    elapsed = timer.elapsed();
    printResult("PowSixCoeff", elapsed, NTESTS, oValue);

    timer.reset();
    oValue = runTestLoop(NTESTS, coefficient, SimpleThreeCoeff);
    elapsed = timer.elapsed();
    printResult("SimpleThreeCoeff", elapsed, NTESTS, oValue);

    timer.reset();
    oValue = runTestLoop(NTESTS, coefficient, LoopPowSixCoeff);
    elapsed = timer.elapsed();
    printResult("LoopPowSixCoeff", elapsed, NTESTS, oValue);

    timer.reset();
    oValue = runTestLoop(NTESTS, coefficient, ZeroLoopSimpleSixCoeff);
    elapsed = timer.elapsed();
    printResult("ZeroLoopSimpleSixCoeff", elapsed, NTESTS, oValue);

    std::cout << "---------------------------------------" << std::endl;

    return;
}    

double PolynomialTiming_TestClass::runTestLoop(const int aNumTests,
                                               const double aCoeff,
                                               std::function<double(const double)> aFuncPtr)
{
    double iValue = 0;
    double oValue = 0;
    for (int iTest = 0; iTest < aNumTests; iTest++)
    {
        iValue = aCoeff * double(iTest);
        oValue += aFuncPtr(iValue);
    }
    return oValue;
}

} // end namespace TEST
} // end namespace SPA

