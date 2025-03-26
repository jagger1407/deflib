#include "string.h"

u32 string::len(const char* str) {
    u32 len = 0;
    if(str == NULL) {
        _prev_len = len;
        _prev_ptr = NULL;
        return len;
    }
    if(str == _prev_ptr) {
        return _prev_len;
    }
    char* cur = (char*)str;
    while(*cur++ != 0x00) {
        len++;
    }
    _prev_len = len;
    _prev_ptr = (char*)str;
    return len;
}

char * string::ncopy(char* dest, const char* src, u32 n) {
    for(int i=0;i<n;i++) {
        dest[i] = src[i];
    }

    return dest;
}

int string::comp(const char* str1, const char* str2) {
    if(str1 == str2) {
        return 0;
    }
    char* s1 = (char*)str1;
    char* s2 = (char*)str2;
    while(*s1 != 0x00 && *s2 != 0x00) {
        if(*s1++ != *s2++) {
            return *s1 - *s2;
        }
    }
    return *s1 - *s2;
}

int string::ncomp(const char* str1, const char* str2, u32 n) {
    if(str1 == str2) {
        return 0;
    }
    if(n < 0) {
        return n;
    }
    char* s1 = (char*)str1;
    char* s2 = (char*)str2;
    for(int i=0;i<n;i++) {
        if(s1[i] == 0x00 || s2[i] == 0x00) {
            return s1[i] - s2[i];
        }
        if(s1[i] != s2[i]) {
            return s1[i] - s2[i];
        }
    }
    return *s1 - *s2;
}

char * string::initptr(u32 len) {
    char* ptr = NULL;
    while(ptr = (char*)malloc(len), ptr == NULL);
    for(int i=0;i<len;i++) {
        ptr[i] = 0x00;
    }
    return ptr;
}

char * string::inclen(u32 length) {
    u32 l = _len + length + 1;
    char* new_alloc = NULL;
    while(new_alloc = (char*)realloc(_c_ptr, l), new_alloc == NULL);
    _c_ptr = new_alloc;
    _real_len = l;
    for(int i=_len;i<l;i++) {
        _c_ptr[i] = 0x00;
    }
    return _c_ptr;
}


u32 string::length() const {
    return this->_len;
}

char * string::c_str() const {
    return this->_cur;
}


string & string::operator=(const char* str) {
    _len = len(str);

    if(_c_ptr != NULL) {
        free(_c_ptr);
    }
    _c_ptr = initptr(_len+1);
    _real_len = _len+1;
    ncopy(_c_ptr, str, _len);
    _cur = _c_ptr;

    return *this;
}
string & string::operator+=(const char* str) {
    if(str == NULL) {
        return *this;
    }
    u32 l = len(str);
    if(l <= 0) {
        return *this;
    }
    inclen(l);
    ncopy(_c_ptr + _len, str, l);
    _len += l;
    return *this;
}
string operator+(const string& left, const char* right) {
    string s(left);
    s += right;
    return s;
}
string operator+(const char* left, const string& right) {
    string s(left);
    s += (string)right;
    return s;
}
string operator+(const string& left, const string& right) {
    string s(left);
    s += (string)right;
    return s;
}
string operator+(const string& left, const char right) {
    string s(left);
    if(left._real_len <= left._len + 2) {
        s.inclen(INC_STEP);
    }
    s._cur[s._len] = right;
    s._len++;
    return s;
}
string operator+(const char left, const string& right) {
    string s(right);
    if(right._real_len <= right._len + 2) {
        s.inclen(INC_STEP);
    }
    string::ncopy(s._cur+1, right._cur, s._len);
    s._cur[0] = left;
    s._len++;
    return s;
}

string & string::operator=(const string& str) {
    if(this == &str) {
        return *this;
    }
    if(_c_ptr != NULL) {
        free(_c_ptr);
    }
    if(str.length() <= 0) {
        _len = 0;
        _c_ptr = NULL;
    }
    _len = str.length();
    _c_ptr = initptr(str._len+1);
    _real_len = str._len+1;
    ncopy(_c_ptr,str._c_ptr, _len);

    return *this;
}
string & string::operator+=(const string& str) {
    if(this == &str || str._len <= 0) {
        return *this;
    }
    inclen(str._len);
    ncopy(_cur + _len, str._c_ptr, str.length());
    _len += str._len;

    return *this;
}
string & string::operator+=(const char ch) {
    if(_real_len <= _len + 2) {
        inclen(INC_STEP);
    }
    _cur[_len] = ch;
    _len++;
    return *this;
}


char& string::operator[](u32 index) {
    if(index < 0 || index >= _len) {
        raise(SIGSEGV);
    }
    return *(_cur + index);
}

bool string::operator==(const string& str) {
    return comp(_cur, str._cur) == 0;
}

string string::reverse() {
    string s = string(*this);

    for(int i=0;i<(s._len/2);i++) {
        int r = s._len - 1 - i;
        char tmp = s._cur[r];
        s._cur[r] = s._cur[i];
        s._cur[i] = tmp;
    }

    return s;
}

bool string::startsWith(const char ch) {
    return *_cur == ch;
}
bool string::startsWith(const string& str) {
    if(str._cur == NULL || str._len == 0) {
        return false;
    }

    return ncomp(_cur, str._cur, str._len) == 0;
}

bool string::endsWith(const char ch) {
    return _cur[_len-1] == ch;
}
bool string::endsWith(const string& str) {
    if(str._cur == NULL || str._len == 0) {
        return false;
    }
    int idx = _len - str._len;
    if(idx < 0) {
        return false;
    }
    return ncomp(_cur + idx, str._cur, str._len) == 0;
}

string string::toLower() {
    string s(*this);

    for(int i=0;i<s._len;i++) {
        if(s[i] >= 'A' && s[i] <= 'Z') {
            s[i] += 'a' - 'A';
        }
    }
    return s;
}
string string::toUpper() {
    string s(*this);

    for(int i=0;i<s._len;i++) {
        if(s[i] >= 'a' && s[i] <= 'z') {
            s[i] -= 'a' - 'A';
        }
    }
    return s;
}

string::string() {
    _len = 0;
    _c_ptr = NULL;
    _cur = NULL;
}


string::string(const char* str) {
    _len = len(str);
    _c_ptr = initptr(_len+1);
    _real_len = _len + 1;
    _cur = _c_ptr;
    ncopy(_c_ptr, str, _len);
}

string::string(const string& str) {
    _real_len = str._real_len;
    _len = str._len;
    _c_ptr = initptr(_real_len);
    _cur = _c_ptr;
    ncopy(_c_ptr, str._c_ptr, _len);
}

string::string(u32 initial_size) {
    _len = 0;
    _c_ptr = initptr(initial_size);
    _cur = _c_ptr;
    _real_len = initial_size;
}

string::~string() {
    if(_c_ptr != NULL) {
        free(_c_ptr);
        _c_ptr = NULL;
        _cur = NULL;
    }
}
