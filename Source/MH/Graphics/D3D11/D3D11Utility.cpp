

#include "D3D11Utility.hpp"
#include "D3D11Result.hpp"


namespace MH {
namespace Graphics {
namespace D3D11 {


Result CreateDefaultDeviceAndImmediateContext(
    bool                            enableDebug,
    bool                            enableBGRASupport,
    D3D_FEATURE_LEVEL&              outFeatureLevel,
    ComPtr<ID3D11Device>&           outDevice,
    ComPtr<ID3D11DeviceContext>&    outImmediateContext
)
{
    Result result = MH_MAKE_RESULT(true);

    // ファクトリーを生成
    ComPtr<IDXGIFactory> factory;
    result = MH_MAKE_D3D11RESULT(
        CreateDXGIFactory(IID_PPV_ARGS(&factory))
    );
    if (!result) { return result; }


    // デバイス&コンテキストを生成
    {
        uint32_t createDeviceFlags = 0;

        if (enableBGRASupport)
        { // BGRAサポートを有効化
            createDeviceFlags |= D3D11_CREATE_DEVICE_BGRA_SUPPORT;
        }

        if (enableDebug)
        { // デバッグを有効化
            createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
        }

        D3D_FEATURE_LEVEL featureLevels[] = {
            D3D_FEATURE_LEVEL_11_1,
            D3D_FEATURE_LEVEL_11_0,
        };

        result = MH_MAKE_D3D11RESULT(
            D3D11CreateDevice(
                nullptr,
                D3D_DRIVER_TYPE_HARDWARE, // ハードウェア ドライバー を使用
                nullptr,
                createDeviceFlags,
                featureLevels,
                _countof(featureLevels),
                D3D11_SDK_VERSION,
                &outDevice,
                &outFeatureLevel,
                &outImmediateContext
            )
        );
    }

    return result;
}


} // namespace D3D11
} // namespace Graphics
} // namespace MH

