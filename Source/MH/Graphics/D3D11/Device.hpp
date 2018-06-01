
#pragma once


#include "MH/Graphics.hpp"
#include "D3D11.hpp"


namespace MH {
namespace Graphics {
namespace D3D11 {


class Device final : public IDevice
{
public:
    static Result Create(
        std::unique_ptr<IDevice>& outDevice,
        const DeviceDesc& deviceDesc
    );

    //Result GetImmediateContext(
    //    std::unique_ptr<IDeviceContext>& outImmediateContext
    //) override;

    Device();

    ~Device();

    Result Initialize(
        const DeviceDesc& deviceDesc
    );

    void Finalize();

private:
    D3D_FEATURE_LEVEL           m_featureLevel;
    ComPtr<ID3D11Device>        m_device;
    ComPtr<ID3D11DeviceContext> m_immediateContext;
};


} // namespace D3D11
} // namespace Graphics
} // namespace MH

