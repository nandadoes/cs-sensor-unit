/*
 * cs_sensorUnit
 * 
 * 
 * 1) Read 7 paarameters (i.e. luminosity, barometric pressure, air temperature 
 * and humidity, soil temperature and humidity and approximated voltage level 
 * of the power supply), all of which are stored in an SD card and uploaded 
 * to a Thinkspeakan channel via a 3G communication shield once a day. 
 * 
 * 2) put Arduino MCU into sleep mode and wakes up by 2 alarms to perform
 * a series of events:   
 * 
 * Alarm 1 -  wake up MCU @ minute 0th of every hour. This is to read and store
 * all data including alarm event in text files in an SD card state before 
 * entering sleep mode. 
 * 
 * Alarm 2 - wake up MCU @ 23:10 every day to upload data to ThingSpeak and record 
 * alarm and 3G communication events in text files in the SD card. After that, 
 * it checks 3G shield's power state and attempts to powerit  off (several times 
 * since the 3G shield is having issue with power on/off feature of the original 
 * hardware). Before going into sleep mode, it sends out an sms notification to 2 
 * phone numbers if the sensed voltage is lower than a mininum threshold.
 * 
 *
 * Required hardware:
 * 1 x Arduino Mega
 * 1 x Adafruit BMP180 breakout
 * 1 x Adafruit INA219 breakout
 * 1 x Adafruit TLS5912 breakout
 * 1 x Chronodot RTC breakout
 * 2 x ST10 sensors
 * 1 x 2.5A/5V output power bank
 * 
 * 
 * Circuit building and set up:
 * See https://github.com/nandadoes/connectedSeeds
 * 
 * Modified from:
 * cs_sensorUnit_0_2_1.ino
 * yhtomitsy's gistfile1.ino <https://gist.github.com/mattfelsen/9467420>
 * Nick Gammon's Power saving techniques for microprocessors <http://www.gammon.com.au/forum/?id=11497>
 * Example sketches of required I2C, SPI, 3G and SD components. 
 * 
 * 
 *  Last modified: 2016-08-24  
 *  By: Nanda Khaorapapong
 *  Contact: nandadoes@gmail.com  
 *   
 *  Copyright (c) 2016 Nanda Khaorapapong and Connected Seeds  
 *  License: GNU GPLv3 license <https://www.gnu.org/licenses/gpl-3.0.en.html>
 * 
 */


#include <DS3232RTC.h>        //http://github.com/JChristensen/DS3232RTC
#include <Streaming.h>        //http://arduiniana.org/libraries/streaming/
#include <Time.h>
#include <TimeLib.h>
#include <Wire.h>             //http://arduino.cc/en/Reference/Wire
#include <Adafruit_Sensor.h>
#include "Adafruit_TSL2591.h"
#include <Adafruit_BMP085.h>
#include <SHT1x.h>
#include <avr/sleep.h>
#include "QuickStats.h"
#include <SPI.h>
#include <SD.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include <Adafruit_INA219.h>
// *************************************************************
//                Variables varied on each unit
// *************************************************************
const char charUnitId[] =  "01";
String strUnitId =   "01";
float V_BANK_THRES = 4.9;// 4.79;


// *************************************************************
//                        RTC varialbles
// *************************************************************

#define ALM_NOTI_PIN 7 // buzzer
#define SQW_PIN 18
const int INTRP_NUM = 5;


volatile boolean alarmIsrWasCalled = false;
int countAlm = 0;
String thisMonth;
int thisY, thisMonthInt, thisH, thisM, thisS, thisD;
int nextM, nextH, nextD, lastDateOfMonth;

int alm1FirstM = 0;
int alm2FirstM = alm1FirstM + 10;

int alm1FirstS = 0;
int alm2FirstS = 0;

//int feedDate;
int feedH = 23;
int feedM = alm2FirstM;
int feedS = alm2FirstS;

int senseM = alm1FirstM;
int senseS = alm1FirstS;

