
#include "MH/MH.hpp"
#include "MH/OS/Log.hpp"


namespace MH {


Application::Application()
    : m_windowHandle(nullptr)
{

}


Application::~Application()
{
    Finalize();
}


Result Application::Initialize(WindowHandle windowHandle, u32 width, u32 height)
{
    MH_LOGV("Application::Initialize");

    m_windowHandle = windowHandle;
    m_width = width;
    m_height = height;

    return Result(true);
}

Result Application::Finalize()
{
    MH_LOGV("Application::Finalize");

    m_windowHandle = nullptr;

    return Result(true);
}

void Application::OnResize(u32 width, u32 height)
{
    MH_LOGV("Application::OnResize");
    MH_UNUSED(width);
    MH_UNUSED(height);
}

void Application::OnKey(KEY_CODE key, bool isDown)
{
    MH_LOGV("Application::OnKey");

    if (isDown && key == KEY_CODE_ESCAPE)
    {
        MHDestroyWindow(m_windowHandle);
    }
}

void Application::OnMouse(u32 x, u32 y, MOUSE_BUTTON button, bool isDown)
{
    MH_LOGV("Application::OnMouse");
    MH_UNUSED(x);
    MH_UNUSED(y);
    MH_UNUSED(button);
    MH_UNUSED(isDown);
}

void Application::OnMouseWheel(u32 x, u32 y, s32 wheelDelta)
{
    MH_LOGV("Application::OnMouseWheel");
    MH_UNUSED(x);
    MH_UNUSED(y);
    MH_UNUSED(wheelDelta);
}

void Application::OnUpdate(f64 deltaTime)
{
    MH_UNUSED(deltaTime);
}

void Application::OnRender()
{

}


} // namespace MH

