
#import <Cocoa/Cocoa.h>
#import "MH/MH.hpp"

using namespace MH;


std::unique_ptr<Application> MHCreateApplication()
{
    return std::make_unique<Application>();
}


int main(int argc, const char * argv[]) {
    return NSApplicationMain(argc, argv);
}