int INTVL_M_SHORT = 2;// ??????????????????????????????????????????????????????????????
int INTVL_H = 1; // 6; // ?????????????????????????????????????????????????????????????
int INTVL_D = 1; //3; // ??????????????????????????????????????????????????????????????
String strT = "";

// *************************************************************
//                        Timer varialbles
// *************************************************************

unsigned long ONEMIN = 60000;
unsigned long ONESEC = 1000;
unsigned long TENSEC = 10000;
unsigned long BTW_READ = 300;
unsigned long WARMUP_P = 300;


// *************************************************************
//              3G shield and communication variables
// *************************************************************
const int ONMOD_PWR_LED = A7;
int pwrLedVal = 0;

//Write here you SIM data
const char phone_number1[] = "07972799200"; // my number
const char phone_number2[] = "07800736525"; // Sara's number
char sms_toSend[25];
char charVal[5];

// Message for notifications
const char CHA_SMS[] = "02 needs manual power off.";
const char CHA_SMS_TEST[] = "Hello";
const char CHA_NW_REGIS[] = " failed gprs regis.";
const char CHA_V_LEV[] = "'s remaining V: ";
const char CHA_3G_PWR[] = " needs manual power off.";

const int MAX_SMS_LENGTH = 50;

// APN info for Giffgaff sim card
const char pin_number[] = "";
const char apn[] =  "giffgaff.com";
const char user_name[] = "giffgaff";
const char password[] = "";

// List API for all Thingspeak channels
char APIWriteKey[] = "abcdefghijklmnop"; // just a dummy api key to be replaced in assignment function
const char APIWriteKey1[] = "xxxxxxxxxxxxxxxx";  //  Seeds Guardian 1 : Lutfun's lablab beans
const char APIWriteKey2[] = "xxxxxxxxxxxxxxxx"; //  Seeds Guardian 2: Anwara's
const char APIWriteKey3[] = "xxxxxxxxxxxxxxxx"; //  Seeds Guardian 3: Lisa's green house
const char APIWriteKey4[] = "xxxxxxxxxxxxxxxx"; //  Seeds Guardian 4: Richard's Gren orach
const char APIWriteKey5[] = "xxxxxxxxxxxxxxxx"; //  Seeds Guardian 5: Nat Cordwainers
const char APIWriteKey6[] = "xxxxxxxxxxxxxxxx"; //  Seeds Guardian 6: [ready to be deployed]
const char APIWriteKey7[] = "xxxxxxxxxxxxxxxx"; //  Seeds Guardian 7: Lutfun's Kudo
const char APIWriteKey8[] = "xxxxxxxxxxxxxxxx"; //  Seeds Guardian 8: Halema's
const char APIWriteKey9[] = "xxxxxxxxxxxxxxxx"; //  Seeds Guardian 9: Sara's garden
const char APIWriteKey10[] = "xxxxxxxxxxxxxxxx"; //  Seeds Guardian 10: [got stolen]
const char APIWriteKey11[] = "xxxxxxxxxxxxxxxx"; //  Seeds Guardian 11: Normadic garden [to be deployed]
const char APIWriteKey12[] = "xxxxxxxxxxxxxxxx"; // Seeds Guardian 12: Zimbabwean association's
const char APIWriteKey13[] = "xxxxxxxxxxxxxxxx"; //  Seeds Guardian 13: [ready to be deployed]
const char APIWriteKey14[] = "xxxxxxxxxxxxxxxx"; //  Seeds Guardian 14: [ready to be deployed]
const char APIWriteKey15[] = "xxxxxxxxxxxxxxxx"; //  Seeds Guardian 15: Debbie & Lisa 2


char url[ ] = "api.thingspeak.com";
int port = 80;
int8_t answer;
int onModulePin = 2, aux;
int data_size = 0;
int end_file = 0;
char aux_str[100];
int x = 0;
long previous;
String strfeedResult = "";
String cregResult = "";
String cgregResult = "";
String atResult = "";
int8_t at, creg, cgreg = 0 ;
unsigned long PWRON_PERIOD = ONEMIN * 5;
unsigned long PWROFF_PERIOD = ONEMIN * 5;
int successFeedCount = 0;

