### GSM Module

Tutorial - https://randomnerdtutorials.com/sim900-gsm-gprs-shield-arduino/
https://lastminuteengineers.com/sim900-gsm-shield-arduino-tutorial/




https://github.com/nthnn/SIM900

The following exaple to send SMS message is ok

```
#include <SoftwareSerial.h>
#include <sim900.h>

SoftwareSerial shieldSerial(7, 8);

void setup() {
  Serial.begin(9600);
  shieldSerial.begin (9600); // Initialize shield communication

  SIM900 sim900(&shieldSerial);
  Serial.println(
    sim900.sendSMS("+09795819487", "Hello, from SIM900!!")
      ? "Sent!" : "Not sent."
  );
  sim900.close();
}

void loop() { }
```
