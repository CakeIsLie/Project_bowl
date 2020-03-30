#include <Servo.h> //need it to make my servo work
#include <SoftwareSerial.h>
#include "WiFiEsp.h"
#include "SoftwareSerial.h"
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>

//SQL stuff
char ssid[] = "COMHEM_f38715"; //Wi-Fi name
char pass[] = "idzknut"; //Wi-Fi password
int status = WL_IDLE_STATUS;
WiFiEspServer server(80);
WiFiEspClient client;
MySQL_Connection conn((Client *)&client);
IPAddress server_addr(192,168,0,12); //my IP adress
char user[] = "kurs1234"; // MySQL user
char password[] = "kurs1234"; // MySQL password

Servo myservo; //create servo object
int pos = 0; //variable to store the servo position

int const trigPin = 13; //choose the trig pin
int const echoPin = 12; //choose the echo pin
int const buzzPin = 10; //choose the buzzer pin
//Duration will be the input pulse width and distance will be the distance to the obstacle in centimeters
int duration; 
int distance;

int inputPin = 2; //choose the input pin (for PIR sensor)
int pirState = LOW; //we start thinking no motion detected
int val = 0; //variable for reading the pin status

SoftwareSerial SerialWifi(9, 8); // TX, RX
int Movment = 0; //counting how many times PIR sensor have gone off
int tooClose = 0; //counting how many times ultrasonic sensor have gone off
unsigned long updateInterval = 60000; 
unsigned long timeNow = 0;

void setup()
{
  //Wi-Fi module stuff
    Serial.begin(115200); //have to be on 115200 to see if it conected
  SerialWifi.begin(9600);
  WiFi.init(&SerialWifi);
  
  Serial.println(F("Initialising connection"));
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    while (true);
  }
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);

// Print your WiFi shield's IP address
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

    while (conn.connect(server_addr, 3306, user, password) != true)  //waiting on a conection to MySQL-server
  {
    delay(200);
    Serial.print ( "." );
  }

  Serial.println("");
  Serial.println("Connected to SQL Server!"); 
    server.begin();
  }
pinMode(3, OUTPUT); //RGB LED green
pinMode(4, OUTPUT); //RGB LED red
pinMode(5, OUTPUT); //RGB LED blue
pinMode(trigPin, OUTPUT); //trig pin will have pulses output
pinMode(echoPin, INPUT); //echo pin should be input to get pulse width
pinMode(buzzPin, OUTPUT); //buzz pin is output to control buzzering
pinMode(inputPin, INPUT); //declare sensor as input
myservo.attach(11);  //attaches the servo on pin 11 to the servo object
Serial.begin(9600);
}

void loop()
{
 WebServ(); //my webserver
 AllSensor(); //what my sensors do and their output

 if(millis() > timeNow + updateInterval){
 ToMySQL(); //my MySQL server

 timeNow = millis();
 }
}

