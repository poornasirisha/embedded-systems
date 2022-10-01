//I2C Master Code (STM32F103C8)
//I2C Communication between STM32 and Arduino
#include<stdio.h>
#include<Wire.h>                      
#include<SoftWire.h>                   //Library for I2C Communication functions
#define LED PA1
#define buttonpin PA0
int x = 0;
void setup()
{ 
	Serial.begin(9600);                  //Begins Serial Communication at 9600 baud rate
	pinMode(buttonpin,INPUT);            //Sets pin PA0 as input 
	pinMode(LED,OUTPUT);                 //Sets PA1 as Output
	Wire.begin();                        //Begins I2C communication at pin (B6,B7)
}
void loop()
{ 
	Wire.requestFrom(8,1);               // request  bytes from slave arduino(8)
	byte a = Wire.read();                // receive a byte from the slave arduino and store in variable a
	if (a==1)                            //Logic to turn Master LED ON (if received value is 1) or OFF (if received value is 0)
	{ 
		digitalWrite(LED,HIGH);
		Serial.println("Master LED ON");
	}
	else
	{
	digitalWrite(LED,LOW);
	Serial.println("Master LED OFF");
	}
{
	int pinvalue = digitalRead(buttonpin);    //Reads the status of the pin PA0
	if(pinvalue==HIGH)                         //Logic for Setting x value (To be sent to slave Arduino) depending upon inuput from pin PA0
	{
	x=1;
	}
	else
	{
	x=0;
	}
	Wire.beginTransmission(8);                 // starts transmit to device (8-Slave Arduino Address)
	Wire.write(x);                             // sends the value x to Slave
	Wire.endTransmission();                    // stop transmitting
	delay(500);
	}
}     

Slave Arduino Code
//I2C Slave Code (Arduino)
//I2C Communication between STM32 and Arduino
#include<Wire.h>                             //Library for I2C Communication functions
byte x =0;
void setup() 
{
	Serial.begin(9600);                        //Begins Serial Communication at 9600 baud rate
	pinMode(LED,OUTPUT);                       //Sets pin 7 as output
	Wire.begin(8);                             // join i2c bus with its slave Address as 8 at pin (A4,A5)
	Wire.onReceive(receiveEvent);              //Function call when Slave Arduino receives value from master STM32
	Wire.onRequest(requestEvent);              //Function call when Master STM32 request value from Slave Arduino
}
void loop() 
{
	delay(100);
}
void receiveEvent (int howMany)              //This Function is called when Slave Arduino receives value from master STM32
{
	byte a = Wire.read();                      //Used to read value received from master STM32 and store in variable a
	if (a == 1)                                //Logic to turn Slave LED ON (if received value is 1) or OFF (if received value is 0)
	{
		digitalWrite(LED,HIGH);
		Serial.println("Slave LED ON");
	}
	else
	{
		digitalWrite(LED,LOW);
		Serial.println("Slave LED OFF");
	}
	delay(500);
}
void requestEvent()                            //This Function is called when Master STM32 wants value from slave Arduino
{
	int value = digitalRead(buttonpin);          //Reads the status of the pin 2   
	if (value == HIGH)                           //Logic to set the value of x to send to master depending upon input at pin 2
	{
	x=1;
	}
	else 
	{
	x=0;
	}
	Wire.write(x);                             // sends one byte of x value to master STM32
}
}
