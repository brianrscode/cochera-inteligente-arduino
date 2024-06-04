#include <Servo.h>

int TRIG_PIN = 2;
int ECHO_PIN = 3;
int SERVO_PIN = 5;
int LED_ROJO = 11;
int LED_VERDE = 12;
int pinBuzzer = 10;

Servo myServo;

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  myServo.attach(SERVO_PIN);
  pinMode(LED_ROJO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(pinBuzzer, OUTPUT);
  myServo.write(0);
}

void loop() {
  long duration, distance;

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // mide la duración del pulso de eco (echo) recibido por el sensor ultrasónico conectado al pin ECHO_PIN
  duration = pulseIn(ECHO_PIN, HIGH);
  // se calcula la distancia en centímetros utilizando la fórmula de la velocidad del sonido en el aire. 
  distance = duration * 0.0343 / 2;

  Serial.print("Distancia: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance < 16) {
    abrirPuerta(90);
    delay(4000); // Espera 4 segundos con la puerta abierta
    tone(pinBuzzer, 1000, 3000);
    cerrarPuerta(0);
    delay(1000); // Espera 1 segundo con la puerta cerrada
  }

  delay(1000);
}

void abrirPuerta(int angulo) {
  digitalWrite(LED_VERDE, HIGH);
  digitalWrite(LED_ROJO, LOW);
  for (int i = myServo.read(); i <= angulo; i++) {
    myServo.write(i);
    delay(30); // Ajusta la velocidad de apertura (más lento)
  }
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_ROJO, LOW);
}

void cerrarPuerta(int angulo) {
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_ROJO, HIGH);
  for (int i = myServo.read(); i >= angulo; i--) {
    myServo.write(i);
    delay(30); // Ajusta la velocidad de cierre (más lento)
  }
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_ROJO, LOW);
}
