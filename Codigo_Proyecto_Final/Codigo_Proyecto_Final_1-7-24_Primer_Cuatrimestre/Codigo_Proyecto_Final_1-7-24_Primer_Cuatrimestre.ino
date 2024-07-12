#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include <UniversalTelegramBot.h>
#include <ESP32Servo.h>

Servo ServoMotor[5];

bool aux = false;
unsigned long tiempo;
unsigned long tiempoUltimoCambio;

const char* ssid = "ORT-IoT";
const char* password = "OrtIOTnew22$2";

#define BOTtoken "6887192498:AAH96GYOpwVlT3cpzu_IwoZmRzhPGEn1WH4"
#define CHAT_ID "6861080846"

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

int Botdelay = 1000;
unsigned long lastTimeBotRan;
int numNewMessages;
int estado = 0;

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 5; i++) {
    ServoMotor[i].attach(12 + i); 
  }

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500); 
  }
  Serial.println("");
  Serial.println("WiFi conectado.");
  bot.sendMessage(CHAT_ID, "Bot iniciado", "");
}

void loop() {
  if (millis() > lastTimeBotRan + Botdelay) {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while (numNewMessages) {
      Serial.println("Mensaje");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    lastTimeBotRan = millis();
  }
  tiempo = millis();
  ServosApagados();
}

void handleNewMessages(int numNewMessages) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));

  for (int i = 0; i < numNewMessages; i++) {
    String chat_id = String(bot.messages[i].chat_id);
    if (chat_id != CHAT_ID) {
      bot.sendMessage(chat_id, "Usuario no autorizado", "");
      continue;
    }
    String text = bot.messages[i].text;

    switch (estado) {
      case 0:
        if (text == "/start") {
          bot.sendMessage(chat_id, "Programa Braille iniciado");
          estado = 1;
        }
        break;
      case 1:
        int text_len = text.length() + 1;
        char char_array_text[text_len];
        text.toCharArray(char_array_text, text_len);

        for (int j = 0; j < text_len - 1; j++) { 
          char letra = char_array_text[j];
          switch (letra) {
            case 'a':
              servo1();
              break;
            case 'b':
              servo1();
              servo2();
              break;
          }
        }
        estado = 0; 
        break;
    }
  }
}

void servo1() {
  ServoMotor[0].write(180);
}

void servo2() {
  ServoMotor[1].write(180);
}

void servo3() {
  ServoMotor[2].write(180);
}

void servo4() {
  ServoMotor[3].write(180);
}

void servo5() {
  ServoMotor[4].write(180);
}

void ServosApagados() {
  if (millis() - tiempo >= 1000) {
    for (int i = 0; i < 5; i++) {
      ServoMotor[i].write(0);
    }
  }
}