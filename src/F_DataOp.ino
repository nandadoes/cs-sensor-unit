String prep_strSensorVals()
{
  String strSensor = "";
  strSensor += ",";
  strSensor += String(modeAmbLight);

  strSensor += ",";
  strSensor += String(modeAirTemp);
  strSensor += ",";
  strSensor += String(modeAirHum);

  strSensor += ",";
  strSensor += String(modeSoilTemp);
  strSensor += ",";
  strSensor += String(modeSoilHum);

  strSensor += ",";
  strSensor += String(modeAirPress);

  strSensor += ",";
  strSensor += String(modeBattVolt);

  //  strSensor += ",";
  return strSensor;

}

