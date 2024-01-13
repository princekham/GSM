#include <SoftwareSerial.h>
#include <sim900.h>


// Create a SoftwareSerial object to communicate with the SIM900 module
SoftwareSerial sim900Serial(7, 8); // RX, TX
SIM900 sim900(&sim900Serial);
const int switchPin = 2; // Pin connected to the switch
bool switchState = LOW;   // Initial state of the switch
String mystring = " ";
int count = 0; // A variable to count the new line characters



void checkSMS() {
  // Read the SMS message
  String smsMessage = "";
  while (sim900Serial.available()) {
    char c = sim900Serial.read();
    smsMessage += c;
    Serial.print (smsMessage);
    
  }

  // Check if the received message contains a specific keyword
  if (smsMessage.indexOf("SWITCH ON") != -1) {
    switchState = HIGH;
    Serial.println ("high");
    digitalWrite(switchPin, switchState);
    sim900.sendSMS("+09795819487", "Switch is now ON.");
   // sendSMS("Switch is now ON.");
  } else if (smsMessage.indexOf("SWITCH OFF") != -1) {
    switchState = LOW;
    Serial.println ("low");
    digitalWrite(switchPin, switchState);
    sim900.sendSMS("+09795819487", "Switch is now OFF.");
    //sendSMS("Switch is now OFF.");
  } else if (smsMessage.indexOf("STATUS") != -1) {
    //sendSMS("Switch is " + String((switchState == HIGH) ? "ON" : "OFF"));
    mystring = ("Switch is " + String((switchState == HIGH) ? "ON" : "OFF"));
    sim900.sendSMS("+09795819487", mystring);
  }
}


void setup() {

/*
  pinMode(9, OUTPUT);
  digitalWrite(9,LOW);
  delay(2000);
  digitalWrite(9,HIGH);
  delay(2000); */

  // Start serial communication with the Arduino IDE Serial Monitor


  Serial.begin(9600);
  
  // Start serial communication with the SIM900 module
  sim900Serial.begin(9200);
  SIM900power();
  // Wait for the SIM900 module to initialize
  delay(20000);


    Serial.println(
    sim900.handshake() ? "Handshaked!" : "Something went wrong."
  );




  // Set the switch pin as OUTPUT
  pinMode(switchPin, OUTPUT);

  // Initialize the switch state
  digitalWrite(switchPin, switchState);

  // Send a startup SMS message
  //sendSMS("System started. Switch is OFF.");

 

    Serial.println(
    sim900.sendSMS("+09795819487", "System started. Switch is OFF.")
      ? "Sent!" : "Not sent."
  );
  //sim900.close(); // 
}

void loop() {
  // Read from the SIM900 module if data is available

  
  if (sim900Serial.available()) {
    char c = sim900Serial.read();
    Serial.write(c);
    
  
    char buffer[32]; // create a buffer to store the data
    Serial.readBytesUntil('\n', buffer, 32); // read the data until the newline character and store it in the buffer
    String second_line = buffer; // convert the buffer to a String variable
    Serial.println(second_line); // print the second line to the serial monitor
   
    // Check for incoming SMS
    if (c == '\n') {
      checkSMS();
    }
  } 



  // Check if the switch status has changed and update if necessary
  if (switchState != digitalRead(switchPin)) {
    mystring = "Switch is " + String ((switchState == HIGH) ? "ON" : "OFF");
    
    sim900.sendSMS("+09795819487", mystring);

   // sendSMS("Switch is " + String((switchState == HIGH) ? "ON" : "OFF"));
  }
}


void SIM900power()
// software equivalent of pressing the GSM shield "power" button
{
digitalWrite(9, LOW);
delay(1000);
digitalWrite(9, HIGH);
delay(5000);
}

