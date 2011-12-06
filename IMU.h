#include "WProgram.h"
#include "Definitions.h"

class IMU
{
  public:
    IMU();
    
    void update(int, float, float, float, float, float, float, float);
    
    float getRoll();
    float getPitch();
    float getHeading();
  
  private:
    void updateAxis(byte, int, float, float);
  
    float data[3];
    
    float _a; // How much bias to accel vs gyro?
    float _b;
    
    float _dtGyro; // Update rate of the gyro
};
