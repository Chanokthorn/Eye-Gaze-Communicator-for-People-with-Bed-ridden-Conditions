#include <MicroGear.h>
#include <ESP8266WiFi.h>

const char* ssid     = "zenf2";
const char* password = "qwertyuiop0";

#define APPID   "Helloworld01"
#define KEY     "NrA9ojvhmZWHz99"
#define SECRET  "X42UD7kLIGX52yVtnNpM2NOOK"

#define ALIAS   "NodeMCU1"
#define TargetWeb "DigitalOUTPUT_HTML_web"

///////////////////Define Pin/////////////////////
static const uint8_t D0   = 16;
static const uint8_t D1   = 5;
static const uint8_t D2   = 4;
static const uint8_t D3   = 0;
static const uint8_t D4   = 2;
static const uint8_t D5   = 14;
static const uint8_t D6   = 12;
static const uint8_t D7   = 13;
static const uint8_t D8   = 15;
static const uint8_t D9   = 3;
static const uint8_t D10  = 1;

#define alertPin D4
uint8_t isAlertStop = 0;
//////////////////////////////////////////////////

WiFiClient client;
MicroGear microgear(client);

void onMsghandler(char *topic, uint8_t* msg, unsigned int msglen) 
{
  Serial.print("Incoming message --> ");
  Serial.print(topic);
  Serial.print(" : ");
  char strState[msglen];
  for (int i = 0; i < msglen; i++) 
  {
    strState[i] = (char)msg[i];
    Serial.print((char)msg[i]);
  }
  Serial.println();

  String stateStr = String(strState).substring(0, msglen);

  //////////////////////////////////////////////////
  if (stateStr == "html_StopAlert")
  {
    microgear.chat(TargetWeb,"nodeMCU_StopAlert");
    isAlertStop = 1;
  }
  //////////////////////////////////////////////////
}

void onConnected(char *attribute, uint8_t* msg, unsigned int msglen) 
{
  Serial.println("Connected to NETPIE...");
  microgear.setAlias(ALIAS);
}

void setup() 
{
    /* Event listener */
    microgear.on(MESSAGE,onMsghandler);
    microgear.on(CONNECTED,onConnected);

    Serial.begin(115200);
    Serial.println("Starting...");

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) 
    {
       delay(250);
       Serial.print(".");
    }

    Serial.println("WiFi connected");  
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    microgear.init(KEY,SECRET,ALIAS);
    microgear.connect(APPID);

    //////////////////////////////////////////////////
    pinMode(alertPin,INPUT);
    //////////////////////////////////////////////////
}

void loop() 
{
  if(microgear.connected()) 
  {
    microgear.loop();
    
    Serial.print("connect... ");

    //////////////////////////////////////////////////
    int alertStatus = digitalRead(alertPin);
    Serial.println(String(alertStatus)+String(isAlertStop));
    if(alertStatus == LOW)
    {
      if(isAlertStop != 1)microgear.chat(TargetWeb,"nodeMCU_alertON");
    }
    else
    {
      // **** on alert signal > set 'isAlertStop' back to default ****
      isAlertStop = 0;
      microgear.chat(TargetWeb,"nodeMCU_StopAlert");
    }
    //////////////////////////////////////////////////
  } 
  else 
  {
    Serial.println("connection lost, reconnect...");
    microgear.connect(APPID);
  }
  delay(250);
}


