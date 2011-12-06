#include "WProgram.h"

// Convert from Gs to Meters Per Second Squared (and vice-versa)
#define G_2_MPS2(g) (g * 9.80665)
#define MPS2_2_G(m) (m * 0.10197162)

void isort(int *, byte);
int findMedian(int *, byte);
float filterSmooth(float, float, float);
