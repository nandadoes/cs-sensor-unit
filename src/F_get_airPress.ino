void get_airPress(void)
{

  float pressureMbar = 0.01 * (bmp.readSealevelPressure());
  Serial << "Pressure at sealevel: " << pressureMbar << " Mbar" << endl;
  airPress = pressureMbar;
}

