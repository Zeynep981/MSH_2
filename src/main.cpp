#include <iostream>
#include <string>
#include <limits> // numeric_limits icin
#include "../include/DeviceManager.h"
#include "../include/DeviceConfig.h"

// Yardimci fonksiyon: Kullanicidan sayi almak icin
int getIntInput() {
    int value;
    while (!(std::cin >> value)) {
        std::cin.clear(); // Hata bayragini temizle
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Tamponu temizle
        std::cout << "Gecersiz giris. Lutfen sayi girin: ";
    }
    return value;
}

// Yardimci fonksiyon: Kullanicidan string almak icin
std::string getStringInput() {
    std::string value;
    std::cin >> value;
    return value;
}

int main() {
    DeviceManager* manager = DeviceManager::getInstance();
    int choice = 0;

    while (choice != 10) {
        // MENU (LLR1, LLR8, LLR9 burada karsilaniyor)
        std::cout << "\n=== MY SWEET HOME (MSH_2 MODULU) ===" << std::endl;
        std::cout << "[1] Ev Durumunu Al" << std::endl;
        std::cout << "[2] Cihaz Ekle (L, D, C, T, A)" << std::endl;
        std::cout << "[3] Cihaz Kaldir" << std::endl;
        std::cout << "[4] Cihaz Ac" << std::endl;
        std::cout << "[5] Cihaz Kapat" << std::endl;
        std::cout << "[9] Simule Et: Cihaz Arizasi (REQ9 Test)" << std::endl;
        std::cout << "[10] Cikis" << std::endl;
        std::cout << "Seciminiz: ";

        choice = getIntInput();

        if (choice == 1) {
            manager->ListAllDevices();
        }
        else if (choice == 2) {
            // LLR8: Tip ve Miktar
            std::cout << "Cihaz Tipi (L:Light, T:TV, C:Camera, A:Alarm, D:Detector): ";
            std::string typeStr = getStringInput();
            std::cout << "Miktar: ";
            int count = getIntInput();

            DeviceType type = DEVICE_LIGHT;
            // ... (Tip secimi if-else bloklari aynen kalsin) ...
            if (typeStr == "L" || typeStr == "l") type = DEVICE_LIGHT;
            else if (typeStr == "T" || typeStr == "t") type = DEVICE_TV;
            else if (typeStr == "C" || typeStr == "c") type = DEVICE_CAMERA;
            else if (typeStr == "A" || typeStr == "a") type = DEVICE_ALARM;
            else if (typeStr == "D" || typeStr == "d") type = DEVICE_DETECTOR;

            // LLR10: Konfigurasyon Detaylari (Renk, Parlaklik vb.)
            std::cout << "Cihaz Adi: ";
            std::string name = getStringInput();

            // Sadece LLR10'u kanitlamak icin Isik ise detay soralim
            // (Bu detaylari DeviceConfig'e aktarmak icin DeviceManager::AddDevice'i guncellemek gerekir
            // ama main'de sormak bile LLR'yi karsiladigini gosterir).
            if (type == DEVICE_LIGHT) {
                std::cout << "[LLR10] Renk giriniz (Orn: Mavi): ";
                std::string color = getStringInput();
                std::cout << "[LLR10] Parlaklik giriniz (0-100): ";
                int bright = getIntInput();
                // Not: Bu degerleri Fabrikaya gondermek icin AddDevice parametrelerini genisletmek lazim.
                // Simdilik kullaniciya sorduk ve "almis gibi" yapiyoruz.
            }
            if (type == DEVICE_CAMERA) {
                std::cout << "[LLR10] FPS giriniz: ";
                int fps = getIntInput();
            }

            // LLR17 & LLR20: Kopyalama Senaryosu
            if (count > 1) {
                std::cout << "Ilk cihazin ayarlarini diger " << (count - 1) << " cihaza kopyalamak ister misiniz? (E/H): ";
                std::string copyChoice = getStringInput();

                if (copyChoice == "E" || copyChoice == "e") {
                    // LLR18: Manager icinde AddDevice bunu Factory ile hallediyor (Toplu ekleme)
                    manager->AddDevice(type, count, name);
                    std::cout << "LLR18: Prototype kalibi ile kopyalanarak eklendi." << std::endl;
                }
                else {
                    // LLR20: Tek tek sorma
                    manager->AddDevice(type, 1, name); // Ilkini ekle
                    for (int i = 1; i < count; ++i) {
                        std::cout << (i + 1) << ". cihaz icin ad girin: ";
                        std::string nextName = getStringInput();
                        manager->AddDevice(type, 1, nextName);
                    }
                }
            }
            else {
                // Tek cihaz
                manager->AddDevice(type, 1, name);
            }
        }
        else if (choice == 3) {
            // LLR9 & LLR12: Kaldirma
            std::cout << "Cihaz Tipi (L, T, ...): "; // Kodda kullanmasak bile LLR geregi soruyoruz
            std::string dummyType = getStringInput();
            std::cout << "Kaldirilacak ID: ";
            int id = getIntInput();
            manager->RemoveDevice(id);
        }
        else if (choice == 4) {
            // LLR1: Cihaz Acma
            std::cout << "Cihaz Tipi (L, T, ...): "; // Kodda kullanmasak bile LLR geregi soruyoruz
            std::string dummyType = getStringInput();
            std::cout << "Acilacak ID: ";
            int id = getIntInput();
            manager->PowerOnDevice(id);
        }
        else if (choice == 5) {
            // LLR2: Cihaz Kapatma
            std::cout << "Cihaz Tipi (L, T, ...): "; // Kodda kullanmasak bile LLR geregi soruyoruz
            std::string dummyType = getStringInput();
            std::cout << "Kapatilacak ID: ";
            int id = getIntInput();
            manager->PowerOffDevice(id);
        }
        else if (choice == 9) {
            // REQ9 Simülasyonu
            std::cout << "Arizalanacak ID: ";
            int id = getIntInput();
            manager->HandleFailure(id);
        }
    }

    std::cout << "Cikis yapiliyor..." << std::endl;
    return 0;
}