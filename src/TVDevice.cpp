#include "../include/TVDevice.h"

// include'larin altina
#include <iostream> 

void TVDevice::SetChannel(int channel) {
    // isActive kontrolü (Device sýnýfýndan miras aldý)
    if (!isActive) {
        std::cout << "[HATA] TV su an kapali! Kanal degistirmek icin once TV'yi acin." << std::endl;
        return;
    }

    std::cout << "[TV] Kanal " << channel << " olarak ayarlandi. Iyi seyirler!" << std::endl;
}

TVDevice::TVDevice(int id, const std::string& name)
    : Device(id, name, DEVICE_TV) {
}

TVDevice::TVDevice(const TVDevice& other)
    : Device(other.GetId(), other.GetName(), DEVICE_TV) {
}

Device* TVDevice::clone() const {
    return new TVDevice(*this);
}

std::string TVDevice::GetStatus() const {
    return Device::GetStatus() + " [Tip: Televizyon]";
}
