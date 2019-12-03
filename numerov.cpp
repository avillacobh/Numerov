#include "numerov.h"
#include "norma.h"

void numerov(std::vector<double> &LEFT, std::vector<double> &RIGHT, std::vector<double> &PHI, double E, double V0, double a, double xmin, double xmax, double xm, double h)
{
  const int i_max = (xmax - xmin)/h;
  const int i_mL = (xm-xmin)/h;
  const int i_mR = i_max - i_mL;
  const int i_a = (xmax - a)/h;
  const int i_amax = i_max - i_a;
  
  const double p = 0.4829; // 2m/(hbar^2)

  const double A1 = 5.0*h*h/12.0;
  const double A2 = h*h/12.0;

  const double b = std::sqrt(std::abs(E)*p);
  
  //Creación del vector k2
  std::vector<double> k2 (i_max + 1, E*p);

  for (int i = i_a; i <= i_amax; i++)
    {
      k2[i] = p*(E+V0);
    }

  ///* Condiciones de frontera *///
  
  LEFT[0] = std::exp(b*xmin);
  LEFT[1] = std::exp(b*(xmin + h));
  RIGHT[i_mR] = -std::exp(-b*xmax);
  RIGHT[i_mR - 1] = -std::exp(b*(-xmax + h));

  
  ///* Implementación del algoritmo numerov *///
  
  for (int i = 2; i <= i_mL; i++) // Numerov para la parte izquierda
    {
      LEFT[i] = (2.0*(1.0 - A1*k2[i-1])*LEFT[i-1] - (1.0 + A2*k2[i-2])*LEFT[i-2])/(1.0+A2*k2[i]);
    }

  
  for (int i = i_mR - 2; i >= 0; i--) // Numerov para la parte derecha
    {
      RIGHT[i] = (2.0*(1.0 - A1*k2[i_mL + i + 1])*RIGHT[i+1] - (1.0 + A2*k2[i_mL + i +2])*RIGHT[i + 2])/(1.0 + A2*k2[i_mL + i]); 
    }

  
  ///*Union de las funciones de onda*///

  for(int i = 0; i<= i_mL; i++) // izquierda
    {
      PHI[i] = LEFT[i];
    }

  for(int i = 1; i<= i_mR; i++) // derecha
    {
      PHI[i + i_mL] = RIGHT[i];
    }

  norma (PHI,h); // Normalizando la función de onda
}
