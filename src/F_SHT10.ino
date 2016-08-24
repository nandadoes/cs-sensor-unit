void get_airTempHum(void)
{

  //  SHT1x sht1x(AIR_DAT, AIR_CLK);
  SHT1x sht1x(AIR_DAT, sht1xClock);

  airTemp = sht1x.readTemperatureC();
  airHum = sht1x.readHumidity();

  Serial << "Air Temp: ";
  Serial << (airTemp, 2); // rounded to 2 decimal float
  Serial << " C, " << "Air Hum: " << airHum << " % RH" << endl;
}
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
void get_soilTempHum(void)
{


  //      SHT1x sht1x(SOIL_DAT, SOIL_CLK);
  SHT1x sht1x(SOIL_DAT, sht1xClock);

  soilTemp = sht1x.readTemperatureC();
  soilHum = sht1x.readHumidity();

  Serial << "Soil Temp: ";
  Serial << (soilTemp, 2); // rounded to 2 decimal float
  Serial << " C, " << "Soil Hum: " << soilHum << " % RH" << endl;
}




