﻿
#pragma once


#if defined(MH_BUILD_DEBUG)
#   define MH_LOGV(message) MH::OS::Log::Verbose(message)
#   define MH_LOGD(message) MH::OS::Log::Debug(message)
#   define MH_LOGI(message) MH::OS::Log::Info(message)
#   define MH_LOGW(message) MH::OS::Log::Warning(message)
#   define MH_LOGE(message) MH::OS::Log::Error(message)
#   define MH_LOGA(message) MH::OS::Log::Assert(message)
#else
#   define MH_LOGV(message)
#   define MH_LOGD(message)
#   define MH_LOGI(message)
#   define MH_LOGW(message)
#   define MH_LOGE(message)
#   define MH_LOGA(message)
#endif


namespace MH {
namespace OS {
namespace Log {


enum class Level
{
    Verbose = 0,
    Debug   = 1,
    Info    = 2,
    Warning = 3,
    Error   = 4,
    Assert  = 5,
};


void Log(Level level, const char* pMessage);


inline void Verbose(const char* pMessage)
{
    Log(Level::Verbose, pMessage);
}


inline void Debug(const char* pMessage)
{
    Log(Level::Debug, pMessage);
}


inline void Info(const char* pMessage)
{
    Log(Level::Info, pMessage);
}


inline void Warning(const char* pMessage)
{
    Log(Level::Warning, pMessage);
}


inline void Error(const char* pMessage)
{
    Log(Level::Error, pMessage);
}


inline void Assert(const char* pMessage)
{
    Log(Level::Assert, pMessage);
}


} // namespace Log
} // namespace OS
} // namespace MH

