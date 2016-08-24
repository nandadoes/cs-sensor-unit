void read_SD_multiFieldsSingleFile(String fn)
{
  Serial << "=====================" << endl;
  Serial << "Clear previous fields" << endl;
  //  Serial.println("arrStrFeedDataset[0-7]: ");
  for (int i = 0; i < FEEDFIELDS_NUM; i++)
  {
    arrStrFeedDataset[i] = "";
    //    Serial.print(i);  Serial.print(": ");
    //    Serial.println(arrStrFeedDataset[i]);
  }


  myFile = SD.open(fn);
  if (myFile)
  {
    gotTheFile = 1;
    Serial << "Reading from " << (fn) << ": " << endl;

    // Reading texts from the whole line in the file and
    // store in a buffer string

    int fieldCount = 0;
    int lastIndex = 0;
    //    const int LN_BUFF_SIZE = 60; // max line length is one less than this
    char inChar;
    //    char arrInChars[LN_BUFF_SIZE];
    //    String strBuff = "";
    String strLnBuff = "";
    while (myFile.available())
    {
      // Keep adding the current character to the string
      // if there is no newline character found,
      if (inChar != '\n')
      {
        inChar = myFile.read();
        //        Serial.print(inChar); // print to see what have been read
        strLnBuff += inChar; // store it in the buffer string
      }
    }
    // close the file:
    myFile.close();


    //    // Check what are in the buffer
    //    Serial.println("strLnBuff:");
    //    Serial.println(strLnBuff);

    // Split all fields with comma delimiter
    for (int i = 0; i < strLnBuff.length(); i++)
    {
      // Loop through each character and check if it's a comma
      if (strLnBuff.substring(i, i + 1) == ",")
      {
        // Grab the field from the last index up to the current position and store it
        arrStrFeedDataset[fieldCount] = strLnBuff.substring(lastIndex, i);
        // Update the last position and add 1, so it starts from the next character
        lastIndex = i + 1;
        // Increase the position in the array that we store into
        fieldCount++;
      }

      // If we're at the end of the string (no more commas to stop us)
      if (i == strLnBuff.length() - 1)
      {
        // Grab the last part of the string from the lastIndex to the end
        arrStrFeedDataset[fieldCount] = strLnBuff.substring(lastIndex, i);
      }
    }


    // Clear out string and counters to get ready for the next incoming string
    strLnBuff = "";
    fieldCount = 0;
    lastIndex = 0;


    Serial << "arrStrFeedDataset[0-7]: " << endl;
    for (int i = 0; i < FEEDFIELDS_NUM; i++)
    {
      Serial << arrStrFeedDataset[i] << endl;
    }

  }
  else
  {
    // if the file didn't open, print an error:
    gotTheFile = 0;
    Serial << "Error opening " << (fn) << endl;


  }

  //String arrStrFeedDataset[] = {feedDataId, feedAmbLight, feedAirTemp, feedAirHum, feedSoilTemp, feedSoilHum, feedAirPress, feedBattVolt};

  Serial << endl;
}
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
void write_SD_multiFieldsUU(String fn)
{

  String strTimeStamp = prep_strUUYYYYMMDDHHUpdatedT( RTC.get() );
  String strSensorVals = prep_strSensorVals();

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open(fn, FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile)
  {
    Serial << endl;
    Serial << "Writing to " << fn << ":" << endl;
    // make a string for assembling the data to log:
    String dataString = "";
    //    dataString += strUnitId;
    dataString += strTimeStamp;
    dataString += strSensorVals;
    delay(300);
    Serial << dataString << endl;
    myFile.println(dataString);

    // close the file:
    myFile.close(); // Close file when you're done to make sure all the data is written permanently!
    Serial << "done." << endl;
  }
  else
  {
    // if the file didn't open, print an error:
    //    Serial.print("error opening ");
    //    Serial.println(strFilename);
    Serial << "Error opening " << fn << endl;
  }
}
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
void write_SD_feedsRec(String recfn)
{


  String strTimeStamp = prep_strUUYYYYMMDDHHMMUpdatedT( RTC.get() );
  String strSensorVals = prep_strSensorVals();

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open(recfn, FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile)
  {
    Serial << endl;
    Serial << "Writing to " << recfn << ":" << endl;
    // make a string for assembling the data to log:
    String dataString = "";
    dataString += strUnitId;
    dataString += strTimeStamp;
    dataString += ",";

    for (int i = 0; i < 8; i++)
    {
      dataString += arrStrFeedDataset[i];
      dataString += ",";
    }

    dataString += atResult;
    dataString += ",";
    dataString += cregResult;
    dataString += ",";
    dataString += cgregResult;
    dataString += ",";
    dataString += strfeedResult;
    delay(300);
    Serial << dataString << endl;
    myFile.println(dataString);


    // close the file:
    myFile.close(); // Close file when you're done to make sure all the data is written permanently!
    Serial << "done." << endl;
  }
  else
  {
    //    Serial << "Error opening " << strFilename << endl;
    Serial << "Error opening " << recfn << endl;
  }
}
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
void write_SD_alarmsRec(String almfn, String almNum, String nextAlm) // nextSenseTime
{


  String strTimeStamp = prep_strUUYYYYMMDDHHMMUpdatedT( RTC.get() );
  String strSensorVals = prep_strSensorVals();

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open(almfn, FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile)
  {
    Serial << endl;
    Serial << "Writing to " << almfn << ":" << endl;
    // make a string for assembling the data to log:
    String dataString = "";

    dataString += almNum;
    dataString += ",";

    dataString += strUnitId;

    dataString += strTimeStamp;

    dataString += strSensorVals;

    dataString += ",";
    dataString += nextAlm;

    //    dataString += strfeedResult;
    delay(300);
    Serial << dataString << endl;
    myFile.println(dataString);


    // close the file:
    myFile.close(); // Close file when you're done to make sure all the data is written permanently!
    Serial << "done." << endl;
  }
  else
  {
    Serial << "Error opening " << almfn << endl;
  }
}
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////



