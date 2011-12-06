#ifndef I2C_h
#define I2C_h

#include "WProgram.h"

class I2C
{
  public:
    I2C();
    
    void setAddress(byte);
    
    byte getAddressFromDevice();
    boolean validateDevice();
    byte writeSetting(byte, byte);
    byte sendReadRequest(byte);
    word readWord();
    word readWordFlip();
    byte readByte();
    void requestBytes(byte);
    
    byte readNextByte();
    word readNextWord();
    word readNextWordFlip();
    
  private:
    byte _address;
};

#endif
