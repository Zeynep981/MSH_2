#include "../include/DeviceFactory.h"
#include "../include/LightDevice.h"
#include "../include/TVDevice.h"       // Yeni
#include "../include/CameraDevice.h"   // Yeni
#include "../include/AlarmDevice.h"    // Yeni
#include "../include/DetectorDevice.h" // Yeni
#include <iostream>

Device* DeviceFactory::createDevice(DeviceType type, const DeviceConfig& config) {
    Device* newDevice = NULL;

    switch (type) {
    case DEVICE_LIGHT:
        newDevice = new LightDevice(config.id, config.name, config.brightness, config.color);
        break;

    case DEVICE_TV:
        newDevice = new TVDevice(config.id, config.name);
        break;

    case DEVICE_CAMERA:
        newDevice = new CameraDevice(config.id, config.name);
        break;

    case DEVICE_ALARM:
        // Artik direkt CriticalDevice degil, AlarmDevice uretiyoruz
        newDevice = new AlarmDevice(config.id, config.name);
        break;

    case DEVICE_DETECTOR:
        // Artik direkt CriticalDevice degil, DetectorDevice uretiyoruz
        newDevice = new DetectorDevice(config.id, config.name);
        break;

    default:
        std::cout << "[FABRIKA] Hata: Gecersiz cihaz tipi!" << std::endl;
        break;
    }

    return newDevice;
}