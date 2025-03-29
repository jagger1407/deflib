#include "time.h"

Time::Time(u64 elapsed) {
    time_t t = (time_t)elapsed;
    _tm = *localtime(&t);
}
Time::Time(s32 day, s32 month, s32 year) {
    _tm = {0};

    _tm.tm_year = year - 1900;
    _tm.tm_mon = month - 1;
    _tm.tm_mday = day;
    _tm.tm_hour = 0;
    _tm.tm_min = 0;
    _tm.tm_sec = 0;
}
Time::Time(s32 day, s32 month, s32 year, s32 hours, s32 minutes, s32 seconds) {
    _tm = {0};

    _tm.tm_year = year - 1900;
    _tm.tm_mon = month - 1;
    _tm.tm_mday = day;
    _tm.tm_hour = hours;
    _tm.tm_min = minutes;
    _tm.tm_sec = seconds;
}

Time Time::Now() {
    return Time(time(NULL));
}

time_t Time::unixTime() {
    return mktime(&_tm);
}
struct tm Time::tmStruct() {
    return _tm;
}

s32 Time::year() {
    return _tm.tm_year + 1900;
}
s32 Time::month() {
    return _tm.tm_mon + 1;
}
string Time::monthName() {
    return string(_nameMonths[_tm.tm_mon]);
}
string Time::monthName(Month month) {
    return string(_nameMonths[month-1]);
}
s32 Time::day() {
    return _tm.tm_mday;
}
s32 Time::weekDay() {
    return _tm.tm_wday;
}
string Time::weekDayName() {
    return string(_nameDays[_tm.tm_wday]);
}
string Time::weekDayName(WeekDay day) {
    return string(_nameDays[day]);
}
s32 Time::hours() {
    return _tm.tm_hour;
}
s32 Time::minutes() {
    return _tm.tm_min;
}
s32 Time::seconds() {
    return _tm.tm_sec;
}

void Time::addYears(s32 years) {
    _tm.tm_year += years;
    mktime(&_tm);
}
void Time::addMonths(s32 months) {
    _tm.tm_mon += months;
    mktime(&_tm);
}
void Time::addDays(s32 days) {
    _tm.tm_mday += days;
    mktime(&_tm);
}
void Time::addHours(s32 hours) {
    _tm.tm_hour += hours;
    mktime(&_tm);
}
void Time::addMinutes(s32 minutes) {
    _tm.tm_min += minutes;
    mktime(&_tm);
}
void Time::addSeconds(s32 seconds) {
    _tm.tm_sec += seconds;
    mktime(&_tm);
}



