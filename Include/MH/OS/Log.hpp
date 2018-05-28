
#pragma once


#include "MH/External/fmt.hpp"


#if defined(MH_BUILD_DEBUG)
#   define MH_LOGV(format, ...) MH::OS::Log::Verbose(format, __VA_ARGS__)
#   define MH_LOGD(format, ...) MH::OS::Log::Debug(format, __VA_ARGS__)
#   define MH_LOGI(format, ...) MH::OS::Log::Info(format, __VA_ARGS__)
#   define MH_LOGW(format, ...) MH::OS::Log::Warning(format, __VA_ARGS__)
#   define MH_LOGE(format, ...) MH::OS::Log::Error(format, __VA_ARGS__)
#   define MH_LOGA(format, ...) MH::OS::Log::Assert(format, __VA_ARGS__)
#else
#   define MH_LOGV(format, ...)
#   define MH_LOGD(format, ...)
#   define MH_LOGI(format, ...)
#   define MH_LOGW(format, ...)
#   define MH_LOGE(format, ...)
#   define MH_LOGA(format, ...)
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

template<class ... Args>
inline void Log(Level level, const char* pFormat, const Args& ... args)
{
    std::string message = fmt::format(pFormat, args ...);
    Log(level, message.c_str());
}


inline void Verbose(const char* pMessage)
{
    Log(Level::Verbose, pMessage);
}

template<class ... Args>
inline void Verbose(const char* pFormat, const Args& ... args)
{
    std::string message = fmt::format(pFormat, args ...);
    Log(Level::Verbose, message.c_str());
}


inline void Debug(const char* pMessage)
{
    Log(Level::Debug, pMessage);
}

template<class ... Args>
inline void Debug(const char* pFormat, const Args& ... args)
{
    std::string message = fmt::format(pFormat, args ...);
    Log(Level::Debug, message.c_str());
}


inline void Info(const char* pMessage)
{
    Log(Level::Info, pMessage);
}

template<class ... Args>
inline void Info(const char* pFormat, const Args& ... args)
{
    std::string message = fmt::format(pFormat, args ...);
    Log(Level::Info, message.c_str());
}


inline void Warning(const char* pMessage)
{
    Log(Level::Warning, pMessage);
}

template<class ... Args>
inline void Warning(const char* pFormat, const Args& ... args)
{
    std::string message = fmt::format(pFormat, args ...);
    Log(Level::Warning, message.c_str());
}


inline void Error(const char* pMessage)
{
    Log(Level::Error, pMessage);
}

template<class ... Args>
inline void Error(const char* pFormat, const Args& ... args)
{
    std::string message = fmt::format(pFormat, args ...);
    Log(Level::Error, message.c_str());
}


inline void Assert(const char* pMessage)
{
    Log(Level::Assert, pMessage);
}

template<class ... Args>
inline void Assert(const char* pFormat, const Args& ... args)
{
    std::string message = fmt::format(pFormat, args ...);
    Log(Level::Assert, message.c_str());
}


} // namespace Log
} // namespace OS
} // namespace MH

