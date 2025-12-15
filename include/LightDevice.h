#ifndef LIGHTDEVICE_H
#define LIGHTDEVICE_H

#include "Device.h"

class LightDevice : public Device {
private:
    int brightness;
    std::string color;

public:
    LightDevice(int id, const std::string& name, int brightness, const std::string& color);
    LightDevice(const LightDevice& other); // Copy Constructor

    virtual Device* clone() const;
    virtual std::string GetStatus() const;
};

#endif