#include <Arduino.h>

#define SW5 1016
#define SW4 697
#define SW3 455
#define SW2 203
#define SW1 3

void setup(){
  pinMode(LED_BUILTIN,OUTPUT);
  Serial.begin(9600);
}

void loop(){
  digitalWrite(LED_BUILTIN,HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN,LOW);
  delay(100);

  int iADKey_value=analogRead(A0);
  String sValue;
  switch(iADKey_value){
    case SW5:
          sValue="SW5";
          break;
    case SW4:
          sValue="SW4";
          break;
    case SW3:
          sValue="SW3";
          break;
    case SW2:
          sValue="SW2";
          break;
    case SW1:
          sValue="SW1";
          break;
    default:
      sValue=String(iADKey_value);
      break;
  }
  Serial.println(sValue);
}
