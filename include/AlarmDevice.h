#ifndef ALARMDEVICE_H
#define ALARMDEVICE_H

#include "CriticalDevice.h"

class AlarmDevice : public CriticalDevice {
public:
    AlarmDevice(int id, const std::string& name);
    AlarmDevice(const AlarmDevice& other);

    virtual Device* clone() const;
};

#endif