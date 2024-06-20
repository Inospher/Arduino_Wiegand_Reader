#ifndef WIEGANDDATA_H
#define WIEGANDDATA_H

#include <Arduino.h>

// Definição de tamanho para diferentes protocolos (deve ser definido antes de incluir este header)
#ifndef WIEGAND_MAX_BITS
    #define WIEGAND_MAX_BITS 256
#endif
#define WIEGAND_MAX_BYTES ((WIEGAND_MAX_BITS + 7) / 8) // Quantidade de bytes necessária

class WiegandData {
public:
    WiegandData();

    byte data[WIEGAND_MAX_BYTES]; // Armazenar até o máximo de bytes necessário
    unsigned int bitCount;        // Número de bits recebidos

    String toBinaryString() const;
    String toHexString() const;
    String toDecimalString() const;
    String toKeyString() const; // Nova função para traduzir teclas
    void removeParityBits(); // Método para remover bits de paridade
    bool isKeyData() const; // Nova função para verificar se os dados são de teclas

private:
    void appendByteAsBinary(String &binData, byte value, bool appendSpace) const;
    char translateKey(byte value) const; // Nova função para traduzir valores Wiegand para teclas
};

#endif
