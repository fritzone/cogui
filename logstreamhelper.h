#ifndef _LOGSTREAMHELPER_H_
#define _LOGSTREAMHELPER_H_

#include "logtypes.h"

#ifndef __PRETTY_FUNCTION__
#define __PRETTY_FUNCTION__ __FUNCTION__
#endif

#define log_emergency()     logstream(__LINE__, __FILE__, __PRETTY_FUNCTION__, LogLevel::LOG_EMERGENCY)
#define log_critical()      logstream(__LINE__, __FILE__, __PRETTY_FUNCTION__, LogLevel::LOG_CRITICAL)
#define log_error()         logstream(__LINE__, __FILE__, __PRETTY_FUNCTION__, LogLevel::LOG_ERROR)
#define log_warning()       logstream(__LINE__, __FILE__, __PRETTY_FUNCTION__, LogLevel::LOG_WARNING)
#define log_info()          logstream(__LINE__, __FILE__, __PRETTY_FUNCTION__, LogLevel::LOG_INFORMATION)
#define log_debug()         logstream(__LINE__, __FILE__, __PRETTY_FUNCTION__, LogLevel::LOG_DEBUG)
#define log_trace()         logstream(__LINE__, __FILE__, __PRETTY_FUNCTION__, LogLevel::LOG_TRACE)

#endif  // LOGSTREAMHELPER_H
