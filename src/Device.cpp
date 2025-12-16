#include "../include/Device.h"
#include <sstream>

Device::Device(int id, const std::string& name, DeviceType type)
    : id(id), name(name), type(type), isActive(false), isFunctional(true), notificationType(NOTIFY_LOG) {
}

Device::~Device() {}

void Device::PowerOn() {
    if (isOn) { // Eðer zaten açýksa
        std::cout << "[UYARI] " << GetName() << " zaten acik durumda. Tekrar acilamaz." << std::endl;
        return;
    }

    // Loglama istersen: Logger::getInstance()->Log(GetName() + " acildi.");
    isOn = true;
    std::cout << "[ACIK] " << GetName() << " basariyla acildi." << std::endl;
}

void Device::PowerOff() {
    if (!isOn) { // Eðer zaten kapalýysa
        std::cout << "[UYARI] " << GetName() << " zaten kapali durumda. Tekrar kapatilamaz." << std::endl;
        return;
    }

    // Loglama istersen: Logger::getInstance()->Log(GetName() + " kapatildi.");
    isOn = false;
    std::cout << "[KAPALI] " << GetName() << " basariyla kapatildi." << std::endl;
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

void Device::SetFunctional(bool status) {
    isFunctional = status;
}

NotificationType Device::GetNotificationType() const {
    return notificationType;
}