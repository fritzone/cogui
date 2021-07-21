#include "logstream.h"
#include <pthread.h>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <locale>
#include <codecvt>

logstream::logstream(int line, const char *pFile, const char *pFunc, LogLevel level) :
    mOutputStream(),
    mFile(pFile),
    mFunc(pFunc),
    mLevel(level),
    mLine(line)
{
}

static std::string timeToStr(const std::chrono::system_clock::time_point &time)
{
    std::stringstream ss;
    const std::string format = "%Y-%m-%d %H:%M:%S";
    std::time_t tt = std::chrono::system_clock::to_time_t(time);
    //std::tm tm = *std::gmtime(&tt); //GMT (UTC)
    std::tm tm = *std::localtime(&tt); //Locale time-zone, usually UTC by default.
    ss << std::put_time( &tm, format.c_str() );
    std::string ts = ss.str();
    return ts;
}

static void do_log(const std::string& msg)
{
    std::ofstream fs;
    fs.open("app.log", std::ios::app | std::ios::out);
    fs << "[" << timeToStr(std::chrono::system_clock::now()) << "] " << msg;
}

logstream::~logstream()
{
    std::stringstream arguments;
    pthread_t tid = pthread_self();

    arguments << errstrings[mLevel] << mFile.substr(mFile.find_last_of('/') + 1) << ":" << mLine << " (" << mFunc << ") [" << (uint64_t)tid << "] " << mOutputStream.str() << "\n";

    do_log(arguments.str());

}

logstream &logstream::appendSpace()
{
    mOutputStream << ' ';
    mOutputStream.flush();
    return *this;
}

logstream &logstream::operator<<(bool t)
{
    mOutputStream << (t ? "true" : "false");
    return appendSpace();
}

logstream &logstream::operator<<(const cogui::rect& r)
{
	mOutputStream << "{ (" << r.x <<", " << r.y <<") x (" << r.width << ", " << r.height << ")}";
	return appendSpace();
}

logstream &logstream::operator<<(char t)
{
    std::string s = "";
    s += t;
    mOutputStream << s;
    return appendSpace();
}

logstream &logstream::operator<<(wchar_t t)
{
    std::wstring s;
    s += t;
    return operator <<(s);
}

logstream &logstream::operator<<(signed short t)
{
    mOutputStream << t;
    return appendSpace();
}

logstream &logstream::operator<<(unsigned short t)
{
    mOutputStream << t;
    return appendSpace();
}

logstream &logstream::operator<<(signed int t)
{
    mOutputStream << t;
    return appendSpace();
}

logstream &logstream::operator<<(unsigned int t)
{
    mOutputStream << t;
    return appendSpace();
}

logstream &logstream::operator<<(signed long t)
{
    mOutputStream << t;
    return appendSpace();
}

logstream &logstream::operator<<(unsigned long t)
{
    mOutputStream << t;
    return appendSpace();
}

logstream &logstream::operator<<(float t)
{
    mOutputStream << t;
    return appendSpace();
}

logstream &logstream::operator<<(double t)
{
    mOutputStream << t;
    return appendSpace();
}

logstream &logstream::operator<<(const char *pChars)
{
    mOutputStream << pChars;
    return appendSpace();
}

logstream &logstream::operator<<(const std::string &rString)
{
    mOutputStream << '\"' << rString << '\"';
    return appendSpace();
}

logstream &logstream::operator<<(const std::wstring& ws)
{
    try {
        using convert_type = std::codecvt_utf8<wchar_t>;
        std::wstring_convert<convert_type, wchar_t> converter;
        std::string s = converter.to_bytes( ws );
        return operator <<(s);

    }  catch (...) {
        return appendSpace();
    }
}

logstream &logstream::operator<<(const void *pData)
{
    mOutputStream << pData;
    return appendSpace();
}

logstream &logstream::operator<<(const std::chrono::system_clock::time_point &time)
{
    auto ts = timeToStr(time);
    mOutputStream << ts;
    return *this;
}
