#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include "Device.h"
#include <vector>

// SINGLETON PATTERN: Sadece bir tane yonetici olabilir.
class DeviceManager {
private:
    // Statik pointer (Tekil ornegi tutar)
    static DeviceManager* instance;

    // Cihazlari saklayan liste (Depo)
    std::vector<Device*> devices;

    // Constructor private yapilir ki kimse kafasina gore 'new DeviceManager()' diyemesin.
    DeviceManager();

public:
    // Yoneticiye ulasmak icin tek kapi
    static DeviceManager* getInstance();

    // REQ8: Cihaz Ekleme ve Cikarma
    void AddDevice(DeviceType type, int count, const std::string& baseName);
    void RemoveDevice(int id);

    // REQ6: Cihaz Kontrolu
    void PowerOnDevice(int id);
    void PowerOffDevice(int id);

    // Genel Durum Listeleme
    void ListAllDevices();
    void HandleFailure(int id);

    Device* GetDevice(int id);
};

#endif