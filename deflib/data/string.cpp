#include "string.h"

u32 string::Len(const char* str) {
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

int string::Compare(const char* str1, const char* str2) {
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

int string::Compare_n(const char* str1, const char* str2, u32 n) {
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
    while(new_alloc = (char*)realloc(_c_str, l), new_alloc == NULL);
    _c_str = new_alloc;
    _cur = _c_str;
    _real_len = l;
    for(int i=_len;i<l;i++) {
        _c_str[i] = 0x00;
    }
    return _c_str;
}


u32 string::length() const {
    return this->_len;
}

char * string::c_str() const {
    return this->_cur;
}
Array<char> string::charArray() {
    Array<char> charr(_real_len);
    copy_mem(charr.ptr(), _c_str, _real_len);
    return charr;
}


string & string::operator=(const char* str) {
    _len = Len(str);

    if(_c_str != NULL) {
        free(_c_str);
    }
    _c_str = initptr(_len+1);
    _real_len = _len+1;
    copy_mem(_c_str, str, _len);
    _cur = _c_str;

    return *this;
}
string & string::operator=(const string& str) {
    if(this == &str) {
        return *this;
    }
    if(_c_str != NULL) {
        free(_c_str);
    }
    if(str._real_len <= 0) {
        _len = 0;
        _real_len = 0;
        _c_str = NULL;
        _cur = NULL;
    }
    _len = str._len;
    _c_str = initptr(str._real_len);
    _cur = _c_str;
    _real_len = str._real_len;
    copy_mem(_c_str,str._c_str, _len);

    return *this;
}
string & string::operator=(const Array<char> char_array) {
    Array<char> arr = (Array<char>)char_array;
    if(_c_str == arr.ptr()) {
        return *this;
    }
    if(_c_str != NULL) {
        free(_c_str);
    }
    u64 len = arr.count();
    if(arr[len-1] != 0x00) {
        _c_str = initptr(len+1);
        _real_len = len+1;
    }
    else {
        _c_str = initptr(len);
        _real_len = len;
    }
    _cur = _c_str;
    _len = len;
    copy_mem(_c_str, arr.ptr(), len);

    return *this;
}

bool string::operator==(const string& str) {
    return Compare(_cur, str._cur) == 0;
}

string & string::operator+=(const char* str) {
    if(str == NULL) {
        return *this;
    }
    u32 l = Len(str);
    if(l <= 0) {
        return *this;
    }
    inclen(l);
    copy_mem(_c_str + _len, str, l);
    _len += l;
    return *this;
}
string & string::operator+=(const string& str) {
    if(this == &str || str._len <= 0) {
        return *this;
    }
    inclen(str._len);
    copy_mem(_cur + _len, str._c_str, str.length());
    _len += str._len;

    return *this;
}
string & string::operator+=(const char ch) {
    if(_real_len <= _len + 2) {
        inclen(1);
    }
    _cur[_len] = ch;
    _len++;
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
    s.inclen(1);
    s._cur[s._len] = right;
    s._len++;
    return s;
}
string operator+(const char left, const string& right) {
    string s(right._len + 2);
    *s._cur = left;
    copy_mem(s._cur+1, right._cur, right._len);
    s._len = right._len + 1;
    return s;
}

char& string::operator[](u32 index) {
    if(index < 0 || index >= _len) {
        raise(SIGSEGV);
    }
    return *(_cur + index);
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
    if(str._len == 1) {
        return startsWith(*str._cur);
    }
    return Compare_n(_cur, str._cur, str._len) == 0;
}

bool string::endsWith(const char ch) {
    return _cur[_len-1] == ch;
}
bool string::endsWith(const string& str) {
    if(str._cur == NULL || str._len == 0) {
        return false;
    }
    if(str._len == 1) {
        return endsWith(*str._cur);
    }
    int idx = _len - str._len;
    if(idx < 0) {
        return false;
    }
    return Compare_n(_cur + idx, str._cur, str._len) == 0;
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
int string::countOccurrences(const char ch) {
    if(_cur == NULL || _c_str == NULL || _len == 0) {
        return 0;
    }
    int cnt = 0;
    for(int i=0;i<_len;i++) {
        if(_cur[i] == ch) {
            cnt++;
        }
    }
    return cnt;
}
int string::countOccurrences(const string& str) {
    if(_cur == NULL || _c_str == NULL || _len <= 0 || _len < str._len) {
        return 0;
    }
    if(str._len == 1) {
        return countOccurrences(*str._cur);
    }

    char* splstr = str._cur;
    int cnt = 0;
    for(int i=0;i<_len;i++) {
        if(_cur[i] == splstr[0]) {
            if(Compare_n(_cur + i, splstr, str._len) == 0) {
                cnt++;
            }
        }
    }
    return cnt;
}

Array<int> string::getOccurrences(const char ch) {
    int count = countOccurrences(ch);
    if(count == 0) {
        return Array<int>();
    }
    Array<int> arr(count);

    int oc = 0;
    for(int i=0;i<_len;i++) {
        if(_cur[i] == ch) {
            arr[oc] = i;
            oc++;
        }
    }

    return arr;
}

Array<int> string::getOccurrences(const string& str) {
    int count = countOccurrences(str);
    if(str._len == 1){
        return getOccurrences(*str._cur);
    }
    if(count == 0) {
        return Array<int>();
    }
    Array<int> arr(count);

    char* splstr = str._cur;
    int oc = 0;
    for(int i=0;i<_len;i++) {
        if(_cur[i] == splstr[0]) {
            if(Compare_n(_cur + i, splstr, str._len) == 0) {
                arr[oc] = i;
                oc++;
            }
        }
    }

    return arr;
}
string string::replace(const char og, const char ch) {
    if(_c_str == NULL || _cur == NULL) {
        return string();
    }
    string s(*this);
    for(int i=0;i<s._len;i++) {
        if(_cur[i] == og) {
            _cur[i] = ch;
        }
    }
    return s;
}
string string::replace(const char og, const string& str) {
    if(_c_str == NULL || _cur == NULL) {
        return string();
    }
    Array<string> sections = split(og);
    string s = sections[0];
    for(int i=1;i<sections.count();i++) {
        s += str + sections[i];
    }
    return s;
}
string string::replace(const string& og, const char ch) {
    if(_c_str == NULL || _cur == NULL) {
        return string();
    }
    Array<string> sections = split(og);
    string s = sections[0];
    for(int i=1;i<sections.count();i++) {
        s += ch + sections[i];
    }
    return s;
}
string string::replace(const string& og, const string str) {
    if(_c_str == NULL || _cur == NULL) {
        return string();
    }
    Array<string> sections = split(og);
    string s = sections[0];
    for(int i=1;i<sections.count();i++) {
        s += str + sections[i];
    }
    return s;
}


Array<string> string::split(const char ch) {
    if(_c_str == NULL || _cur == NULL) {
        return NULL;
    }
    string s(*this);
    Array<int> occ = getOccurrences(ch);
    int occlen = occ.length();
    int arrlen = occlen + 1;
    Array<string> arr(arrlen);
    arr.clear();
    if(occlen == 0) {
        arr[0] = *this;
        return arr;
    }
    int start = -1;
    for(int i=0;i<occlen;i++) {
        arr[i] = string(occ[i] - start);
        start++;
        copy_mem(arr[i]._cur, _cur + start, occ[i] - start);
        arr[i]._len = occ[i] - start;
        start = occ[i];
    }
    arr[arrlen-1] = string(_len - occ[occlen-1]);
    copy_mem(arr[arrlen-1]._cur, _cur + start + 1, arr[arrlen-1]._real_len);
    arr[arrlen-1]._len = _len - occ[occlen-1] - 1;

    return arr;
}
Array<string> string::split(const string& str) {
    if(_c_str == NULL || _cur == NULL ||  str._cur == NULL || str._len == 0 || _len == 0) {
        return NULL;
    }
    if(str._len == 1) {
        return split(*str._cur);
    }

    string s(*this);
    Array<int> occ = getOccurrences(str);
   int occlen = occ.length();
    int arrlen = occlen + 1;
    Array<string> arr(arrlen);
    arr.clear();
    if(occlen == 0) {
        arr[0] = *this;
        return arr;
    }
    int start = 0 - str._len;
    for(int i=0;i<occlen;i++) {
        start += str._len;
        arr[i] = string(occ[i] - start + 1);
        copy_mem(arr[i]._cur, _cur + start, occ[i] - start);
        arr[i]._len = occ[i] - start;
        start = occ[i];
    }
    start += str._len;

    if(occ[occlen-1] == _len - str._len) {
        arr[arrlen-1] = "";
        arr[arrlen-1]._len = 0;
        return arr;
    }
    arr[arrlen-1] = string(_len - (occ[occlen-1] + str._len) + 1);
    copy_mem(arr[arrlen-1]._cur, _cur + start, arr[arrlen-1]._real_len);
    arr[arrlen-1]._len = _len - occ[occlen-1];

    return arr;
}
string string::substring(u32 start, u32 n) {
    if(_c_str == NULL || _cur == NULL || _len <= 0) {
        return string();
    }
    if(start + n > _len) {
        n = _len - start;
    }
    string s(n+1);
    copy_mem(s._cur, _cur + start, n);
    s._len = n;
    return s;
}
string string::substring(u32 start) {
    if(_c_str == NULL || _cur == NULL || _len <= 0) {
        return string();
    }
    u32 new_size = _len - start;
    string s(new_size + 1);
    copy_mem(s._cur, _cur + start, new_size);
    s._len = new_size;
    return s;
}
string string::format(const string& fmt, ...) {
    string s = "";
    if(s == fmt || fmt._len == 0) {
        return s;
    }
    char* fmtstr = fmt.c_str();
    va_list args;
    va_start(args, fmtstr);
    char* buf;
    vasprintf(&buf, fmt.c_str(), args);
    s += buf;
    free(buf);
    va_end(args);
    return s;
}


string::string() {
    _len = 0;
    _c_str = NULL;
    _cur = NULL;
}


string::string(const char* str) {
    _len = Len(str);
    _c_str = initptr(_len+1);
    _real_len = _len + 1;
    _cur = _c_str;
    copy_mem(_c_str, str, _len);
}

string::string(const string& str) {
    _real_len = str._real_len;
    _len = str._len;
    _c_str = initptr(_real_len);
    _cur = _c_str;
    copy_mem(_c_str, str._c_str, _len);
}

string::string(u32 initial_size) {
    _len = 0;
    _c_str = initptr(initial_size);
    _cur = _c_str;
    _real_len = initial_size;
}

string::~string() {
    if(_c_str != NULL) {
        free(_c_str);
        _c_str = NULL;
        _cur = NULL;
    }
}
