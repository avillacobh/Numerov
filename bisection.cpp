#include "bisection.h"

double bisection(std::vector<double> &LEFT, std::vector<double> &RIGHT, std::vector<double> &PHI, double E, double V0, double a, double xmin, double xmax, double xm, double h, double eps, double NSTEPS)
{
  double Er = E*1.15;
  double El = E*0.85;
  for(int i = 0; i< NSTEPS; i++) // Método de bisection para el intevalo hallado
    {
      double A2 = func (LEFT, RIGHT, PHI, Er, V0, a, xmin, xmax, xm, h);
      double A0 = func (LEFT, RIGHT, PHI, E, V0, a, xmin, xmax, xm, h);
      if (A0*A2 < 0)
	{
	  El = E;
	}else{
	Er = E;
	    }
      if (std::abs(Er-El) < eps)
	{
	  E = 0.5*(Er+El);
	  std::cout << "La raiz es E=" << E <<"\n";
	  numerov(LEFT, RIGHT, PHI, E, V0, a, xmin, xmax, xm, h);
	  print (PHI, E, V0, xmin, h);
	  return E;
	}
      E = 0.5*(Er+El);
      if (i == NSTEPS -1 )
	{
	  std::cout << "No hubo una buena convergencia\n";
	  return E;
	}
    }
}
