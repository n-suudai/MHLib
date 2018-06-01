
#pragma once


#include "MH/Result.hpp"
#include "D3D11.hpp"


namespace MH {
namespace Graphics {
namespace D3D11 {


Result CreateDefaultDeviceAndImmediateContext(
    bool                            enableDebug,
    bool                            enableBGRASupport,
    D3D_FEATURE_LEVEL&              outFeatureLevel,
    ComPtr<ID3D11Device>&           outDevice,
    ComPtr<ID3D11DeviceContext>&    outImmediateContext
);


} // namespace D3D11
} // namespace Graphics
} // namespace MH

