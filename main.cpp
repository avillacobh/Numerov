#include "numerov.h"
#include "func.h"
#include "print.h"

int main (void)
{
  const double xmin = -4.0, xmax = 4.0;
  const double a = 2;// Mitad del ancho del pozo
  const double xm = -1; // Punto de matching
  const double V0 = 10.0; //Altura del pozo de potencial
  const double E0 = 1.0;
  const double h = 0.004; //Tamaño de pasos en x

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

      if(A1*A2 > 0){
	std::cout << "No hay una raiz cercanca a E= " << E << "\n";
	El = Er;
	Er = El + delta ;
	E = 0.5*(Er+El);
      }else{
	E = 0.5*(Er+El);
	std::cout<< "Se encontró una raiz cerca de E= " << E << std::endl;
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
		break;
	      }
	    E = 0.5*(Er+El);
	  }
	break;
      }
      if(ii == NSTEPS - 1)  std::cout << "No se encontró una raíz en el dominio \n"; 
    }
  

  return 0;
}


