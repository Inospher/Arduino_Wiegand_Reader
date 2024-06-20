#include "Wiegand.h"

Wiegand* Wiegand::instance = nullptr;

Wiegand::Wiegand(int pinD0, int pinD1)
    : _pinD0(pinD0), _pinD1(pinD1), _newData(false), _bufferHead(0), _bufferTail(0) {
    instance = this;
}

void Wiegand::begin() {
    pinMode(_pinD0, INPUT_PULLUP);
    pinMode(_pinD1, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(_pinD0), isrD0, FALLING);
    attachInterrupt(digitalPinToInterrupt(_pinD1), isrD1, FALLING);
    Serial.println("Interrupts attached.");
}

void Wiegand::update() {
    unsigned long currentTime = millis();
    bool idle = digitalRead(_pinD0) == HIGH && digitalRead(_pinD1) == HIGH;    
    bool timeout = currentTime - _lastPulseTime > 100;

    if (timeout && idle) {
        if (_newData) {
            WiegandData tempData;
            memcpy(&tempData, (const void*)&_currentData, sizeof(WiegandData)); // Copiar os dados
            enqueueData(tempData);
            reset();
        } else {
            static unsigned long lastIdlePrintTime = 0;
            if (currentTime - lastIdlePrintTime > 30000) {
                Serial.println("Idle...");
                lastIdlePrintTime = currentTime;
            }
        }
    }

    WiegandData data;
    while (dequeueData(data)) {
        processData(data);
    }
}

void Wiegand::handleD0() {
    _lastPulseTime = millis();
    if (_currentData.bitCount < WIEGAND_MAX_BITS) {
        _currentData.data[_currentData.bitCount / 8] <<= 1;
        _currentData.bitCount++;
    }
    _newData = true;
}

void Wiegand::handleD1() {
    _lastPulseTime = millis();
    if (_currentData.bitCount < WIEGAND_MAX_BITS) {
        _currentData.data[_currentData.bitCount / 8] = (_currentData.data[_currentData.bitCount / 8] << 1) | 1;
        _currentData.bitCount++;
    }
    _newData = true;
}

void Wiegand::enqueueData(WiegandData data) {
    int next = (_bufferHead + 1) % BUFFER_SIZE;
    if (next != _bufferTail) {
        _buffer[_bufferHead] = data;
        _bufferHead = next;
        Serial.println("Data enqueued.");
    } else {
        Serial.println("Buffer overflow.");
    }
}

bool Wiegand::dequeueData(WiegandData &data) {
    if (_bufferHead == _bufferTail) {
        return false;
    }
    data = _buffer[_bufferTail];
    _bufferTail = (_bufferTail + 1) % BUFFER_SIZE;
    return true;
}

void Wiegand::processData(WiegandData data) {
    Serial.println("Processing data.");
#if WIEGAND_PROTOCOL > 0
    if (data.bitCount == WIEGAND_PROTOCOL && isValidWiegand(data)) {
        data.removeParityBits();
        Serial.println("Protocol " + String(WIEGAND_PROTOCOL) + " detected.");
        Serial.println("Data: ");
        formatData(data);
    } else if (data.isKeyData()) {
        Serial.println("Key press detected: " + data.toKeyString());
    } else {
        Serial.println("Invalid data for protocol " + String(WIEGAND_PROTOCOL));
    }
#else
    autodetectProtocol(data);
#endif
}

bool Wiegand::isValidWiegand(const WiegandData &data) {
    return data.bitCount == 26 || data.bitCount == 34 || data.bitCount == 66 || data.bitCount == 256 || data.isKeyData();
}

void Wiegand::autodetectProtocol(WiegandData data) {
    Serial.println("Autodetecting protocol.");
    if (isValidWiegand(data)) {
        if (!data.isKeyData()) {
            data.removeParityBits();
        }
        Serial.println("Protocol with " + String(data.bitCount) + " bits detected.");
        Serial.println("Data: ");
        formatData(data);
    } else {
        Serial.println("Invalid data detected.");
    }
}

void Wiegand::reset() {
    memset((void*)&_currentData, 0, sizeof(WiegandData));  // Limpar os dados
    _newData = false;
    Serial.println("Reset performed.");
}

void Wiegand::isrD0() {
    instance->handleD0();
}

void Wiegand::isrD1() {
    instance->handleD1();
}

void Wiegand::formatData(const WiegandData &data) {
    Serial.println(data.toBinaryString() + " (bin)");
    Serial.println(data.toHexString() + " (hex)");
    if (data.isKeyData()) {
        Serial.println(data.toKeyString() + " (keys)");
    } else {
        Serial.println(data.toDecimalString() + " (dec)");
    }
}

inline void Wiegand::logMessage(const String &message) {
    Serial.println(message);
}