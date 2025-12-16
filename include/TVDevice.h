#ifndef TVDEVICE_H
#define TVDEVICE_H

#include "Device.h"

class TVDevice : public Device {
public:
    TVDevice(int id, const std::string& name);
    TVDevice(const TVDevice& other); // Copy Constructor

    virtual Device* clone() const;
    virtual std::string GetStatus() const;

    void SetChannel(int channel);
};

#endif