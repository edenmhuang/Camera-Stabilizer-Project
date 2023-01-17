#include <Adafruit_MPU6050.h> 
#include <Adafruit_Sensor.h>
#include <Servo.h>

Servo sg90; // motor x // pin 2
Servo sg90two; // motor y // pin 3


int servo_pin = 2; // motor x
int servo_pin1 = 3; // motor y

Adafruit_MPU6050 myAccel;

char tmp_str[7]; // temporary variable used in convert function

// converts int16 to string. Moreover, resulting strings will have the same length in the debug monitor
char* convert_int16_to_str(int16_t i) {
  sprintf(tmp_str, "%6d", i);
  return tmp_str;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // The serial monitor begins
  Serial.println  ( "Initializing the sensor" );

  sg90.attach ( servo_pin ); // This code sets the servo motor PIN
  sg90two.attach ( servo_pin1 ); // This code sets the servo motor PIN

 
  myAccel.begin(); /* doesn't work change myAccel to Serial+ need */

  sg90.write(90); // Servo motor turns to starting position
  sg90two.write(90); // Servo motor turns to starting position

  delay(500); // delay

}

void loop() {
  // put your main code here, to run repeatedly:

  sensors_event_t a, g, temp; // Get new sensor events with the readings
  myAccel.getEvent(&a, &g, &temp);

  int x_value = a.acceleration.x; // Accelerator X-axis values are put into the variable
  int y_value = a.acceleration.y; // Accelerator Y-axis values are put into the variable

  x_value = map(x_value, -10, 10, 180, 0); // This value is converted from 0 to 180
  y_value = map(y_value, -10, 10, 180, 0); // This value is converted from 0 to 180


   sg90two.write(y_value); // This code line rotate the servo motor y using y_value
   sg90.write(x_value); // This code line rotate the servo motor x using x_value



  Serial.print("aX = "); Serial.print(convert_int16_to_str(x_value));
  Serial.print(" | aY = "); Serial.print(convert_int16_to_str(y_value));


  delay(500);

}