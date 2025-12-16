#ifndef CAMERADEVICE_H
#define CAMERADEVICE_H

#include "Device.h"

class CameraDevice : public Device {
private:
    int fps; // <--- YENI: FPS degeri

public:
    CameraDevice(int id, const std::string& name);
    CameraDevice(const CameraDevice& other);

    virtual Device* clone() const;
    virtual std::string GetStatus() const;

    // YENI: Kapaliyken ayar yapilmasini engelleyecek fonksiyon
    void SetFPS(int newFps);

    // Opsiyonel: FPS'i almak icin (main'de goruntulemek istersen)
    int GetFPS() const { return fps; }
};

#endif