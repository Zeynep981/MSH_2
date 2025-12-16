#ifndef DEVICEPROTOTYPE_H
#define DEVICEPROTOTYPE_H

// Class Diyagramindaki <<Interface>> DevicePrototype kutusu
// Sadece clone metodu olan saf bir arayuzdur.
class Device; // Forward declaration

class DevicePrototype {
public:
    virtual ~DevicePrototype() {}

    // Saf sanal fonksiyon (Pure Virtual)
    // Bunu uygulayan herkes kendini kopyalamayi bilmek zorunda.
    virtual Device* clone() const = 0;
};

#endif