boolean threeGIsOff = false;
// *************************************************************
//                 Battery sensor varialbles
// *************************************************************
int val = 0;       // variable for the A/D value
float pinVoltage = 0; // variable to hold the calculated voltage
float ratio = 2.00449438;  // Change this to match the MEASURED ration of the circuit
Adafruit_INA219 ina219;
#define AMPVOLT_PWR A0 // INA219's VCC
float V_THRES = V_BANK_THRES;

// *************************************************************
//                   Statistic varialbles
// *************************************************************
QuickStats stats; //initialize an instance of this class


// *************************************************************
//                        ST10 varialbles
// *************************************************************
#define sht1xClock 12
#define AIR_DAT  10
#define AIR_PWR  11
#define SOIL_DAT  8
#define SOIL_PWR  9


// *************************************************************
//                    Light sensor varialbles
// *************************************************************
#define LI_PWR 5
Adafruit_TSL2591 tsl = Adafruit_TSL2591(2591);


// *************************************************************
//                 Pressure sensor varialbles
// *************************************************************
#define AIRPRESS_PWR 4
Adafruit_BMP085 bmp;


// *************************************************************
//                   Sensor data variables
// *************************************************************

//int ambLight;
unsigned long ambLight;
float soilTemp, soilHum, airTemp, airHum, airPress, battVolt;
const int NUM_READINGS = 5;
float arrAmbLight[NUM_READINGS];
float arrAirTemp[NUM_READINGS];
float arrAirHum[NUM_READINGS];
float arrSoilTemp[NUM_READINGS];
float arrSoilHum[NUM_READINGS];
float arrAirPress[NUM_READINGS];
float arrBattVolt[NUM_READINGS];
float  modeAmbLight, modeAirTemp, modeAirHum, modeSoilTemp, modeSoilHum, modeAirPress, modeBattVolt;
const int FEEDFIELDS_NUM = 8;
const int FEEDS_NUM =  24;
String strFeedYear, strFeedMonth, strFeedD, strFeedH, strFeedM;
String arrStrFeedDataset[FEEDFIELDS_NUM];


// *************************************************************
//                      SD card varialbles
// *************************************************************
#define SD_SS 53 // SC to 53, SCK to 52, MOSI to 51, MISO to 50
File myFile;
String strFilename = "";
String feedRecFn = "FEEDS.TXT";
String alarmsRecFn = "ALARMS.TXT";
boolean gotTheFile = 0;


