/*
 * Receiver for data of wireless weather sensors with RX868 and Raspberry Pi.
 *
 * Main program.
 */
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

static volatile int keepRunning = 1;

// String to recognize the sensor
char idst[] = "11111110011011001110\0";

char sign[200];
char sipo = 0;
int  temp = 0;
int  rainl = 0;
int  rainb = 0;

int  newbit(char bit);

/*
 * Signal handler to catch Ctrl-C to terminate the program safely.
 */
void sigIntHandler(int dummy) {
  keepRunning = 0;
} 

/*
 * Thread to read the output of the receiver module.
 */
PI_THREAD (decoderThread) {
  piHiPri(50);

  int x;
  int len = 0;
  int lo = 0;
  int hi = 0;
  int px = 0;

  while (keepRunning) {
    x = digitalRead(2);

    len++;
    if (0 == x) {
      lo++;
    } else {
      hi++;
    }

    if (x != px && 0 == x) {
      // slope high->low
      if (hi > 3 && hi < 12) {
        newbit('0');
      } else {
        newbit('1');
      }
      len = 1;
      lo = 1;
      hi = 0;
    }
    px = x;

    delayMicroseconds(100);
  }
}

// Not the best decoder, but working...
int newbit(char bit) {
   if ((strlen(idst) - 1 > sipo) && (bit != idst[sipo])) {
     // Not the sensor -> reset
     sipo = 0;
     temp = 0;
     rainl = 0;
     rainb = 0;
     return 0; 
   } 
   sign[sipo] = bit;
   if (sipo > 19 && sipo < 31) {
     temp *= 2;
     if (bit == '1') {
       temp += 1;
     }
   }
   if (sipo > 30 && sipo < 39) {
     rainl *= 2;
     if (bit == '1') {
       rainl += 1;
     }
   }
   if (sipo > 38 && sipo < 47) {
     rainb *= 2;
     if (bit == '1') {
       rainb += 1;
     }
   }
   if (sipo > 93) {
     // Print the signal
     printf("Signal found:\n%s\n  .   .   .   i   i ?ttttttttttrrrrrrrrRRRRRRRR   .   .   m   m   m   m   d   d   d   d   d   d\n", sign);
     float rtemp = (temp - 400) / 10.0;
     printf("Temp: %.1f°C\n", rtemp);
     float rrain = (rainb * 256 + rainl) * 0.3;
     printf("Rain: %.1f mm\n", rrain);
     sipo = 0;
     temp = 0;
     rainl = 0;
     rainb = 0;
     return 0;
   }
   sipo++;
   return 0;

}

/*
 * MAIN
 */
int main() {
  wiringPiSetup();
/*
  BCM GPIO 27: DATA (IN) == WiPin 2
*/
  pinMode(2, INPUT);
  pullUpDnControl(2, PUD_DOWN);

  signal(SIGINT, sigIntHandler);

  piThreadCreate(decoderThread);

  while (keepRunning) {
    piLock(1);
    piUnlock(1);
    delay(100);
  }

  printf("clean up and exit\n");
}
