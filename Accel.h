#include "WProgram.h"
#include "I2C.h"

class Accel : public I2C
{
  public:
    Accel();
    void init();
    void calibrate();
    void autoZero();
    
    void updateAll();
    
    float getXAngle();
    float getYAngle();
    float getZAngle();
    
    // Smoothed/compensated values
    float getRoll();
    float getPitch();
    float getYaw();
    
    // The raw values from the sensor
    int getRawRoll();
    int getRawPitch();
    int getRawYaw();
    
    float getSmoothFactor();
    
  private:
    I2C _i2c;
    
    int dataRaw[3]; // Raw and unfiltered accel data
    float dataSmoothed[3]; // Smoothed accel data
    int zero[3]; // Zero points for the accel axes
    
    float gConstant[3];
    float gB[3];
    
    float _smoothFactor; // 1.0 to not smooth, otherwise adjust as necessary
    
    float toDegrees(float);
};
