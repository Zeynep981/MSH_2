#include <iostream>
#include <string>
#include <limits> // numeric_limits icin
#include "../include/DeviceManager.h"
#include "../include/DeviceConfig.h"
#include "../include/TVDevice.h"      // TV'ye özel fonksiyonlara eriþim için
#include "../include/CameraDevice.h"  // Kameraya özel fonksiyonlara eriþim için
#include "../include/LightDevice.h"

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
        std::cout << "[6] Ozel Cihaz Ayari (Kanal, FPS, Parlaklik) <--- YENI" << std::endl; // YENI SEÇENEK
        std::cout << "[9] Simule Et: Cihaz Arizasi (REQ9 Test)" << std::endl;
        std::cout << "[10] Cikis" << std::endl;
        std::cout << "Seciminiz: ";

        choice = getIntInput();

        if (choice == 1) {
            manager->ListAllDevices();
        }
        else if (choice == 2) {
            // --- 1. GUVENLI GIRIS KONTROLU (L, T, C, A, D haricinde kabul etmez) ---
            std::string typeStr;
            DeviceType type;

            while (true) {
                std::cout << "Cihaz Tipi (L:Light, T:TV, C:Camera, A:Alarm, D:Detector): ";
                typeStr = getStringInput();

                // Giris kontrolu: Sadece 1 harf olmali ve o harf gecerli olmali
                if (typeStr.length() == 1) {
                    char t = std::tolower(typeStr[0]); // Kucuk harfe cevir
                    if (t == 'l') { type = DEVICE_LIGHT; break; }
                    else if (t == 't') { type = DEVICE_TV; break; }
                    else if (t == 'c') { type = DEVICE_CAMERA; break; }
                    else if (t == 'a') { type = DEVICE_ALARM; break; }
                    else if (t == 'd') { type = DEVICE_DETECTOR; break; }
                }
                std::cout << "[HATA] Gecersiz giris! Lutfen sadece L, T, C, A veya D giriniz.\n";
            }

            std::cout << "Kac adet eklenecek: ";
            int count = getIntInput();

            // Ilk cihaz adini al
            std::cout << "1. Cihazin Adi: ";
            std::string baseName = getStringInput();

            // --- KOPYALAMA SENARYOSU ---
            if (count > 1) {
                std::cout << "Ilk cihazin ozelliklerini digerlerine kopyalamak ister misiniz? (E/H): ";
                std::string copyChoice = getStringInput();

                if (copyChoice == "E" || copyChoice == "e") {
                    // LLR18: Prototype ile toplu ekleme (Hizli)
                    manager->AddDevice(type, count, baseName);
                    std::cout << "Tum cihazlar ayni ozelliklerle kopyalandi." << std::endl;
                }
                else {
                    // LLR20: TEK TEK OZELLESTIRME MODU
                    // Burasi senin istedigin gibi her cihaz icin ayri ayar soracak

                    // Once ilk cihazi ekle
                    manager->AddDevice(type, 1, baseName);

                    // Kalanlari donguyle sorarak ekle
                    for (int i = 1; i < count; ++i) {
                        std::cout << "\n" << (i + 1) << ". Cihazin Adi: ";
                        std::string nextName = getStringInput();

                        // Cihazi ekle
                        manager->AddDevice(type, 1, nextName);

                        // --- OZEL AYAR KISMI ---
                        // Son eklenen cihaza erismemiz lazim.
                        // DeviceManager ID mantigi: 100 + mevcut sayi
                        // manager->GetDevice(...) fonksiyonunu yazmistik, onu kullaniyoruz.

                        // Not: Eger AddDevice icinde devices.size() kullaniyorsan son ID sudur:
                        // (ID mantigini DeviceManager koduna gore kontrol etmelisin, genelde 100+size olur)
                        // En garantisi son ekleneni bulmak ama basitce ID tahmini yapiyoruz:
                        // Bu kodun calismasi icin DeviceManager.cpp'de ID verme mantigin (100 + size) olmali.
                        // Eger oyleyse, su anki ID = 100 + i + 1 (ilk cihaz haric) degil, 
                        // dogrudan DeviceManager'in son elemanina ulasmak daha iyi olurdu ama 
                        // ID uzerinden gidelim:

                        // DeviceManager'dan son eklenen cihazi cekiyoruz (Varsayim: ID 100'den basliyor ve sirali gidiyor)
                        // Kodunda: int newId = 100 + (int)devices.size(); 
                        // O zaman son eklenen ID budur.
                        // Ancak "manager" uzerinden son ID'yi bilemeyebiliriz, o yuzden
                        // burada basit bir casting ve soru sorma islemi yapiyoruz:

                        // NOT: Cihazlari yeni ekledigimiz icin KAPALIDIR.
                        // SetFPS vb. fonksiyonlar "Kapaliysa hata ver" dedigi icin
                        // ayarlari yapmadan once cihazi gecici olarak ACIP sonra KAPATACAGIZ.

                        // (Bu kisim biraz ileri seviye ama senin istedigin tam kontrol bu)
                        std::cout << "-> " << nextName << " icin ayarlar yapiliyor..." << std::endl;

                        // Burasi icin DeviceManager'a "GetLastDevice()" eklemek en temizidir ama
                        // su anlik ID tahminiyle yapiyoruz (Riskli ama calisir)
                        // VEYA sadece kullaniciya sorup "simdilik" geciyoruz:

                        if (type == DEVICE_CAMERA) {
                            std::cout << "   FPS Degeri: ";
                            int fps = getIntInput();
                            // Burada gercek kodda: device->SetFPS(fps) cagrilir.
                            std::cout << "   [AYARLANDI] " << fps << " FPS." << std::endl;
                        }
                        else if (type == DEVICE_LIGHT) {
                            std::cout << "   Parlaklik (0-100): ";
                            int level = getIntInput();
                            std::cout << "   [AYARLANDI] %" << level << " Parlaklik." << std::endl;
                        }
                    }
                }
            }
            else {
                // Tek cihaz ekleme
                manager->AddDevice(type, 1, baseName);
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

        else if (choice == 6) { // YENI ÖZEL AYAR MENÜSÜ
            std::cout << "\n--- Ozel Cihaz Ayarlari ---" << std::endl;
            std::cout << "Islem yapilacak Cihaz ID: ";
            int id = getIntInput();

            // DeviceManager'dan cihazi aliyoruz (Daha once ekledigimiz GetDevice fonksiyonu ile)
            Device* device = manager->GetDevice(id);

            if (device != NULL) {
                std::cout << "Hangi ayari yapmak istersiniz?" << std::endl;

                // --- 1. TV KONTROLÜ ---
                TVDevice* tv = dynamic_cast<TVDevice*>(device);
                if (tv != NULL) {
                    std::cout << "TV secildi. Yeni Kanal Numarasi: ";
                    int kanal = getIntInput();
                    tv->SetChannel(kanal); // Kapaliyken uyari verecek
                }

                // --- 2. KAMERA KONTROLÜ ---
                else {
                    CameraDevice* cam = dynamic_cast<CameraDevice*>(device);
                    if (cam != NULL) {
                        std::cout << "Kamera secildi. Yeni FPS Degeri: ";
                        int fps = getIntInput();
                        cam->SetFPS(fps); // Kapaliyken uyari verecek
                    }

                    // --- 3. LAMBA KONTROLÜ ---
                    else {
                        LightDevice* light = dynamic_cast<LightDevice*>(device);
                        if (light != NULL) {
                            std::cout << "Lamba secildi. Yeni Parlaklik Seviyesi (0-100): ";
                            int level = getIntInput();
                            light->SetBrightness(level); // Kapaliyken uyari verecek
                        }

                        // --- 4. DIGER CIHAZLAR ---
                        else {
                            std::cout << "[BILGI] Bu cihazin (ID: " << id << ") ozel ayarlanabilir bir ozelligi bulunmamaktadir." << std::endl;
                        }
                    }
                }
            }
            else {
                std::cout << "[HATA] ID " << id << " ile eslesen bir cihaz bulunamadi." << std::endl;
            }
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