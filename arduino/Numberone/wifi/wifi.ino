#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>   // Incluimos la librería  SoftwareSerial  

SoftwareSerial BT(13,15);    // Definimos los pines RX y TX del Arduino conectados al Bluetooth
String baseApi = "numberoneapi/Reasons/";
const int failure = -1;
String host = "numberzero.com.mx";
int skip = 0;
int take = 1;
int userToId = 1;
int totalResponse = 0;
int currentReason = 0;
const size_t bufferSize = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(4) + 780;
String ssid = "";
String password = "";
DynamicJsonBuffer jsonBuffer(bufferSize);
bool inputAction = false;
String inputString = "";
bool stringComplete = false;
int epromCounter = 1;
bool isAvailable = true;
//A5d8n9V2y3z7

void setup()
{
  Serial.begin(115200);
  BT.begin(115200); 
  EEPROM.begin(512); //Max bytes of eeprom to use
  epromCounter=1;
  readWifi();
  setupNetwork();
  inputString.reserve(200);
}

void saveWifi(String val)
{
  for(int i= 0; i<val.length(); i++){
    EEPROM.write(epromCounter, val[i]);
    epromCounter++;
  }
  EEPROM.write(0, epromCounter);
  int z = EEPROM.read(0);
}

void readWifi()
{
  String full = "";
  int split = 0;
  char especial = '/';
  int fullSize = EEPROM.read(0);
  for(int x =0; x< fullSize ; x++){
    byte z = EEPROM.read(x);
    char a = char(z); // Converts the byte value back to a character
    if(a == especial)
    {
        split = x;
    }
    else
    {
      full+=a;
    }
  }
    int stringSize = full.length();
    ssid = full.substring(0, split);
    password = full.substring(split, stringSize);
}

void setupNetwork(){
  WiFi.mode(WIFI_STA);
  connectWifi();
}

void connectWifi()
{      
  int ssidSize = ssid.length();
  int passSize = password.length();
  char _ssid[ssidSize];
  char _pass[passSize];
  ssid.toCharArray(_ssid, ssidSize);
  password.toCharArray(_pass, passSize);
              
  WiFi.begin(_ssid, _pass);  
  int take = 10;
  int count = 0;
  while (WiFi.status() != WL_CONNECTED && count < take)
  {
    delay(500);
    count++;
  }
}

void getReasons(){
   if (WiFi.status() == WL_CONNECTED) 
   {
      HTTPClient http;  //Declare an object of class HTTPClient
      http.begin("http://"+host+"/"+baseApi+"GetDashboard?take="+take+"&skip="+skip+"&usertoid="+userToId);  
      int httpCode = http.GET();                                                                  //Send the request
      if (httpCode > 0) 
      { 
          String payload = http.getString();   
          JsonObject& obj = jsonBuffer.parseObject(payload);
          if (obj.success()) 
          {
            totalResponse = obj["Total"];
            int a =0;
            if(totalResponse > 0) {
              skip++;
              String currentReason = obj["Data"][a]["Reason"];
              String numberReason = obj["Data"][a]["Number"];
              String fromReason = obj["Data"][a]["FromUserName"];
              Serial.println(currentReason);                     //Print the response payload
              delay(100);
              Serial.println(numberReason);                     //Print the response payload
              delay(100);
              Serial.println(fromReason);                     //Print the response payload
              delay(1000);
            }
            else
            {
              skip = 0;
              errorResponse(-2);    
            }
          }
          else
          {
              errorResponse(-3);    
          }
          http.end();
    }
    else
    {
       errorResponse(-1);    
    }
  }
  else
  {
      errorResponse(-4);    
  }
  isAvailable = true;
}

void loop() {
  if (Serial.available() > 0) 
   {
      // read the incoming byte:
      String inputString = Serial.readString();
      if(inputString.substring(0,1) == "1")
      {
        if(WiFi.status() == WL_CONNECTED)
         {
          getReasons();
         }
         else
         {      
          errorResponse(-4);    
          connectWifi();
         }
      }
   }
   if(BT.available() > 0)
   {
        String btInputString = BT.readString();
        int stringSize = btInputString.length();
        String intro = btInputString.substring(0,4);
        char _wifi[stringSize];
        char _pass[stringSize];
        if(intro == "WIFI")
        {
          ssid = btInputString.substring(4);
          saveWifi(ssid+"/");
          connectWifi();
        }
        if(intro == "PASS")
        {
          password = btInputString.substring(4);
          saveWifi(password);
          connectWifi();
          epromCounter = 1;
        }
   }
}

void errorResponse(int error)
{
   Serial.println(error);
}
