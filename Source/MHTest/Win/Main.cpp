

#include <tchar.h>
#include <Windows.h>


#if defined(DEBUG) || defined(_DEBUG)
#include <crtdbg.h>
#define EnableMemoryLeakCheck() _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF)
#else
#define EnableMemoryLeakCheck()
#endif


#include "MH/MH.hpp"
#include "MH/Graphics.hpp"
#include "Window.hpp"


using namespace MH;


#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")
#pragma comment(lib, "dxguid.lib")


class ApplicationTest : public Application
{
public:
    typedef Application Super;

    Result Initialize(WindowHandle windowHandle, u32 width, u32 height) override
    {
        Result result = Super::Initialize(windowHandle, width, height);

        if (!result) { return result; }

        Graphics::DeviceDesc deviceDesc;
        deviceDesc.enableDebug = true;

        result = Graphics::CreateDevice(
            m_device,
            deviceDesc
        );

        return result;
    }

    Result Finalize() override
    {
        return Super::Finalize();
    }

private:
    std::unique_ptr<Graphics::IDevice> m_device;
};


std::unique_ptr<MH::Application> MHCreateApplication()
{
    return std::make_unique<ApplicationTest>();
}


void MHDestroyWindow(WindowHandle windowHandle)
{
    HWND hWnd = reinterpret_cast<HWND>(windowHandle);
    DestroyWindow(hWnd);
}


// リサイズ
void OnResize(const Size2D& newSize, void* pUser)
{
    Application* pApplication = reinterpret_cast<Application*>(pUser);
    pApplication->OnResize(newSize.width, newSize.height);
}


// キーダウン
void OnKeyDown(KEY_CODE key, void* pUser)
{
    Application* pApplication = reinterpret_cast<Application*>(pUser);
    pApplication->OnKey(key, true);
}


// キーアップ
void OnKeyUp(KEY_CODE key, void* pUser)
{
    Application* pApplication = reinterpret_cast<Application*>(pUser);
    pApplication->OnKey(key, false);
}


// マウスキーダウン
void OnMouseKeyDown(const Position2D& position, MOUSE_BUTTON button, void* pUser)
{
    Application* pApplication = reinterpret_cast<Application*>(pUser);
    pApplication->OnMouse(position.x, position.y, button, true);
}


// マウスキーアップ
void OnMouseKeyUp(const Position2D& position, MOUSE_BUTTON button, void* pUser)
{
    Application* pApplication = reinterpret_cast<Application*>(pUser);
    pApplication->OnMouse(position.x, position.y, button, false);
}


// マウスホイール
void OnMouseWheel(const Position2D& position, s32 wheelDelta, void* pUser)
{
    Application* pApplication = reinterpret_cast<Application*>(pUser);
    pApplication->OnMouseWheel(position.x, position.y, wheelDelta);
}


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

    Size2D clientSize = { 640, 480 };
    std::unique_ptr<Window> window = std::make_unique<Window>();

    Result result = window->Initialize(clientSize, "MHTest");
    if (!result)
    {
        return 0;
    }

    std::unique_ptr<Application> application = MHCreateApplication();
    result = application->Initialize(window->GetWindowHandle(), 640, 480);

    if (!result)
    {
        return 0;
    }

    // コールバックの設定
    {
        WindowCallbacks callbacks = { 0 };
        // リサイズ
        callbacks.pOnResize = OnResize;
        callbacks.pOnResizeUser = application.get();
        // キーダウン
        callbacks.pOnKeyDown = OnKeyDown;
        callbacks.pOnKeyDownUser = application.get();
        // キーアップ
        callbacks.pOnKeyUp = OnKeyUp;
        callbacks.pOnKeyUpUser = application.get();
        // マウスキーダウン
        callbacks.pOnMouseKeyDown = OnMouseKeyDown;
        callbacks.pOnMouseKeyDownUser = application.get();
        // マウスキーアップ
        callbacks.pOnMouseKeyUp = OnMouseKeyUp;
        callbacks.pOnMouseKeyUpUser = application.get();
        // マウスホイール
        callbacks.pOnMouseWheel = OnMouseWheel;
        callbacks.pOnMouseWheelUser = application.get();

        window->SetCallbacks(callbacks);
    }

    while (window->IsLoop())
    {
        if (application->IsAlive())
        {
            application->OnUpdate(0.0);
            application->OnRender();
            window->Sleep(16);
        }
        else
        {
            window->PostQuit();
        }
    }

    return 0;
}




