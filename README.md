# ESP8266-Neopixel-Web-Control
Acendendo Leds via Wifi
Este projeto consiste em uma página web hospedada em um ESP8266 que controla LEDs Neopixel. Ele permite ligar e desligar LEDs individualmente, bem como exibir um efeito de arco-íris nos LEDs.

## Como Funciona

O ESP8266 atua como um servidor web, permitindo o acesso a uma página HTML através da rede local. A página web exibe botões para controlar o acendimento e apagamento dos LEDs, bem como para ativar e desativar o efeito de arco-íris nos LEDs.

![image](https://github.com/JLourencao/ESP8266-Neopixel-Web-Control/assets/113789779/746f8d17-49d6-461d-8b4c-0483650b022a)

## Componentes Utilizados

- ESP8266 (NodeMCU)
![image](https://github.com/JLourencao/ESP8266-Neopixel-Web-Control/assets/113789779/d1c718dd-375c-4742-8480-95aee4accd43)

- LEDs Neopixel
![image](https://github.com/JLourencao/ESP8266-Neopixel-Web-Control/assets/113789779/f400c9dc-2aca-412a-b5a2-abf57964de86)

  
- Biblioteca Adafruit Neopixel

## Configuração da Rede Wi-Fi

Antes de usar o projeto, defina as credenciais da sua rede Wi-Fi no código:

```cpp
const char* ssid = "ssid"; 
const char* password = "senha";

