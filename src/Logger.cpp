#include "../include/Logger.h"

Logger* Logger::instance = NULL;

Logger::Logger() {}

Logger* Logger::getInstance() {
    if (instance == NULL) {
        instance = new Logger();
    }
    return instance;
}

void Logger::Log(const std::string& message) {
    // Simdilik ekrana yaziyoruz ama gercek projede burasi dosyaya yazar (REQ4)
    std::cout << "[LOG KAYDI] " << message << std::endl;
}