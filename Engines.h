#include "WProgram.h"
#include "Definitions.h"

class Engines
{
  public:
    Engines();
    void init();
    void allStop();
    void setEngineSpeed(int, int);
    int getEngineSpeed(int);
    void setAllSpeed(int);
    void setThrottle(int);
    int getThrottle();
    void arm(int);
    void disarm();
    boolean isArmed();
  
  private:
    int engines[4];
    int engine_speeds[4];
    int throttle;
    boolean _armed;
};
