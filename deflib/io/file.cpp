#include "file.h"

File::File() {
    initialized = false;
    _fp = NULL;
    _fname = NULL;
    _path = NULL;
    _path_full = NULL;
    _fsize = 0;
    _pos = 0;
}

File::File(const string& path, OpenMode mode, bool binary) {
    initialized = false;
    string open_mode = _modes[mode];
    if(binary) {
        open_mode += 'b';
    }
    _fp = fopen(path.c_str(), open_mode.c_str());
    if(_fp == NULL) {
        _fname  = NULL;
        _path = NULL;
        _path_full = NULL;
        _fsize = 0;
        _pos = 0;
        return;
    }

    _pos = ftell(_fp);
    fseek(_fp, 0, SEEK_SET);
    _fsize = ftell(_fp);
    fseek(_fp, 0, SEEK_END);
    _fsize = ftell(_fp) - _fsize;
    fseek(_fp, _pos, SEEK_SET);

    initPaths(path);
    initialized = true;
}

File::~File() {
    if(_fp != NULL) {
        fclose(_fp);
    }
    _fp = NULL;
}

u64 File::size() {
    return _fsize;
}

s64 File::seek(s64 offset, s32 whence) {
    if(_fp == NULL || _fsize <= 0) {
        return -1;
    }

    if(whence == SEEK_SET) {
        if(offset >= _fsize || offset < 0) {
            return -2;
        }
        _pos = offset;
    }
    else if(whence == SEEK_CUR) {
        if(offset < ((~_pos) + 1) || offset >= _fsize - _pos) {
            return -2;
        }
        _pos += offset;
    }
    else if(whence == SEEK_END) {
        if(offset > 0) {
            return -2;
        }
        _pos = _fsize + offset;
    }
    else {
        _pos = 0;
        return -3;
    }
    fseek(_fp, offset, whence);
    return 0;
}

u64 File::tell() {
    return ftell(_fp);
}
u64 File::pos() {
    return _pos;
}

string File::location() {
    return _path_full.replace(PATH_SEPERATOR + _fname, "");
}
string File::path() {
    return _path;
}
string File::fullPath() {
    return _path_full;
}

string File::name() {
    return _fname;
}
bool File::eof() {
    return _pos >= _fsize;
}
int File::open(const string& path, OpenMode mode, bool binary) {
    if(_fp != NULL || initialized) {
        return -1;
    }
    string open_mode = _modes[mode];
    if(binary) {
        open_mode += 'b';
    }
    _fp = fopen(path.c_str(), open_mode.c_str());
    if(_fp == NULL) {
        _fname  = NULL;
        _path = NULL;
        _path_full = NULL;
        _fsize = 0;
        _pos = 0;
        return -2;
    }

    _fsize = ftell(_fp);
    fseek(_fp, 0, SEEK_END);
    _fsize = ftell(_fp) - _fsize;
    fseek(_fp, 0, SEEK_SET);

    initPaths(path);
    _pos = 0;

    return 0;
}
void File::close() {
    if(_fp == NULL || !initialized) {
        return;
    }
    fclose(_fp);
    _fp = NULL;
    _path = NULL;
    _path_full = NULL;
    _fsize = 0;
    _pos = 0;
    initialized = false;
}
bool File::isOpen() {
    return initialized;
}


u64 File::read(Array<u8>& buffer, u64 n) {
    u64 cnt = buffer.count();
    if(cnt <= 0) {
        return 0;
    }
    if(cnt < n) {
        n = cnt;
    }
    int read_els = fread(buffer.ptr(), 1, n, _fp);

    return read_els;
}
Array<byte> File::readFile() {
    if(_fp == NULL || _fsize <= 0) {
        return Array<byte>();
    }
    Array<byte> ba(_fsize);
    if(_fsize <= 0) {
        return ba;
    }
    fseek(_fp, 0, SEEK_SET);
    fread(ba.ptr(), 1, _fsize, _fp);
    fseek(_fp, _pos, SEEK_SET);
    return ba;
}

char File::readChar() {
    if(_fp == NULL || _fsize == 0 || _pos >= _fsize) {
        return 0;
    }
    return fgetc(_fp);
}
byte File::readByte() {
    if(_fp == NULL || _fsize == 0 || _pos >= _fsize) {
        return 0;
    }
    return fgetc(_fp);
}
s16 File::readShort() {
    if(_fp == NULL || _fsize == 0 || _pos >= _fsize) {
        return 0;
    }
    s16 val;
    fread(&val, sizeof(s16), 1, _fp);
    return val;
}
u16 File::readUnsignedShort() {
    return (u16)readShort();
}
s32 File::readInt() {
    if(_fp == NULL || _fsize == 0 || _pos >= _fsize) {
        return 0;
    }
    s32 val;
    fread(&val, sizeof(s32), 1, _fp);
    return val;
}
u32 File::readUnsignedInt() {
    return (u32)readInt();
}
s64 File::readLong() {
    if(_fp == NULL || _fsize == 0 || _pos >= _fsize) {
        return 0;
    }
    s64 val;
    fread(&val, sizeof(s64), 1, _fp);
    return val;
}
u64 File::readUnsignedLong(){
    return (u64)readLong();
}
string File::readLine() {
    if(_fp == NULL || _fsize == 0 || _pos >= _fsize) {
        return string();
    }
    char* cstr = (char*)malloc(_fsize);
    fgets(cstr, _fsize, _fp);
    string s(cstr);
    free(cstr);
    s = s.replace('\n', "");
    return s;
}

void File::initPaths(const string& path) {
    _path = string(path);
    Array<string> dirs_path = _path.split(PATH_SEPERATOR);
    int curpath = dirs_path.count() - 2;
    _fname = dirs_path[curpath+1];

    char* tmp = (char*)malloc(PATH_MAX);
    realpath(".", tmp);
    string cwd = string(tmp);
    cwd += PATH_SEPERATOR + _fname;
    free(tmp);
    Array<string> dirs_cwd = cwd.split(PATH_SEPERATOR);
    int curcwd = dirs_cwd.count() - 2;

    _path_full = _fname;
    if(curpath == 0) {
        _path_full = cwd;
        return;
    }

}















