#ifndef _LOGSTREAM_H_
#define _LOGSTREAM_H_

#include "logtypes.h"
#include "rect.h"

#include <sstream>
#include <string>
#include <chrono>

class logstream
{
public:

    logstream(int line, const char *pFile, const char *pFunc, LogLevel level);

    virtual ~logstream();

    logstream& operator<<(bool t);
    logstream& operator<<(char t);
    logstream& operator<<(wchar_t t);
    logstream& operator<<(signed short t);
    logstream& operator<<(unsigned short t);
    logstream& operator<<(signed int t);
    logstream& operator<<(unsigned int t);
    logstream& operator<<(signed long t);
    logstream& operator<<(unsigned long t);
    logstream& operator<<(float t);
    logstream& operator<<(double t);
    logstream& operator<<(const char *pChars);
    logstream& operator<<(const std::string &rString);
    logstream& operator<<(const std::wstring &ws);
    logstream& operator<<(const void *pData);
	logstream& operator<<(const cogui::rect& r);
    logstream& operator<< (const std::chrono::system_clock::time_point& time);

private:
    logstream();
    logstream &operator=(const logstream &rOther);
    logstream(const logstream &rOther);

    inline logstream &appendSpace();

private:
    std::string mStreamBuffer;
    std::stringstream mOutputStream;
    std::string mFile;
    std::string mFunc;
    LogLevel mLevel;
    int mLine;
};

#endif  // logstream_H
