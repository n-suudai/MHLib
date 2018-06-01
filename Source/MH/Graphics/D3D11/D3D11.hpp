
#pragma once


#include <d3d11.h>
#include <dxgi.h>
#include <wrl.h>


namespace MH {
namespace Graphics {
namespace D3D11 {


template<typename T>
using ComPtr = Microsoft::WRL::ComPtr<T>;


} // namespace D3D11
} // namespace Graphics
} // namespace MH

