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
  if (x < 80) {
        return 0.0625 * x + 0.0000;
    } else if (x < 153) {
        return 0.0685 * x - 0.4795;
    } else if (x < 242) {
        return 0.0562 * x + 1.4045;
    } else if (x < 319) {
        return 0.0649 * x - 0.7143;
    } else if (x < 409) {
        return 0.0556 * x + 2.2778;
    } else if (x < 478) {
        return 0.0725 * x - 4.6377;
    } else if (x < 574) {
        return 0.0521 * x + 5.1042;
    } else if (x < 655) {
        return 0.0617 * x - 0.4321;
    } else if (x < 737) {
        return 0.0610 * x + 0.0610;
    } else if (x < 816) {
        return 0.0633 * x - 1.6456;
    } else if (x < 890) {
        return 0.0676 * x - 5.1351;
    } else if (x < 981) {
        return 0.0549 * x + 6.0989;
    } else if (x < 1069) {
        return 0.0568 * x + 4.2614;
    } else if (x < 1147) {
        return 0.0641 * x - 3.5256;
    } else if (x < 1233) {
        return 0.0581 * x + 3.3140;
    } else if (x < 1326) {
        return 0.0538 * x + 8.7097;
    } else if (x < 1408) {
        return 0.0610 * x - 0.8537;
    } else if (x < 1488) {
        return 0.0625 * x - 3.0000;
    } else if (x < 1567) {
        return 0.0633 * x - 4.1772;
    } else if (x < 1652) {
        return 0.0588 * x + 2.8235;
    } else if (x < 1730) {
        return 0.0641 * x - 5.8974;
    } else if (x < 1815) {
        return 0.0588 * x + 3.2353;
    } else if (x < 1887) {
        return 0.0694 * x - 16.0417;
    } else if (x < 1968) {
        return 0.0617 * x - 1.4815;
    } else if (x < 2045) {
        return 0.0649 * x - 7.7922;
    } else if (x < 2137) {
        return 0.0543 * x + 13.8587;
    } else if (x < 2215) {
        return 0.0641 * x - 6.9872;
    } else if (x < 2278) {
        return 0.0794 * x - 40.7937;
    } else if (x < 2353) {
        return 0.0667 * x - 11.8667;
    } else if (x < 2434) {
        return 0.0617 * x - 0.2469;
    } else if (x < 2517) {
        return 0.0602 * x + 3.3735;
    } else if (x < 2601) {
        return 0.0595 * x + 5.1786;
    } else if (x < 2671) {
        return 0.0714 * x - 25.7857;
    } else if (x < 2750) {
        return 0.0633 * x - 4.0506;
    } else if (x < 2833) {
        return 0.0602 * x + 4.3373;
    } else if (x < 2912) {
        return 0.0633 * x - 4.3038;
    } else if (x < 2990) {
        return 0.0641 * x - 6.6667;
    } else if (x < 3066) {
        return 0.0658 * x - 11.7105;
    } else if (x < 3155) {
        return 0.0562 * x + 17.7528;
    } else if (x < 3245) {
        return 0.0556 * x + 19.7222;
    } else if (x < 3328) {
        return 0.0602 * x + 4.5181;
    } else if (x < 3435) {
        return 0.0467 * x + 49.4860;
    } else if (x < 3530) {
        return 0.0526 * x + 29.2105;
    } else if (x < 3652) {
        return 0.0410 * x + 70.3279;
    } else if (x < 3769) {
        return 0.0427 * x + 63.9316;
    } else if (x < 4009) {
        return 0.0417 * x + 67.9583;
    } else if (x <= 4095) {
        return 0.0581 * x + 1.9186;
    } else {
        return 0.0; // Default case if x is out of defined range
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
