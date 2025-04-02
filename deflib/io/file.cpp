#include "file.h"

File::File() {
    _initialized = false;
    _fp = (FILE*)NULL;
    _fname = "";
    _path = "";
    _path_full = "";
    _binary = false;
    _fsize = 0;
    _pos = 0;
}

File::File(const string& path, OpenMode mode, bool binary) {
    _initialized = false;
    _mode = mode;
    string open_mode = _modes[mode];
    if(binary) {
        open_mode += 'b';
    }
    _fp = fopen(path.c_str(), open_mode.c_str());
    if(_fp == NULL) {
        _fname  = "";
        _path = "";
        _path_full = "";
        _fsize = 0;
        _pos = 0;
        return;
    }
    _binary = binary;

    _pos = ftell(_fp);
    fseek(_fp, 0, SEEK_SET);
    _fsize = ftell(_fp);
    fseek(_fp, 0, SEEK_END);
    _fsize = ftell(_fp) - _fsize;
    fseek(_fp, _pos, SEEK_SET);

    initPaths(path);
    _initialized = true;
}
File::File(const string& path, string mode) {
    _initialized = false;

    if(mode.startsWith('r')) {
        _mode = OpenMode::Read;
        if(mode.contains('+')) {
            _mode = OpenMode::ReadWrite;
        }
    }
    else if(mode.startsWith('w')) {
        _mode = OpenMode::CreateWrite;
        if(mode.contains('+')) {
            _mode = OpenMode::CreateReadWrite;
        }
    }
    else if(mode.startsWith('a')) {
        _mode = OpenMode::Append;
        if(mode.contains('+')) {
            _mode = OpenMode::ReadAppend;
        }
    }
    else {
        _fname  = "";
        _path = "";
        _path_full = "";
        _fsize = 0;
        _pos = 0;
        return;
    }
    _binary = mode.contains('b');

    _fp = fopen(path.c_str(), mode.c_str());
    if(_fp == NULL) {
        _fname  = "";
        _path = "";
        _path_full = "";
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
    _initialized = true;
}

File::~File() {
    if(_fp != NULL) {
        fclose(_fp);
    }
    _fp = (FILE*)NULL;
}

u64 File::size() {
    return _fsize;
}

s32 File::seek(s64 offset, s32 whence) {
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
s32 File::seek(s64 offset) {
    if(_fp == NULL || _fsize <= 0) {
        return -1;
    }
    if(offset < 0) {
        return -2;
    }
    _pos = offset;
    fseek(_fp, offset, SEEK_SET);
    return 0;
}

u64 File::tell() {
    _pos = ftell(_fp);
    return _pos;
}
u64 File::pos() {
    return _pos;
}

string File::location() {
    string test = _path_full.replace(PATH_SEPERATOR + _fname, "");
    return test;
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
    if(_fp != NULL || _initialized) {
        return -1;
    }
    *this = File(path, mode, binary);
    if(_initialized) {
        return 0;
    }
    else return -2;
}
int File::open(const string& path, string mode) {
    if(_fp != NULL || _initialized) {
        return -1;
    }
    *this = File(path, mode);
    if(_initialized) {
        return 0;
    }
    else return -2;
}

void File::close() {
    if(_fp == NULL || !_initialized) {
        return;
    }
    fclose(_fp);
    _fp = (FILE*)NULL;
    _path = "";
    _path_full = "";
    _fsize = 0;
    _pos = 0;
    _initialized = false;
}
bool File::isOpen() {
    return _initialized;
}
File::OpenMode File::mode() {
    return _mode;
}
File& File::operator=(const File& f) {
    if(_fp != NULL) {
        fclose(_fp);
    } 
    _fp = f._fp;
    _path = f._path;
    _path_full = f._path_full;
    _fsize = f._fsize;
    _pos = f._pos;
    _initialized = f._initialized;
    _mode = f._mode;
    _binary = f._binary;
    _modes = f._modes;

    (*(File*)&f)._fp = (FILE*)NULL;

    return *this;
}
u64 File::read(Array<u8>& buffer, u64 n) {
    if(!_initialized || _fp == NULL || _mode == Append || _mode == CreateWrite) {
        return 0;
    }
    u64 cnt = buffer.count();
    if(cnt <= 0) {
        return 0;
    }
    if(cnt < n) {
        n = cnt;
    }
    int read_els = fread(buffer.ptr(), 1, n, _fp);
    _pos += n;
    return read_els;
}
Array<byte> File::readFile() {
    if(!_initialized || _fp == NULL || _mode == Append || _mode == CreateWrite || _fsize == 0) {
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
    if(_fp == NULL || _fsize == 0 || _pos >= _fsize || _mode == Append || _mode == CreateWrite) {
        return 0;
    }
    _pos++;
    return fgetc(_fp);
}
byte File::readByte() {
    if(_fp == NULL || _fsize == 0 || _pos >= _fsize || _mode == Append || _mode == CreateWrite) {
        return 0;
    }
    _pos++;
    return fgetc(_fp);
}
s16 File::readShort() {
    if(_fp == NULL || _fsize == 0 || _pos >= _fsize || _mode == Append || _mode == CreateWrite) {
        return 0;
    }
    s16 val;
    fread(&val, sizeof(s16), 1, _fp);
    _pos += sizeof(s16);
    return val;
}
u16 File::readUnsignedShort() {
    return (u16)readShort();
}
s32 File::readInt() {
    if(_fp == NULL || _fsize == 0 || _pos >= _fsize || _mode == Append || _mode == CreateWrite) {
        return 0;
    }
    s32 val;
    fread(&val, 1, sizeof(s32), _fp);
    _pos += sizeof(s32);
    return val;
}
u32 File::readUnsignedInt() {
    return (u32)readInt();
}
s64 File::readLong() {
    if(_fp == NULL || _fsize == 0 || _pos >= _fsize|| _mode == Append || _mode == CreateWrite) {
        return 0;
    }
    s64 val;
    fread(&val, sizeof(s64), 1, _fp);
    _pos += sizeof(s64);
    return val;
}
u64 File::readUnsignedLong(){
    return (u64)readLong();
}
f32 File::readFloat() {
    s32 data = readInt();
    return *((f32*)&data);
}
f64 File::readDouble() {
    s64 data = readLong();
    return *((f64*)&data);
}
string File::readLine() {
    if(_fp == NULL || _fsize == 0 || _pos >= _fsize || _mode == Append || _mode == CreateWrite) {
        return string();
    }
    char* cstr = (char*)malloc(_fsize);
    fgets(cstr, _fsize, _fp);
    string s(cstr);
    free(cstr);
    s = s.replace('\n', "");
    _pos = ftell(_fp);
    return s;
}

u64 File::write(Array<u8> bytes) {
    if(_fp == NULL || !_initialized || _mode == Read) {
        return 0;
    }
    if(bytes.count() <= 0 || bytes.ptr() == NULL) {
        return 0;
    }
    u64 written = fwrite(bytes.ptr(), 1, bytes.count(), _fp);
    _pos += written;
    _fsize += written;
    return written;
}
u64 File::write(Array<u8> bytes, u64 n) {
    if(_fp == NULL || !_initialized || _mode == Read) {
        return 0;
    }
    if(bytes.count() <= 0 || bytes.ptr() == NULL || n <= 0) {
        return 0;
    }
    if(n > bytes.count()) {
        n = bytes.count();
    }
    u64 written = fwrite(bytes.ptr(), 1, n, _fp);
    _pos += written;
    _fsize += written;
    return written;
}

void File::writeChar(char value) {
    if(_fp == NULL || !_initialized || _mode == Read) {
        return;
    }
    s32 written = fputc(value, _fp);
    if(written != (s32)value) {
        return;
    }
    _pos++;
    _fsize++;
}
void File::writeByte(byte value) {
    writeChar((s8)value);
}
void File::writeShort(s16 value) {
    if(_fp == NULL || !_initialized || _mode == Read) {
        return;
    }
    if(fwrite(&value, sizeof(s16), 1, _fp) < 1) {
        return;
    }
    _pos += sizeof(s16);
    _fsize += sizeof(s16);
}
void File::writeUnsignedShort(u16 value) {
    writeShort((s16)value);
}
void File::writeInt(s32 value) {
    if(_fp == NULL || !_initialized || _mode == Read) {
        return;
    }
    if(fwrite(&value, sizeof(s32), 1, _fp) < 1) {
        return;
    }
    _pos += sizeof(s32);
    _fsize += sizeof(s32);
}
void File::writeUnsignedInt(u32 value) {
    writeInt((s32)value);
}
void File::writeLong(s64 value) {
    if(_fp == NULL || !_initialized || _mode == Read) {
        return;
    }
    if(fwrite(&value, sizeof(s64), 1, _fp) < 1) {
        return;
    }
    _pos += sizeof(s64);
    _fsize += sizeof(s64);
}
void File::writeUnsignedLong(u64 value) {
    writeLong((u64)value);
}
void File::writeFloat(f32 value) {
    if(_fp == NULL || !_initialized || _mode == Read) {
        return;
    }
    if(fwrite(&value, sizeof(f32), 1, _fp) < 1) {
        return;
    }
    _pos += sizeof(f32);
    _fsize += sizeof(f32);
}
void File::writeDouble(f64 value) {
    if(_fp == NULL || !_initialized || _mode == Read) {
        return;
    }
    if(fwrite(&value, sizeof(f64), 1, _fp) < 1) {
        return;
    }
    _pos += sizeof(f64);
    _fsize += sizeof(f64);
}
void File::writeLine(string line) {
    line += '\n';
    write(line.charArray().reinterpret<u8>(), line.length());
    return;
}

void File::setLength(u64 new_length) {
    if(new_length == _fsize) {
        return;
    }
    u8* data = (u8*)NULL;
    while(data = (u8*)malloc(new_length), data == NULL);
    u64 prevPos = _pos;
    u64 prevSize = _fsize;
    OpenMode prevMode = _mode;
    if(_mode == OpenMode::Append || _mode == OpenMode::CreateWrite) {
        fclose(_fp);
        string open_mode = _modes[OpenMode::ReadWrite];
        if(_binary) {
            open_mode += 'b';
        }
        _fp = fopen(_path.c_str(), open_mode.c_str());
    }
    fseek(_fp, 0, SEEK_SET);
    if(new_length > prevSize) {
        fread(data, 1, prevSize, _fp);
        fill_mem(data + prevSize, 0x00, new_length - prevSize);
    }
    else {
        fread(data, 1, new_length, _fp);
    }
    fclose(_fp);
    _fp = fopen(_path.c_str(), "wb");
    fwrite(data, 1, new_length, _fp);
    fclose(_fp);

    string open_mode = _modes[prevMode];
    if(_binary) {
        open_mode += 'b';
    }
    _fp = fopen(_path.c_str(), open_mode.c_str());
    fseek(_fp, prevPos, SEEK_SET);
    _fsize = new_length;

    free(data);
}

void File::initPaths(const string& path) {
    _path = string(path);
    _path_full = "";
    Array<string> dirs_path = _path.split(PATH_SEPERATOR);
    int curpath = dirs_path.count() - 1;
    _fname = dirs_path[curpath];

    char* tmp = (char*)malloc(PATH_MAX);
    realpath(".", tmp);
    string cwd = string(tmp);
    free(tmp);
    if(_path.startsWith(string(".") + PATH_SEPERATOR)) {
        _path_full = cwd + PATH_SEPERATOR + _path.substring(2);
        return;
    }
    if(curpath <= 0) {
        _path_full = cwd + PATH_SEPERATOR + _path;
        return;
    }
    Array<string> dirs_cwd = cwd.split(PATH_SEPERATOR);
    int updirs =  _path.countOccurrences(string("..") + PATH_SEPERATOR);
    if(updirs <= 0) {
        _path_full = _path;
        return;
    }
    int cwddir = dirs_cwd.count() - updirs;
    int pathdir = dirs_path.count() - updirs;

    for(int i=0;i<cwddir;i++) {
        _path_full += dirs_cwd[i] + PATH_SEPERATOR;
    }
    _path_full += _path.replace("../", "");
}
