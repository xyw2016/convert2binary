#ifndef PARAMETER_H
#define PARAMETER_H
#ifndef HBARC
#define HBARC 0.197326979
#endif
#ifndef small_eps
#define small_eps 1e-16
#endif  
#ifndef M_PI_F
#define M_PI_F 3.1415926
#endif
#include <string>
#include "INIReader.h"




class INIReader;


namespace Parameter {


extern std::string PATHIN;
extern std::string PATHOUT;
extern int NX;
extern int NY;
extern int NZ;



extern double DX;
extern double DY;
extern double DZ;


extern double TAU0;
extern double TAU1;
extern double NT;

extern int EOS_ID;

extern int turn_on_rhob;
extern int turn_on_shear;
extern int turn_on_bulk;
extern int turn_on_diff;



void Setup(INIReader &reader);
}
#endif
