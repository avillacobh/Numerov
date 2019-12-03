#include "norma.h"

void norma (std::vector<double> &PHI, double h)
{
  //Normalización
  
  double s = 0.0;
  int i_max = PHI.size();
  
  for(int i = 0; i < i_max; i++)
    {
      s += PHI[i]*PHI[i]*h;
    }
  
  s = std::sqrt(s);
  
  for(int i = 0; i < i_max; i++)
    {
      PHI[i]= PHI[i]/s;
    }
}
