#include "../include/Device.h"
#include <sstream>

Device::Device(int id, const std::string& name, DeviceType type)
    : id(id), name(name), type(type), isActive(false), isFunctional(true), notificationType(NOTIFY_LOG) {
}

Device::~Device() {}

void Device::PowerOn() {
    if (!isFunctional) {
        std::cout << "[ARIZA] " << name << " arizali, acilamiyor." << std::endl;
        return;
    }
    isActive = true;
    std::cout << name << " (" << id << ") acildi." << std::endl;
}

void Device::PowerOff() {
    isActive = false;
    std::cout << name << " (" << id << ") kapatildi." << std::endl;
}

std::string Device::GetStatus() const {
    std::stringstream ss;
    ss << "ID: " << id << " | Ad: " << name << " | Durum: " << (isActive ? "ACIK" : "KAPALI");
    return ss.str();
}

int Device::GetId() const { return id; }
void Device::SetId(int newId) { id = newId; }
std::string Device::GetName() const { return name; }
void Device::SetNotificationType(NotificationType type) { notificationType = type; }