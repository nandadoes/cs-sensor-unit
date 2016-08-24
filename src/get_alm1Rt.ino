void get_alm1Rt(void)
{

  nextH = thisH + INTVL_H;
  if (nextH > 23)
  {
    nextH = nextH - 24;
  }
  String nextSenseTime = "";
  nextSenseTime += "NEXTSENSE-" + String(nextH) + ":" + String(alm1FirstM) + ":" + String(senseS);
  Serial << "nextSenseTime: " << nextSenseTime << endl;

  delay(50);

  for (int i = 0; i < 3; i++)
  {
    beep(25);
  }



  // **********************************************************
  //         Read and store sensor values in SD card
  // **********************************************************

  read_sensors();

  // Remove and write to a new file
  strFilename = prep_strUUMMDDHH( RTC.get() ) + ".TXT";

  if (SD.exists(strFilename))
  {
    Serial << strFilename << " exists." << endl;
    SD.remove(strFilename);
    Serial << strFilename << " removed." << endl;
  }


  delay(500);
  write_SD_multiFieldsUU(strFilename);
  delay(100);

  printDateTime( RTC.get() );
  Serial.println();


  // **********************************************************
  //          Record Alarm eventin ALARM.TXT file
  // **********************************************************
  String strAlarmNum = "A1";
  delay(500);
  write_SD_alarmsRec(alarmsRecFn, strAlarmNum, nextSenseTime);
  delay(100);


  // **********************************************************
  // Check 3G shield power status via its onmodule power LED
  // **********************************************************
  //   test_3gLedPrw(ONEMIN / 6);

  // **********************************************************
  // Report remain voltage level if it drops below threshold
  // **********************************************************

  if (modeBattVolt < V_THRES)
  {

    send_sms1Num1Msg(1, 2); // phone num, msg num
    delay(ONESEC * 5);
    send_sms1Num1Msg(2, 2); // phone num, msg num
    delay(ONESEC * 5);

  }

  // **********************************************************
  //                    Power OFF 3G shield
  // **********************************************************
  printDateTime( RTC.get() );
  Serial << endl;

  for (int i = 0; i < 4; i++)
  {
    power_offDoubleCheckStatus();

    Serial << "threeGIsOff ? : " << threeGIsOff << endl; // useless when 3G shield is stuck in power on mode
    delay(6000);
  }
  // **********************************************************
  //              Report time at operation completion
  // **********************************************************
  printDateTime( RTC.get() );
  Serial << endl;

  delay(100);


}

