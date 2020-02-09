#include <LiquidCrystal.h> // includes the LiquidCrystal Library 
LiquidCrystal lcd(A5, A4, A3, A2, A1, A0); // Creates an LC object. Parameters: (rs, enable, d4, d5, d6, d7) 
String inputString = "";
bool stringComplete = false;                                                                                                                 
int btnsIn[] = {4,4,4,4};
int buttonState = 0;  
bool inputAction = false;
bool point = false;
int btnouts[] = {5,7,9,11};
int buzzer = 13;
int btnReason = 12;
String reason;
String reasonNumber;
String reasonFrom;
int readCase = 0;
unsigned long previousMillis = 0;        // will store last time LED was updated
int currentLed = 0;
// constants won't change:
long interval = 1000; 
bool pause = false;
int buttonsSize = 4;

void setup() {

  delay(1/000);
  lcd.begin(16, 2);
  lcd.clear(); // clear and cursor in upper left corner
  lcd.setCursor(0, 0);
  
  
  // init ports
  pinMode(buzzer, OUTPUT);
  pinMode(btnReason, OUTPUT);
  digitalWrite(btnReason, LOW);

  for(int x = 0; x < buttonsSize; x++)
  {
    pinMode(btnouts[x], OUTPUT);
    pinMode(btnsIn[x], INPUT);
  }
  
  // initialize serial:
  Serial.begin(115200);
  lcd.setCursor(0, 0);
  lcd.print("Hola Mundo");
  lcd.setCursor(0, 1);
  for(int a=0;a<5;a++)
  {
    lcd.setCursor(a, 1);
    lcd.print(".");
    customDelay(2);
  }
  inputString.reserve(200);
}

void loop() {

  unsigned long currentMillis = millis();
  if(!pause){
    if (currentMillis - previousMillis >= interval) {
      for(int x = 0; x < buttonsSize; x++)
      {
        digitalWrite(btnouts[x], HIGH);
      }
      // save the last time you blinked the LED
      previousMillis = currentMillis;
      interval = random(200, 1000);
      int a = random(0, buttonsSize );
      while(a == currentLed)
      {
         a = random(0, buttonsSize);
      }
      digitalWrite(btnouts[a], LOW);
      currentLed = a;
    }
  
     int states[] = 
     {
        digitalRead(btnsIn[0]),
        digitalRead(btnsIn[1]),
        digitalRead(btnsIn[2]),
        digitalRead(btnsIn[3])
      };
      
    for(int x = 0; x < buttonsSize; x++)
    {
      if(states[x] == HIGH && x == currentLed && !inputAction)
      {
           pause = true;
           handleDisplayReason();
           break;
      } 
      else if (states[x] == HIGH && !inputAction)
      {
          inputAction = true;
          lcd.clear();
          customDelay(1);
          lcd.setCursor(0, 0);
          lcd.print("X_____x");
          digitalWrite(buzzer, HIGH);
          customDelay(2);
          digitalWrite(buzzer, LOW);
          customDelay(7);
          lcd.clear();
          inputAction = false;
          break;
      }
    }
  }
}

void handleDisplayReason()
{
  inputAction = true;
  Serial.println("1");
}

void displayReason(){
    /*Display reason/from*/
    customDelay(1);
    lcd.clear();
    customDelay(1);
    lcd.setCursor(0, 0);
    customDelay(1);
    String rN = reasonNumber.substring(0, reasonNumber.length()-1);
    lcd.print("Razon #: "+rN);
    customDelay(4); 
    lcd.setCursor(0, 1);
    String rF = reasonFrom.substring(0, reasonFrom.length()-1);
    lcd.print("De: "+rF);   
    customDelay(4); 
    int maxSize = 15;
    int start = 0;
    int tempMax = start + maxSize;
    int finish = tempMax > reason.length() ? reason.length()-1 : tempMax;
    do
    {
      lcd.clear();
      customDelay(1);
      lcd.setCursor(0, 0);
      customDelay(1);
      lcd.print(reason.substring(start, finish));

      start = finish;
      tempMax = start + maxSize;
      finish = tempMax > reason.length() ? reason.length()-1 : tempMax;
     
      customDelay(1);
      if(start < reason.length()-1){
        lcd.setCursor(0, 1);
        lcd.print(reason.substring(start, finish));      
        start = start + maxSize;
        tempMax = start + maxSize;
        finish = tempMax > reason.length() ? reason.length()-1 : tempMax; 
      }
      else
      {
        start++;
      }
      customDelay(8);
    }while(start < reason.length());

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
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
        bool fail = false;
        if(inputString.toInt())
        {
          int x = inputString.toInt();
          if(x == -1)
          {
            lcd.clear();
            customDelay(1);
            lcd.setCursor(0, 0);
            lcd.print("ERROR HTTP");
            customDelay(5);
            lcd.clear();
            inputAction = false;
            inputString = "";
            fail = true;
          } 
          else if(x == -2)
          {
            lcd.clear();
            customDelay(1);
            lcd.setCursor(0, 0);
            lcd.print("NO HAY MAS...");
            customDelay(5);
            lcd.clear();
            inputAction = false;
            pause = false;
            fail = true;
          }
          else if(x == -3)
          {
            lcd.clear();
            customDelay(1);
            lcd.print("ERROR DATOS");
            customDelay(5);
            lcd.clear();
            inputAction = false;
            pause = false;
            fail = true;
          }
          else if(x == -4)
          {
            lcd.clear();
            customDelay(1);
            lcd.print("ERROR WIFI");
            customDelay(5);
            lcd.clear();
            inputAction = false;
            pause = false;
            fail = true;
          }
        }
      if(!fail)
      {
        switch(readCase)
        {
          case 0:
            customDelay(3);
            reason = inputString;
            readCase++;
          break;
          case 1:
            reasonNumber = inputString;
            customDelay(3);
            readCase++;
          break;
          case 2:
            reasonFrom = inputString;
            displayReason();
            inputAction = false;
            pause = false;
            readCase = 0;
          break;
        }    
      }
      else
      {
        readCase = 0;
      }
      inputString = "";
      stringComplete = true;
    }
    else {
      inputString += inChar;
    }
  }
}

String getRequestJson()
{
    String json = "1";
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
