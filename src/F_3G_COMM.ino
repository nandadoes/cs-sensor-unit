void assign_apiKey(void)
{

  Serial << strUnitId << endl;

  for ( int i = 0; i < sizeof(APIWriteKey);  ++i )
  {
    APIWriteKey[i] = (char)0;
  }




  if (strUnitId == "01")
  {
    for (int i = 0; i < 16; i++)
    {
      APIWriteKey[i] = APIWriteKey1[i];
    }


    Serial << "Seeds Guardian 1 : Lutfun's lablab beans" << endl;
  }



  if (strUnitId == "02")
  {
    for (int i = 0; i < 16; i++)
    {
      APIWriteKey[i] = APIWriteKey2[i];
    }

    Serial << "Seeds Guardian 2: Anwara's" << endl;
  }




  if (strUnitId == "03")
  {
    for (int i = 0; i < 16; i++)
    {
      APIWriteKey[i] = APIWriteKey3[i];
    }

    Serial << "Seeds Guardian 3: Lisa's green house" << endl;
  }




  if (strUnitId == "04")
  {
    for (int i = 0; i < 16; i++)
    {
      APIWriteKey[i] = APIWriteKey4[i];
    }
    Serial << "Seeds Guardian 4: Richard's Green orach" << endl;
  }




  if (strUnitId == "05")
  {
    for (int i = 0; i < 16; i++)
    {
      APIWriteKey[i] = APIWriteKey5[i];
    }
    Serial << "Seeds Guardian 5: Nat Cordwainers" << endl;
  }




  if (strUnitId == "06")
  {
    for (int i = 0; i < 16; i++)
    {
      APIWriteKey[i] = APIWriteKey6[i];
    }
    Serial << "Seeds Guardian 6: [ready to be deployed]" << endl;
  }


  if (strUnitId == "07")
  {
    for (int i = 0; i < 16; i++)
    {
      APIWriteKey[i] = APIWriteKey7[i];
    }
    Serial << "Seeds Guardian 7: Lutfun's Kudo" << endl;
  }




  if (strUnitId == "08")
  {
    for (int i = 0; i < 16; i++)
    {
      APIWriteKey[i] = APIWriteKey8[i];
    }
    Serial << "Seeds Guardian 8: Halema's" << endl;
  }




  if (strUnitId == "09")
  {
    for (int i = 0; i < 16; i++)
    {
      APIWriteKey[i] = APIWriteKey9[i];
    }
    Serial << "Seeds Guardian 9: Sara's" << endl;
  }




  if (strUnitId == "10")
  {
    for (int i = 0; i < 16; i++)
    {
      APIWriteKey[i] = APIWriteKey10[i];
    }
    Serial << "Seeds Guardian 10: [got stolen]" << endl;
  }


  if (strUnitId == "11")
  {
    for (int i = 0; i < 16; i++)
    {
      APIWriteKey[i] = APIWriteKey11[i];
    }
    Serial << "Seeds Guardian 11: Normadic garden [to be deployed]" << endl;
  }




  if (strUnitId == "12")
  {
    for (int i = 0; i < 16; i++)
    {
      APIWriteKey[i] = APIWriteKey12[i];
    }
    Serial << "Seeds Guardian 12: Zimbabwean association's" << endl;
  }




  if (strUnitId == "13")
  {
    for (int i = 0; i < 16; i++)
    {
      APIWriteKey[i] = APIWriteKey13[i];
    }
    Serial << "Seeds Guardian 13: [ready to be deployed]" << endl;
  }




  if (strUnitId == "14")
  {
    for (int i = 0; i < 16; i++)
    {
      APIWriteKey[i] = APIWriteKey14[i];
    }
    Serial << "Seeds Guardian 14: [ready to be deployed]" << endl;
  }




  if (strUnitId == "15")
  {
    for (int i = 0; i < 16; i++)
    {
      APIWriteKey[i] = APIWriteKey15[i];
    }
    Serial << "Seeds Guardian 15: [need repair]" << endl;
  }



  if (strUnitId == "16")
  {
    char APIWriteKey[] = ""; //
    Serial << "channel not in use" << endl;
  }

  for (int i = 0; i < 16; i++)
  {
    Serial << APIWriteKey[i] << endl;
  }
  Serial << endl;

}
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
void startup_3GRepCrOnly(unsigned long t)
{
  Serial << "3G creg starting ..." << endl;

  // Wait for network registration
  unsigned long startTime = millis();

  uint8_t answer1 = send_atCommand("AT + CREG ? ", " + CREG : 0, 1", 500);
  uint8_t answer2 = send_atCommand("AT + CREG ? ", " + CREG : 0, 5", 500);

  while (  (millis() - startTime <= t)  && ((answer1 != 1) || (answer2 != 1))  )
  {

    answer1 = send_atCommand("AT + CREG ? ", " + CREG : 0, 1", 500);
    answer2 = send_atCommand("AT + CREG ? ", " + CREG : 0, 5", 500);

    //    if ((answer1 == 1) && (answer2 == 1))
    if ((answer1 == 1) || (answer2 == 1))
    {
      cregResult = "1";
      creg = 1;
      delay(50);
      break;
    }
    else
    {
      cregResult = "0";
      creg = 0;
      delay(50);
    }

  }

}
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
void startup_3GRepCgOnly(unsigned long t)
{
  Serial << "3G cgreg starting ..." << endl;

  // Wait for network registration
  unsigned long startTime = millis();

  uint8_t   answer3 = send_atCommand("AT + CGREG ? ", " + CGREG : 0, 1", 500);
  uint8_t   answer4 = send_atCommand("AT + CGREG ? ", " + CGREG : 0, 5", 500);

  while (  (millis() - startTime <= t)  && ((answer3 != 1) || (answer4 != 1))  )
  {

    answer3 = send_atCommand("AT + CGREG ? ", " + CGREG : 0, 1", 500);
    answer4 = send_atCommand("AT + CGREG ? ", " + CGREG : 0, 5", 500);

    //    if ((answer3 == 1) && (answer4 == 1))
    if ((answer3 == 1) || (answer4 == 1))
    {
      cgregResult = "1";
      cgreg = 1;
      delay(50);
      break;
    }
    else
    {
      cgregResult = "0";
      cgreg = 0;
      delay(50);
    }

  }

  // sets APN, user name and password
  sprintf(aux_str, "AT + CGSOCKCONT = 1, \"IP\",\"%s\"", apn);
  send_atCommand(aux_str, "OK", 2000);

  sprintf(aux_str, "AT+CSOCKAUTH=1,1,\"%s\",\"%s\"", user_name, password);
  send_atCommand(aux_str, "OK", 2000);
}
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

