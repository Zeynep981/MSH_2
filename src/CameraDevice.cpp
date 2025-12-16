#include "../include/CameraDevice.h"
#include <iostream> // cout icin gerekli

CameraDevice::CameraDevice(int id, const std::string& name)
    : Device(id, name, DEVICE_CAMERA), fps(30) { // Varsayilan 30 FPS
}

CameraDevice::CameraDevice(const CameraDevice& other)
    : Device(other.GetId(), other.GetName(), DEVICE_CAMERA), fps(other.fps) {
}

Device* CameraDevice::clone() const {
    return new CameraDevice(*this);
}

// YENI EKLENEN FONKSIYON
void CameraDevice::SetFPS(int newFps) {
    // KORUMA: Cihaz kapaliysa islem yapma
    if (!isActive) {
        std::cout << "[HATA] Kamera kapali! FPS ayari icin once cihazi acin." << std::endl;
        return;
    }

    this->fps = newFps;
    std::cout << "[KAMERA] FPS degeri " << fps << " olarak ayarlandi." << std::endl;
}

std::string CameraDevice::GetStatus() const {
    // Status'te FPS'i de gosterelim
    return Device::GetStatus() + " [Guvenlik: Aktif] [FPS: " + std::to_string(fps) + "]";
}