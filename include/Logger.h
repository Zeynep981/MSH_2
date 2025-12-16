#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <iostream>

// SINGLETON: Sistemde tek bir log defteri olur.
class Logger {
private:
    static Logger* instance;

    // Private constructor (Kimse kafasina gore new Logger() diyemesin)
    Logger();

public:
    static Logger* getInstance();

    // Log mesajini yazdiran fonksiyon
    void Log(const std::string& message);
};

#endif