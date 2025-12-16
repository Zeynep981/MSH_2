#include "../include/DeviceManager.h"
#include "../include/DeviceFactory.h"
#include "../include/DeviceConfig.h"
#include "../include/Logger.h"
#include "../include/NotificationService.h"
#include <iostream>

#include <sstream>
template <typename T>
std::string to_string_98(const T& n) {
    std::ostringstream stm;
    stm << n;
    return stm.str();
}

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
void DeviceManager::HandleFailure(int id) {
    // 1. Loglama servisine ulas
    Logger* logger = Logger::getInstance();

    // 2. Bildirim servisini olustur
    NotificationService notifyService;

    bool found = false;
    for (size_t i = 0; i < devices.size(); ++i) {
        if (devices[i]->GetId() == id) {
            // LLR14: Durumu Inaktif yap
            devices[i]->SetFunctional(false);

            // Logla
           // SSTR yerine to_string_98 kullaniyoruz
            std::string logMsg = "Ariza Tespiti: " + devices[i]->GetName() + " (ID: " + to_string_98(id) + ")";
            logger->Log(logMsg);

            // LLR15: Kullaniciya SMS gonder
            std::string userMsg = devices[i]->GetName() + " failure.";
            notifyService.NotifyUser(devices[i]->GetNotificationType(), userMsg);

            found = true;
            break;
        }
    }

    if (!found) {
        // SSTR yerine to_string_98 kullaniyoruz
        logger->Log("HATA: Ariza bildirilen ID bulunamadi: " + to_string_98(id));
    }
}