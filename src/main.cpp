#include <iostream>
#include "../include/LightDevice.h"
#include "../include/CriticalDevice.h"

int main() {
    std::cout << "=== MSH_2 TEST BASLADI ===\n" << std::endl;

    // TEST 1: KOPYALAMA (PROTOTYPE)
    std::cout << "--- 1. Prototype (Klonlama) Testi ---" << std::endl;
    LightDevice* lamba1 = new LightDevice(1, "Salon Avize", 100, "Sari");
    lamba1->PowerOn();
    std::cout << "Orijinal: " << lamba1->GetStatus() << std::endl;

    // Kopyaliyoruz...
    Device* lamba2 = lamba1->clone();
    lamba2->SetId(2); // Yeni ID veriyoruz
    std::cout << "Kopya:    " << lamba2->GetStatus() << std::endl;

    // TEST 2: KRITIK CIHAZ
    std::cout << "\n--- 2. Kritik Cihaz Testi ---" << std::endl;
    CriticalDevice* alarm = new CriticalDevice(99, "Yangin Alarmi", DEVICE_ALARM);

    std::cout << "Kullanici alarmi kapatmayi deniyor..." << std::endl;
    alarm->PowerOff(); // Kapanmamali!

    // Temizlik
    delete lamba1;
    delete lamba2;
    delete alarm;

    return 0;
}