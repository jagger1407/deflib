#ifndef DATE_H
#define DATE_H

#include "../types.h"
#include "string.h"
#include "../collections/array.h"
#include <time.h>

/**
 * Time Class.
 * For storing times and dates and the likes.
 */
class Time
{
public:
    typedef enum {
        January = 1,
        February,
        March,
        April,
        May,
        June,
        July,
        August,
        September,
        October,
        November,
        December
    } Month;
    typedef enum {
        Sunday,
        Monday,
        Tuesday,
        Wednesday,
        Thursday,
        Friday,
        Saturday
    } WeekDay;

    /**
     * Creates a Time object based on Unix time (time_t).
     */
    Time(u64 elapsed);
    /**
     * Creates a Time object with the given date.
     * @note all daytime members will be set to 0.
     */
    Time(s32 day, s32 month, s32 year);
    /**
     * Creates a Time object with the given date and time.
     */
    Time(s32 day, s32 month, s32 year, s32 hours, s32 minutes, s32 seconds);

    /**
     * Gets this Time object as a Unix time (time_t).
     */
    time_t unixTime();
    /**
     * Gets this Time object as a tm struct.
     */
    struct tm tmStruct();

    /**
     * Gets the year.
     */
    s32 year();
    /**
     * Gets the month.
     */
    s32 month();
    /**
     * Gets the name of the month.
     */
    string monthName();
    /**
     * Gets the name of the given month.
     */
    string monthName(Month month);
    /**
     * Gets the month-day.
     */
    s32 day();
    /**
     * Gets the week-day.
     */
    s32 weekDay();
    /**
     * Gets the name of the week-day.
     */
    string weekDayName();
    /**
     * Gets the name of a specified week-day as a string.
     */
    string weekDayName(WeekDay day);
    /**
     * Gets the hours.
     */
    s32 hours();
    /**
     * Gets the minutes.
     */
    s32 minutes();
    /**
     * Gets the seconds.
     */
    s32 seconds();

    /**
     * Adds specified amount of seconds to the Time.
     */
    void addSeconds(s32 seconds);
    /**
     * Adds specified amount of minutes to the Time.
     */
    void addMinutes(s32 minutes);
    /**
     * Adds specified amount of hours to the Time.
     */
    void addHours(s32 hours);
    /**
     * Adds specified amount of month-days to the Time.
     */
    void addDays(s32 days);
    /**
     * Adds specified amount of months to the Time.
     */
    void addMonths(s32 months);
    /**
     * Adds specified amount of years to the Time.
     */
    void addYears(s32 years);

    /**
     * Gets the current time as a Time object.
     * Essentially just Time(time(NULL)).
     */
    static Time Now();
private:
    struct tm _tm;
    /**
     * Contains the string representation of each month.
     */
    const Array<string> _nameMonths = {
        "January",
        "February",
        "March",
        "April",
        "May",
        "June",
        "July",
        "August",
        "September",
        "October",
        "November",
        "December"
    };
    /**
     * Contains the string representation of each weekday.
     */
    const Array<string> _nameDays = {
        "Sunday",
        "Monday",
        "Tuesday",
        "Wednesday",
        "Thursday",
        "Friday",
        "Saturday"
    };
};

#endif // DATE_H
