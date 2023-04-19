//bibliotecas
#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
// neopixel
#define leds 8
#define pino D7
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(leds, pino, NEO_GRB + NEO_KHZ800);

//

//rainbow
uint32_t Wheel(byte WheelPos);
void rainbow() {
  uint16_t i, j;

  for (j = 0; j < 256; j++) {
    for (i = 0; i < pixels.numPixels(); i++) {
      pixels.setPixelColor(i, Wheel((i + j) & 255));
    }
    pixels.show();
    delay(20);
  }
} 

uint32_t Wheel(byte WheelPos) {
  if (WheelPos < 85) {
    return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
    WheelPos -= 170;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

//desativar rainbow

void handle_pixelsclear() {
  for (int i = 0; i < pixels.numPixels(); i++) {
    pixels.setPixelColor(i, 0); // Define a cor de todos os pixels para preto
  }
  pixels.show(); // Mostra as cores dos pixels atualizadas
}


//wifi config
const char* ssid = "deathsdance"; 
const char* password = "12345678";  

//handles
void handle_OnConnect();
void handle_ledon();
void handle_ledoff();
void handle_rainbowon();
void handle_rainbowoff();
void handle_NotFound();


//string/porta
String SendHTML(uint8_t led);
ESP8266WebServer server(80);

//estados leds
bool LEDstatus = LOW;
bool LEDstatus1 = LOW;
bool rainbowst = false;

//setup
void setup() {
  pixels.begin();
  Serial.begin(115200); 
  pinMode(D2, OUTPUT); 
  pinMode(LED_BUILTIN, OUTPUT);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Rede WiFi: ");
  Serial.println(ssid);
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());
  delay(100);
  server.on("/", handle_OnConnect);
  server.on("/ledon", handle_ledon);
  server.on("/ledoff", handle_ledoff);
  server.on("/rainbowon", handle_rainbowon);
  server.on("/rainbowoff", handle_rainbowoff);
  server.onNotFound(handle_NotFound);
  server.begin();
  Serial.println("Servidor HTTP iniciado!");
}

//loop
void loop() {
  server.handleClient(); 
 if (rainbowst)
  digitalWrite(D7, HIGH);
 else 
    digitalWrite(D7, LOW); // Limpa todos os pixels
  if (LEDstatus)
    digitalWrite(D2, HIGH);  
  else
    digitalWrite(D2, LOW); 
  if (LEDstatus1)
    digitalWrite(LED_BUILTIN, HIGH);
  else
    digitalWrite(LED_BUILTIN, LOW);
}
void handle_OnConnect() {
  LEDstatus = LOW;
  LEDstatus1 = HIGH;
  server.send(200, "text/html", SendHTML(false));
}
void handle_rainbowon(){
  rainbow();
  server.send(200, "text/html", SendHTML(rainbowst));
}
void handle_rainbowoff(){
  handle_pixelsclear();
  server.send(200, "text/html", SendHTML(rainbowst));
}

void handle_ledon() {
  LEDstatus = HIGH;
  LEDstatus1 = LOW;
  server.send(200, "text/html", SendHTML(LEDstatus));
}
void handle_ledoff() {
  LEDstatus = LOW;
  LEDstatus1 = HIGH;
  server.send(200, "text/html", SendHTML(LEDstatus));
}
void handle_NotFound() {
  server.send(404, "text/plain", "Not found");
} 
///HTMLCSS 
String SendHTML(uint8_t led) {
  const char css[] = R"=====(
<!DOCTYPE html>
    <html>
      <head>
        <meta charset="UTF-8">
        <title>Web Server - Esp8266</title>
        <style>
        body {
            margin: 0;
            padding: 0;
            font-family: sans-serif;
        }
        header {
            background-color: #333;
            color: #fff;
            padding: 10px;
            text-align: center;
        }
        section {
            display: flex;
            flex-direction: column;
            align-items: center;
            margin-top: 30px;
        }
        .item-head {
            display: flex;
            justify-content: space-between;
            align-items: center;
            width: 50%;
            margin-bottom: 10px;
            padding: 5px;
            background-color: #ddd;
        }
        .titulo {
            font-size: 20px;
            font-weight: bold;
        }
        .estado {
            padding: 5px;
            border-radius: 5px;
            text-transform: uppercase;
            font-size: 14px;
        }
        .on {
            background-color: green;
            color: #fff;
        }
        .off {
            background-color: red;
            color: #fff;
        }
        .acoes {
            display: flex;
            justify-content: space-between;
            width: 50%;
        }
        .ligar, .desligar {
            width: 40%;
            height: 40px;
            background-color: gray;
            display: flex;
            justify-content: center;
            align-items: center;
            text-decoration: none;
            font-size: 15px;
            text-transform: uppercase;
            color: black;
            transition: all 0.4s;
        }
        .ligar:hover {
            background-color: green;
        }
        .desligar:hover {
            background-color: red;
        }
        </style>
      </head>
      <body>
      <header>
        <h1>Web Server - Esp8266</h1>   
    </header>
    <section>
        <div class="item-head">
            <div class="titulo">Controle de Led Azul
            e Led Builtin</div>
        </div>
        <div class="acoes">
          <a href="/ledon" class="ligar">Ligar</a>
          <a href="/ledoff" class="desligar">Desligar</a>
        </div>
        <div class="item-head">
            <div class="titulo">Rainbow</div>
        </div>
        <div class="acoes">
          <a href="/rainbowon" class="ligar">Ligar</a>
          <a href="/rainbowoff" class="desligar">Desligar</a>
        </div>
    </section>
    <footer>
        Feito por João!
    </footer>
      </body>
    </html>
  )=====";
  const char rodape[] = R"=====(
    <footer>
      <p>Esp8266 - WebServer.</p>
    </footer>
  )=====";
  return String(css) + String(rodape); 
  // Retorna a página HTML completa
}