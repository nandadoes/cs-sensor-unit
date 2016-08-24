void get_advancedLightFull(void)
{
  // Show how to read IR and Full Spectrum at once and convert to lux

  // More advanced data read example. Read 32 bits with top 16 bits IR, bottom 16 bits full spectrum
  // That way you can do whatever math and comparisons you want!
  uint32_t lum = tsl.getFullLuminosity();
  uint16_t ir, full;
  ir = lum >> 16;
  full = lum & 0xFFFF;

  ambLight = full;

  Serial << "Light: -- " << "IR: " << ir << "  " << "Full: " << full << "  " << "Visible: " <<
         full - ir << "  " << "Lux: " << tsl.calculateLux(full, ir) << endl;

}

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
void config_lightSensor(void)
{
  //Configures the gain and integration time for the TSL2591

  tsl.setTiming(TSL2591_INTEGRATIONTIME_500MS);
  // tsl.setTiming(TSL2591_INTEGRATIONTIME_600MS);  // longest integration time (dim light)
}

