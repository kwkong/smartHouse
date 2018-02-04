// #include "Servo.h"
// #include "NeoSWSerial.h"


#define nano Serial2

const int fanPin = 9;
const int lightPin = 13;
const int pirPin = 7;
const int buzzerPin= 6;

int val;
int lightState;
int fanState;
int alarmState;
int ecoState;
int timerState;
int pirState;

unsigned long timer;




void setup()
{
	Serial.begin(9600);
	nano.begin(9600);

	pinMode(lightPin, OUTPUT);
	pinMode(fanPin, OUTPUT);
	pinMode(buzzerPin, OUTPUT);

	pinMode(12, OUTPUT);
	pinMode(13, OUTPUT);

}


void loop()
{
	getState();
	writeState();
	ecoMode();
	alarm();
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
	alarmState = (msg.charAt(val+3) - '0');
	ecoState = (msg.charAt(val+4) - '0');
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

void alarm()
{
	if (alarmState == 1 || alarmState == 0)
	{
		if (alarmState == 1)
		{
			fastBeep();
		}

		else
		{
			digitalWrite(buzzerPin, LOW);
		}
	}
}

void ecoMode()
{
	if (ecoState == 1)
	{
		lightTimer();
	}
}

void lightTimer()
{
	pirState = digitalRead(pirPin);

	if (pirState == 0)
	{	
		if (timerState == 0)
		{
			timer = millis();
			timerState = 1;
			//lightStateOld = lightState;
		}

		if (timerState == 1)
		{
			if ((millis()-timer) >= 5000)
			{
				digitalWrite(lightPin, LOW);
				lightState = 0;
				timerState = 0;
			}
		}
	}

	else
	{
		timer = millis();
		digitalWrite(lightPin, lightState);
	}
}

void fastBeep()
{
	digitalWrite(buzzerPin, HIGH);
    delay(50);
    digitalWrite(buzzerPin, LOW);
}


