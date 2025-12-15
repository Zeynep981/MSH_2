#include "../include/CriticalDevice.h"

CriticalDevice::CriticalDevice(int id, const std::string& name, DeviceType type)
    : Device(id, name, type) {
    isActive = true; // Kritik cihazlar varsayilan olarak aciktir
}

Device* CriticalDevice::clone() const {
    return new CriticalDevice(*this);
}

void CriticalDevice::PowerOff() {
    // LLR5: Kapatilamaz kurali
    std::cout << "[UYARI] " << name << " kritik cihazdir, KAPATILAMAZ!" << std::endl;
}