////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
void setup(void)
{

  Serial.begin(115200);

  Wire.begin();
  delay(100);
  // *************************************************************
  //                           INA219 setup
  // *************************************************************

  pinMode(AMPVOLT_PWR, OUTPUT);
  digitalWrite(AMPVOLT_PWR, 0);
  ina219.begin();
  Serial << "Set up INA219" << endl;
  delay(100);

  // *************************************************************
  //                          TSL2591 setup
  // *************************************************************

  pinMode(LI_PWR, OUTPUT);
  digitalWrite(LI_PWR, 1);
  delay(WARMUP_P);
  if (!tsl.begin())
  {
    Serial << "No TSL2591 found ... Check its wiring!" << endl;
    while (1);
  }
  digitalWrite(LI_PWR, 0);
  delay(100);

  // *************************************************************
  //                          BMP180 setup
  // *************************************************************

  pinMode(AIRPRESS_PWR, OUTPUT);
  digitalWrite(AIRPRESS_PWR, 1);
  delay(WARMUP_P);
  bmp.begin();

  if (!bmp.begin())
  {
    Serial << "No BMP180 found ... Check its wiring!" << endl;
    while (1)
    {
      //      Serial.println("while 1");
    }
  }
  digitalWrite(AIRPRESS_PWR, 0);
  delay(100);

  // *************************************************************
  //                         ST10 setup
  // *************************************************************

  pinMode(AIR_PWR, OUTPUT);
  pinMode(SOIL_PWR, OUTPUT);
  digitalWrite(AIR_PWR, 0);
  digitalWrite(SOIL_PWR, 0);
  delay(100);

  // *************************************************************
  //                        SD card setup
  // *************************************************************
  //  initialise_SD();

  Serial << "Initializing SD card..." << endl;
  // or the SD library functions will not work.
  pinMode(SD_SS, OUTPUT);
  if (!SD.begin(SD_SS)) {
    Serial << "initialization failed!" << endl;
    return;
  }
  Serial << "initialization done." << endl;
  delay(100);

  // *************************************************************
  //                      3G shield setup
  // *************************************************************
  pinMode(ONMOD_PWR_LED, INPUT);

  pinMode(onModulePin, OUTPUT);
  digitalWrite(onModulePin, 0);

  assign_apiKey();

  delay(100);

  Serial << "charUnitId: " << charUnitId << endl;
  delay(200);
  Serial << "strUnitId: " << strUnitId << endl;
  delay(200);
  // *************************************************************
  //                          RTC setup
  // *************************************************************
  pinMode(ALM_NOTI_PIN, OUTPUT);
  for (int i = 0; i < 3; i++)
  {
    beep(25);
  }
  //setSyncProvider() causes the Time library to synchronize with the
  //external RTC by calling RTC.get() every five minutes by default.
  setSyncProvider(RTC.get);
  Serial << "RTC Sync";
  if (timeStatus() != timeSet) {
    Serial << " FAIL!";
  }
  Serial << endl;

  printDateTime( RTC.get() );
  Serial << " --> Current RTC time." << endl;

  //Disable the default square wave of the SQW pin.
  RTC.squareWave(SQWAVE_NONE);

  //Attach an interrupt on the falling of the SQW pin.
  //digitalWrite(SQW_PIN, HIGH);    //redundant with the following line
  pinMode(SQW_PIN, INPUT_PULLUP);
  attachInterrupt(INTRP_NUM, alarmIsr, FALLING);
  delay(100);



  //Set Alarms
  get_currentTimeVariables( RTC.get() ); // vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

  RTC.setAlarm(ALM1_MATCH_MINUTES, alm1FirstS, alm1FirstM, 0, 1); // causes an alarm when the minutes and seconds match.
  RTC.alarm(ALARM_1);                   //ensure RTC interrupt flag is cleared
  RTC.alarmInterrupt(ALARM_1, true);


  // Set Alarm 2
  RTC.setAlarm(ALM2_MATCH_HOURS, 0, alm2FirstM, feedH, 1); // causes an alarm when the hours and minutes match.
  RTC.alarm(ALARM_2);                   //ensure RTC interrupt flag is cleared
  RTC.alarmInterrupt(ALARM_2, true);

  delay(100);

  Serial << "Next sense minute:" << alm1FirstM << endl;
  Serial << "Next upload time:" << feedH << ":" << alm2FirstM << ":0" << endl;
  Serial << "Num data points to upload:" << FEEDS_NUM << endl;

}
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
void loop(void)
{

  if (alarmIsrWasCalled)
  {
    get_currentTimeVariables( RTC.get() );



    if (RTC.alarm(ALARM_1))
    {
      Serial << endl;
      printDateTime( RTC.get() );
      Serial << " --> Alarm 1!" << endl;
      Serial << "==================" << endl;

      get_alm1Rt();
    }



    if (RTC.alarm(ALARM_2))
    {
      Serial << endl;
      printDateTime( RTC.get() );
      Serial << " --> Alarm 2 2 !" << endl;
      Serial << "==================" << endl;

      get_alm2Rt();
    }



    alarmIsrWasCalled = false;
    Serial.println("alarmIsrWasCalled = false; ");
  }


  Serial << "MCU entering sleep mode." << endl;
  delay(10);
  set_mcuToSleep();




}

