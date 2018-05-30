
#include "MH/OS/Log.hpp"
#include <string>
#include <sstream>
#include <Windows.h>


namespace MH {
namespace OS {
namespace Log {


void PlatformLog(Level level, const char* pMessage)
{
    std::stringstream ss;

    switch (level)
    {
    case Level::Verbose:
        ss << "【VERBOSE】 : ";
        break;

    case Level::Debug:
        ss << "【DEBUG】 : ";
        break;

    case Level::Info:
        ss << "【INFO】 : ";
        break;

    case Level::Warning:
        ss << "【WARNING】 : ";
        break;

    case Level::Error:
        ss << "【ERROR】 : ";
        break;

    case Level::Assert:
        ss << "【ASSERT】 : ";
        break;
    }

    ss << pMessage << "\n";

    OutputDebugStringA(ss.str().c_str());
}


} // namespace Log
} // namespace OS
} // namespace MH

