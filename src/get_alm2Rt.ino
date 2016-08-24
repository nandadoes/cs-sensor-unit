void get_alm2Rt(void)
{

  int lastD, nextD;
  lastD = get_lastDateOfMonth();

  // Caculate next date for feeding
  nextD = thisD + INTVL_D;
  if (nextD > lastD)
  {
    nextD = nextD - lastD;
  }

  String nextFeedTime = "";
  nextFeedTime += "NEXTFEED-" + String(thisY) + "-" +
                  String(thisMonthInt) + "-" + String(nextD)
                  + "@" + String(feedH) + ":" + String(feedM) + ":"
                  + String(feedS);
  Serial << "nextFeedTime: " << nextFeedTime << endl;
  delay(50);

  for (int i = 0; i < 3; i++)
  {
    beep(25);
  }



  // **********************************************************
  //          Record Alarm eventin ALARM.TXT file
  // **********************************************************

  String strAlarmNum = "A2";
  delay(100);
  write_SD_alarmsRec(alarmsRecFn, strAlarmNum, nextFeedTime);



  // **********************************************************
  //                   Power ON 3G shield
  // **********************************************************

  power_onBreakNew(ONEMIN);
  unsigned long startTime = millis();

  do
  {


    if (at == 1)
    {

      startup_3GRepCrOnly(ONEMIN);

      if (creg == 1)
      {
        startup_3GRepCgOnly(ONEMIN);

        if (cgreg == 1)
        {
          break;
        }
        else
        {
          startup_3GRepCgOnly(ONEMIN);
        }
      }
      else
      {
        startup_3GRepCrOnly(ONEMIN);
      }

    }
    else
    {
      power_onBreakNew(ONEMIN);
    }


    Serial << "at: " << at << endl;
    Serial << "creg: " << creg << endl;
    Serial << "cgreg: " << cgreg << endl;

    Serial << millis() - startTime << endl;
  }
  while (millis() - startTime <= ONEMIN * 3); // PWRON_PERIOD);


  Serial << "out of do-while loop !!!" << endl;
  Serial << "at: " << at << endl;
  Serial << "creg: " << creg << endl;
  Serial << "cgreg: " << cgreg << endl;





  // **********************************************************
  // Feed 24 datasets if 3G and GPRS Registration is successful
  // If not, send sms to notify unsuccesful registration.
  // **********************************************************

  // Feed 24 datasets from today's readings
  if ((at == 1) && (creg == 1) && (cgreg == 1))
  {
    //    for (int h = 0; h < 24 ; h++)
    for (int h = 0; h < FEEDS_NUM ; h++)
    {
      Serial << endl;
      Serial << endl;
      printDateTime( RTC.get() );
      String feedFilename = get_strFeedFnUUMMDDHH( thisMonthInt, thisD, h);
      delay(100);
      read_SD_multiFieldsSingleFile(feedFilename);
      delay(50);

      if (gotTheFile == 1)
      {

        feed_singleDataset();

        gotTheFile = 0;
      }
      delay(100);
      write_SD_feedsRec(feedRecFn);
      printDateTime( RTC.get() );
      Serial << endl;
      Serial << endl;
    }
  }



  else
  {
    // **********************************************************
    // Report via sms if no 3G network nor GPRS registerations
    // **********************************************************
    //    send_sms1Num1Msg(1, 1); // phone num, msg num
    //    delay(ONESEC * 5);
    //    send_sms1Num1Msg(2, 1); // phone num, msg num
    //    delay(ONESEC * 5);

  }

  // **********************************************************
  // Report remain voltage level if it drops below threshold
  // **********************************************************

  read_modeBattV();
  if (modeBattVolt < V_THRES)
  {

    send_sms1Num1Msg(1, 2); // phone num, msg num
    delay(ONESEC * 5);
    send_sms1Num1Msg(2, 2); // phone num, msg num
    delay(ONESEC * 5);

  }

  // **********************************************************
  //                   Power OFF 3G shield
  // **********************************************************
  printDateTime( RTC.get() );
  Serial << endl;

  for (int i = 0; i < 4; i++)
  {
    power_offDoubleCheckStatus();

    Serial << "threeGIsOff?: " << threeGIsOff << endl; // useless when 3G shield is stuck in power on mode
    delay(6000);
  }

  // **********************************************************
  // Check 3G shield power status via its onmodule power LED
  // **********************************************************
  //   test_3gLedPrw(ONEMIN / 6);


  // **********************************************************
  //       Reset all 3G shield connection's variables
  // **********************************************************
  //  at = offTest;
  at = 0;
  creg = 0;
  cgreg = 0;
  successFeedCount = 0;
  printDateTime( RTC.get() );
  Serial << endl;
  for (int i = 0; i < 6; i++)
  {
    beep(25);
    delay(50);
  }


}

