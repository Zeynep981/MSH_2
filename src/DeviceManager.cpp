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
    if (count <= 0) return;

    // 1. ILK CIHAZI FABRIKADAN URET (Master Copy)
    int firstId = 100 + (int)devices.size() + 1;
    DeviceConfig config(firstId, baseName);

    // Ilk cihaz icin ozel ayar (Ornegin main'den gelen degerler buraya tasinabilir)
    // Simdilik varsayilan ayarlarla uretiyoruz.
    Device* prototypeDevice = DeviceFactory::createDevice(type, config);

    if (prototypeDevice != NULL) {
        devices.push_back(prototypeDevice);
        std::cout << "[YONETICI] Eklendi (Orijinal): " << prototypeDevice->GetName() << " (ID: " << firstId << ")" << std::endl;

        // 2. GERI KALANLARI KOPYALA (PROTOTYPE PATTERN - LLR18)
        for (int i = 1; i < count; ++i) {
            // BURASI KRITIK: Factory degil, clone() kullaniyoruz!
            Device* clonedDevice = prototypeDevice->clone();

            // LLR19: Benzersiz Kimlik ve Ad Guncellemesi
            int newId = 100 + (int)devices.size() + 1;
            clonedDevice->SetId(newId);

            // Isim guncelleme (Ornek: Lamba -> Lamba_2)
            // Not: Device sinifina SetName eklememiz gerekebilir, yoksa eski isim kalir.
            // Simdilik sadece ID degisiyor.

            devices.push_back(clonedDevice);
            std::cout << "[YONETICI] Eklendi (Kopya): " << clonedDevice->GetName() << " (ID: " << newId << ")" << std::endl;
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
    // 1. Cihaz listesi bos mu kontrol et
    if (devices.empty()) {
        std::cout << "\n[UYARI] Ekli bir cihaz yoktur." << std::endl;

        // 2. Log dosyasina yaz
        // Logger singleton yapida oldugu icin boyle cagiriyoruz:
        Logger::getInstance()->Log("Uyari: Listelenecek cihaz bulunamadi.");

        return; // Listelenecek bir sey olmadigi icin cikiyoruz
    }

    // 3. Bos degilse standart listeleme devam eder
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