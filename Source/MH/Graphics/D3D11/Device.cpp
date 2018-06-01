

#include "Device.hpp"
#include "D3D11Utility.hpp"


namespace MH {
namespace Graphics {


Result CreateDevice(
    std::unique_ptr<IDevice>& outDevice,
    const DeviceDesc& deviceDesc
)
{
    return D3D11::Device::Create(
        outDevice,
        deviceDesc
    );
}


namespace D3D11 {


Result Device::Create(
    std::unique_ptr<IDevice>& outDevice,
    const DeviceDesc& deviceDesc
)
{
    Result result;

    std::unique_ptr<Device> device = std::make_unique<Device>();

    result = device->Initialize(deviceDesc);

    if (!result) { return result; }

    outDevice = std::move(device);

    return MH_MAKE_RESULT(true);
}

//Result Device::GetImmediateContext(
//    std::unique_ptr<IDeviceContext>& outImmediateContext
//)
//{
//
//}

Device::Device()
    : m_featureLevel(D3D_FEATURE_LEVEL_11_0)
    , m_device()
    , m_immediateContext()
{

}

Device::~Device()
{
    Finalize();
}

Result Device::Initialize(
    const DeviceDesc& deviceDesc
)
{
    return CreateDefaultDeviceAndImmediateContext(
        deviceDesc.enableDebug,
        true,
        m_featureLevel,
        m_device,
        m_immediateContext
    );
}

void Device::Finalize()
{

}


} // namespace D3D11
} // namespace Graphics
} // namespace MH

