
#include <SoftwareSerial.h>

#define DEBUG true


SoftwareSerial esp(3,2); // make RX Arduino line is pin 2, make TX Arduino line is pin 3.
                             // This means that you need to connect the TX line from the esp to the Arduino's pin 2
                             // and the RX line from the esp to the Arduino's pin 3

char lightState;
char fanState;
char alarmState;
char faceState;



void setup()
{
    Serial.begin(9600);

    esp.begin(9600); 
    
    //Serial.print("Ayyy i'm starting over heeere");

    sendData("AT+RST\r\n",2000,DEBUG); // reset module

    pinMode(12, INPUT_PULLUP);


}

void loop()
{
    webCheck();
    sendState();
}

String sendData(String command, const int timeout, boolean debug)
{
    String response = "";
    
    esp.print(command); // send the read character to the esp
    
    long int time = millis();
    
    while( (time+timeout) > millis())
    {
        while(esp.available())
        {
        
            // The esp has data so display its output to the serial window 
            char c = esp.read(); // read the next character.
            response+=c;
        }
    }
    
        int val = response.indexOf('*');

        if (val > 0)
     	{
     		lightState = (response.charAt(val+1));
     		fanState = (response.charAt(val+2));
            alarmState = (response.charAt(val+3));
            faceState = (response.charAt(val+4));

    	}

    	//Serial.print(response);
    	return response;
}



void webCheck()
{
	if(!esp.available()) // check if the esp is sending a message 
    {

        String cipStart = "AT+CIPSTART=\"TCP\",\"172.16.192.59\",80\r\n";
        
        String params = "esp=";
        
        String post = "POST /ESPsmartHouse/ESPsmartHouse.php HTTP/1.1\r\nHost: 172.16.192.59\r\nContent-Type: application/x-www-form-urlencoded\r\nContent-Length: ";
        post += params.length();
        post += "\r\n\r\n";
        post += params;
        post += "\r\n\r\n";
        
        String cipSend = "AT+CIPSEND=";
        cipSend += post.length();
        cipSend += "\r\n";
        
        sendData(cipStart,20,DEBUG);
        sendData(cipSend,20,DEBUG);
        sendData(post,500,DEBUG);

    }
}

void sendState()
{
	String msg = "";

	msg += '*';

	if (lightState == '1' || lightState == '0' )
	{
		msg += lightState;
	}

	else
	{
		msg+='2';  
	}


	if (fanState == '1' || fanState == '0' )
	{
		msg += fanState;
	}

	else
	{
		msg += '2' ;    
	}

    if (alarmState == '1' || alarmState == '0' )
    {
        msg += alarmState;
    }

    else
    {
        msg += '2' ;
    }

    if (faceState == '1' || faceState == '0' )
    {
        msg += faceState;
    }

    else
    {
        msg += '2' ;      
    }

    msg += '@';

	Serial.print(msg);

    while(digitalRead(12)==1);	
}