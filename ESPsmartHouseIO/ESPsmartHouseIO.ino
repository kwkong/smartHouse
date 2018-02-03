#include "Servo.h"


#define nano Serial1

const int fanPin = 9;
const int lightPin = 8;

int val;

int lightState,fanState;





void setup()
{
	Serial.begin(9600);
	nano.begin(115200);

	pinMode(lightPin, OUTPUT);
	pinMode(fanPin, OUTPUT);

	pinMode(12, OUTPUT);
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
	char c;
	int start; 
 
 		while(1)
 		{
			if (nano.available())
	        {  
	            c = nano.read(); // read the next character.

	            if(c == '@')
	            {
	            	digitalWrite(12, LOW);
	            	break;
	            }
				
	            if (c == '*')
	            {
                	start = 1;
	            }

	            if(start == 1)
	            {
	            	msg+=c;
	            }            
	        }  
  	    }

    digitalWrite(12, HIGH);
 	Serial.println(msg);

	val = msg.indexOf('*');

	lightState = (msg.charAt(val+1) - '0');
	fanState = (msg.charAt(val+2) - '0');
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



