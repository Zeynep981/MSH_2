#ifndef DEVICE_H
#define DEVICE_H

#include <string>
#include <iostream>

// LLR13: Bildirim Tipleri
enum NotificationType {
    NOTIFY_LOG,
    NOTIFY_ALARM,
    NOTIFY_SMS
};

// Cihaz Tipleri
enum DeviceType {
    DEVICE_LIGHT,
    DEVICE_CAMERA,
    DEVICE_TV,
    DEVICE_DETECTOR,
    DEVICE_ALARM
};

// Abstract Base Class (Soyut Temel Sinif)
class Device {
protected:
    int id;
    std::string name;
    DeviceType type;
    bool isActive;
    bool isFunctional;
    NotificationType notificationType; // LLR13

public:
    Device(int id, const std::string& name, DeviceType type);
    virtual ~Device();

    // LLR3-LLR4: Acma Kapama
    virtual void PowerOn();
    virtual void PowerOff();

    // Durum Bilgisi
    virtual std::string GetStatus() const;

    // Getter & Setter
    int GetId() const;
    void SetId(int newId);
    std::string GetName() const;
    void SetNotificationType(NotificationType type);

    // LLR18: Prototype Pattern (Klonlama)
    virtual Device* clone() const = 0;

    void SetFunctional(bool status);
    NotificationType GetNotificationType() const;
};

#endif