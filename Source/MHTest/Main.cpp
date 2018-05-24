

#include <tchar.h>
#include <Windows.h>


#if defined(DEBUG) || defined(_DEBUG)
#include <crtdbg.h>
#define EnableMemoryLeakCheck() _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF)
#else
#define EnableMemoryLeakCheck()
#endif


#include "MH/MH.hpp"


int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                       _In_opt_ HINSTANCE hPrevInstance,
                       _In_ LPWSTR    lpCmdLine,
                       _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hInstance);
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nCmdShow);

    EnableMemoryLeakCheck();

    MH::Initialize();

    return 0;
}



