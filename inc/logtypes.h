#ifndef _LOG_TYPES_H
#define _LOG_TYPES_H

#include <map>
#include <string>

enum class LogLevel
{
    LOG_EMERGENCY   = 1,
    LOG_CRITICAL    = 2,
    LOG_ERROR       = 3,
    LOG_WARNING     = 4,
    LOG_INFORMATION = 5,
    LOG_DEBUG       = 6,
    LOG_TRACE       = 7
};

static std::map<LogLevel, std::string> errstrings
{
    {LogLevel::LOG_EMERGENCY,  "EMERGENCY   "},
    {LogLevel::LOG_CRITICAL,   "CRITICAL    "},
    {LogLevel::LOG_ERROR,      "ERROR       "},
    {LogLevel::LOG_WARNING,    "WARNING     "},
    {LogLevel::LOG_INFORMATION,"INFORMATION "},
    {LogLevel::LOG_DEBUG,      "DEBUG       "},
    {LogLevel::LOG_TRACE,      "TRACE       "}
};

#endif
