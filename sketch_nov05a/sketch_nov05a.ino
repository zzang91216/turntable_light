#include <Wire.h>
#include <Adafruit_TCS34725.h>
int Rp = 9;
int Gp = 11;
int Bp = 10;
int mp = 40;
int Mp = 6;

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void setup(){
Serial.begin(9600); 
if (tcs.begin()) {
  Serial.println("Found sensor"); 
  } else { 
    Serial.println("No TCS34725 found ... check your connections"); 
    while(1);
}
pinMode(A0, INPUT);
pinMode(Rp, OUTPUT);
pinMode(Bp, OUTPUT);
pinMode(Mp, OUTPUT);
pinMode(Gp, OUTPUT);
}

void loop(){
uint16_t clear, rd, gr, bl;
tcs.getRawData(&rd, &gr, &bl, &clear);
int r = map(rd, 0, 21504, 0, 1000); 
int g = map(gr, 0, 21504, 0, 1700); 
int b = map(bl, 0, 21504, 0, 2500);

int rs = analogRead(A0);
int m = map(rs,  0, 1023, 40, 180);
if(m != mp){mp += 4*(m - mp)/abs(m - mp);}

r = min(max(0, 2.5*r-40),255);
g = min(max(0, 2.5*g-40),255);
b = min(max(0, 2.5*b-40),255);

Serial.print("\tm:\t"); Serial.print(rs); 
Serial.print("\tR:\t"); Serial.print(r); 
Serial.print("\tG:\t"); Serial.print(g);
Serial.print("\tB:\t"); Serial.println(b); 
analogWrite(Mp, mp);
analogWrite(Rp, r);
analogWrite(Gp, g);
analogWrite(Bp, b);

}
