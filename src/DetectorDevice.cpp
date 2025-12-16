#include "../include/DetectorDevice.h"

DetectorDevice::DetectorDevice(int id, const std::string& name)
    : CriticalDevice(id, name, DEVICE_DETECTOR) {
}

DetectorDevice::DetectorDevice(const DetectorDevice& other)
    : CriticalDevice(other.GetId(), other.GetName(), DEVICE_DETECTOR) {
}

Device* DetectorDevice::clone() const {
    return new DetectorDevice(*this);
}