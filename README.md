## English

# Arduino Wiegand Reader

This project is a Wiegand input device reader using an Arduino. It includes the `Wiegand` and `WiegandData` classes to facilitate the reading and processing of data from Wiegand protocol devices. Additionally, it identifies Wiegand messages in the 8-bit format for use with numeric keypads.

## Index

1. [Introduction](#introduction)
2. [Installation](#installation)
3. [Usage](#usage)
4. [Wiegand Class](#wiegand-class)
   - [Public Methods](#public-methods-of-the-wiegand-class)
5. [WiegandData Class](#wieganddata-class)
   - [Public Methods](#public-methods-of-the-wieganddata-class)
6. [License](#license)

## Introduction

The goal of this project is to create a Wiegand input device reader using an Arduino. The Wiegand protocol is commonly used in access control systems. This project reads data from Wiegand devices and processes it for use in Arduino applications. It also identifies Wiegand messages in the 8-bit format, making it suitable for use with numeric keypads.

## Installation

1. Download or clone this repository:
   ```sh
   git clone https://github.com/your-username/arduino-wiegand-reader.git
   ```
2. Open the Arduino IDE and load the sketch `Arduino_Wiegand_Reader.ino`.
3. Ensure that the files `Wiegand.cpp`, `Wiegand.h`, `WiegandData.cpp`, and `WiegandData.h` are in the same folder as the sketch or in the Arduino library.

## Usage

Load the sketch `Arduino_Wiegand_Reader.ino` onto your Arduino. The code reads data from a Wiegand device when it is activated and prints the data to the serial console.

## Wiegand Class

The `Wiegand` class is responsible for managing the interface for reading Wiegand device data.

### Public Methods of the Wiegand Class

- `Wiegand(int pinD0, int pinD1)`: Constructor that initializes the data pins D0 and D1.
- `void begin()`: Initializes the pins and sets up interrupts.
- `bool available()`: Checks if data is available.
- `uint32_t getCode()`: Returns the code read from the device.
- `uint8_t getBits()`: Returns the number of bits read from the device.

## WiegandData Class

The `WiegandData` class is used internally by the `Wiegand` class to store and manipulate device data.

### Public Methods of the WiegandData Class

- `WiegandData()`: Constructor of the class.
- `void setData(uint8_t bitLength, uint32_t data)`: Sets the data and the bit length.
- `uint32_t getData()`: Returns the stored data.
- `uint8_t getBitLength()`: Returns the bit length of the stored data.

## License

This project is licensed under the [MIT License](LICENSE).

### Disclaimer and Usage Instructions

This content is provided freely for educational purposes, and you are encouraged to use and share it, citing the source and author when doing so. Suggestions for improvements or corrections are welcome. This content is provided "as is," without warranty of any kind, and I do not assume responsibility for any consequences resulting from its use. The goal is to create efficient and effective code that benefits the community, suitable for laboratory exercises in courses or as a foundation for developing professional resources. Use of this project should be done under the guidance of a qualified instructor or professional, or by individuals with the necessary knowledge and competence.

## Appendix: Suggested Interface Using Optocouplers

### English

To protect the Arduino against high currents from a Wiegand input device, it is recommended to use LTV-817 optocouplers with 200-ohm resistors. This method electrically isolates the input device from the Arduino, ensuring safety and efficiency.

### Required Components

- 2 LTV-817 optocouplers
- 2 200-ohm resistors
- Protoboard
- Connecting wires
- Arduino (e.g., Arduino Uno)
- Power supply compatible with the Wiegand input device
- Wiegand input device

### Step-by-Step Assembly

1. **Initial Setup**:
   - Connect the GND of the protoboard to the GND of the Arduino.
   - Connect the power supply for the Wiegand device to the protoboard (positive and negative).

2. **Connecting the Optocouplers**:
   - Insert the two LTV-817 optocouplers into the protoboard.

3. **Connecting the Wiegand Input Device**:
   - Connect the W0 terminal of the device to the anode of the first optocoupler LED through a 200-ohm resistor.
   - Connect the cathode of the optocoupler LED to the device GND.
   - Connect the W1 terminal of the device to the anode of the second optocoupler LED through a 200-ohm resistor.
   - Connect the cathode of the optocoupler LED to the device GND.
   - Connect the negative of the device to the common GND.

4. **Connecting to the Arduino**:
   - Connect the collector of the first optocoupler's phototransistor to pin 2 of the Arduino.
   - Connect the emitter of the phototransistor to the Arduino GND.
   - Connect the collector of the second optocoupler's phototransistor to pin 3 of the Arduino.
   - Connect the emitter to the Arduino GND.

5. **Powering the Arduino**:
   - Connect the Arduino to the computer via USB for power and sketch upload.

### Final Description

- **Input Device**: Connected to an appropriate power supply.
- **LTV-817 Optocouplers**: Used to electrically isolate the input device from the Arduino.
- **200-ohm Resistors**: Limit the current through the optocoupler LEDs.
- **Arduino**: Connected to the optocoupler phototransistors on digital pins (pin 2 for W0 and pin 3 for W1) and powered via USB.

This method ensures that the Arduino is protected from high currents originating from the Wiegand input device.

---

If you have any questions or need help, feel free to open an issue on the GitHub repository.

## Português

# Leitor Wiegand com Arduino

Este projeto é um leitor de dispositivos de entrada Wiegand utilizando um Arduino. Ele inclui as classes `Wiegand` e `WiegandData` para facilitar a leitura e processamento dos dados dos dispositivos que utilizam o protocolo Wiegand. Além disso, identifica mensagens Wiegand no formato de 8 bits para uso com teclados numéricos.

## Índice

1. [Introdução](#introdução)
2. [Instalação](#instalação)
3. [Uso](#uso)
4. [Classe Wiegand](#classe-wiegand)
   - [Métodos Públicos](#métodos-públicos-da-classe-wiegand)
5. [Classe WiegandData](#classe-wieganddata)
   - [Métodos Públicos](#métodos-públicos-da-classe-wieganddata)
6. [Licença](#licença)

## Introdução

O objetivo deste projeto é criar um leitor de dispositivos de entrada Wiegand utilizando um Arduino. O protocolo Wiegand é comumente usado em sistemas de controle de acesso. Este projeto lê os dados dos dispositivos Wiegand e os processa para uso em aplicações Arduino. Ele também identifica mensagens Wiegand no formato de 8 bits, tornando-o adequado para uso com teclados numéricos.

## Instalação

1. Faça o download ou clone este repositório:
   ```sh
   git clone https://github.com/seu-usuario/arduino-wiegand-reader.git
   ```
2. Abra o Arduino IDE e carregue o sketch `Arduino_Wiegand_Reader.ino`.
3. Certifique-se de que os arquivos `Wiegand.cpp`, `Wiegand.h`, `WiegandData.cpp` e `WiegandData.h` estejam na mesma pasta do sketch ou na biblioteca do Arduino.

## Uso

Carregue o sketch `Arduino_Wiegand_Reader.ino` no seu Arduino. O código lê os dados de um dispositivo Wiegand quando ele é ativado e imprime os dados no console serial.

## Classe Wiegand

A classe `Wiegand` é responsável por gerenciar a interface de leitura dos dados dos dispositivos Wiegand.

### Métodos Públicos da Classe Wiegand

- `Wiegand(int pinD0, int pinD1)`: Construtor da classe que inicializa os pinos de dados D0 e D1.
- `void begin()`: Inicializa os pinos e configura as interrupções.
- `bool available()`: Verifica se há dados disponíveis.
- `uint32_t getCode()`: Retorna o código lido do dispositivo.
- `uint8_t getBits()`: Retorna o número de bits lidos do dispositivo.

## Classe WiegandData

A classe `WiegandData` é usada internamente pela classe `Wiegand` para armazenar e manipular os dados do dispositivo.

### Métodos Públicos da Classe WiegandData

- `WiegandData()`: Construtor da classe.
- `void setData(uint8_t bitLength, uint32_t data)`: Configura os dados

 e o comprimento em bits.
- `uint32_t getData()`: Retorna os dados armazenados.
- `uint8_t getBitLength()`: Retorna o comprimento em bits dos dados armazenados.

## Licença

Este projeto está licenciado sob a [MIT License](LICENSE).

### Aviso e Instruções de Uso

Este conteúdo está sendo disponibilizado gratuitamente para fins educacionais, e você é encorajado a utilizá-lo e compartilhá-lo, citando a fonte e autoria ao fazê-lo. Sugestões para melhorias ou correções são bem-vindas. Este conteúdo é fornecido "como está", sem qualquer garantia, e não assumo responsabilidade por quaisquer consequências resultantes de seu uso. O objetivo é criar um código eficiente e eficaz que beneficie a comunidade, adequado para exercícios de laboratório em cursos ou como base para o desenvolvimento de recursos profissionais. O uso deste projeto deve ser feito sob a orientação de um instrutor qualificado ou profissional, ou por pessoas com o conhecimento e competência necessários.

### Apêndice: Interface Sugerida Usando Optoacopladores

### Português

Para proteger o Arduino contra correntes elevadas de um dispositivo de entrada Wiegand, recomenda-se o uso de optoacopladores LTV-817 com resistores de 200 ohms. Este método isola eletricamente o dispositivo de entrada do Arduino, garantindo segurança e eficiência.

### Componentes Necessários

- 2 optoacopladores LTV-817
- 2 resistores de 200 ohms
- Protoboard
- Fios de conexão
- Arduino (por exemplo, Arduino Uno)
- Fonte de alimentação compatível com o dispositivo de entrada Wiegand
- Dispositivo de entrada Wiegand

### Passo a Passo para a Montagem

1. **Configuração Inicial**:
   - Conectar o GND da protoboard ao GND do Arduino.
   - Conectar a fonte de alimentação do dispositivo Wiegand à protoboard (positivo e negativo).

2. **Conexão dos Optoacopladores**:
   - Inserir os dois optoacopladores LTV-817 na protoboard.

3. **Conexão do Dispositivo de Entrada Wiegand**:
   - Conectar o terminal W0 do dispositivo ao anodo do LED do primeiro optoacoplador através de um resistor de 200 ohms.
   - Conectar o catodo do LED do optoacoplador ao GND do dispositivo.
   - Conectar o terminal W1 do dispositivo ao anodo do LED do segundo optoacoplador através de um resistor de 200 ohms.
   - Conectar o catodo do LED do optoacoplador ao GND do dispositivo.
   - Conectar o negativo do dispositivo ao GND comum.

4. **Conexão ao Arduino**:
   - Conectar o coletor do fototransistor do primeiro optoacoplador ao pino 2 do Arduino.
   - Conectar o emissor do fototransistor ao GND do Arduino.
   - Conectar o coletor do fototransistor do segundo optoacoplador ao pino 3 do Arduino.
   - Conectar o emissor ao GND do Arduino.

5. **Alimentação do Arduino**:
   - Conectar o Arduino ao computador via cabo USB para alimentação e upload do sketch.

### Descrição Final

- **Dispositivo de Entrada**: Conectado à fonte de alimentação adequada.
- **Optoacopladores LTV-817**: Utilizados para isolar eletricamente o dispositivo de entrada do Arduino.
- **Resistores de 200 ohms**: Limitam a corrente através dos LEDs dos optoacopladores.
- **Arduino**: Conectado aos fototransistores dos optoacopladores nos pinos digitais (pino 2 para W0 e pino 3 para W1) e alimentado via USB.

Este método garante que o Arduino esteja protegido contra correntes elevadas provenientes do dispositivo de entrada Wiegand.

---

Se você tiver alguma dúvida ou precisar de ajuda, sinta-se à vontade para abrir uma issue no repositório GitHub.