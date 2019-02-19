#include<ESP8266WiFi.h>
#include<WiFiClient.h>
#include<ESP8266WebServer.h>

//SSID and password of 8266 wifi
const char* ssid = "ESP WiFi";
const char* password = "connecttooperate";

WiFiServer server(1337); //server on port 1337

//Pin Configrations
const int motor1Pin1 = D0;
const int motor1Pin2 = D1;
const int enable1 = D4;
const int motor2Pin1 = D2;
const int motor2Pin2 = D3;
const int enable2 = D5;
String lef = "";
String rig = "";
int left  = 0;
int right = 0;
void doit(String command);
void setup() {
  // put your setup code here, to run once:
    delay(1000);    
    Serial.begin(115200);
    Serial.println();
    Serial.print("Configuring access point...");
    WiFi.softAP(ssid, password);
    IPAddress myIP = WiFi.softAPIP();
    Serial.print(myIP);
    server.begin();
    Serial.println("TCP server started");
    pinMode(motor1Pin1, OUTPUT);
    pinMode(motor1Pin2, OUTPUT);
    pinMode(enable1, OUTPUT); 
    pinMode(motor2Pin1, OUTPUT); 
    pinMode(motor2Pin2, OUTPUT); 
    pinMode(enable2, OUTPUT); 

}

void loop() {
  WiFiClient client = server.available();
  if(client) {
    Serial.println("Client Connected.");

    while(client.connected()) {
      if(client.available()) {
        String command = client.readStringUntil('z');
        Serial.println(command);
        doit(command);
      }
    }
  } else {
    client.stop();
  }
}

void doit(String command){
  if ((command.substring(0,1)).compareTo("f")){
    lef = command.substring(1,5);
    rig = command.substring(5,10);
    
    digitalWrite(motor1Pin1, HIGH);
    digitalWrite(motor1Pin2, LOW); 
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, HIGH);
    analogWrite(enable1,lef.toInt());
    analogWrite(enable2,rig.toInt()); 
    }
  else if ((command.substring(0,1)).compareTo("r")){
    lef = command.substring(1,5);
    rig = command.substring(5,10);
   
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH); 
    digitalWrite(motor2Pin1, HIGH);
    digitalWrite(motor2Pin2, LOW);
    analogWrite(enable1,lef.toInt());
    analogWrite(enable2,rig.toInt());
    }
  else{
    lef = command.substring(0,4);
    rig = command.substring(4,9);
   
    digitalWrite(motor1Pin1, HIGH);
    digitalWrite(motor1Pin2, LOW);
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, HIGH);
    analogWrite(enable1,lef.toInt());
    analogWrite(enable2,rig.toInt());
      
      }
      
    Serial.println("Left = " + lef + " Right =" + rig);
   
  
  }
