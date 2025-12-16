#ifndef CAMERADEVICE_H
#define CAMERADEVICE_H

#include "Device.h"

class CameraDevice : public Device {
public:
    CameraDevice(int id, const std::string& name);
    CameraDevice(const CameraDevice& other);

    virtual Device* clone() const;
    virtual std::string GetStatus() const;
};

#endif