
#include <Arduino.h>

String command1 = "";
String command2 = "";

void dumpSerial3() {

  if (Serial3.available()>0) { 
    while(Serial3.available()>0) {
      command1 += (char)Serial1.read();
      delay(10);
    }
    Serial.print(command1);
    command1 = ""; 
  }
//  Serial.println();
}

void setup() {
  Serial3.begin(9600); 
  Serial.begin(115200);
/*  delay(1000);
//  Serial1.println("AT+VERSION");
  Serial1.print("AT+VERSION");
  delay(1000);
  dumpSerial1();
  delay(1000);
//  Serial1.println("AT+ADDR");
  Serial1.print("AT+ADDR?");
  delay(1000);
  dumpSerial1();
  delay(1000);
//  Serial1.print("AT+NAMEPapillonBT");
  Serial1.println("AT+NAME=PapillonBT2");
  delay(1000);
  dumpSerial1();
  delay(1000);
//  Serial1.print("AT+PIN0000");
  Serial1.println("AT+PSWD=0000");
  delay(1000);
  dumpSerial1();
  delay(1000);
//  Serial1.print("AT+BAUD6");
  Serial1.println("AT+UART=38400,1,0");
  delay(1000);
  dumpSerial1();
*/
  delay(1000);
  Serial.println("Setup OK");
}

void loop() {

  if (Serial3.available()>0) { 
    while(Serial3.available()>0) {
      command1 += (char)Serial3.read();
      delay(10);
    }
    Serial.print(command1);
    command1 = ""; 
  }
  
  if (Serial.available()>0) { 
    while(Serial.available()>0) {
      command2 += (char)Serial.read();
      delay(10);
    }
    Serial3.print(command2);
    command2 = ""; 
  }

}