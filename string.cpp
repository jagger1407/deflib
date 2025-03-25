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
    for(int i=_len;i<l;i++) {
        _c_ptr[i] = 0x00;
    }
    return _c_ptr;
}


u32 string::length() const {
    return this->_len;
}

char * string::c_str() const {
    return this->_c_ptr;
}


string & string::operator=(const char* str) {
    _len = len(str);

    if(_c_ptr != NULL) {
        free(_c_ptr);
    }
    _c_ptr = initptr(_len+1);
    ncopy(_c_ptr, str, _len);

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

string & string::operator=(string& str) {
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
    _c_ptr = initptr(str.length()+1);
    ncopy(_c_ptr,str.c_str(), _len);

    return *this;
}
string & string::operator+=(const string& str) {
    if(this == &str || str.length() <= 0) {
        return *this;
    }
    inclen(str.length());
    ncopy(_c_ptr + _len, str.c_str(), str.length());
    _len += str.length();

    return *this;
}

string string::reverse() {
    string s = string(*this);

    for(int i=0;i<(s._len/2);i++) {
        int r = s._len - 1 - i;
        char tmp = s._c_ptr[r];
        s._c_ptr[r] = s._c_ptr[i];
        s._c_ptr[i] = tmp;
    }

    return s;
}


string::string() {
    _len = 0;
    _c_ptr = NULL;
}


string::string(const char* str) {
    _len = len(str);
    _c_ptr = initptr(_len+1);
    ncopy(_c_ptr, str, _len);
}

string::string(const string& str) {
    _len = str.length();
    _c_ptr = initptr(_len+1);
    ncopy(_c_ptr, str.c_str(), _len);
}

string::~string() {
    if(_c_ptr != NULL) {
        free(_c_ptr);
    }
}
