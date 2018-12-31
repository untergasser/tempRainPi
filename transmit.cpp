/*
 * Receiver for data of wireless weather sensors with RX868 and Raspberry Pi.
 *
 * Main program.
 */
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

   char sendSig[] = "11111110011011001110010011010110001010100000000111111111101100011111111010010011110011101011100\0";
// char sendSig[] = "11111110011011001110010101010100001010100000000111111110101001010111000010010010111110011110000\0";

int main() {
  wiringPiSetup();
/*
  BCM GPIO 17: DATA (OUT) == WiPin 0
*/
  pinMode(0, OUTPUT);
  digitalWrite(0, 0);
  for (int i = 0 ; i < strlen(sendSig) ; i++) {
    digitalWrite(0, 1);
    if (sendSig[i] == '1') {
      delayMicroseconds(480);
    } else {
      delayMicroseconds(1460);
    }
    digitalWrite(0, 0);
    delayMicroseconds(940);
  }
  delayMicroseconds(34500);
  for (int i = 0 ; i < strlen(sendSig) ; i++) {
    digitalWrite(0, 1);
    if (sendSig[i] == '1') {
      delayMicroseconds(480);
    } else {
      delayMicroseconds(1460);
    }
    digitalWrite(0, 0);
    delayMicroseconds(940);
  }
  digitalWrite(0, 0);
  printf("Signal send:\n%s\n", sendSig);
}
