#ifndef DEVICEFACTORY_H
#define DEVICEFACTORY_H

#include "Device.h"
#include "DeviceConfig.h"

// REQ8: Yeni cihaz ekleme altyapisi (Factory Pattern)
class DeviceFactory {
public:
    // Statik metod: Nesne olusturmadan dogrudan cagrilabilir.
    static Device* createDevice(DeviceType type, const DeviceConfig& config);
};

#endif