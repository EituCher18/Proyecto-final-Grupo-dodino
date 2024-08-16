#include <WiFi.h>
  #include <WiFiClientSecure.h>
  #include <ArduinoJson.h>
  #include <UniversalTelegramBot.h>
  #include <ESP32Servo.h>

  Servo ServoMotor[5];

  unsigned long tiempo;

  const char* ssid = "ORT-IoT";
  const char* password = "OrtIOT2024";

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

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
    while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi conectado.");
    bot.sendMessage(CHAT_ID, "Bot iniciado", "");

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
                servo1();
                break;
              case 'b':
                servo1();
                servo2();
                break;
              case 'c':
                servo1();
                servo4();
                break;
              case 'd':
                servo1();
                servo4();
                servo5();
                break:
              case 'e':
                servo1();
                servo5();
                break:
              case 'f':
                servo1();
                servo2();
                servo4();
                break;
              case 'g'
                servo1();
                servo2();
                servo4();
                servo5();
                break;
              case 'h':
                servo1();
                servo2();
                servo5();
                break:
              case 'i':
                servo2();
                servo4();
                servo5();
                break:
              case 'k':
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