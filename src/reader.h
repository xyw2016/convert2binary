#ifndef READER_H
#define READER_H
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <chrono>
#include <random>
#include <map>
#include <iomanip>

#include "parameter.h"
#include "eos.h"



class Events{

    public:

    Events(int use_eos);

    ~Events();

    void ReadandWrite();

    private:

    const int NX;
    const int NY;
    const int NZ;



    const double DX;
    const double DY;
    const double DZ;


    const double TAU0;
    const double TAU1;
    const double NT;

    EOS eos;

    
};


#endif
