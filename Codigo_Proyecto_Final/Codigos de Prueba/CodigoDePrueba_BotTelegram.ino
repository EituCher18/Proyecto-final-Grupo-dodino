#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include <UniversalTelegramBot.h>

#define BOT1 35

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
  Serial.begin(115200);

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
    Serial.println(text);

    String from_name = bot.messages[i].from_name;
    int estado = 0;
    
    switch (estado) {

      case 0:
        if (text == "/start") {
          bot.sendMessage(chat_id, "Programa Braille iniciado ");
          estado = 1;
          break;
        }
      case 1:
      char letra = text.toCharArray(0,0);
        while(Serial.available){
        }
        switch (letra) {
          case "a":
            if (letra == "a") {
              Serial.print1n(letra);
              break;
            }
          case b:
            if (letra == "b") {
              serial.print1n(letra);
              break;
            }
        }
    }
  }
}
