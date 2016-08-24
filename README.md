# Connected Seeds' sensor unit

### Description:
As part of a research into how Internet of Things and sensor technologies can benefit an urban food growing community in London, this [Connected Seeds](http://www.connectedseeds.org) (CS) sensor unit is designed for outdoor monitoring weather and plant growing conditions. It measures 7 parameters hourly (i.e. luminosity, barometric pressure, air temperature and humidity, soil temperature and humidity and approximated voltage level of the power supply), all of which are stored in an SD card and uploaded to an online server [Thingspeak](http://thingspeak.com) channels via 3G communication once a day.


### Required hardware:
See [component list](https://github.com/nandadoes/cs-sensor-unit/wiki/Component-list)

### Required software:
* [CS_sensorUnit](https://github.com/nandakrpp/connectedseeds/raw/master/cs_sensorUnit.zip) (tested with Arduino 1.6.9)
* [Arduino IDE](https://www.arduino.cc/en/Main/Software)
* Jack Christensen's [DS3232RTC library](https://github.com/JChristensen/DS3232RTC)
* Michael Margolis's [Time ](http://www.pjrc.com/teensy/td_libs_Time.html)
* Adafruit [Sensor library](https://github.com/adafruit/Adafruit_Sensor)
* Ardafruit [TSL2591 library](https://github.com/adafruit/Adafruit_TSL2591_Library)
* Adafruit [BMP085 library](https://github.com/adafruit/Adafruit-BMP085-Library)
* Adafruit [INA219 library](https://github.com/adafruit/Adafruit_INA219)
* Jonathan Oxer's [SHT1x library](https://github.com/practicalarduino/SHT1x)

### Circuit Building and Installation: 
  1. Prepare CS shields – download PCB design files (i.e. [L2](http://nandadoes.com/download_seeds/docu_media/seedsShieldTwo.zip) and [L4](http://nandadoes.com/download_seeds/docu_media/seedsShieldFour.zip)) and print each as a double-sided shield. See [PCB design note](https://github.com/nandadoes/cs-sensor-unit/wiki/PCB-design-note) for details.      
  2.  Assemble – Solder components on both shields and assemble a 4-layer circuit. See [Assemble note](https://github.com/nandadoes/cs-sensor-unit/wiki/Assemble-note) for details.
      <br/>
      _A fully assembled CS sensor circuit:_     
      <img src="http://nandadoes.com/download_seeds/docu_media/stacking_circuit_4_Layers.jpg" width="350">
 
  3. Download and install all required libraries into Arduino/library folder
  4. Download the zip folder of [CS_sensorUnit](https://github.com/nandadoes/cs-sensor-unit/blob/master/cs_sensorUnit.zip) software, unzip and open CS_sensorUnit.ino file in Arduino or other preferred IDE
  5. Create a channel on [Thingspeak](https://thingspeak.com/channels) with 7 [fields](https://www.mathworks.com/help/thingspeak/create-a-channel.html); copy the channel's API write key to replace the 16-digit key on line 153 in CS_sensorUnit.ino file   
  6. Upload software: set two slide switches on the top shield at 'usb' positions before uploading CS_sensorUnit software onto Arduino Mega board. Set both switches back at 'serial' positions once the uploading process is completed.
  7. Switch on the circuit
  8. Place all of the components in the enclosure and install it half way into the soil. Make sure the upper SHT10 sensor is exposed to air.   
    <br/>
    _A fully assembled CS sensor unit with two ST10 sensors on the side:_    

    <br/>
    <img src="http://nandadoes.com/download_seeds/docu_media/sensor_unit_dried_cut.jpg" width="350">


### Usage:
* __How it works__ – On start up, MCU is put into sleep mode and only wakes up by 2 alarms to perform series of events: 
    + _Alarm 1_ wakes up MCU @ minute zero of every hour. This is to read, do a simple stat and store all data including alarm event in text files before entering sleep mode. 
    + _Alarm 2_ wakes up MCU @ 23:10 every day to upload data toThingSpeak and record alarm and 3G communication events in text files. After that, it checks 3G shield's power state and attempts to power it off (several times since the 3G shield is having issue with its power on/off feature of the original hardware). Before going into sleep mode, it sends out an sms notification to two phone numbers if the sensed voltage is lower than the mininum threshold.


### Contributing: 
The work is still under development. Though it is fully functional, several elements regarding both hardware and software can be improved. I willbe very grateful if some parts or the entire system can be beneficial to your research or practice or play, and/or if you like to help improve. If so, please feedback using a [contributing template](https://github.com/nandakrpp/connectedseeds/edit/nandakrpp-cs-contributing-1/contributing.md?pr=/nandakrpp/connectedseeds/pull/2) or drop me a line at nandadoes@gmail.com

### Credits:
* Connected Seeds project is sponsored by EPSRC and developed at   Queen Mary University of London. 
* Special thanks go to: 
    + Research team i.e. [Dr Nick Bryan-Kinns (PI)](http://www.eecs.qmul.ac.uk/~nickbk/), [Dr Hamed Haddadi (Co-I)](http://www.eecs.qmul.ac.uk/~hamed/) and [Dr Sara Heitlinger (Researcher Col)](http://saraheitlinger.net/)
    + All seeds guardians i.e. Lutfun and Richard at Spitalfields City Farm, Lisa at Wilton Estate, Halema and Anwara at Selby Estate, Zimbabwean association and Nat at Cordwainer Garden
    + QMUL Electronics Lab
    + Production team Ireti, Meng, Matt and Yulia
    + Flim maker Donna
* [Project partners](http://connectedseeds.eecs.qmul.ac.uk/partners/)

### Licenses:

Copyright (c) 2016 Nanda Khaorapapong and Connected Seeds     
[GNU GPLv3](https://www.gnu.org/licenses/gpl-3.0.en.html) license
