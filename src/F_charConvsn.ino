void convert_floatToChar(float floatVal)
{
  String stringVal = "";

  stringVal += String(int(floatVal)) + "." + String(getDecimal(floatVal)); //combining both whole and decimal part in string with a fullstop between them

  stringVal.toCharArray(charVal, stringVal.length() + 1);  //passing the value of the string to the character array
}
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
long getDecimal(float val)
{
  int intPart = int(val);
  long decPart = 100 * (val - intPart); // get only 2 decimal places from the float value

  if (decPart > 0)
  {
    return (decPart);       //return the decimal part of float number if it is available
  }
  else if (decPart < 0)
  {
    return ((-1) * decPart); //if negative, multiply by -1
  }
  else if (decPart = 0)
  {
    return (00);       //return 0 if decimal part of float number is not available
  }
}

