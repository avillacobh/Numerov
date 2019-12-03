#include "func.h"

double func (std::vector<double> &LEFT, std::vector<double> &RIGHT, std::vector<double> &PHI, double E, double V0, double a, double xmin, double xmax, double xm, double h)
{
  int i_xm = LEFT.size() - 1;
  numerov(LEFT, RIGHT, PHI, E, V0, a, xmin, xmax, xm, h);
  
  return (LEFT[i_xm] - RIGHT[0])/LEFT[i_xm];
}
