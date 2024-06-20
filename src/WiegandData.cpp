#include "WiegandData.h"

WiegandData::WiegandData() : bitCount(0) {
    memset(data, 0, WIEGAND_MAX_BYTES);
}

String WiegandData::toBinaryString() const {
    String binData = "";
    for (unsigned int i = 0; i < bitCount; i++) {
        int byteIndex = i / 8;
        int bitIndex = 7 - (i % 8); // Ordem dos bits no byte
        binData += String((data[byteIndex] >> bitIndex) & 1);
    }
    return binData;
}

String WiegandData::toHexString() const {
    String hexData = "";
    unsigned int fullBytes = bitCount / 8;
    unsigned int remainingBits = bitCount % 8;

    for (unsigned int i = 0; i < fullBytes; i++) {
        if (data[i] < 0x10) {
            hexData += "0";
        }
        hexData += String(data[i], HEX);
    }

    if (remainingBits > 0) {
        byte lastByte = data[fullBytes] >> (8 - remainingBits);
        if (lastByte < 0x10) {
            hexData += "0";
        }
        hexData += String(lastByte, HEX);
    }

    return hexData;
}

String WiegandData::toDecimalString() const {
    unsigned long long decData = 0;
    for (unsigned int i = 0; i < (bitCount + 7) / 8; i++) {
        decData = (decData << 8) | data[i];
    }

    char decStr[21]; // Buffer para armazenar a string decimal
    snprintf(decStr, sizeof(decStr), "%llu", decData);

    return String(decStr);
}

String WiegandData::toKeyString() const {
    String keyData = "";
    for (unsigned int i = 0; i < bitCount / 8; i++) {
        keyData += translateKey(data[i]);
    }
    return keyData;
}

void WiegandData::removeParityBits() {
    byte newData[WIEGAND_MAX_BYTES] = {0};
    unsigned int newBitCount = 0;

    // Remover o primeiro bit (paridade inicial)
    for (unsigned int i = 1; i < bitCount - 1; i++) {
        int byteIndex = i / 8;
        int bitIndex = 7 - (i % 8); // Ordem dos bits no byte
        int newByteIndex = newBitCount / 8;
        int newBitIndex = 7 - (newBitCount % 8);

        if ((data[byteIndex] >> bitIndex) & 1) {
            newData[newByteIndex] |= (1 << newBitIndex);
        }
        newBitCount++;
    }

    memcpy(data, newData, WIEGAND_MAX_BYTES);
    bitCount = newBitCount;
}

char WiegandData::translateKey(byte value) const {
    switch (value) {
        case 0xF0: return '0';
        case 0xE1: return '1';
        case 0xD2: return '2';
        case 0xC3: return '3';
        case 0xB4: return '4';
        case 0xA5: return '5';
        case 0x96: return '6';
        case 0x87: return '7';
        case 0x78: return '8';
        case 0x69: return '9';
        case 0x5A: return 'A'; // e.g ESC
        case 0x4B: return 'B'; // e.g Enter
        default: return '?';  // Desconhecido
    }
}

bool WiegandData::isKeyData() const {
    // Verificar se o número de bits é 8 e se o valor dos dados corresponde a um padrão de tecla
    return bitCount == 8 && translateKey(data[0]) != '?';
}
