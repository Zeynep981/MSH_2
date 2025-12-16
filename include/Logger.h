#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <iostream>
#include <fstream> // YENI: Dosya islemleri icin gerekli

class Logger {
private:
    static Logger* instance;
    std::ofstream logFile; // YENI: Log dosyamiz

    Logger(); // Constructor'da dosyayi acacagiz

public:
    static Logger* getInstance();

    // YENI: Destructor (Program kapanirken dosyayi kapatmak icin)
    ~Logger();

    void Log(const std::string& message);
};

#endif