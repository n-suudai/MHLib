
#include "MH/MH.hpp"
#include "MH/OS/Log.hpp"


namespace MH {


Application::Application()
    : m_windowHandle(nullptr)
    , m_width(0)
    , m_height(0)
    , m_isAlive(true)
{

}

Application::~Application()
{
    Finalize();
}

Result Application::Initialize(WindowHandle windowHandle, u32 width, u32 height)
{
    MH_LOGV("Application::Initialize(windowHandle : {0}, width : {1}, height : {2})", (u64)windowHandle, width, height);

    m_windowHandle = windowHandle;
    m_width = width;
    m_height = height;

    return MH_MAKE_RESULT(true);
}

Result Application::Finalize()
{
    MH_LOGV("Application::Finalize()");

    m_windowHandle = nullptr;

    return Result(true);
}

void Application::OnResize(u32 width, u32 height)
{
    MH_LOGV("Application::OnResize(width : {0}, height{1})", width, height);
}

void Application::OnKey(KEY_CODE key, bool isDown)
{
    MH_LOGV("Application::OnKey(key : {0}, isDown : {1})",
            KeyCodeToString(key).c_str(),
            isDown ? "true" : "false"
    );

    if (isDown && key == KEY_CODE_ESCAPE)
    {
        m_isAlive = false;
    }
}

void Application::OnMouse(u32 x, u32 y, MOUSE_BUTTON button, bool isDown)
{
    MH_LOGV("Application::OnMouse(x : {0}, y : {1}, button : {2}, isDown : {3})",
            x,
            y,
            MouseButtonToString(button).c_str(),
            isDown ? "true" : "false"
    );
}

void Application::OnMouseWheel(u32 x, u32 y, s32 wheelDelta)
{
    MH_LOGV("Application::OnMouseWheel(x : {0}, y : {1}, wheelDelta : {2})",
            x,
            y,
            wheelDelta
    );
}

void Application::OnUpdate(f64 deltaTime)
{
    MH_UNUSED(deltaTime);
}

void Application::OnRender()
{

}


} // namespace MH

