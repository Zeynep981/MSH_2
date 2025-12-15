#include <iostream>
#include "../include/DeviceManager.h"

int main() {
    std::cout << "=== MSH_2 YONETICI TESTI ===\n" << std::endl;

    // 1. Yoneticiyi cagir (Singleton)
    DeviceManager* manager = DeviceManager::getInstance();

    // 2. Cihazlari Ekle (REQ8)
    std::cout << ">> Cihazlar Ekleniyor..." << std::endl;
    manager->AddDevice(DEVICE_LIGHT, 2, "Salon Isigi"); // 2 tane isik
    manager->AddDevice(DEVICE_ALARM, 1, "Ana Alarm");   // 1 tane alarm

    // 3. Listeyi Gor
    manager->ListAllDevices();

    // 4. Cihazlari Yonet (REQ6)
    std::cout << ">> Cihazlar Aciliyor..." << std::endl;
    // Not: ID'ler 101, 102, 103 diye gidecek (kodda oyle ayarladik)
    manager->PowerOnDevice(101);
    manager->PowerOnDevice(103); // Alarm

    // 5. Kritik Cihaz Kapatma Denemesi (LLR5)
    std::cout << "\n>> Kritik Cihaz Kapatma Testi..." << std::endl;
    manager->PowerOffDevice(103); // Alarm kapanmamali

    // 6. Cihaz Silme (REQ8)
    std::cout << "\n>> Cihaz Silme Testi..." << std::endl;
    manager->RemoveDevice(102); // Ikinci isigi silelim

    // Son Durum
    manager->ListAllDevices();

    return 0;
}