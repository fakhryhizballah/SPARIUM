#include <SoftwareSerial.h>
SoftwareSerial sim(3, 2);

#include "HX711.h"
HX711 scale(6, 5);

int Kode = 0;

float calibration_factor = -107; // this calibration factor is adjusted according to my load cell
float units;
float ounces;

int _timeout;
String _buffer;
String number = "+62895373130201"; //-> change with your number
void setup() {
  delay(7000); //delay for 7 seconds to make sure the modules get the signal
  Serial.begin(9600);
  _buffer.reserve(50);
  Serial.println("Sistem Started...");
  sim.begin(9600);
  delay(1000);
  Serial.println("Type s to send an SMS, r to receive an SMS, and c to make a call");

  scale.set_scale();
  //scale.tare();  //Reset the scale to 0

  long zero_factor = scale.read_average(); //Get a baseline reading
  Serial.print("Zero factor: "); //This can be used to remove the need to tare the scale. Useful in permanent scale projects.
  Serial.println(zero_factor);
}

void loop() {
  scale.set_scale(calibration_factor); //Adjust to this calibration factor
  Serial.print("Reading: ");
  units = scale.get_units(), 10;
  //if (units < 0)
  //{
    //units = 0.00;
  //}
  
  ounces = units * 0.035274;
  Serial.print(units);
  Serial.print(" grams"); 
  Serial.print(" calibration_factor: ");
  Serial.print(calibration_factor);
  Serial.println();

  if (units < 600){
     Kode = 7;
     Serial.println(" SMS");
     callNumber();
     low();
  }
  delay (1000);
   if (sim.available() > 0)
    Serial.write(sim.read());
delay(2000);
}

 void low(){
  Serial.println("sudah sms");
  scale.set_scale(calibration_factor); //Adjust to this calibration factor
  Serial.print("Reading: ");
  units = scale.get_units(), 10;
  //if (units < 0)
  //{
    //units = 0.00;
  //}
  
  ounces = units * 0.035274;
  Serial.print(units);
  Serial.print(" grams");

   if (units < 300){
     Kode = 7;
     Serial.println(" Pangill");
     callNumber();
     Habis();
  }
  delay (2000);
  low();
  
  }

  void Habis(){
  Serial.println(" sudah call");
  scale.set_scale(calibration_factor); //Adjust to this calibration factor
  Serial.print("Reading: ");
  units = scale.get_units(), 10;
  //if (units < 0)
  //{
    //units = 0.00;
  //}
  
  ounces = units * 0.035274;
  Serial.print(units);
  Serial.print(" grams");
  delay(2000); 
  Habis();
  }

void SendMessage()
{
  //Serial.println ("Sending Message");
  sim.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);
  //Serial.println ("Set SMS Number");
  sim.println("AT+CMGS=\"" + number + "\"\r"); //Mobile phone number to send message
  delay(1000);
  String SMS = "Air udah Mau Habis";
  sim.println(SMS);
  delay(100);
  sim.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  _buffer = _readSerial();
}
void RecieveMessage()
{
  Serial.println ("SIM800L Read an SMS");
  delay (1000);
  sim.println("AT+CNMI=2,2,0,0,0"); // AT Command to receive a live SMS
  delay(1000);
  Serial.write ("Unread Message done");
}
String _readSerial() {
  _timeout = 0;
  while  (!sim.available() && _timeout < 12000  )
  {
    delay(13);
    _timeout++;
  }
  if (sim.available()) {
    return sim.readString();
  }
}
void callNumber() {
  sim.print (F("ATD"));
  sim.print (number);
  sim.print (F(";\r\n"));
  _buffer = _readSerial();
  Serial.println(_buffer);
}
