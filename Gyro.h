#include "WProgram.h"
#include "Definitions.h"
#include "I2C.h"

class Gyro : public I2C
{
  public:
    Gyro();
    void init();
    void autoZero();
    
    void updateAll();
    
    // Smoothed/compensated values
    int getTemp();
    float getRoll();
    float getPitch();
    float getYaw();
    
    // The raw values from the sensor
    int getRawRoll();
    int getRawPitch();
    int getRawYaw();
    
    void sleep();
    void unsleep();
    
  private:
    I2C _i2c;
    
    int temp; // Most recent temp (converted to degrees F)
    int dataRaw[3]; // Raw and unfiltered gyro data
    float dataSmoothed[3]; // Smoothed gyro data
    int zero[3]; // Zero points for the gyro axes
    
    float _scaleFactor; // How to convert raw sensor data to SI units
    
    boolean _sleeping;
};
