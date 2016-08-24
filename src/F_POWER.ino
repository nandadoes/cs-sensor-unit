void power_offDoubleCheckStatus(void)
{
  // Max time: 2 min and 30 sec
  Serial << "Double check 3G sheield power ..." << endl;
  delay(3000);

  power_offOppOn_2(ONEMIN / 2);
  delay(3000);

  // Double check if 3G is off without time out
  // but restart the operation every minute.
  unsigned long startPowerCheckTime = millis();
  while ((threeGIsOff == false) && (startPowerCheckTime <= ONEMIN * 5) )
  {

    Serial << "while (threeGIsOff == false)" << endl;
    Serial << "Double checking 3G shield power" << endl;
    unsigned long startOffTime = millis();
    while (millis() - startOffTime <= ONEMIN * 2)
    {

      delay(3000);
      power_offOppOn_2(ONEMIN);

      if (threeGIsOff == true)
      {
        break;
      }
    }

  }

}
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
void power_offOppOn_2(unsigned long t)
{

  threeGIsOff = false;


  Serial << "Checking power ..." << endl;

  uint8_t answer = 0;

  // checks if the module is started
  answer = send_atCommand("AT", "OK", 2000);
  if (answer == 1)
  {
    Serial << "It is ON." << endl;
    // power on pulse
    digitalWrite(onModulePin, HIGH);
    delay(5000);
    digitalWrite(onModulePin, LOW);

    // waits for an answer from the module
    unsigned long startTime = millis();
    while ( (answer == 1) && (millis() - startTime <= t) )
    {
      // Send AT every two seconds and wait for the answer
      answer = send_atCommand("AT", "OK", 2000);

      if (answer == 0)
      {
        threeGIsOff = true;
        break;
      }

    }
  }
  else
  {
    Serial << "It is OFF" << endl;
    threeGIsOff = true;

  }

}
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
void power_onBreakNew(unsigned long t)
{
  uint8_t answer = 0;

  // checks if the module is started
  answer = send_atCommand("AT", "OK", 3000);
  //  Serial.print("answer: ");
  //  Serial.println(answer);

  if (answer == 0) // if it's off
  {

    // waits for an answer from the module
    unsigned long startTime = millis();
    while ((millis() - startTime <= t) &&  (answer == 0))

    {


      // power on pulse
      digitalWrite(onModulePin, HIGH);
      delay(3000);
      digitalWrite(onModulePin, LOW);
      delay(3000);

      // Send AT every two seconds and wait for the answer
      answer = send_atCommand("AT", "OK", 2000);

      delay(50);
      atResult = "0";
      at = 0;
      delay(50);

      if (answer == 1)
      {
        atResult = "1";
        at = 1;
        delay(50);
        Serial << "break power_onBreak" << endl;
        break;
      }
    }
    Serial << "out of while loop" << endl;

  }
  else
  {
    atResult = "1";
    at = 1;
    delay(50);
  }

}
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

void set_mcuToWakup(void)
{
  // execute code here after wake-up before returning to the loop() function
  // timers and code using timers (serial.print and more...) will not work here.
  // we don't really need to execute any special functions here, since we
  // just want the thing to wake up

  //  Serial<<"Woke up"endl;
  //  beep(50);
}
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
void set_mcuToSleep(void)
{

  set_sleep_mode(SLEEP_MODE_PWR_DOWN);    // sleep mode is set here
  sleep_enable();                         // enables the sleep bit in the mcucr register

  // Disable other power consuming features
  power_adc_disable(); // ADC converter
  power_spi_disable(); // SPI
  power_usart0_disable();// Serial (USART)
  power_timer0_disable();// Timer 0
  power_timer1_disable();// Timer 1
  power_timer2_disable();// Timer 2


  //  attachInterrupt(0, wakeUpNow, FALLING); // use interrupt 0 (pin 2) and run function
  attachInterrupt(INTRP_NUM, alarmIsr, FALLING);
  sleep_mode();                           // here the device is actually put to sleep!!
  // THE PROGRAM CONTINUES FROM HERE AFTER WAKING UP

  // Enable other power consuming features
  power_adc_enable(); // ADC converter
  power_spi_enable(); // SPI
  power_usart0_enable(); // Serial (USART)
  power_timer0_enable(); // Timer 0
  power_timer1_enable(); // Timer 1
  power_timer2_enable(); // Timer 2

  sleep_disable();         // first thing after waking from sleep: disable sleep...

  detachInterrupt(INTRP_NUM);      // disables interrupt 0 on pin 2 so the wakeUpNow code will not be executed during normal running time.
}



