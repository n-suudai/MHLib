
#pragma once


#include "MH/OS/Types.hpp"
#include "MH/KeyCode.hpp"
#include "MH/Result.hpp"
#include "Windows.hpp"
#include <string>


namespace MH {


struct Position2D
{
    s32 x;
    s32 y;
};


struct Size2D
{
    u32 width;
    u32 height;
};


struct WindowCallbacks
{
    // リサイズ
    void(*pOnResize)(Size2D const& size, void* pUser);
    void* pOnResizeUser;

    // キーダウン
    void(*pOnKeyDown)(KEY_CODE key, void* pUser);
    void* pOnKeyDownUser;

    // キーアップ
    void(*pOnKeyUp)(KEY_CODE key, void* pUser);
    void* pOnKeyUpUser;

    // マウスキーダウン
    void(*pOnMouseKeyDown)(Position2D const& position, MOUSE_BUTTON button, void* pUser);
    void* pOnMouseKeyDownUser;

    // マウスキーアップ
    void(*pOnMouseKeyUp)(Position2D const& position, MOUSE_BUTTON button, void* pUser);
    void* pOnMouseKeyUpUser;

    // マウスホイール
    void(*pOnMouseWheel)(Position2D const& position, s32 delta, void* pUser);
    void* pOnMouseWheelUser;
};


class Window
{
public:
    Window();

    ~Window();

    Result Initialize(Size2D const& clientSize, std::string const& title);

    void Finalize();

    void SetCallbacks(WindowCallbacks const& callbacks);

    bool IsLoop() const;

    void Sleep(u32 milliSeconds);

    void PostQuit();

    Size2D const& GetClientSize() const;

    WindowHandle GetWindowHandle() const;

    void ShowMessageBox(std::string const& message, std::string const& caption);

private:
    static LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

    LRESULT CALLBACK WindowProcedureInstance(HWND, UINT, WPARAM, LPARAM);

private:
    HWND            m_hWnd;
    HINSTANCE       m_hInstance;
    Size2D          m_ClientSize;
    Size2D          m_WindowSize;
    WindowCallbacks m_Callbacks;
};


} // namespace MH

