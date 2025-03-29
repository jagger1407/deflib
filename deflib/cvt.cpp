#include "cvt.h"

string Cvt::ToString(bool b) {
    return b ? string("true") : string("false");
}

string Cvt::ToString(char ch) {
    return ToString((s64)ch);
}
string Cvt::ToString(byte value) {
    return ToString((u64)value);
}
string Cvt::ToString(s16 value) {
    return ToString((s64)value);
}
string Cvt::ToString(u16 value) {
    return ToString((u64)value);
}
string Cvt::ToString(s32 value) {
    return ToString((s64)value);
}
string Cvt::ToString(u32 value) {
    return ToString((u64)value);
}
string Cvt::ToString(s64 value) {
    if(value == (s64)0x8000000000000000) {
        return string("-9223372036854775808");
    }
    int num_digits = 1;
    int end = 0;
    if(value < 0)  {
        value = (~value) + 1;
        num_digits++;
        end = 1;
    }
    s64 tmp = value;
    while(tmp /= 10, tmp > 0) {
        num_digits++;
    }

    char* s = new char[num_digits+1];
    for(int i=num_digits-1;i>=end;i--) {
        s[i] = '0' + (value % 10);
        value /= 10;
    }
    s[num_digits] = 0x00;
    if(end > 0) {
        s[0] = '-';
    }
    string out(s);
    delete[] s;
    return out;
}
string Cvt::ToString(u64 value) {
    int num_digits = 1;

    u64 tmp = value;
    while(tmp /= 10, tmp > 0) {
        num_digits++;
    }

    char* s = new char[num_digits+1];
    for(int i=num_digits-1;i>=0;i--) {
        s[i] = '0' + (value % 10);
        value /= 10;
    }
    s[num_digits] = 0x00;
    string out(s);
    delete[] s;
    return out;
}
string Cvt::ToString(Array<u8> array) {
    u64 len = array.count();

    Array<char> charr = Array<char>(len);
    copy_mem(charr.ptr(), array.ptr(), len);
    string s;
    s = charr;

    return s;
}
string Cvt::ToString(Time& value) {
    struct tm tm = value.tmStruct();
    return string(asctime(&tm));
}
string Cvt::ToString(Time& value, const string& format) {
    string s(format);

    int year = s.countOccurrences('y');
    int hour12 = s.countOccurrences('h');
    int hour24 = s.countOccurrences('H');
    int mins = s.countOccurrences('m');
    int secs = s.countOccurrences('s');
    int ampm = s.countOccurrences("tt");
    Array<int> month = s.getOccurrences('M');
    Array<int> day = s.countOccurrences('d');

    if(year == 2) {
        s = s.replace("yy", ToString(value.year() % 100));
    }
    else if(year == 4) {
        s = s.replace("yyyy", ToString(value.year()));
    }

    int t = value.hours();
    int at = (t % 12 == 0) ? 12 : t % 12;
    if(hour12 == 1) {
        s = s.replace('h', ToString(at));
    }
    else if(hour12 == 2) {
        s = s.replace("hh", string::Format("%02d", at));
    }

    if(hour24 == 1) {
        s = s.replace('H', ToString(t));
    }
    else if(hour24 == 2) {
        s = s.replace("HH", string::Format("%02d", t));
    }

    if(mins == 1) {
        s = s.replace('m', ToString(value.minutes()));
    }
    else if(mins == 2) {
        s = s.replace("mm", string::Format("%02d", value.minutes()));
    }

    if(secs == 1) {
        s = s.replace('s', ToString(value.seconds()));
    }
    else if(secs == 2) {
        s = s.replace("ss", string::Format("%02d", value.seconds()));
    }

    int months = month.count();
    if(months == 1) {
        s = s.replace('M', ToString(value.month()));
    }
    else if(months == 2) {
        s = s.replace("MM", string::Format("%02d", value.month()));
    }
    else if(months == 3) {
        s = s.replace("MMM", value.monthName().substring(0,3));
    }
    else if(months == 4) {
        s = s.replace("MMMM", value.monthName());
    }

    int days = day.count();
    if(days == 1) {
        s = s.replace('d', ToString(value.day()));
    }
    else if(days == 2) {
        s = s.replace("dd", string::Format("%02d", value.day()));
    }
    else if(days == 3) {
        s = s.replace("ddd", value.weekDayName().substring(0, 3));
    }
    else if(days == 4) {
        s = s.replace("dddd", value.weekDayName());
    }

    if(ampm == 1) {
        string m = value.hours() >= 12 ? "PM" : "AM";
        s = s.replace("tt", m);
    }

    return s;
}

s8 Cvt::ToInt8(const string& str) {
    return (s8)(ToInt64(str) % 0x100);
}
s16 Cvt::ToInt16(const string& str) {
    return (s16)(ToInt64(str) % 0x10000);
}
s32 Cvt::ToInt32(const string& str) {
    return (s32)(ToInt64(str) % 0x100000000);
}
s64 Cvt::ToInt64(const string& str) {
    s64 out = 0;

    string s = string(str);
    char* digit = s.c_str();
    int len = s.length();
    while(digit <= s.c_str()+s.length()-1) {
        if(*digit != '+' && *digit != '-' && (*digit < '0' || *digit > '9')) {
            len = digit - s.c_str();
            break;
        }
        digit++;
    }
    digit = s.c_str();
    s64 mult = 1;
    int end = 0;
    if(s.startsWith('-')) {
        mult = -1;
        end = 1;
    }
    else if(s.startsWith('+')) {
        mult = 1;
        end = 1;
    }
    for(int i=len-1;i>=end;i--) {
        out += (digit[i] - '0') * mult;
        mult *= 10;
    }

    return out;
}
