#include "../include/Logger.h"

Logger* Logger::instance = NULL;

Logger::Logger() {
    // REQ4: Kalici bellege kaydetme.
    // "ios::app" modu, dosya varsa silmez, sonuna ekler (Append).
    logFile.open("msh_log.txt", std::ios::app);

    if (logFile.is_open()) {
        logFile << "--- MSH SISTEM BASLATILDI ---" << std::endl;
    }
    else {
        std::cout << "[LOGGER HATA] Log dosyasi acilamadi!" << std::endl;
    }
}

Logger::~Logger() {
    if (logFile.is_open()) {
        logFile << "--- MSH SISTEM KAPATILDI ---\n" << std::endl;
        logFile.close();
    }
}

Logger* Logger::getInstance() {
    if (instance == NULL) {
        instance = new Logger();
    }
    return instance;
}

void Logger::Log(const std::string& message) {
    // 1. Ekrana yaz (Kullanici gorsun)
    std::cout << "[LOG EKRAN] " << message << std::endl;

    // 2. Dosyaya yaz (REQ4 - Kalici Kayit)
    if (logFile.is_open()) {
        logFile << message << std::endl;
        // flush: Verinin tamponda beklemeden aninda dosyaya yazilmasini saglar
        logFile.flush();
    }
}