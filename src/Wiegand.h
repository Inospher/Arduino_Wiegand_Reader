#ifndef WIEGAND_H
#define WIEGAND_H

#include <Arduino.h>
#include "WiegandData.h"

#define WIEGAND_PROTOCOL 0 // Defina o protocolo desejado
#define BUFFER_SIZE 10

class Wiegand {
public:
    Wiegand(int pinD0, int pinD1);
    void begin();
    void update();

private:
    int _pinD0;
    int _pinD1;
    volatile unsigned long _lastPulseTime;
    volatile WiegandData _currentData;
    volatile bool _newData;

    WiegandData _buffer[BUFFER_SIZE];
    volatile int _bufferHead;
    volatile int _bufferTail;

    void handleD0();
    void handleD1();
    void enqueueData(WiegandData data);
    bool dequeueData(WiegandData &data);
    void processData(WiegandData data);
    bool isValidWiegand(const WiegandData &data);
    void autodetectProtocol(WiegandData data);
    void reset();
    void formatData(const WiegandData &data);

    static void isrD0();
    static void isrD1();
    static Wiegand* instance;

    inline void logMessage(const String &message); // Adicione esta linha
};

#endif
