
#pragma once


#include "MH/Result.hpp"
#include "D3D11.hpp"


#define MH_MAKE_D3D11RESULT(hr)    MH_MAKE_RESULT(SUCCEEDED(hr), "{0}", MH::Graphics::D3D11::MakeResultText(hr))


namespace MH {
namespace Graphics {
namespace D3D11 {


std::string MakeResultText(HRESULT hr)
{
    std::string text;

    LPVOID lpMsgBuf;

    FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        hr,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // 既定の言語
        (LPSTR)&lpMsgBuf,
        0,
        NULL
    );

    // 文字列をコピーする。
    if (lpMsgBuf != nullptr)
    {
        text = (LPCSTR)lpMsgBuf;
    }

    // バッファを解放する。
    LocalFree(lpMsgBuf);

    return text;
}


} // namespace D3D11
} // namespace Graphics
} // namespace MH

