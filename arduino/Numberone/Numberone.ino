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
const int capacity = JSON_OBJECT_SIZE(70);
int skip = 0;
const int take = 2;
int userId = 1;
int totalResponse = 0;
int currentReason = 0;
String host = "10.0.0.94";
String reasonsData[take];
String numbersData[take];
String fromData[take];

void setup() {

  delay(1/000);
  lcd.begin(16, 2);
  lcd.clear(); // clear and cursor in upper left corner
  lcd.setCursor(0, 0);
  
  
  // init ports
  pinMode(button, INPUT);
  // initialize serial:
  Serial.begin(115200);
  lcd.setCursor(0, 0);
  lcd.print("Razones por las que");
  lcd.setCursor(0, 1);
  lcd.print("you rock lml");
  inputString.reserve(200);
}

void loop() {

  buttonState = digitalRead(button);
  if (buttonState == HIGH && !inputAction) {
    // Call api
    inputAction = true;
    String json = getRequestJson();
    if(currentReason == 0){
      Serial.println(json);
    }
    else if(currentReason >= totalResponse )
    {
      skip = skip + totalResponse;
      currentReason = 0;
      json = getRequestJson();
      Serial.println(json);
    }
    else
    {
      displayReason(currentReason);
      customDelay(3);
      inputAction = false;
    }
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
        totalResponse = obj["Total"];
        String reasons[totalResponse] PROGMEM;
        for(int a =0; a < totalResponse; a++)
        {
          String currentReason = obj["Data"][a]["Reason"];
          String numberReason = obj["Data"][a]["Number"];
          String fromReason = obj["Data"][a]["FromUserName"];
          reasonsData[a] = currentReason;
          numbersData[a] = numberReason;
          fromData[a] = fromReason;
        }
        if(totalResponse > 0) {
          currentReason = 0;
          displayReason(currentReason);
        }
        else
        {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("No hay mas :/");
          currentReason = 0;
          skip = 0;
        }
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

void displayReason(int reason){
    currentReason++;
    /*Display reason/from*/
    customDelay(1);
    lcd.clear();
    customDelay(1);
    lcd.print("Razon #: "+numbersData[reason]);
    lcd.setCursor(0, 1);
    lcd.print("De: "+fromData[reason]);   
    customDelay(6); 
    /*Display reason*/
    int maxSize = 15;
    int start = 0;
    int finish = start + maxSize;
    do
    {
      lcd.clear();
      customDelay(1);
      lcd.setCursor(0, 0);
      customDelay(1);
      lcd.print(reasonsData[reason].substring(start, finish));

      start = finish;
      finish = start + maxSize;
      
      customDelay(1);
      lcd.setCursor(0, 1);
      lcd.print(reasonsData[reason].substring(start, finish));      
      customDelay(8);
      start = start + maxSize;
      finish = start + maxSize;
      
    }while(start < reasonsData[reason].length());

    start = 0;
    finish = 0;
    maxSize = 0;
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

String getRequestJson()
{
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
    return json;
}

void customDelay(int secs)
{
  int time = secs * 1000;
  for(int x=0;x<time;x++)
  {    
     lcd.setCursor(0, 0);  
  }
}
