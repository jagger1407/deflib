#include "stopwatch.h"


#ifdef _WIN32
// TODO: Implement windows methods
Stopwatch::Stopwatch() {
    QueryPerformanceFrequency(&_li_res);
    _stopped = true;
    _started = false;
    _li_start.QuadPart = 0;
    _li_end.QuadPart = 0;
}

void Stopwatch::start() {
    _started = true;
    _stopped = false;
    QueryPerformanceCounter(&_li_start);
}

void Stopwatch::stop() {
    if(_stopped || !_started) {
        return;
    }
    QueryPerformanceCounter(&_li_end);
    _stopped = true;
}

double Stopwatch::elapsed() {
    double time = (_li_end.QuadPart - _li_start.QuadPart) * 1e9 / _li_res.QuadPart;
    if(time < 0) return 0;
    return time / 1e9;
}

u64 Stopwatch::elapsed_secs() {
    if(!_started) {
        return -1;
    }
    if(!_stopped) {
        LARGE_INTEGER li;
        QueryPerformanceCounter(&li);
        return li.QuadPart - _li_start.QuadPart / _li_res.QuadPart;
    }
    return (_li_end.QuadPart - _li_start.QuadPart) / _li_res.QuadPart;
}

u64 Stopwatch::elapsed_nsecs() {
    if(!_started) {
        return -1;
    }
    if(!_stopped) {
        LARGE_INTEGER li;
        QueryPerformanceCounter(&li);
        return li.QuadPart - _li_start.QuadPart;
    }
    return (_li_end.QuadPart - _li_start.QuadPart) * 100;
}

double Stopwatch::resolution() {
    return 1.0 / (double)_li_res.QuadPart;
}

u64 Stopwatch::resolution_secs() {
    return (u64)(1 / _li_res.QuadPart);
}

u64 Stopwatch::resolution_nsecs() {
    return (1e9 / _li_res.QuadPart);
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

