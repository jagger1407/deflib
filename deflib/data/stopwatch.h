#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <stdio.h>
#include <time.h>
#include "../types.h"

#ifdef _WIN32
#include <windows.h>
#endif

/**
 * Stopwatch class
 * For measuring performance.
 */
class Stopwatch
{
public:
    /**
     * Creates a new Stopwatch object.
     */
    Stopwatch();
    /**
     * Starts the timer.
     */
    void start();
    /**
     * Stops the timer and stores the elapsed time since the start.
     */
    void stop();
    /**
     * Gets the elapsed time of this stopwatch in seconds (double precision).
     */
    double elapsed();
    /**
     * Gets the elapsed time of this stopwatch in seconds (whole seconds).
     */
    u64 elapsed_secs();
    /**
     * Gets the elapsed time of this stopwatch in nanoseconds.
     */
    u64 elapsed_nsecs();

    /**
     * Gets the resolution of this stopwatch.
     * @note The resolution is the smallest unit this stopwatch can use.
     */
    double resolution();
    /**
     * Gets the resolution of this stopwatch in seconds (whole seconds).
     * @note The resolution is the smallest unit this stopwatch can use.
     */
    u64 resolution_secs();
    /**
     * Gets the resolution of this stopwatch in nanoseconds.
     * @note The resolution is the smallest unit this stopwatch can use.
     */
    u64 resolution_nsecs();

    /**
     * Checks whether the stopwatch has been started.
     */
    bool ticking();
    /**
     * Checks whether the stopwatch is currently running.
     */
    bool stopped();

private:
#ifdef __unix__
    struct timespec _ts_res;
    struct timespec _ts_start;
    struct timespec _ts_end;
#endif
#ifdef _WIN32
    LARGE_INTEGER _li_res;
    LARGE_INTEGER _li_start;
    LARGE_INTEGER _li_end;
#endif
    bool _started;
    bool _stopped;
};

#endif // STOPWATCH_H
