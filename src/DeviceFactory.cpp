#include "../include/DeviceFactory.h"
#include "../include/LightDevice.h"
#include "../include/CriticalDevice.h"
#include <iostream>

Device* DeviceFactory::createDevice(DeviceType type, const DeviceConfig& config) {
    Device* newDevice = NULL;

    switch (type) {
    case DEVICE_LIGHT:
        // Isik icin config icindeki renk ve parlakligi kullaniyoruz
        newDevice = new LightDevice(config.id, config.name, config.brightness, config.color);
        break;

    case DEVICE_ALARM:
    case DEVICE_DETECTOR:
        // Kritik cihazlar (Alarm/Dedektor)
        newDevice = new CriticalDevice(config.id, config.name, type);
        break;

    case DEVICE_TV:
    case DEVICE_CAMERA:
        // Henuz bu siniflari yazmadik, simdilik bos geciyoruz veya hata veriyoruz
        std::cout << "[FABRIKA] Uyari: TV ve Kamera henuz yapilmadi!" << std::endl;
        break;

    default:
        std::cout << "[FABRIKA] Hata: Gecersiz cihaz tipi!" << std::endl;
        break;
    }

    return newDevice;
}