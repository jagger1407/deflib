#include "stopwatch.h"


#ifdef _WIN32
// TODO: Implement windows methods
Stopwatch::Stopwatch() {

}

void Stopwatch::start() {

}

void Stopwatch::stop() {

}

double Stopwatch::elapsed() {

}

#endif
#ifdef __unix__

Stopwatch::Stopwatch() {
    if(clock_getres(CLOCK_MONOTONIC, &_ts_res) != 0) {
        return;
    }
    _stopped = true;
    _started = false;
    _ts_start = { 0, 0 };
    _ts_end = { 0, 0 };
}

void Stopwatch::start() {
    clock_gettime(CLOCK_MONOTONIC, &_ts_start);
    _started = true;
    _stopped = false;
}

void Stopwatch::stop() {
    if(_stopped || !_started) {
        return;
    }
    clock_gettime(CLOCK_MONOTONIC, &_ts_end);
    _stopped = true;
}

double Stopwatch::elapsed() {
    double time = (_ts_end.tv_sec - _ts_start.tv_sec) + ((_ts_end.tv_nsec / 1e9) - (_ts_start.tv_nsec / 1e9));
    if(time < 0) return 0;
    return time;
}

#endif

bool Stopwatch::ticking() {
    return _started && !_stopped;
}

bool Stopwatch::stopped() {
    return _stopped;
}

