#include "../include/CameraDevice.h"

CameraDevice::CameraDevice(int id, const std::string& name)
    : Device(id, name, DEVICE_CAMERA) {
}

CameraDevice::CameraDevice(const CameraDevice& other)
    : Device(other.GetId(), other.GetName(), DEVICE_CAMERA) {
}

Device* CameraDevice::clone() const {
    return new CameraDevice(*this);
}

std::string CameraDevice::GetStatus() const {
    return Device::GetStatus() + " [Guvenlik: Aktif]";
}