
#pragma once


#include "MH/Result.hpp"
#include <memory>


namespace MH {
namespace Graphics {


struct DeviceDesc
{
    bool  enableDebug;
};

struct IDeviceContext
{
    virtual ~IDeviceContext() = default;
};

struct IDevice
{
    virtual ~IDevice() = default;

    //virtual Result GetImmediateContext(
    //    std::unique_ptr<IDeviceContext>& outImmediateContext
    //) = 0;
};

Result CreateDevice(
    std::unique_ptr<IDevice>& outDevice,
    const DeviceDesc& deviceDesc
);


} // namespace Graphics
} // namespace MH

