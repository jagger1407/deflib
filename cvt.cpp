#include "cvt.h"

string Cvt::ToString(s32 number) {
    if(number == 0x80000000) {
        // can't be turned into a positive s32
        // so I had to treat it seperately
        return string("-2147483648");
    }
    int num_digits = 1;
    int end = 0;
    if(number < 0)  {
        number = (~number) + 1;
        num_digits++;
        end = 1;
    }
    int tmp = number;
    while(tmp /= 10, tmp > 0) {
        num_digits++;
    }

    char s[num_digits+1];
    for(int i=num_digits-1;i>=end;i--) {
        s[i] = '0' + (number % 10);
        number /= 10;
    }
    s[num_digits] = 0x00;
    if(end > 0) {
        s[0] = '-';
    }

    return string(s);
}
string Cvt::ToString(u32 number) {
    int num_digits = 1;

    u32 tmp = number;
    while(tmp /= 10, tmp > 0) {
        num_digits++;
    }

    char s[num_digits+1];
    for(int i=num_digits-1;i>=0;i--) {
        s[i] = '0' + (number % 10);
        number /= 10;
    }
    s[num_digits] = 0x00;

    return string(s);
}
string Cvt::ToString(bool b) {
    return b ? string("true") : string("false");
}

s32 Cvt::ToInt32(const string& str) {
    s32 out = 0;

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
    int mult = 1;
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
