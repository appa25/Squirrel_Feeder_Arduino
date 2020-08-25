// Date and time functions using a DS3231 RTC connected via I2C and Wire lib
#include <Servo.h>
#include "RTClib.h"

RTC_DS3231 rtc;
Servo myservo;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
int pos = 0;    // variable to store the servo position
bool oneSide = true;
void setup () {
  myservo.attach(9);
  myservo.write(30);
  Serial.begin(57600);

#ifndef ESP8266
  while (!Serial); // wait for serial port to connect. Needed for native USB
#endif

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

  // When time needs to be re-set on a previously configured device, the
  // following line sets the RTC to the date & time this sketch was compiled
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  // This line sets the RTC with an explicit date & time, for example to set
  // January 21, 2014 at 3am you would call:
  // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
}

void loop () {
    DateTime now = rtc.now();
    /*Serial.print(now.second(), DEC);
    Serial.print(" ");
    Serial.print(now.minute(), DEC);
    Serial.print(" ");
    Serial.println(now.hour(), DEC);
    delay(3000);
    */
    if (now.second() == 0 && now.minute() == 20 && now.hour() == 15) {
      if (oneSide) {
        for (pos = 25; pos <= 155; pos += 1) { // goes from 0 degrees to 180 degrees
        // in steps of 1 degree
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(15);                       // waits 15ms for the servo to reach the position
        }
      } else {
      for (pos = 155; pos >= 25; pos -= 1) { // goes from 180 degrees to 0 degrees
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(15);                       // waits 15ms for the servo to reach the position
        }
      }
      oneSide = !oneSide;
  }
}
