// DRA818V_3

// set parameters for DRA818V/u                                                                                                                                                               
#include <SoftwareSerial.h>

const byte V_PTT = A2;
const byte V_SQ = A0;
const byte U_SQ = A1;
const byte U_PTT = A3;
const byte U_TX = 2;
const byte U_RX = 10;
const byte PD = 3;
const byte HL = A6;
int bw = 1; // bandwidth in KHz ( 0= 12.5KHz or 1= 25KHz )

float u_ftx = 432.6000; // tx frequency in MHz (134.0000 - 174.0000)
float u_frx = 432.6000; // rx frequency in MHz (134.0000 - 174.0000)
String u_tx_ctcss = "0000"; // ctcss frequency ( 0000 - 0038 ); 0000 = "no CTCSS" 
String u_rx_ctcss = "1000"; // ctcss frequency ( 0000 - 0038 ); 0000 = "no CTCSS" 
int u_squ = 3; // squelch level ( 0 - 8 ); 0 = "open" 
// Adjusted squelch and ctcss

float v_ftx = 145.7000; // tx frequency in MHz (134.0000 - 174.0000)
float v_frx = 145.7000; // rx frequency in MHz (134.0000 - 174.0000)
String v_tx_ctcss = "0000"; // ctcss frequency ( 0000 - 0038 ); 0000 = "no CTCSS" 
String v_rx_ctcss = "0000"; // ctcss frequency ( 0000 - 0038 ); 0000 = "no CTCSS" 
int v_squ = 0; // squelch level ( 0 - 8 ); 0 = "open" 

SoftwareSerial uSerial(U_RX, U_TX); // RX, TX

void setup()
{
  
  Serial.begin(9600);

  Serial.print("AT+DMOSETGROUP="); // begin message
  Serial.print(bw,1);
  Serial.print(",");
  Serial.print(v_ftx,4);
  Serial.print(",");
  Serial.print(v_frx,4);
  Serial.print(",");
  Serial.print(v_tx_ctcss);
  Serial.print(",");
  Serial.print(v_squ);
  Serial.print(",");
  Serial.println(v_rx_ctcss);

  uSerial.begin(9600);

  uSerial.print("AT+DMOSETGROUP="); // begin message
  uSerial.print(bw,1);
  uSerial.print(",");
  uSerial.print(u_ftx,4);
  uSerial.print(",");
  uSerial.print(u_frx,4);
  uSerial.print(",");
  uSerial.print(u_tx_ctcss);
  uSerial.print(",");
  uSerial.print(u_squ);
  uSerial.print(",");
  uSerial.println(u_rx_ctcss);

  pinMode(V_PTT, OUTPUT);
  pinMode(V_SQ, INPUT);
  pinMode(U_PTT, OUTPUT);
  pinMode(U_SQ, INPUT);
  pinMode(PD, OUTPUT);
  pinMode(HL, OUTPUT);

  digitalWrite(V_PTT, HIGH);
  digitalWrite(U_PTT, HIGH);
  digitalWrite(PD, LOW);
  //digitalWrite(HL, LOW); //don't enable this yet, as we may need the higher power
}

void loop()
{
 if (digitalRead(U_SQ) == HIGH){ //if we get a high enough squelch
  digitalWrite(PD,HIGH); //get out of sleep mode
  digitalWrite(V_PTT,LOW); //turn ptt on
  delay(100);
 }
  if (digitalRead(U_SQ) == LOW){ 
  digitalWrite(PD,LOW);
  digitalWrite(V_PTT,HIGH);
  delay(100);
 }
 }
}
