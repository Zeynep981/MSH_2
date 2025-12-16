#ifndef DETECTORDEVICE_H
#define DETECTORDEVICE_H

#include "CriticalDevice.h"

class DetectorDevice : public CriticalDevice {
public:
    DetectorDevice(int id, const std::string& name);
    DetectorDevice(const DetectorDevice& other);

    virtual Device* clone() const;
};

#endif