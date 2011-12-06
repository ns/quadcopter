#include "WProgram.h"
#include "Definitions.h"

#define WINDUP_GUARD_GAIN 500.0

class PID
{
  public:
    PID();
    PID(float, float, float);
    
    float getP();
    float getI();
    float getD();
    
    void setP(float);
    void setI(float);
    void setD(float);
    
    float updatePID(float, float, float);
    
    void resetError();
  
  private:
    float pgain, igain, dgain; 
    float pTerm, iTerm, dTerm;
    
    float iState;
    float last;
};
