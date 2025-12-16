#include "../include/NotificationService.h"
#include <iostream>

void NotificationService::NotifyUser(NotificationType type, const std::string& message) {
    // LLR15: Bildirim tipi ne olursa olsun SMS mesaji gosterilmeli.
    std::cout << ">> BIR SMS GONDERILDI: " << message << std::endl;

    // Ekstra bilgi (Opsiyonel)
    if (type == NOTIFY_ALARM) {
        std::cout << ">> (Ayrica Alarm caliniyor...)" << std::endl;
    }
}