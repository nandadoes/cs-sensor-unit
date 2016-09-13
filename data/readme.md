#File description 



### Filename  
Format: UUMMDDHH   
Example:
_01070614.TXT_ is logged from sensor unit 01 on July 6th at 14:00 


### File content      
Format: data id in UUYYYYMMDDHH, light level (lux), air temp (C), air humid (%), soil temp (C), soil humid (%), air pressure at sea level (mBar), approximated remaining voltages (V)   
Example:   
_012016070614,3800.00,26.55,32.31,26.55,34.64,1020.52,4.88_    
data id = logged from sensor unit 01 on July 6th 2016 at 14:00    
light level = 3800.00 lux   
air temp = 26.55 Celcius   
air humid = 32.31 %   
soil temp = 26.55 Celcius   
soil humid = 34.64 %   
air pressure at sea level = 1020.52 millibar   
remained voltages = 4.88 V.   

### File conversion method
see [TXT to JSON format conversion: how to](https://github.com/nandadoes/cs-sensor-unit/wiki/TXT-to-JSON-format-conversion:-how-to)

### Notes:    

1. Next update of datasets for both json and txt ([datasets.zip](https://github.com/nandadoes/cs-sensor-unit/raw/master/data/datasets.zip)) formats will be notified here. 
2. Daily updates on Thingspeak [channels](https://github.com/nandadoes/cs-sensor-unit/wiki/Thingspeak-pages) are not fully pushed through due to 3G network connectivity issue
3. Awaiting content for seeds09.json