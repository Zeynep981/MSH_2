#include <iostream>
#include "../include/DeviceManager.h"

int main() {
    std::cout << "=== MSH_2 FINAL TEST ===\n" << std::endl;
    DeviceManager* manager = DeviceManager::getInstance();

    // 1. Cihazlari Ekle
    manager->AddDevice(DEVICE_LIGHT, 1, "Salon Lambasi"); // ID 101
    manager->AddDevice(DEVICE_DETECTOR, 1, "Gaz Sensoru"); // ID 102 (Kritik)

    manager->ListAllDevices();

    // 2. Normal Kullanim
    manager->PowerOnDevice(101);

    // 3. SENARYO: Cihaz Bozuluyor (REQ9 Testi)
    std::cout << ">>> OLAY: Salon Lambasi patladi!" << std::endl;
    manager->HandleFailure(101);

    // 4. Bozuk Cihazi Acma Denemesi
    std::cout << ">>> Kullanici bozuk lambayi acmayi deniyor..." << std::endl;
    manager->PowerOnDevice(101); // "Arizali oldugu icin acilamiyor" demeli

    // Son Durum
    manager->ListAllDevices();

    return 0;
}