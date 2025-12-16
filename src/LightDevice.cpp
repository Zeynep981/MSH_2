#include "../include/LightDevice.h"
#include <iostream> // cout icin gerekli

LightDevice::LightDevice(int id, const std::string& name, int brightness, const std::string& color)
    : Device(id, name, DEVICE_LIGHT), brightness(brightness), color(color) {
}

// Copy Constructor
LightDevice::LightDevice(const LightDevice& other)
    : Device(other.GetId(), other.GetName(), DEVICE_LIGHT),
    brightness(other.brightness), color(other.color) {
}

Device* LightDevice::clone() const {
    return new LightDevice(*this);
}

// YENI EKLENEN FONKSIYON
void LightDevice::SetBrightness(int level) {
    // KORUMA: Cihaz kapaliysa islem yapma
    if (!isActive) {
        std::cout << "[HATA] Lamba kapali! Parlaklik ayari icin once lambayi acin." << std::endl;
        return;
    }

    // Sinir kontrolu (0-100 arasi)
    if (level < 0) level = 0;
    if (level > 100) level = 100;

    this->brightness = level;
    std::cout << "[LAMBA] Parlaklik %" << level << " yapildi." << std::endl;
}

std::string LightDevice::GetStatus() const {
    return Device::GetStatus() + " [Renk: " + color + "] [Parlaklik: %" + std::to_string(brightness) + "]";
}