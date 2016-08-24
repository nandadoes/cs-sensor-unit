---
title: "README"
author: "nandadoes"
date: "24 August 2016"
output: html_document
---

# Connected Seeds' sensor unit



### Description:
As part of a research into how Internet of Things and sensor technologies can benefit an urban food growing community in London, this [Connected Seeds](http://www.connectedseeds.org) (CS) sensor unit is designed for outdoor monitoring weather and plant growing conditions. It measures 7 parameters hourly (i.e. luminosity, barometric pressure, air temperature and humidity, soil temperature and humidity and approximated voltage level of the power supply), all of which are stored in an SD card and uploaded to an online server [Thingspeak] (http://thingspeak.com) channels via 3G communication once a day.



### Table of Contents:
* [Required hardware](https://github.com/nandadoes/cs-sensor-unit#required-hardware)
* [Required software](https://github.com/nandadoes/cs-sensor-unit#required-software)
* [Circuit Building and Installation](https://github.com/nandadoes/cs-sensor-unit#circuit-building-and-installation)
* [Usage](https://github.com/nandadoes/cs-sensor-unit#usage)
* [Credits](https://github.com/nandadoes/cs-sensor-unit#credits)
* [Licenses](https://github.com/nandadoes/cs-sensor-unit#licenses)

### Required hardware:
* 1 of [Arduino or Genuino Mega 2560](https://www.arduino.cc/en/Main/ArduinoBoardMega2560)   
<img src="http://www.nandadoes.com/download_seeds/docu_media/mega.jpg" width="500">     

* 1 of CS sensor unit stackable shield-L2    
<img src="http://nandadoes.com/download_seeds/docu_media/sheildL2_print_cleanBG_top.jpg" width="250">

* 1 of CS sensor unit stackable shield-L4   
<img src="http://www.nandadoes.com/download_seeds/docu_media/sheildL4_print_cleanBG_top.jpg" width="250">

* 1 of [Cooking Hacks 3G/GPRS shield for Arduino and 3G antenna](https://www.cooking-hacks.com/documentation/tutorials/3g-gps-shield-arduino-raspberry-pi-tutorial/)   
![image](http://www.nandadoes.com/download_seeds/docu_media/3g_shield.jpg)

* 1 of [Adafruit BMP180 barometric sensor breakout](https://www.adafruit.com/product/1603)    
<img src="https://cdn-shop.adafruit.com/1200x900/1603-03.jpg" width="150">

* 1 of [Adafruit TSL2591 luminosity sensor breakout](https://www.adafruit.com/product/1980)   
<img src="https://cdn-shop.adafruit.com/1200x900/1980-01.jpg" width="150">

* 1 of [Adafruit INA219 current sensor breakout](https://www.adafruit.com/product/904)    
<img src="https://cdn-shop.adafruit.com/1200x900/904-00.jpg" width="150">

* 2 of [Seeed Soil Moisture & Temperature Sensor](http://www.seeedstudio.com/depot/Soil-Moisture-Temperature-Sensor-p-1356.html)   
<img src="http://statics3.seeedstudio.com/images/product/Soil%20Moisture.jpg" width="350">

* 1 of [ChronoDot - Ultra-precise Real Time Clock - v2.1](https://www.adafruit.com/product/255)          
<img src="https://cdn-shop.adafruit.com/970x728/255-01.jpg" width="200">

* 1 of [SPI micro SD breakout](http://www.ebay.co.uk/itm/Micro-SD-Board-Reader-TF-Storage-Card-Memory-Shield-Module-SPI-Arduino-RAS-Pi-UK-/181919545635)   
<img src="http://i.ebayimg.com/images/g/6EYAAOSwNsdXRUtz/s-l1600.jpg"" width="200">

* 2 of [TPS2113A Power Multiplexer Carrier with USB Micro-B Connector](https://www.pololu.com/product/2596)    
<img src="https://a.pololu-files.com/picture/0J5492.1200.jpg?a67eb2612201bcb0753fdec17b0de2ea" width="150">

* 2 of [SPDT Ultraminiature Slide Switch](https://www.rapidonline.com/taiway-1260-ultraminiature-slide-switches-60329)    
<img src="https://static.rapidonline.com/catalogueimages/Product/S76-0303P01WL.jpg" width="50">

* 1 of [RVFM S251A SPDT Right Angle PCB Slide Switch](https://www.rapidonline.com/rvfm-s251a-spdt-right-angle-pcb-slide-switch-76-0205)            
<img src="https://static.rapidonline.com/catalogueimages/Module/M030268P01WL.jpg" width="150">

* 7 of [1/4W 10KΩ 5% resistor](http://www.tandyonline.co.uk/10k-1-4w-5-carbon-film-resistor-5pk.html)   
<img src="http://www.tandyonline.co.uk/media/catalog/product/cache/1/image/9df78eab33525d08d6e5fb8d27136e95/2/7/271-1335-10k-carbon-resistors.png" width="150">

* 2 of [1/4W 2.2KΩ 5% resistor](http://www.tandyonline.co.uk/2-2k-1-4w-5-carbon-film-resistor-5pk.html)   
<img src="http://www.tandyonline.co.uk/media/catalog/product/cache/1/image/9df78eab33525d08d6e5fb8d27136e95/2/7/271-1325-2.2k-carbon-resistors.png" width="150">

* 2 of [CDIL 2N2222A NPN Transistor General Purpose RF](https://www.rapidonline.com/Electronic-Components/CDIL-2N2222A-NPN-Transistor-General-Purpose-RF-81-0256?IncVat=1&gclid=CO6mrafDyM4CFRa3Gwodg6kPbQ)     
<img src="https://static.rapidonline.com/catalogueimages/Product/S81-0256P01WL.jpg" width="80">

* 1 of [Lock & Lock rectangular 1 litre container (HPL817)](http://www.reallyusefulproducts.co.uk/uk/html/onlineshop/locklock/rec_hpl817.php)    
<img src="http://www.reallyusefulproducts.co.uk/images/onlineshop/locklock/fullsize/hpl817.jpg" width="300">

* 1 or 2 of [Swees Ultra Compact 26800mAh High Capacity Portable Power Bank Charger and USB cables](https://www.amazon.co.uk/dp/B017IHB7A4/ref=pd_lpo_sbs_dp_ss_2?pf_rd_p=569136327&pf_rd_s=lpo-top-stripe&pf_rd_t=201&pf_rd_i=B0155WSN5Q&pf_rd_m=A3P5ROKL5A1OLE&pf_rd_r=0P299RMGTQWQBV1Q6PR1)   
<img src="https://images-na.ssl-images-amazon.com/images/I/612ELlo98HL._SL1500_.jpg" width="300">

* 2 of [4-way terminal block connector](http://uk.rs-online.com/web/p/pcb-terminal-blocks/3617689/)   
<img src="http://uk.rs-online.com/largeimages/F3617689-01.jpg" width="100">

* 1 of [5V piezo tranducer](http://cpc.farnell.com/pro-signal/abt-402-rc/piezo-transducer-5v-pcb/dp/LS03781?CMP=CPC-PLA)   
<img src="http://cpc.farnell.com/productimages/standard/en_GB/102240105-40.jpg" width="50">

* Some hot glue and PVC fasteners

* Some PCB pin headers and sockets



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
  1. Prepare CS shields – download and print both CS shields (i.e. [L2](http://nandadoes.com/download_seeds/docu_media/seedsShieldTwo.zip) and [L4](http://nandadoes.com/download_seeds/docu_media/seedsShieldFour.zip)) designed as double-sided PCBs. See details below.       
       
     _Cs-Shield-L2 schematic:_ 
      ![shieldL2_sch.png](http://nandadoes.com/download_seeds/docu_media/shieldL2_sch_gpl.png)     
      <br/>
      _Cs-Shield-L2 double-sided board design:_        
    <img src="http://nandadoes.com/download_seeds/docu_media/shieldL2_brd.png" width="500">
    <br/>   
    _CS shield-L2 top (left) and bottom (right) sides:_    
    ![shieldL2_print](http://nandadoes.com/download_seeds/docu_media/shieldL2_print.jpg)     
    <br/>
      _Cs-Shield-L4 schematic:_       
     ![shieldL4_sch.png](http://nandadoes.com/download_seeds/docu_media/shieldL4_sch_gpl.png)   
     <br/>  
     _Cs-Shield-L4 board design:_             
    <img src="http://nandadoes.com/download_seeds/docu_media/shieldL4_brd.png" width="500">
     <br/>      
     _CS shield-L4 top (left) and bottom (right) sides:_     
     ![shieldL4_print](http://nandadoes.com/download_seeds/docu_media/shieldL4_print.jpg)    
     <br/> 
      
      

     










  2.  Assemble – Solder components on both shields and assemble a 4-layer circuit   
     <br/>   
     _Top view of circuit destacked in 4 layers:_        
     <img src="http://nandadoes.com/download_seeds/docu_media/circuit_destacked_noted_top_view.jpg" width="500">
     <br/>  
    _Bottom view of circuit destacked in 4 layers:_     
     <img src="http://nandadoes.com/download_seeds/docu_media/circuit_destacked_noted_bottom_view.jpg" width="500">
    <br/>   
    _Side view of the circuit assembled from 4 layers (i.e. bottom layer - Arduino, layer 2 - Cs shield L2, layer 3 - 3G shield, top layer - Cs shield L4:_      
     <img src="http://nandadoes.com/download_seeds/docu_media/stacking_circuit_4_Layers.jpg" width="500">
     <br/>   
    _Top view of the circuit assembled from 4 layers (i.e. bottom layer - Arduino, layer 2 - Cs shield L2, layer 3 - 3G shield, top layer - Cs shield L4) with two power banks:_      
     ![stacking_circuit_4_Layers_top_view](http://nandadoes.com/download_seeds/docu_media/stacking_circuit_4_Layers_top_view.jpg)
    <br/>   
    
    
  3. Download and install all required libraries into Arduino/library folder
  4. Download the zip folder of [CS_sensorUnit](https://github.com/nandakrpp/connectedseeds/raw/master/cs_sensorUnit.zip) software, unzip and open CS_sensorUnit.ino file in Arduino or other preferred IDE
  5. Create a channel on [Thingspeak](https://thingspeak.com/channels) with 7 [fields](https://www.mathworks.com/help/thingspeak/create-a-channel.html); copy the channel's API write key to replace the 16-digit key on line 153 in CS_sensorUnit.ino file   
  6. Upload software: set two slide switches on the top shield at 'usb' positions before uploading CS_sensorUnit software onto Arduino Mega board. Set both switches back at 'serial' positions once the uploading process is completed.
  7. Switch on the circuit
  8. Place all of the components in the enclosure and install it half way into the soil. Make sure the upper SHT10 sensor is exposed to air.   
    <br/>
    _A full assembled CS sensor unit with two ST10 sensors on the side:_    

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
