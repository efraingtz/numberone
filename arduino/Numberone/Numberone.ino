#include <ArduinoJson.h>

/*
  Serial Event example

  When new serial data arrives, this sketch adds it to a String.
  When a newline is received, the loop prints the string and clears it.

  A good test for this is to try it with a GPS receiver that sends out
  NMEA 0183 sentences.

  NOTE: The serialEvent() feature is not available on the Leonardo, Micro, or
  other ATmega32U4 based boards.

  created 9 May 2011
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/SerialEvent
*/
#include <LiquidCrystal.h> // includes the LiquidCrystal Library 
LiquidCrystal lcd(7,8, 9, 10, 11, 12); // Creates an LC object. Parameters: (rs, enable, d4, d5, d6, d7) 
String inputString = "";
bool stringComplete = false;
const int button =  13;
int buttonState = 0;  
bool inputAction = false;
const int failure = -1;
const int capacity = JSON_OBJECT_SIZE(10);
int skip = 0;
int take = 1;
int userId = 1;
String host = "10.0.0.94";
void setup() {

  delay(1/000);
  lcd.begin(16, 2);
  lcd.clear(); // clear and cursor in upper left corner
  lcd.setCursor(0, 0);
  
  
  // init ports
  pinMode(button, INPUT);
  // initialize serial:
  Serial.begin(115200);
  //delay(500);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
}


//{"skip": "0","take": "8","userid" : "1","host": "10.0.0.94"}

void loop() {

  buttonState = digitalRead(button);
  if (buttonState == HIGH && !inputAction) {
    // Call api
    inputAction = true;
    String json = "{\"skip\": \"";
    json = json + skip;
    json = json + "\"";
    json = json + ",\"take\": \"";
    json = json + take;
    json = json + "\"";
    json = json + ",\"userid\": \"";
    json = json + userId;
    json = json + "\"";
    json = json + ",\"host\": \"";
    json = json + host;
    json = json + "\"";
    json = json + "}";
    Serial.println(json);
  } 
  
  // print the string when a newline arrives:
  if (stringComplete) {
    if(inputString.toInt())
    {
      int x = inputString.toInt();
      if(x == failure)
      {
        
      }
    }
    else 
    {
      //Deserialize response from api
      DynamicJsonBuffer jb(capacity);
      //JsonObject& obj = jb.parseObject("{\"Total\":1,\"Success\":true,\"Message\":\"Data recovered successfully\"}");
      JsonObject& obj = jb.parseObject(inputString);
      if (obj.success()) {
      // parseObject() succeeded
        String from = obj["Data"][0]["FromUserName"];
        String reason = obj["Data"][0]["Reason"];
        String numero = obj["Data"][0]["Number"];
        lcd.clear(); // clear and cursor in upper left corner
        lcd.setCursor(0, 0);
        lcd.print("Reason #"+numero);
        lcd.setCursor(0, 1);
        lcd.print("De: "+from);
        
        for(int x=0;x<500;x++)
        {
            lcd.setCursor(0, 0);
            lcd.print("Reason #"+numero);
            lcd.setCursor(0, 1);
            lcd.print("De: "+from);
            if(x == 499)
            {
              lcd.setCursor(0, 0);
              lcd.print(reason);
            }
        }
        lcd.setCursor(0, 0);
        lcd.print(reason);
      } else {
      // parseObject() failed
        Serial.println(inputString);
      }
    }
    // clear the string:
    inputString = "";
    stringComplete = false;
    inputAction = false;
  }
  //delay(100); 
}

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