void AllSensor()
{
digitalWrite(trigPin, LOW); //Start with it off
delay(2);
//Output pulse with 1ms width on trigPin
digitalWrite(trigPin, HIGH);
delay(1);
digitalWrite(trigPin, LOW);

duration = pulseIn(echoPin, HIGH); //Measure the pulse input in echo pin

distance = (duration/2) / 29.1; //Don't know why but this should be here
val = digitalRead(inputPin); //read input value
  if (val == HIGH) { //check if the input is HIGH
    //RGB_LED(0, 255, 0); //turn LED ON
     if (pirState == LOW) {
      //we have just turned on
      Serial.println("Motion detected!"); //We only want to print on the output change, not state
      Movment++; //add to Movment tally
      Serial.print("Times you tried: ");
      Serial.println(Movment); //print what the tally is of Movment
      pirState = HIGH;
    }
  } else {
    digitalWrite(5, LOW); // turn LED OFF
    if (pirState == HIGH){
      //we have just turned off
      Serial.println("Motion ended!"); //We only want to print on the output change, not state
      pirState = LOW;
    }
  }
if (distance <= 10 && distance >= 0) { //if distance less than 0.1 meter and more than 0
digitalWrite(buzzPin, HIGH); //Buzz
//digitalWrite(4,HIGH);
delay(1000);
tooClose++; //add to tooClose tally
Serial.print("Times you were too close: ");
Serial.println(tooClose); //print tooClose tally
} else {
digitalWrite(buzzPin, LOW); //Don't buzz
digitalWrite(4,LOW);
}
//counting the tally of Movment and tooClose and see what the output should be
if(tooClose <=3 && Movment <= 5){
  RGB_LED(0, 255, 0);
  }
else if(tooClose<= 6 && Movment <= 10){
  RGB_LED(255, 255, 0);
  }
  else
  {
    RGB_LED(255, 0, 0);
  }
if(tooClose == 10|| Movment == 15){ //if the tally is to high
 for (pos = 180; pos >= 0; pos -= 1) { //goes from 0 degrees to 180 degrees in steps of 1 degree
    myservo.write(pos); //tell servo to go to position in variable 'pos'
    delay(15); //waits 15ms for the servo to reach the position
 while(tooClose == 10|| Movment == 15){ //turns buzzPin off and exits this code so nothing is registerd any more
  digitalWrite(buzzPin,LOW);}
 //break;
  }
  } 
delay(60);
}

void RGB_LED(int red, int blue, int green){ //the RGB_LEDs code
  analogWrite(4, red);
  analogWrite(3, green);
  analogWrite(5, blue);
}

void WebServ() //my webserver
{
    WiFiEspClient Webclient = server.available();

  if (Webclient) {
    Serial.println("New Web client");
    boolean currentLineIsBlank = true;
    while (Webclient.connected()) {
      if (Webclient.available()) {
        char c = client.read();
        sendToHTML(Webclient);
        Serial.write(c);
        if (c == '\n' && currentLineIsBlank) {
          Serial.println("Sending response");

          // Send a standard HTTP response header
          Webclient.print(
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html\r\n"
            "Connection: close\r\n"
            "\r\n");
        }
        if (c == '\n') {
          currentLineIsBlank = true;
        }
        else if (c != '\r') {
          currentLineIsBlank = false;
        }
      }
    }
    delay(3000);
    Webclient.stop();
    Serial.println("Client disconnected");
  }
  }

void ToMySQL() //my MySQL
{
  Serial.println(F("Recording data."));
  MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
  //Inserting sensordata
  String query = "INSERT INTO `project_bowl`.`bowl` (`DateTime`, `Movment`, `TooClose`) VALUES (now(), " + String (Movment,2) + ", " + String(tooClose,2) +")";

  Serial.println(query);
  char *q = query.c_str();
  cur_mem->execute(q);
  delete cur_mem;
  Serial.println(F("Recorded. Web Server will respond."));
}

void sendToHTML(WiFiEspClient Webclient) //my HTML code
{
  Webclient.println("HTTP/1.1 200 OK");
  Webclient.println("Content-type:text/html");
  Webclient.println();

  Webclient.print(F("<!DOCTYPE html><html lang=\"en\"><head><link href=\"BowlLook.css\" rel=\"stylesheet\"><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><title>No Snack Bowl</title><style>img{float: right;} </style></head>"));
  Webclient.print(F("<body><div class=\"header\"><h1>The no snack bowl</h1></div><img src=\"NOsnack.jpg\" alt=\"Don't have chips\" width=\"500px\" height=\"300px\"><ul><li><a href=\"index.html?text=Tips&nouse=0\">Tips</a></li><li><a href=\"index.html?text=Result&nouse=0\">Results</a></li><li><a href=\"index.html?text=Home&nouse=0\">Home</a></li></ul><div id=\"texten\"></div>"));
  Webclient.print(F("<p>Movment ="));
  Webclient.print(Movment);
  Webclient.print(F("<br/></p><p>Close ="));
  Webclient.print(tooClose);
  Webclient.print(F("<br/></p><script src=\"BowlCan.js\"></script></body></html>"));
  
Webclient.println(); //it must end with a blank line
}
