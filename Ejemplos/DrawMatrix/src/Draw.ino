/***************************************************
  This is a library for our I2C LED Backpacks

  Designed specifically to work with the Adafruit LED Matrix backpacks
  ----> http://www.adafruit.com/products/872
  ----> http://www.adafruit.com/products/871
  ----> http://www.adafruit.com/products/870

  These displays use I2C to communicate, 2 pins are required to
  interface. There are multiple selectable I2C addresses. For backpacks
  with 2 Address Select pins: 0x70, 0x71, 0x72 or 0x73. For backpacks
  with 3 Address Select pins: 0x70 thru 0x77

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h>
#include <Adafruit_GFX.h>
// #include <Adafruit_LEDBackpack.h>


#define SW5 990
#define SW4 678
#define SW3 442
#define SW2 192
#define SW1 0

#ifndef _BV
  #define _BV(bit) (1<<(bit))
#endif


Adafruit_LEDBackpack matrix = Adafruit_LEDBackpack();

void setup() {
  Serial.begin(9600);
  matrix.begin(0x70);  // pass in the address
  pinMode(LED_BUILTIN,OUTPUT);
}

void pixel(int i,int j, bool color,bool refresh){
  if(color)
    matrix.displaybuffer[i]|=_BV(j);
  else
    matrix.displaybuffer[i]&=255-_BV(j);
  if(refresh)
    matrix.writeDisplay();
}

void randomPixel(){
  pixel(random(0,8),random(0,8),random(0,2),true);
}

int x=3,y=3;
bool pinta=false;
void leeTecla(){
  int iADKey_value=analogRead(A0);
  String sValue;
  switch(iADKey_value){
    case SW5+4:
    case SW5+1:
    case SW5:
          sValue="SW5";
          pinta=!pinta;
          digitalWrite(LED_BUILTIN,!pinta);
          delay(50);
          break;
    case SW4:
          sValue="SW4";
          x++;
          break;
    case SW3-1:
    case SW3:
    case SW3+1:
          sValue="SW3";
          y++;
          break;
    case SW2:
          sValue="SW2";
          y--;
          break;
    case SW1:
          sValue="SW1";
          x--;
          break;
    default:
      sValue=String(iADKey_value);
      break;
  }
  if(iADKey_value!=1024)
      Serial.println(sValue);
  if(x<0) x=7;
  if(y<0) y=7;
  if(x>7) x=0;
  if(y>7) y=0;
}

void loop() {



  if(!pinta)
    pixel(x,y,false,false);
  leeTecla();
  pixel(x,y,true,true);


  delay(80);
}
