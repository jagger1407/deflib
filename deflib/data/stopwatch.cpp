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

u64 Stopwatch::elapsed_secs() {
    if(!_started) {
        return -1;
    }
    if(!_stopped) {
        struct timespec ts;
        clock_gettime(CLOCK_MONOTONIC, &ts);
        return ts.tv_sec - _ts_start.tv_sec;
    }
    return _ts_end.tv_sec - _ts_start.tv_sec;
}

u64 Stopwatch::elapsed_nsecs() {
    if(!_started) {
        return -1;
    }
    if(!_stopped) {
        struct timespec ts;
        clock_gettime(CLOCK_MONOTONIC, &ts);
        return ts.tv_nsec - _ts_start.tv_nsec;
    }
    return (_ts_end.tv_sec - _ts_start.tv_sec) * 1000000000 + (_ts_end.tv_nsec - _ts_start.tv_nsec);
}

double Stopwatch::resolution() {
    return _ts_res.tv_sec + (_ts_res.tv_nsec / 1e9);
}

u64 Stopwatch::resolution_secs() {
    return _ts_res.tv_sec;
}

u64 Stopwatch::resolution_nsecs() {
    return _ts_res.tv_nsec;
}
#endif

bool Stopwatch::ticking() {
    return _started && !_stopped;
}

bool Stopwatch::stopped() {
    return _stopped;
}

