#ifndef DEVICECONFIG_H
#define DEVICECONFIG_H

#include <string>

// Cihaz olustururken gereken tum ayarlari tasiyan kutu
struct DeviceConfig {
    int id;
    std::string name;

    // Iþýk icin
    int brightness;
    std::string color;

    // Diger cihazlar icin (ileride eklenebilir)
    // std::string model;
    // int fps;

    // Varsayilan yapici (Default Constructor)
    DeviceConfig(int id, std::string name)
        : id(id), name(name), brightness(100), color("Beyaz") {}
};

#endif#pragma once
