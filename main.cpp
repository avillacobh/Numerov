#include "numerov.h"
#include "func.h"
#include "print.h"
#include "bisection.h"

int main (void)
{
  const double xmin = -4.0, xmax = 4.0;
  const double a = 2.0;// Mitad del ancho del pozo
  const double xm = -1.0; // Punto de matching
  const double V0 = 30.0; //Altura del pozo de potencial
  const double E0 = -28.0;
  const double h = 0.0004; //Tamaño de pasos en x

  const double eps = 1.0e-7; // Precisión
  const double delta = 0.01;
  const int NSTEPS = 1.0e6; // Máximo de pasos
    
  ///* Hallanado tamaño de los vectores *///
  const int size = (xmax -xmin)/h;
  const int size_left = (xm - xmin)/h;
  const int size_right = size - size_left;

  ///*Inicializando los vectores*///
  std::vector<double> PHI(size + 1, 0.0);// Vector de la función de onda
  std::vector<double> LEFT(size_left +1, 0.0); //Parte izquierda
  std::vector<double> RIGHT(size_right+ 1, 0.0); // Parte derecha

  double E = E0;
  double El = E-delta;
  double Er = E+delta;

  for(int ii = 0; ii < NSTEPS; ii++) // Buscando donde se encuentra la raiz
    {
     
      double A1 = func (LEFT, RIGHT, PHI, El, V0, a, xmin, xmax, xm, h);
      double A2 = func (LEFT, RIGHT, PHI, Er, V0, a, xmin, xmax, xm, h);
      
      if(A1*A2 >= 0){
	std::cout << "No hay una raiz cercanca a E= " << E << "\n";
	El = Er;
	Er = El + delta ;
	E = 0.5*(Er+El);
      }else{
	E = 0.5*(Er+El);
	std::cout<< "Se encontró una raiz cerca de E= " << E << std::endl;
	E = bisection(LEFT, RIGHT, PHI, E, V0, a, xmin, xmax, xm, h, eps, NSTEPS); 
	break;
      }
      if(ii == NSTEPS - 1)  std::cout << "No se encontró una raíz en el dominio \n"; 
    }
  
  return 0;
}


