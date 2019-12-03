#include "numerov.h"
#include "print.h"
#include "func.h"
#include <vector>

double bisection(std::vector<double> &LEFT, std::vector<double> &RIGHT, std::vector<double> &PHI, double E, double V0, double a, double xmin, double xmax, double xm, double h, double eps, double NSTEPS); 
