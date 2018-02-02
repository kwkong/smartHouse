#include "Servo.h"


#define nano Serial3

const int fanPin = 9;
const int lightPin = 8;

int val;

char lightState,fanState;




void setup()
{
	Serial.begin(9600);
	nano.begin(9600);

	pinMode(lightPin, OUTPUT);
	pinMode(fanPin, OUTPUT);
	pinMode(13, OUTPUT);


}

void loop()
{
	getState();
	writeState();
}

void getState()
{
	String msg="";
	int leave;

	Serial.println("Entering first while");

	//while (leave != 1)
	//{
        if (nano.available())
        {  
            char c = nano.read(); // read the next character.
            msg+=c;
            Serial.println(msg);

            if(msg == '@')
            {
            	leave = 1;

            	Serial.println("leaving");
            }
        }
    //}    

	val = msg.indexOf('*');

    if (val > 0)
 	{
 		lightState = (msg.charAt(val+1));
 		fanState = (msg.charAt(val+2));
	}
}

void writeState()
{
	if (lightState == 1 || lightState == 0)
	{
		digitalWrite(lightPin, lightState);
		digitalWrite(13, lightState);
	}
	
	if (fanState == 1 || fanState == 0)
	{
		digitalWrite(fanPin, fanState);
	}
}



