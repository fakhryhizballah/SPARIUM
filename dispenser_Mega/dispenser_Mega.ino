#include <UTFT.h>
#include <URTouch.h>
#include <UTFT_Buttons.h>
#include <SoftwareSerial.h>

// Declare which fonts we will be using

extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];


UTFT        myGLCD(ILI9341_16,38,39,40,41); 
URTouch      myTouch(6,5,4,3,2);
UTFT_Buttons  myButtons(&myGLCD, &myTouch);
SoftwareSerial BTSerial(10,11); //RX, TX
int var = 100 ;
int BTval ;

int pressed_button, btnAir, btnStop, btnPause;
void setup() {
  BTSerial.begin(9600);
  Serial.begin(9600);
  Serial.print(" I received:"); 
  BTSerial.print(" BTS Tersambung");  
  myGLCD.InitLCD();
  myGLCD.clrScr();
  myGLCD.setFont(BigFont);
  myTouch.InitTouch();
  myTouch.setPrecision(PREC_MEDIUM);
  myButtons.setTextFont(BigFont);
  //myGLCD.fillScr(248,255,131);
  pinMode(8, OUTPUT);
  digitalWrite(8, HIGH);
  pinMode(9, OUTPUT);
  digitalWrite(9, HIGH);

}

void start(){
  myButtons.deleteAllButtons();
  myGLCD.fillScr(255,255,255);
  myGLCD.setBackColor(255,255,255);
  myGLCD.setColor(144, 222, 255);
  myGLCD.setFont(BigFont);
  
  myGLCD.print("SPAIRUM PROJECT", CENTER, 0);
  myGLCD.print("Tekan Tombol AMBIL", CENTER, 16); 
  btnAir = myButtons.addButton( 10, 50, 300, 30, "Ambil air");
  myButtons.drawButtons();
  myGLCD.print("SALDO:", 10, 150);
  myGLCD.setColor(94, 255, 0);
  myGLCD.setFont(SevenSegNumFont);
  myGLCD.printNumI(var, 100,150);
  myGLCD.setColor(144, 222, 255);
  myGLCD.setFont(BigFont);
  myGLCD.print("ML",210,150);
  
  while (var == 0){
    if (BTSerial.available()>0){
     BTval = BTSerial.parseInt();
      var = BTval;
    BTSerial.print("Saldo:");
    BTSerial.print(var);
    BTSerial.print(BTval);
    BTSerial.println();
    Serial.print(BTval);
    start();
    }
   
  
   if (Serial.available()){
    int val = Serial.parseInt();
      var = val;
    Serial.print("Saldo:");
    Serial.print(var);
    Serial.println();
    BTSerial.print(val);
    start();
   } 
   }
   
     //myGLCD.clrScr();
       
  
  while (1){
  if (myTouch.dataAvailable() == true){
      pressed_button = myButtons.checkButtons();
      if (pressed_button==btnAir){
      menu();
     myButtons.deleteButton(btnAir);
    }
    }
  }
}



void menu(){
   myGLCD.clrScr();
   if (var == 0){
       digitalWrite(8, HIGH); 
       myGLCD.setColor(205, 0,0);
       myGLCD.setFont(BigFont);
       myGLCD.print("SALDO HABIS",CENTER,100);
       delay(2500);
        myGLCD.clrScr();
       start();
    
   }
   myButtons.deleteButton(btnAir);
   btnStop = myButtons.addButton( 10, 50, 75, 75, "STOP");
   btnPause = myButtons.addButton( 95, 50, 85, 75, "PAUSE");
   pressed_button = myButtons.checkButtons();
    myButtons.drawButtons();
  
while (var > 0) {
  digitalWrite(8, LOW);
  if (myTouch.dataAvailable() == true){
      pressed_button = myButtons.checkButtons();
      if (pressed_button==btnStop){
        digitalWrite(8, HIGH);
        var = 1;
      }
      if (pressed_button==btnPause){
        var = var;
        digitalWrite(8, HIGH); 
        myGLCD.clrScr();
          start();
      }
  }
  myGLCD.setColor(205, 0,0);
  myGLCD.fillRect(0, 306, 479, 319);
  myGLCD.print("Tekan Tombol Stop:",LEFT, 0);
  myGLCD.print("Pause Pengisisan", LEFT,16);
  myGLCD.setColor(0,10,220);
  myGLCD.print("SALDO: ", 10, 150);
  myGLCD.printNumI(var, 130,150,4 ,' ');
  myGLCD.print("ML",210,150);
  Serial.println(var);
  
  var--;
  BTSerial.println(var);
  delay(0.0005);
}
  
       delay(1000);
       digitalWrite(8, HIGH); 
        myGLCD.clrScr();
          start();
        
  }

void TopUP(){
  
}

void loop() {
  boolean default_colors = true;
 
start();

}
