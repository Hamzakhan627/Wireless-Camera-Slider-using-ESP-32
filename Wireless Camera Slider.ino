const int potPin = 27;
int potstate=0;
int previousState = 0;
int speede;
int limitbtnR=32;
int limitbtnL=33;
int pinR;
int pinL;
#include <Stepper.h>
#define STEPS 200
Stepper stepper1(STEPS, 19,18);
Stepper stepper2(STEPS, 2,4);
const int joypin1=12;
const int joypin2=13;
int joystate1=1850;
int joystate2=1850;
#include <U8x8lib.h>
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
U8X8_SH1106_128X64_NONAME_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE);

void setup()
{    
  Serial.begin(9600);
  u8x8.begin();
  u8x8.setPowerSave(0);
  u8x8.setFont(u8x8_font_chroma48medium8_r);
  u8x8.draw2x2String(0,3,"WELCOME");
  delay(1000);
  u8x8.clearDisplay();
  u8x8.drawString(0,2,"Speed:");
}

void loop()
{
    
    Serial.println(analogRead(joypin2));
    
    pinR=analogRead(limitbtnR);
    pinL=analogRead(limitbtnL);
    joystate1=analogRead(joypin1);
    
    stepper1.setSpeed(pot());// Horizontal Stepper
    if (joystate1>2200 && pinR==4095){
    stepper1.step(10);
    }
    if (joystate1<1600 && pinL==4095){
    stepper1.step(-10);
    }
    joystate2=analogRead(joypin2);
    stepper2.setSpeed(100); // Pan Stepper
    if (joystate2>2200){
    stepper2.step(10);
    }
    if (joystate2<1600){
    stepper2.step(-10);
    }

    if(speede != previousState){
    previousState = speede;
    u8x8.setFont(u8x8_font_chroma48medium8_r);
    u8x8.clearDisplay();
    u8x8.drawString(0,2,"Speed:");
    u8x8.setCursor(2,4);
    u8x8.print(previousState);
    }
    
}

int pot(){
  potstate=analogRead(potPin);
  if (potstate<=500)
  speede=10;
  else if (potstate>500&&potstate<=1000)
  speede=20;
  else if (potstate>1000&&potstate<=1500)
  speede=30;
  else if (potstate>1500&&potstate<=2000)
  speede=40;
  else if (potstate>2000&&potstate<=2500)
  speede=50;
  else if (potstate>2500&&potstate<=3000)
  speede=60;
  else if (potstate>3000&&potstate<3500)
  speede=70;
  else if (potstate>3500&&potstate<=4100)
  speede=80;

  return speede;
  
}
