void send_sms1Num1Msg(int phoneNum, int msgNum)
{

  //  char sms_toSend[25];

  // ****************************************************************
  //                          Clear char arrays
  // ****************************************************************
  for ( int i = 0; i < sizeof(sms_toSend);  ++i )
  {
    sms_toSend[i] = (char)0;
  }

  for ( int i = 0; i < sizeof(charVal);  ++i )
  {
    charVal[i] = (char)0;
  }



  // ****************************************************************
  //                       Add unit id to the sms
  // ****************************************************************
  strcat(sms_toSend, charUnitId);

  // ****************************************************************
  //                    Add notified message to the sms
  // ****************************************************************
  if (msgNum == 1)
  {

    strcat(sms_toSend, CHA_NW_REGIS);
//    Serial.println(sms_toSend);
  }

  if (msgNum == 2)
  {

    strcat(sms_toSend, CHA_V_LEV);

    convert_floatToChar(modeBattVolt);
    strcat(sms_toSend, charVal);

//    Serial.println(sms_toSend);
  }

  if (msgNum == 3)
  {
    //    strcat(sms_toSend, charUnitId);
    strcat(sms_toSend, CHA_3G_PWR);
//    Serial.println(sms_toSend);
  }




  // ****************************************************************
  //                          Send sms
  // ****************************************************************
  Serial<<"Starting sms..." << endl;
  power_onBreakNew(ONEMIN);


  delay(3000);

  //sets the PIN code
  sprintf(aux_str, "AT+CPIN=%s", pin_number);
  send_atCommand(aux_str, "OK", 2000);

  delay(3000);

  Serial<<"Connecting to the network..." << endl;

  //  while ( (sendATcommand("AT+CREG?", "+CREG: 0,1", 500) ||
  //           sendATcommand("AT+CREG?", "+CREG: 0,5", 500)) == 0 );


  startup_3GRepCrOnly(ONEMIN);
  Serial.print("Setting SMS mode...");
  send_atCommand("AT+CMGF=1", "OK", 1000);    // sets the SMS mode to text
  Serial.println("Sending SMS");



  if (phoneNum == 1)
  {
    sprintf(aux_str, "AT+CMGS=\"%s\"", phone_number1);
  }
  if (phoneNum == 2)
  {
    sprintf(aux_str, "AT+CMGS=\"%s\"", phone_number2);
  }



  answer = send_atCommand(aux_str, ">", 2000);    // send the SMS number
  if (answer == 1)
  {

    Serial<< sms_toSend << endl;




    Serial.write(0x1A);
    answer = send_atCommand("", "OK", 20000);
    if (answer == 1)
    {
      Serial<<"Sent ";

    }
    else
    {
      Serial<<"error ";
    }
  }
  else
  {
    Serial<<"error "<<(answer, DEC) << endl;
  }
}
