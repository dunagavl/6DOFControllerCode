#include <Arduino.h>
#include <Wire.h>
#include <math.h>

//Potentiometer connected to GPIO pin 34
const int V_OUT = 35;

void setup() {
  Serial.begin(115200);
  analogReadResolution(12); // Ensure the ADC resolution is set to 12 bits.
  Serial.println("Setup successful.");
  delay(2000);
}

float calcDegree(float x) {
  if (x < 87) { 
    return 0.0575 * x + 0.0000;
  } else if (x < 149) { 
    return 0.0806 * x - 2.0161; 
  } else if (x < 230) { 
    return 0.0617 * x + 0.8025; 
  } else if (x < 301) { 
    return 0.0704 * x - 1.1972; 
  } else if (x < 398) { 
    return 0.0515 * x + 4.4845; 
  } else if (x < 471) { 
    return 0.0685 * x - 2.2603;
  } else if (x < 564) { 
    return 0.0538 * x + 4.6774; 
  } else if (x < 639) { 
    return 0.0667 * x - 2.6000; 
  } else if (x < 721) { 
    return 0.0610 * x + 1.0366; 
  } else if (x < 802) { 
    return 0.0617 * x + 0.4938; 
  } else if (x < 870) { 
    return 0.0735 * x - 8.9706; 
  } else if (x < 949) { 
    return 0.0633 * x - 0.0633; 
  } else if (x < 1023) { 
    return 0.0676 * x - 4.1216; 
  } else if (x < 1107) { 
    return 0.0595 * x + 4.1071; 
  } else if (x < 1185) { 
    return 0.0641 * x - 0.9615; 
  } else if (x < 1277) { 
    return 0.0543 * x + 10.5978; 
  } else if (x < 1360) { 
    return 0.0602 * x + 3.0723; 
  } else if (x < 1440) { 
    return 0.0625 * x + 0.0000; 
  } else if (x < 1529) { 
    return 0.0562 * x + 9.1011; 
  } else if (x < 1623) { 
    return 0.0532 * x + 13.6702; 
  } else if (x < 1692) { 
    return 0.0725 * x - 17.6087; 
  } else if (x < 1780) { 
    return 0.0568 * x + 8.8636; 
  } else if (x < 1855) { 
    return 0.0667 * x - 8.6667;
  } else if (x < 1931) { 
    return 0.0658 * x - 7.0395; 
  } else if (x < 2010) { 
    return 0.0633 * x - 2.2152; 
  } else if (x < 2104) { 
    return 0.0532 * x + 18.0851; 
  } else if (x < 2185) { 
    return 0.0617 * x + 0.1235; 
  } else if (x < 2254) { 
    return 0.0725 * x - 23.3333; 
  } else if (x < 2327) { 
    return 0.0685 * x - 14.3836; 
  } else if (x < 2417) { 
    return 0.0556 * x + 15.7222; 
  } else if (x < 2569) { 
    return 0.0658 * x - 9.0132; 
  } else if (x < 2641) { 
    return 0.0694 * x - 18.4028;
  } else if (x < 2721) { 
    return 0.0625 * x - 0.0625; 
  } else if (x < 2802) { 
    return 0.0617 * x + 2.0370; 
  } else if (x < 2871) { 
    return 0.0725 * x - 28.0435; 
  } else if (x < 2949) { 
    return 0.0641 * x - 4.0385; 
  } else if (x < 3033) { 
    return 0.0595 * x + 9.4643; 
  } else if (x < 3113) { 
    return 0.0625 * x + 0.4375; 
  } else if (x < 3297) { 
    return 0.0543 * x + 25.8152; 
  } else if (x < 3400) { 
    return 0.0485 * x + 44.9515; 
  } else if (x < 3500) {
    return 0.0500 * x + 40.0000; 
  } else if (x < 3608) { 
    return 0.0463 * x + 52.9630; 
  } else if (x < 3737) { 
    return 0.0388 * x + 80.1550; 
  } else if (x < 3860) { 
    return 0.0407 * x + 73.0894; 
  } else if (x < 3992) { 
    return 0.0379 * x + 83.7879; 
  } else if (x <= 4095) { 
    return 0.0485 * x + 41.2136; 
  } else { 
    return 0.0; // Default case if x is out of defined range }
  }
}

float calcResistance(float degrees) {
  return ((39.794 * degrees) - 113.32);
}

void loop() {
  float digiVOut = analogRead(V_OUT);
  Serial.print("Digital Value: ");
  Serial.println(digiVOut);

  float degrees = calcDegree(digiVOut);
  Serial.print("Degrees: ");
  Serial.println(degrees);

  float resistance = calcResistance(degrees);
  Serial.print("Resistance: ");
  Serial.println(resistance);

  delay(1000);
}
