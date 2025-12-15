#include "../include/DeviceManager.h"
#include "../include/DeviceFactory.h"
#include "../include/DeviceConfig.h"
#include <iostream>

// Baslangicta bos
DeviceManager* DeviceManager::instance = NULL;

DeviceManager::DeviceManager() {
    std::cout << "[SYSTEM] DeviceManager baslatildi." << std::endl;
}

DeviceManager* DeviceManager::getInstance() {
    if (instance == NULL) {
        instance = new DeviceManager();
    }
    return instance;
}

void DeviceManager::AddDevice(DeviceType type, int count, const std::string& baseName) {
    for (int i = 0; i < count; ++i) {
        // Her yeni cihaz icin essiz bir ID uretiyoruz (Simdilik basitce 100 + size)
        int newId = 100 + (int)devices.size() + 1;

        // Fabrika icin siparis fisini hazirla
        DeviceConfig config(newId, baseName);

        // Fabrikayi cagir
        Device* newDevice = DeviceFactory::createDevice(type, config);

        if (newDevice != NULL) {
            devices.push_back(newDevice); // Listeye ekle
            std::cout << "[YONETICI] Eklendi: " << newDevice->GetName() << " (ID: " << newId << ")" << std::endl;
        }
    }
}

void DeviceManager::RemoveDevice(int id) {
    // Listede cihaz arama (Iterator ile)
    for (std::vector<Device*>::iterator it = devices.begin(); it != devices.end(); ++it) {
        if ((*it)->GetId() == id) {
            std::cout << "[YONETICI] Siliniyor: " << (*it)->GetName() << std::endl;
            delete* it; // Hafizadan sil
            devices.erase(it); // Listeden sil
            return;
        }
    }
    std::cout << "[HATA] ID " << id << " bulunamadi!" << std::endl;
}

void DeviceManager::PowerOnDevice(int id) {
    for (size_t i = 0; i < devices.size(); ++i) {
        if (devices[i]->GetId() == id) {
            devices[i]->PowerOn();
            return;
        }
    }
    std::cout << "[HATA] Cihaz bulunamadi: " << id << std::endl;
}

void DeviceManager::PowerOffDevice(int id) {
    for (size_t i = 0; i < devices.size(); ++i) {
        if (devices[i]->GetId() == id) {
            devices[i]->PowerOff();
            return;
        }
    }
    std::cout << "[HATA] Cihaz bulunamadi: " << id << std::endl;
}

void DeviceManager::ListAllDevices() {
    std::cout << "\n--- TUM CIHAZLAR ---" << std::endl;
    for (size_t i = 0; i < devices.size(); ++i) {
        std::cout << devices[i]->GetStatus() << std::endl;
    }
    std::cout << "--------------------\n" << std::endl;
}