#include <UTFT.h>
#include <URTouch.h>
#include <UTFT_Buttons.h>
#include <SoftwareSerial.h>

// Declare which fonts we will be using

extern uint8_t GroteskBold16x32[];
extern uint8_t BigFont[];
extern uint8_t CalibriBold32x48[];
extern uint8_t arial_bold[];


UTFT        myGLCD(ILI9341_16,38,39,40,41); 
URTouch      myTouch(6,5,4,3,2);
UTFT_Buttons  myButtons(&myGLCD, &myTouch);
SoftwareSerial BTSerial(10,11); //RX, TX
int var = 40 ;
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
  myGLCD.fillScr(255,255,255);
  myGLCD.setBackColor(255,255,255);
  //myButtons.setTextFont(BigFont);
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
  myGLCD.print("SPAIRUM PROJECT", CENTER, 5);
  myButtons.setTextFont(arial_bold);
  myGLCD.print("Tekan Start AMBIL", CENTER, 21);
  myButtons.setTextFont(arial_bold); 
  btnAir = myButtons.addButton( 190, 50, 120, 70, "START");
  myButtons.drawButtons();
  myButtons.setTextFont(arial_bold);
  myGLCD.print("TOKEN:", 20, 50);
  myGLCD.setColor(17, 0, 225);
  myGLCD.setFont(CalibriBold32x48);
  myGLCD.printNumI(var, 20,80);
  myGLCD.setColor(144, 222, 255);
  myGLCD.setFont(BigFont);
  myGLCD.print("x10 ML",35,150);
  
  while (var == 0){
    if (BTSerial.available()>0){
     BTval = BTSerial.parseInt();
      var = BTval;
    BTSerial.print("Saldo:");
    BTSerial.print(var);
    //BTSerial.print(BTval);
    //BTSerial.println();
    //Serial.print(BTval);
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
   myGLCD.fillScr(255,255,255);
   myGLCD.setBackColor(255,255,255);
   
   myButtons.deleteButton(btnAir);
   
   myButtons.setTextFont(arial_bold);
   myGLCD.print("STOP Untuk menghabiskan TOKEN",LEFT, 5);
   myGLCD.print("Pause Untuk menjeda pengisisan", LEFT,21);
   btnStop = myButtons.addButton( 190, 50, 120, 70, "STOP");
   btnPause = myButtons.addButton( 190, 130, 120, 70, "PAUSE");
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
  myGLCD.print("TOKEN:", 20, 50);
  myGLCD.setColor(17, 0, 225);
  myGLCD.setFont(CalibriBold32x48);
  myGLCD.printNumI(var, 20,80);
  myGLCD.setColor(144, 222, 255);
  myGLCD.setFont(BigFont);
  myGLCD.print("x10 ML",35,150);
  
  var--;
  BTSerial.println(var);
  delay(0.0005);
}
  
       delay(1000);
       digitalWrite(8, HIGH); 
        //myGLCD.clrScr();
          start();
        
}


void loop() {
  boolean default_colors = true;
 
start();

}
