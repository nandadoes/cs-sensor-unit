void read_sensors()
{

  // ************************************************************
  //                       Light sensor routine
  // ************************************************************

  //  digitalWrite(LI_PWR, 1);
  //  delay(WARMUP_P);
  for (int r = 0; r < NUM_READINGS; r++)
  {
    digitalWrite(LI_PWR, 1);
    delay(WARMUP_P * 2);
    config_lightSensor(); // Configure the sensor
    get_advancedLightFull();
    arrAmbLight[r] = ambLight;
    digitalWrite(LI_PWR, 0);
    delay(BTW_READ);
  }

  // Get mode values
  modeAmbLight = stats.mode(arrAmbLight, NUM_READINGS);

  if (modeAmbLight <= 0.00)
  {
    modeAmbLight = stats.median(arrAmbLight, NUM_READINGS);
  }
  Serial << "mode ambLight : " << modeAmbLight << endl;




  // **********************************************************
  //                    Air sensor routine
  // **********************************************************
  digitalWrite(AIR_PWR, 1);
  delay(WARMUP_P);
  for (int r = 0; r < NUM_READINGS - 2; r++)
  {
    get_airTempHum();
    arrAirTemp[r] = airTemp;
    arrAirHum[r] = airHum;
    delay(BTW_READ); // for SHT1xx
  }
  digitalWrite(AIR_PWR, 0);


  // Get mode values
  modeAirTemp = stats.mode(arrAirTemp, NUM_READINGS);
  if (modeAirTemp == 0.0)
  {
    modeAirTemp = stats.maximum(arrAirTemp, NUM_READINGS);
  }
  Serial << "mode airTemp : " << modeAirTemp << endl;

  modeAirHum = stats.mode(arrAirHum, NUM_READINGS);
  if (modeAirHum == 0.0)
  {
    modeAirHum = stats.maximum(arrAirHum, NUM_READINGS);
  }
  Serial << "mode airHum : " << modeAirHum << endl;

  delay(1000);


  // ************************************************************
  //                      Soil sensor routine
  // ************************************************************
  digitalWrite(SOIL_PWR, 1);
  delay(WARMUP_P);
  // Read sensor values
  for (int r = 0; r < NUM_READINGS - 2 ; r++)
  {
    get_soilTempHum();
    arrSoilTemp[r] = soilTemp;
    arrSoilHum[r] = soilHum;
    delay(BTW_READ);
  }
  digitalWrite(SOIL_PWR, 0);

  // Get mode values
  modeSoilTemp = stats.mode(arrSoilTemp, NUM_READINGS);
  if (modeSoilTemp == 0.0)
  {
    modeSoilTemp = stats.maximum(arrSoilTemp, NUM_READINGS);
  }
  Serial << "mode soilTemp : " << modeSoilTemp << endl;

  modeSoilHum = stats.mode(arrSoilHum, NUM_READINGS);
  if (modeSoilHum == 0.0)
  {
    modeSoilHum = stats.maximum(arrSoilHum, NUM_READINGS);
  }
  Serial << "mode soilHum : " << modeSoilHum << endl;








  // ****************************************************************
  //                 Air Pressure sensor routine
  // ****************************************************************
  // Alteration on the sensor board: remove 2 pull-up resistors
  //  for (int r = 0; r < NUM_READINGS; r++)
  for (int r = 0; r < NUM_READINGS - 2; r++)
  {
    digitalWrite(AIRPRESS_PWR, 1);
    //    delay(WARMUP_P);
    delay(WARMUP_P / 2);
    get_airPress();
    arrAirPress[r] = airPress;
    digitalWrite(AIRPRESS_PWR, 0);
    delay(BTW_READ);
  }

  // Get mode values
  modeAirPress = stats.mode(arrAirPress, NUM_READINGS);
  if (modeAirPress == 0.0)
  {
    modeAirPress = stats.maximum(arrAirPress, NUM_READINGS);
  }
  Serial << "mode airPress : " << modeAirPress << endl;

  // ****************************************************************
  //                 Battery measurement routine
  // ****************************************************************
  for (int r = 0; r < NUM_READINGS - 2; r++)
  {

    digitalWrite(AMPVOLT_PWR, 1);
    //        delay(WARMUP_P);
    delay(WARMUP_P / 2);
    get_battVoltINA219();

    arrBattVolt[r] = battVolt;

    digitalWrite(AMPVOLT_PWR, 0);
    delay(BTW_READ);
  }

  // Get mode values
  modeBattVolt = stats.mode(arrBattVolt, NUM_READINGS);
  if (modeBattVolt == 0.0)
  {
    modeBattVolt = stats.median(arrBattVolt, NUM_READINGS);
  }
  Serial << "mode battVolt : " << modeBattVolt << endl;


}





