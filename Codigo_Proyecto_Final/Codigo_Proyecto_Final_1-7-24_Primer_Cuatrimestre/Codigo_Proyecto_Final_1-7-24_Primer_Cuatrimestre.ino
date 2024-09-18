#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include <UniversalTelegramBot.h>
#include <ESP32Servo.h>

Servo ServoMotor[5];

unsigned long tiempo;

const char* ssid = "iPhone de Ezequiel";
const char* password = "Eze05eze07";

#define BOTtoken "6887192498:AAH96GYOpwVlT3cpzu_IwoZmRzhPGEn1WH4"
#define CHAT_ID "6861080846"

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

int numeritos;
int estado;
String text = "";
String chat_id = "";

TaskHandle_t Task1;
TaskHandle_t Task2;

enum estados {
  INICIO,
  CONVERSION,
  a,
  b,
  c,
  d,
  e,
  f,
  g,
  h,
  i,
  j,
  k,
  l,
  m,
  n,
  o,
  p,
  q,
  r,
  s,
  t,
  u,
  v,
  w,
  x,
  y,
  z
};

void setup() {
  Serial.begin(115200);
  for (int i = 1; i < 5; i++) {
    ServoMotor[i].attach(15 + i);
  }



  xTaskCreatePinnedToCore(
    Task1code, /* Task function. */
    "Task1",   /* name of task. */
    10000,     /* Stack size of task */
    NULL,      /* parameter of the task */
    1,         /* priority of the task */
    &Task1,    /* Task handle to keep track of created task */
    0);        /* pin task to core 0 */


  xTaskCreatePinnedToCore(
    Task2code, /* Task function. */
    "Task2",   /* name of task. */
    10000,     /* Stack size of task */
    NULL,      /* parameter of the task */
    1,         /* priority of the task */
    &Task2,    /* Task handle to keep track of created task */
    1);        /* pin task to core 1 */

  estado = INICIO;
}
void loop() {
}

void Task1code(void* pvParameters) {
  int numNewMessages;
  int lastTimeBotRan;
  int Botdelay = 1000;

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectado.");
  bot.sendMessage(CHAT_ID, "Bot iniciado", "");

  for (;;) {
    if (millis() > lastTimeBotRan + Botdelay) {
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);

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
}

void handleNewMessages(int numNewMessages) {

  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));

  for (numeritos = 0; numeritos < numNewMessages; numeritos++) {
    chat_id = String(bot.messages[i].chat_id);
    if (chat_id != CHAT_ID) {
      bot.sendMessage(chat_id, "Usuario no autorizado", "");
      continue;
    }
    text = bot.messages[numeritos].text;
  }
}
void Task2code(void* parameter) {
  int text_len;
  int longitud;
  char letra;
  char char_array_text[text_len];

  for (;;) {
    switch (estado) {
      case INICIO:
        if (text == "/start") {
          bot.sendMessage(chat_id, "Programa Braille iniciado");
          estado = CONVERSION;
        }
        break;
      case CONVERSION:
        text.toCharArray(char_array_text, text_len);
        for (longitud = 0; longitud < text_len - 1; longitud++) {
          letra = char_array_text[j];
          switch (letra) {
            case 'a':
              bot.sendMessage(chat_id, "a");
              servo1();
              break;
            case 'b':
              bot.sendMessage(chat_id, "b");
              servo1();
              servo2();
              break;
            case 'c':
              bot.sendMessage(chat_id, "c");
              servo1();
              servo4();
              break;
            case 'd':
              bot.sendMessage(chat_id, "d");
              servo1();
              servo4();
              servo5();
              break;
            case 'e':
              bot.sendMessage(chat_id, "e");
              servo1();
              servo5();
              break;
            case 'f':
              bot.sendMessage(chat_id, "f");
              servo1();
              servo2();
              servo4();
              break;
            case 'g':
              bot.sendMessage(chat_id, "g");
              servo1();
              servo2();
              servo4();
              servo5();
              break;
            case 'h':
              bot.sendMessage(chat_id, "h");
              servo1();
              servo2();
              servo5();
              break;
            case 'i':
              bot.sendMessage(chat_id, "i");
              servo2();
              servo4();
              break;
            case 'j':
              bot.sendMessage(chat_id, "j");
              servo2();
              servo4();
              servo5();
              break;
            case 'k':
              bot.sendMessage(chat_id, "k");
              servo1();
              servo3();
              break;
            case 'l':
              bot.sendMessage(chat_id, "l");
              servo1();
              servo2();
              servo3();
              break;
            case 'm':
              bot.sendMessage(chat_id, "m");
              servo1();
              servo3();
              servo4();
              break;
            case 'n':
              bot.sendMessage(chat_id, "n");
              servo1();
              servo3();
              servo4();
              servo5();
              break;
            case 'ñ':
              bot.sendMessage(chat_id, "ñ");
              servo1();
              servo3();
              servo4();
              servo5();
              servo6();
            case 'o':
              bot.sendMessage(chat_id, "o");
              servo1();
              servo3();
              servo5();
              break;
            case 'p':
              bot.sendMessage(chat_id, "p");
              servo1();
              servo2();
              servo3();
              servo4();
              break;
            case 'q':
              bot.sendMessage(chat_id, "q");
              servo1();
              servo2();
              servo3();
              servo4();
              servo5();
              break;
            case 'r':
              bot.sendMessage(chat_id, "r");
              servo1();
              servo2();
              servo3();
              servo5();
              break;
            case 's':
              bot.sendMessage(chat_id, "s");
              servo2();
              servo3();
              servo4();
              break;
            case 'u':
              bot.sendMessage(chat_id, "u");
              servo1();
              servo3();
              servo6();
              break;
            case 'v':
              bot.sendMessage(chat_id, "v");
              servo1();
              servo2();
              servo3();
              servo6();
              break;
            case 'w':
              bot.sendMessage(chat_id, "w");
              servo2();
              servo4();
              servo5();
              servo6();
              break;
            case 'x':
              bot.sendMessage(chat_id, "x");
              servo1();
              servo3();
              servo4();
              servo6();
              break;
            case 'y':
              bot.sendMessage(chat_id, "y");
              servo1();
              servo3();
              servo4();
              servo5();
              servo6();
              break;
            case 'z':
              bot.sendMessage(chat_id, "z");
              servo1();
              servo3();
              servo5();
              servo6();
              break;
          }
        }
        estado = INICIO;
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
