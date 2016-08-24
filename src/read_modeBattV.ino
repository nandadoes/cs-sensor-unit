void read_modeBattV(void)
{

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





