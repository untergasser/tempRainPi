# TempRainPi

This is a proof of principle project to decode wireless weather sensors with simple modules and 
Raspberry Pi. Currently it only supports the Alecto WS 1200. As the reciver decodes the frequency, 
it should work with 868Mhz as well as 433Mhz depending on the reciver used. The Raspberry Pi does 
not handle any high frequency decoding and just reads the signal on one pin 10000 times a second. 
In principle it could work for any frequency if decoders are available and the output signal is 
digital. Cheap modules supporting on/off keying (OOK) modulation are available. The code only 
requires the WiringPi library. It consumes low energy and creates low processor load.

## Prerequisites

* Raspberry Pi
* [Generic 433Mhz reciver](https://github.com/milaq/rpi-rf)
or (not used here)
* [RX868 receiver for 868.35Mhz](http://www.elv.de/output/controller.aspx?cid=74&detail=10&detail2=42432)
* [WiringPi library](http://wiringpi.com/)

The transmitter can be used to send an identical signal, which can be recorded with an SDR:

`rtl_fm -M am -f 433.9M -s 10k > rtl.dat`

And visualized with audacity (import raw data, Signed 16 bit PCM, Little-endian and Mono).
The station displays do not respond to the signal yet, probably due to the low amplitude.


## History and Credits

The whole idea and the basic source code were inspired by the TempHygroRX868 project from Martin 
Kompf. I also really enjoy his web page.

[TempHygroRX868](https://github.com/skaringa/TempHygroRX868)

[Kompf Web Page](https://www.kompf.de/tech/rxdec.html)

The hardware setup is identical to rpi-rf, I also use the same sensors and wireing of the sensors 
and Raspberry Pi, but no code was used. It inspired the idea to send data back to the display.

[rpi-rf](https://github.com/milaq/rpi-rf)

A great project to deal with weather sensors is rtl_433.

[rtl_433](https://github.com/merbanan/rtl_433)

Many thanks to Benjamin Larsson and especially to Christian W. Zuckschwerdt for their support 
decoding the Alecto WS-1200 signals.

[rtl_433_tests](https://github.com/merbanan/rtl_433_tests/tree/master/tests/alecto_ws_1200/01)

Now I am still left with SDR for the TFA KLIMALOGG...pro sensors.

[tfrec](https://github.com/baycom/tfrec)


## License

Copyright 2018 Andreas Untergasser

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
 
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

