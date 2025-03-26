#include "file.h"

File::File() {
    _fp = NULL;
    _fname = NULL;
    _path = NULL;
    _fsize = 0;
}

File::File(const string& path, OpenMode mode, bool binary) {
    string open_mode = _modes[mode];
    if(binary) {
        open_mode += 'b';
    }
    _fp = fopen(path.c_str(), open_mode.c_str());
    if(_fp == NULL) {
        _fname  = NULL;
        _path = NULL;
        _fsize = 0;
        return;
    }

    _fsize = ftell(_fp);
    fseek(_fp, 0, SEEK_END);
    _fsize = ftell(_fp) - _fsize;
    fseek(_fp, 0, SEEK_SET);

    string p(path);
    Array<int> dirs = p.countOccurrences('/');

    if(dirs.count() > 0) {
        Array<string> sa = p.split('/');
        _fname = sa[sa.count()-1];
        _path = p.substring(0, dirs[dirs.count()-1]+1);
    }
    else {
        _fname = p;
        _path = "./";
    }
}

File::~File() {
    fclose(_fp);
    _fp = NULL;
}

u64 File::size() {
    return _fsize;
}

int File::seek(s64 offset, s32 whence) {
    return fseek(_fp, offset, whence);
}

u64 File::tell() {
    return ftell(_fp);
}

u64 File::read(Array<u8>& buffer, u64 n) {
    u64 cnt = buffer.count();
    if(cnt <= 0) {
        buffer = *(new Array<u8>(n));
        cnt = n;
    }
    if(cnt < n) {
        n = cnt;
    }
    int read_els = fread(buffer.ptr(), 1, n, _fp);

    return read_els;
}

