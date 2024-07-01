#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include <UniversalTelegramBot.h>
#include <ESP32Servo.h>

//#define SERVO
//#define SERVO
//#define SERVO
//#define SERVO
//#define SERVO
//#define SERVO

Servo ServoMotor[5];


bool aux = false;

unsigned long tiempo;
unsigned long tiempoUltimoCambio;

const char* ssid = "ORT-IoT";
const char* password = "OrtIOTnew22$2 ";

#define BOTtoken "6887192498:AAH96GYOpwVlT3cpzu_IwoZmRzhPGEn1WH4"
#define CHAT_ID "6861080846"

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);


int Botdelay = 1000;
unsigned long lastTimeBotRan;
int numNewMessages;

void setup() {
  Serial.begin(9600);
  for (int i = 0; i <= 5; i++) {
    ServoMotor[i].attach(12, 13, 14);
  }

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
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
    int estado = 0;
    switch (estado) {
      case 0:
        if (text == "/start") {
          bot.sendMessage(chat_id, "Programa Braille iniciado ");
          estado = 1;
        }
        break;
      case 1:
        int text_len = text.length() + 1;
        char char_array_text[text_len];
        text.toCharArray(char_array_text, text_len);
        const char letra
        switch (letra) {
          case "a":
            servo1();
            ServosApagados();
            break;
          case "b":
            servo1();
            servo2();
            ServosApagados();
        }
    }
  }
  //  String from_name = bot.messages[i].from_name;      preguntar a cherniak para que sirve esto
}
void servo1() {
  ServoMotor[1].write(180);
}
void servo2() {
  ServoMotor[2].write(180);
}
void servo3() {
  ServoMotor[3].write(180);
}
void servo4() {
  ServoMotor[4].write(180);
}
void servo5() {
  ServoMotor[5].write(180);
}
void ServosApagados() {
  tiempo = millis();
  if (tiempo >= 1000) {
    ServoMotor[1].write(0);
    ServoMotor[2].write(0);
    ServoMotor[3].write(0);
    ServoMotor[4].write(0);
    ServoMotor[5].write(0);
  }
  //  if (tiempo >= 2000) {}    delay de los servos apagados https://forum.arduino.cc/t/proyecto-para-braille/516633
}
