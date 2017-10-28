#include "Arduino.h"
#include "SPI.h"
#include "Servo.h"

#define DATAOUT 11//MOSI
#define DATAIN  12//MISO
#define SPICLOCK  13//sck
#define SLAVESELECT 10//ss

//opcodes
int esc_output_data=0;
uint16_t esc_input_data=0;
uint16_t address=0x2;
int val = 1000;

Servo firstESC;

void setup()
{
    Serial.begin(9600);
    Serial.println(address);
    //Serial.println("started the program");
    firstESC.attach(9);
    SPI.begin();
    SPI.beginTransaction(SPISettings(20000000, MSBFIRST, SPI_MODE0));
    pinMode(DATAOUT, OUTPUT);
    pinMode(DATAIN, INPUT);
    pinMode(SPICLOCK,OUTPUT);
    pinMode(SLAVESELECT,OUTPUT);
    digitalWrite(SLAVESELECT,HIGH); //disable device
    SPI.endTransaction();
    firstESC.writeMicroseconds(0);
}
/*
byte read_esc(int ESC_address)
{
    int data;
    digitalWrite(SLAVESELECT,LOW);
    data = SPI.transfer(ESC_address);
    digitalWrite(SLAVESELECT,HIGH); //release chip, signal end transfer
    delay(10);
    return data;
}
*/
void loop()
{
    val = Serial.read();
    firstESC.writeMicroseconds(val);
    SPI.beginTransaction(SPISettings(20000000, MSBFIRST, SPI_MODE0));
//    Serial.println("made it here");
    digitalWrite(SLAVESELECT,LOW);
    esc_output_data = SPI.transfer(0x0);
    digitalWrite(SLAVESELECT,HIGH);
    Serial.println(esc_output_data);
//    Serial.println("make sense");
    delay(500); //pause for readability
    SPI.endTransaction();
}

