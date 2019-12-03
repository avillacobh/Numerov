#include "print.h"

void print( const std::vector<double> &PHI, const double E, const double V0, const double xmin, const double h)
{
  std::string name = "E=" + std::to_string(E) + "-V0=" + std::to_string(V0) + ".txt";
    
  const int size = PHI.size();
  
  std::ofstream fout (name);
  for(int ii =0 ; ii < size ; ii++)
    {
      fout << ii*h + xmin << "\t" << PHI[ii] << "\n";
    }
  fout.close();
}
