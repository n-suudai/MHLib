
#include "MH/OS/Log.hpp"
#include <string>
#include <sstream>
#import <Foundation/Foundation.h>

namespace MH {
namespace OS {
namespace Log {


void Log(Level level, const char* pMessage)
{
    std::stringstream ss;
    
    switch (level) {
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
        default:
            break;
    }
    
    ss << pMessage << " \n";
    
    @autoreleasepool
    {
        NSString * pNSString = [NSString stringWithCString : ss.str().c_str() encoding : NSUTF8StringEncoding];
        if (pNSString)
        {
            NSLog(@"%@", pNSString);
        }
    }
}


} // namespace Log
} // namespace OS
} // namespace MH

