#ifndef NOTIFICATIONSERVICE_H
#define NOTIFICATIONSERVICE_H

#include <string>
#include "Device.h" // NotificationType icin

class NotificationService {
public:
    // LLR15: Arýza bildirimi
    void NotifyUser(NotificationType type, const std::string& message);
};

#endif