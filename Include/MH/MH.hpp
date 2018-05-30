
#pragma once


#include "MH/OS/Types.hpp"
#include "MH/Result.hpp"
#include "MH/KeyCode.hpp"
#include <memory>


#if !defined(MH_UNUSED)
#    define MH_UNUSED(x) static_cast<void>(x)
#endif


namespace MH {


class Application
{
public:
    Application();

    virtual ~Application();

    virtual Result Initialize(WindowHandle windowHandle, u32 width, u32 height);

    virtual Result Finalize();

    virtual void OnResize(u32 width, u32 height);

    virtual void OnKey(KEY_CODE key, bool isDown);

    virtual void OnMouse(u32 x, u32 y, MOUSE_BUTTON button, bool isDown);

    virtual void OnMouseWheel(u32 x, u32 y, s32 wheelDelta);

    virtual void OnUpdate(f64 deltaTime);

    virtual void OnRender();
    
    virtual bool IsAlive() const { return m_isAlive; }

protected:
    WindowHandle    m_windowHandle;
    u32             m_width;
    u32             m_height;
    bool            m_isAlive;
};


} // namespace MH


std::unique_ptr<MH::Application> MHCreateApplication();

