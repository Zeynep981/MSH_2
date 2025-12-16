#include "../include/TVDevice.h"

TVDevice::TVDevice(int id, const std::string& name)
    : Device(id, name, DEVICE_TV) {
}

TVDevice::TVDevice(const TVDevice& other)
    : Device(other.GetId(), other.GetName(), DEVICE_TV) {
}

Device* TVDevice::clone() const {
    return new TVDevice(*this);
}

std::string TVDevice::GetStatus() const {
    return Device::GetStatus() + " [Tip: Televizyon]";
}