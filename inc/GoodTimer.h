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
 * @file  GoodTimer.h
 * @brief Self-contained timer class using std::chrono and the high
 *   resolution timer with no external dependencies.
 * @ingroup group_util
 *
 * @limitations Requires C++11
 *
 * @author dave.strickland@gmail.com
 * 
 * @version Jul 17, 2018 dks : Initial coding for SPA
 */

#ifndef GOODTIMER_HEADER
#define GOODTIMER_HEADER

#include <algorithm>  //  For min, max
#include <chrono> 
#include <iostream>

namespace SPA
{

/**
 * @defgroup group_util SPA Utilities
 * @brief Utilities created for SPA that are not explicitly part of
 *   Practical Astronomy With Your Calculator
 *
 */


/**
 * @brief Timer type
 * @ingroup group_util
 */
typedef double gtimer_t;

/**
 * @brief Controls whether the timer starts counting from instantiation
 * @ingroup group_util
 */
enum class TIMER_START_OPTIONS
{
   TIMER_START_AUTO = 0, //!< Start counting from construction
   TIMER_START_MANUAL    //!< Don't count from construction
};

/**
 * @brief Controls how the timer resolution is measured
 * @ingroup group_util
 */
enum class TIMER_RES_OPTIONS
{
   TIMER_RES_MIN = 0, //!< Minimum difference from all runs.
   TIMER_RES_MEAN     //!< Mean time difference
};

/**
 * @brief Nanosecond resolution duration, floating point
 * @ingroup group_util
 */
typedef std::chrono::duration<long double, std::nano> TimerNanoseconds;

/**
 * @brief Chosen clock for timing purposes
 * @ingroup group_util
 */

typedef std::chrono::high_resolution_clock TimerClock;

/**
 * @brief Time point associated with our chosen clock
 * @ingroup group_util
 */
typedef TimerClock::time_point TimerTimePoint;

/**
 * @brief Self-contained timer class using std::chrono and the high
 *   resolution timer with no external dependencies.
 * @ingroup group_util
 *
 * @limitations Requires C++11
 *
 * A simple header-only timer that uses std::chrono internally but outputs
 * elapsed time in 64-bit floaying point seconds.
 * 
 * @limitations Internal time measurements and differences use std::chrono
 * and retain their intrinsic accuracy, but the count of elapsed time and
 * output elapsed time are type double with the associated limits in precision.
 * For reasonable uses of this class this does cause problems.
 */
class GoodTimer
{
   public:

      /**
       * Creates and starts a timer.
       *
       * By default, create the timer without any time offset,
       * and start it running right now.
       *
       * @param aTime the initial offset for the timer, default to 0
       * @param aStartOption indicicate whether the timer should run now (option is either
       * TIMER_START_AUTO or TIMER_START_MANUAL), default to TIMER_START_AUTO
       */
      explicit GoodTimer(gtimer_t aTime = gtimer_t(0), 
                         TIMER_START_OPTIONS aStartOption = TIMER_START_OPTIONS::TIMER_START_AUTO) :
         theElapsedTime(aTime), 
         theRunState(false)
      {
         if (aStartOption == TIMER_START_OPTIONS::TIMER_START_AUTO)
         {
             start();
         }
      }

      /**
       * Start (or restart) the timer from now.
       *
       * Calling start() on a running timer has no effect.
       * Calling start on a non-running timer does not reset the elapsed time,
       *   as expected. So you can run a timer, pause it (to stop measuring
       *   elapsed time), and then start it again.
       */
      void start()
      {
         if (!theRunState)
         {
            theStartTime = TimerClock::now();
            theRunState = true;
         } // If we're already running calling start() again does nothing.
      }

      /**
       * Return the current total of elapsed time.
       *
       * If the timer is running this function updated the elapsed time and returns it.
       * If the timer is not running then the current value of the elapsed time is
       * return, but this value dates back to when the timer was last running and
       * elapsed() was called.
       *
       * @returns The current total of elapsed time (units: seconds)
       */
      gtimer_t elapsed()
      {
         if (theRunState)
         {
            TimerTimePoint currentTime = TimerClock::now();
            theElapsedTime += TimerNanoseconds(currentTime - theStartTime).count() * NANOSEC_IN_SEC;

            //  Reset the start time to now, so that the next call to elapsed will
            //  calcuate the change in time from now. We need to store elapsed time
            //  separately from the start time to make pausing work. (Otherwise
            //  we could just have a fixed theStartTime.)
            theStartTime = TimerClock::now();
         }
         return theElapsedTime;
      }

      /**
       * Reset the timer and elapsed time to zero now. The timer continues running.
       *
       */
      void reset()
      {
         theElapsedTime = gtimer_t(0);
         theStartTime = TimerClock::now();
      }

      /**
       * Pause the timer. The elapsed time is not updated or reset.
       *
       * Use start() to restart timing.
       */
      void pause()
      {
         theRunState = false;
      }

      /**
       * Returns whether the timer is currently running
       *
       * @return the states of the timer; true if the timer is running, false otherwise
       */
      bool isRunning() const
      {
         return theRunState;
      }

    /**
     *  Returns a good estimate of the time resolution of the timer
     *         (units: seconds)
     * 
     *  @param aMethod The method to determine the resolution, default to TIMER_RES_MIN
     *
     *  @return the time resolution of the current system being run on (in seconds)
     */
    gtimer_t resolution(TIMER_RES_OPTIONS aMethod = TIMER_RES_OPTIONS::TIMER_RES_MIN)
    {
        const int NUMBER_TIME_SAMPLES = 21;
        TimerTimePoint time1;
        TimerTimePoint time[NUMBER_TIME_SAMPLES];
        
        // Get a number of times that differ by at least minimum minres
        // but do not do any additional work in the loop that could throw
        // off timing.
        time[0] = TimerClock::now();
        for (int index = 1; index < NUMBER_TIME_SAMPLES; index++)
        {
            do
            {
                time1 = TimerClock::now();
            } while (time1 == time[index-1]); // Loop
            time[index] = time1;
        }
        
        // Determine the mean and minimum difference between successive values
        // in units of nanoseconds.
        gtimer_t meanres = gtimer_t(0);
        gtimer_t timeResolution = TimerNanoseconds(time[1] - time[0]).count();
        for (int index = 1; index < NUMBER_TIME_SAMPLES; index++)
        {
            gtimer_t delta = TimerNanoseconds(time[index] - time[index - 1]).count();
            meanres += delta;
            timeResolution = std::min(timeResolution, delta);
        }
        if (aMethod == TIMER_RES_OPTIONS::TIMER_RES_MEAN)
        {
            timeResolution = meanres / gtimer_t(NUMBER_TIME_SAMPLES-1);
        }
        return NANOSEC_IN_SEC * timeResolution;
    }
    
    private:
    /**
     * the amount of time elapsed
     */
    gtimer_t theElapsedTime;
    
    /**
     * the start time associated with this timer
     */
    TimerTimePoint theStartTime;
    
    /**
     * Indicate whether the timer is running
     */
    bool theRunState;
    
    /**
     * Constant used for conversion to double precision seconds.
     */
    static constexpr double NANOSEC_IN_SEC = 1.0e-9;
};

} // end namespace SPA

#endif /* GOODTIMER_HEADER */
