#ifndef CRITICALDEVICE_H
#define CRITICALDEVICE_H

#include "Device.h"

// LLR5: Dedektor ve Alarm kapatilamaz.
class CriticalDevice : public Device {
public:
    CriticalDevice(int id, const std::string& name, DeviceType type);

    virtual Device* clone() const;
    virtual void PowerOff(); // Override ederek kapatmayi engelliyoruz
};

#endif#pragma once
