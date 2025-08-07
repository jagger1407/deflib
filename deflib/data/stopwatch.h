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
    Stopwatch();

    void start();
    void stop();
    double elapsed();
    u64 elapsed_secs();
    u64 elapsed_nsecs();

    double resolution();
    u64 resolution_secs();
    u64 resolution_nsecs();

    bool ticking();
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