int8_t send_atCommand(char* ATcommand, char* expected_answer1, unsigned int timeout)
{

  uint8_t x = 0,  answer = 0;
  char response[100];
  unsigned long previous;

  memset(response, '\0', 100);    // Initialize the string

  delay(100);

  while ( Serial.available() > 0) Serial.read();   // Clean the input buffer


  Serial << ATcommand << endl;


  x = 0;
  previous = millis();

  // this loop waits for the answer
  do {

    if (Serial.available() != 0) {
      if (x == 100)
      {
        strncpy(response, response + 1, 99);
        response[99] = Serial.read();
      }
      else
      {
        response[x] = Serial.read();
        x++;
      }
      // check if the desired answer is in the response of the module
      if (strstr(response, expected_answer1) != NULL)
      {
        answer = 1;
      }
    }
    // Waits for the asnwer with time out
  }
  while ((answer == 0) && ((millis() - previous) < timeout));



  return answer;
}

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
void feed_singleDataset()
{

  // The miminum time taken for this function -- in case when there are
  // Error watiing the request and Error sending the request plus Thingspeak's
  // minimum upload interval -- is xxxxxxx msec or xx sec or x.xx minutes
  // 24 datasets feeding will take about x ms or x s or x minutes
  // in total



  String getStr = "GET /update?api_key=";
  getStr += APIWriteKey;

  getStr += "&field1=";
  //      getStr += String(arrStrFeedDataset[0]);
  getStr += arrStrFeedDataset[0];

  getStr += "&field2=";
  //      getStr += String(arrStrFeedDataset[1]);
  getStr += arrStrFeedDataset[1];



  getStr += "&field3=";
  //    getStr += String(arrStrFeedDataset[2]);
  getStr += arrStrFeedDataset[2];
  getStr += "&field4=";
  //    getStr += String(arrStrFeedDataset[3]);
  getStr += arrStrFeedDataset[3];


  getStr += "&field5=";
  //    getStr += String(arrStrFeedDataset[4]);
  getStr += arrStrFeedDataset[4];

  getStr += "&field6=";
  //    getStr += String(arrStrFeedDataset[5]);
  getStr += arrStrFeedDataset[5];


  getStr += "&field7=";
  //    getStr += String(arrStrFeedDataset[6]);
  getStr += arrStrFeedDataset[6];


  getStr += "&field8=";
  //    getStr += String(arrStrFeedDataset[7]);
  getStr += arrStrFeedDataset[7];


  getStr += " HTTP/1.1\r\nHost: api.thingspeak.com\r\nContent-Length: 0\r\n\r\n";


  // request the url
  sprintf(aux_str, "AT+CHTTPACT=\"%s\",%d", url, port);
  //  answer = send_atCommand(aux_str, "+CHTTPACT: REQUEST", 60000);
  answer = send_atCommand(aux_str, "+CHTTPACT: REQUEST", ONEMIN / 10); // 6 sec
  if (answer == 1)
  {

    Serial << getStr << endl;
    // Sends "Ctrl+Z"
    aux_str[0] = 0x1A;
    aux_str[1] = 0x00;
    //    answer = send_atCommand(aux_str, "+CHTTPACT: 0", 60000);
    answer = send_atCommand(aux_str, "+CHTTPACT: 0", ONEMIN / 12); // 6 sec

    x = 0;
    if (answer == 1)
    {

      Serial << "OK" << endl;

      strfeedResult = "1";
      successFeedCount ++;
    }
    else
    {
      Serial << "Error sending the request" << endl;

      strfeedResult = "0.2";
    }
  }
  else
  {
    Serial << "Error waiting the request" << endl;

    strfeedResult = "0.1";
  }

  //    delay(10000);
  delay(15000); // Thingspeak minimum upload interval is 15 seconds
}



