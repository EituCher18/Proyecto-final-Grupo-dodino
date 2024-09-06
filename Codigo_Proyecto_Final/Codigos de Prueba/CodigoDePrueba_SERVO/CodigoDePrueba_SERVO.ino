#include <ESP32Servo.h>
 //Se tienen que conectar a pines PWM
// Declaramos el nombre de los servo motores a usar
Servo servoMotor1;
Servo servoMotor2;
Servo servoMotor3;
Servo servoMotor4;
Servo servoMotor5;
Servo servoMotor6;

void setup() {
  // Iniciamos el monitor serie para mostrar el resultado
  Serial.begin(9600);
 
 //Marcamos en que piines van a estar conectado los servos
  servoMotor1.attach(33);
  servoMotor2.attach(18);
  servoMotor3.attach(21);

}
// pines de los servos 18 21 23 25 26 33  
void loop ()
{
//se escribe nombre del servo.write(el valor del giro);
servoMotor1.write(90);
servoMotor2.write(90);
servoMotor3.write(90);
delay(1000);
servoMotor1.write(180);
servoMotor2.write(180);
servoMotor3.write(180);
delay(1000);
servoMotor1.write(0);
servoMotor2.write(0);
servoMotor3.write(0);
delay(1000);
servoMotor1.write(90);
servoMotor2.write(90);
servoMotor3.write(90);
delay(1000);
servoMotor1.write(180);
servoMotor2.write(180);
servoMotor3.write(180);
delay(1000);
servoMotor1.write(0);
servoMotor2.write(0);
servoMotor3.write(0);
delay(1000);
}