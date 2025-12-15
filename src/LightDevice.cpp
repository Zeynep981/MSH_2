#include "../include/LightDevice.h"

LightDevice::LightDevice(int id, const std::string& name, int brightness, const std::string& color)
    : Device(id, name, DEVICE_LIGHT), brightness(brightness), color(color) {
}

// Copy Constructor
LightDevice::LightDevice(const LightDevice& other)
    : Device(other.GetId(), other.GetName(), DEVICE_LIGHT),
    brightness(other.brightness), color(other.color) {
}

Device* LightDevice::clone() const {
    return new LightDevice(*this); // Kendisinin kopyasini dondurur
}

std::string LightDevice::GetStatus() const {
    return Device::GetStatus() + " [Renk: " + color + "]";
}