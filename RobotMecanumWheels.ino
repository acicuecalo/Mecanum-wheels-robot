// Paco Carabaza 17/12/2020
// Lee los valores de un receptor de radiocontrol conectando los canales 1 al 4 a los pines del arduino 5 al 8
// Variables para 4 canales arduino UNO

#include <Wire.h>
#include <Adafruit_MotorShield.h>
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); // Create the motor shield objects with the default I2C address
Adafruit_DCMotor *motorDelanteroIzquierdo = AFMS.getMotor(1);   //port M1
Adafruit_DCMotor *motorDelanteroDerecho = AFMS.getMotor(2);     //port M2
Adafruit_DCMotor *motorTraseroDerecho = AFMS.getMotor(3);       //port M3
Adafruit_DCMotor *motorTraseroIzquierdo = AFMS.getMotor(4);     //port M4

int rcPins[4] = {5, 6, 7, 8};
int chValue[4];
int pesoMezcla[4];
int channels = 4;
int iChannel;
const int pulseInDelay = 35000;

void setup()
{
  Serial.begin(115200);
  AFMS.begin();         // create with the default frequency 1.6KHz  //AFMS.begin(1000);   // OR with a different frequency, say 1KHz
  pararMotores();
}

void loop()
{
  leerCanales();
  calcularPesosMezclas();
  printMezclas();
  //printChannel();
  salidaMotores();
}

void pararMotores()
{
  motorDelanteroIzquierdo->run(RELEASE);
  motorDelanteroDerecho->run(RELEASE);
  motorTraseroDerecho->run(RELEASE);
  motorTraseroIzquierdo->run(RELEASE);
}

void leerCanales()
{
  for (int iChannel = 0; iChannel < channels; iChannel++)
  {
    int rawValue = pulseIn(rcPins[iChannel], HIGH, pulseInDelay);
    chValue[iChannel] = rawValue;
  }
}

void calcularPesosMezclas()
{
  int deadband = 15;
  //pesoMezcla[0] = (map(chValue[0], 977, 2007, -255, 255));
  pesoMezcla[0] = (map(chValue[0], 980, 2020, -255, 255));
  pesoMezcla[0] = constrain(pesoMezcla[0], -255, 255);
  if (pesoMezcla[0] > (deadband * -1) && pesoMezcla[0] < deadband) {
    pesoMezcla[0] = 0;
  }

  //pesoMezcla[1] = (map(chValue[1], 980, 2010, -255, 255));
  pesoMezcla[1] = (map(chValue[1], 980, 2020, -255, 255));
  pesoMezcla[1] = constrain(pesoMezcla[1], -255, 255);
  if (pesoMezcla[1] > (deadband * -1) && pesoMezcla[1] < deadband) {
    pesoMezcla[1] = 0;
  }

  //pesoMezcla[2] = (map(chValue[2], 965, 1995, -255, 255));
  pesoMezcla[2] = (map(chValue[2], 980, 2020, -255, 255));
  pesoMezcla[2] = constrain(pesoMezcla[2], -255, 255);
  if (pesoMezcla[2] > (deadband * -1) && pesoMezcla[2] < deadband) {
    pesoMezcla[2] = 0;
  }

  //pesoMezcla[3] = (map(chValue[3], 974, 2003, -255, 255));
  pesoMezcla[3] = (map(chValue[3], 980, 2020, -255, 255));
  pesoMezcla[3] = constrain(pesoMezcla[3], -255, 255);
  if (pesoMezcla[3] > (deadband * -1) && pesoMezcla[3] < deadband) {
    pesoMezcla[3] = 0;
  }
}


void salidaMotores()
{
  motorDelanteroIzquierdo->setSpeed(abs(pesoMezcla[0]));
  if (pesoMezcla[0] == 0) {
    motorDelanteroIzquierdo->run(RELEASE);
  }
  if (pesoMezcla[0] > 0) {
    motorDelanteroIzquierdo->run(FORWARD);
  }
  if (pesoMezcla[0] < 0) {
    motorDelanteroIzquierdo->run(BACKWARD);
  }

  motorDelanteroDerecho->setSpeed(abs(pesoMezcla[1]));
  if (pesoMezcla[1] == 0) {
    motorDelanteroDerecho->run(RELEASE);
  }
  if (pesoMezcla[1] > 0) {
    motorDelanteroDerecho->run(FORWARD);
  }
  if (pesoMezcla[1] < 0) {
    motorDelanteroDerecho->run(BACKWARD);
  }

  motorTraseroDerecho->setSpeed(abs(pesoMezcla[2]));
  if (pesoMezcla[2] == 0) {
    motorTraseroDerecho->run(RELEASE);
  }
  if (pesoMezcla[2] > 0) {
    motorTraseroDerecho->run(FORWARD);
  }
  if (pesoMezcla[2] < 0) {
    motorTraseroDerecho->run(BACKWARD);
  }

  motorTraseroIzquierdo->setSpeed(abs(pesoMezcla[3]));
  if (pesoMezcla[3] == 0) {
    motorTraseroIzquierdo->run(RELEASE);
  }
  if (pesoMezcla[3] > 0) {
    motorTraseroIzquierdo->run(FORWARD);
  }
  if (pesoMezcla[3] < 0) {
    motorTraseroIzquierdo->run(BACKWARD);
  }

}

/*
  void readChannel(int channel)
  {
  int rawValue = pulseIn(rcPins[channel], HIGH, pulseInDelay);
  chValue[channel] = rawValue;
  }
*/


void printMezclas()
{
  for (int iChannel = 0; iChannel < channels; iChannel++)
  {
    Serial.print(pesoMezcla[iChannel]);
    Serial.print(" ");
  };
  Serial.println("");
}

void printChannel()
{
  for (int iChannel = 0; iChannel < channels; iChannel++)
  {
    Serial.print(chValue[iChannel]);
    Serial.print(" ");
  };
  Serial.println("");
}
