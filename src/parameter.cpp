#ifndef PARAMETER_CPP
#define PARAMETER_CPP
#include "parameter.h"
#include <iostream>

#include "INIReader.h"

namespace Parameter {

int NX=67;
int NY=67;
int NZ=1;


double DX=0.3;
double DY=0.3;
double DZ=0.3;

double TAU0 = 0.4;
double TAU1 = 0.4;
double NT   = 10;

int EOS_ID = 14;
int turn_on_rhob  = 1;
int turn_on_shear = 0;
int turn_on_bulk  = 0;
int turn_on_diff  = 0;

std::string PATHIN="./input";
std::string PATHOUT="./output";

void Setup(INIReader &reader) {
  PATHIN = reader.Get("Input", "PATHIN", PATHIN);
  PATHOUT = reader.Get("Input", "PATHOUT", PATHOUT);

  NX   = reader.GetInteger("Input", "NX", NX);
  NY   = reader.GetInteger("Input", "NY", NY);
  NZ   = reader.GetInteger("Input", "NZ", NZ);
  
  DX   = reader.GetReal("Input", "DX", DX);
  DY   = reader.GetReal("Input", "DY", DY);
  DZ   = reader.GetReal("Input", "DZ", DZ);
  
  TAU0 = reader.GetReal("Input", "TAU0", TAU0);
  TAU1 = reader.GetReal("Input", "TAU1", TAU1);
  NT = reader.GetReal("Input", "NT", NT);
  
  EOS_ID   = reader.GetInteger("Input", "EOS_ID", EOS_ID);
  turn_on_rhob   = reader.GetInteger("Input", "turn_on_rhob", turn_on_rhob);
  turn_on_shear   = reader.GetInteger("Input", "turn_on_shear", turn_on_shear);
  turn_on_bulk   = reader.GetInteger("Input", "turn_on_bulk", turn_on_bulk);
  turn_on_diff = reader.GetInteger("Input", "turn_on_diff", turn_on_diff);



  std::cout << "\n ****************************************** \n " ;
  std::cout << "\n The parameter sets\n" 
            << "  NX     = " << NX << "\n"
            << "  NY     = " << NY << "\n"
            << "  NZ     = " << NZ << "\n"
            << "  DX     = " << DX << "\n"
            << "  DY     = " << DY << "\n"
            << "  DZ     = " << DZ<< "\n"
            << "  TAU0   = " << TAU0 <<"\n"
            << "  TAU1   = " << TAU1 <<"\n"
            << "  NT     = " << NT <<"\n"
            << "  EOS_ID = " << EOS_ID <<"\n"
            
            << "  turn_on_rhob     = " << turn_on_rhob << "\n"
            << "  turn_on_shear     = " << turn_on_shear << "\n"
            << "  turn_on_bulk     = " << turn_on_bulk << "\n"
            << "  turn_on_diff     = " << turn_on_diff << "\n" <<  std::endl;
  std::cout << "\n ******************************************" ;
}
}


#endif
