#include "../include/AlarmDevice.h"

AlarmDevice::AlarmDevice(int id, const std::string& name)
    : CriticalDevice(id, name, DEVICE_ALARM) {
}

AlarmDevice::AlarmDevice(const AlarmDevice& other)
    : CriticalDevice(other.GetId(), other.GetName(), DEVICE_ALARM) {
}

Device* AlarmDevice::clone() const {
    return new AlarmDevice(*this);
}