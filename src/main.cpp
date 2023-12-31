#include <iostream>
#include <cstring>
//#include <omp.h>

//input file parser
#include "INIReader.h"

#include "parameter.h"
#include "reader.h"


int main(int argc, char **argv) {
  // Try to open input file
  if (argc < 2) {
    std::cerr << "Error: ** " << argv[0] << " ** no input filename " << std::endl;
    std::cerr << "USAGE:" << std::endl;
    std::cerr << "    " << argv[0] << " setup.ini" << std::endl;
    exit(EXIT_FAILURE);
  }

  INIReader reader(argv[1]) ;
  if (reader.ParseError()){
    std::cerr << "Error: ** " << argv[0] << " ** failed to open " << argv[1] << std::endl;
    exit(EXIT_FAILURE);
  }

  std::cout<< "Config loaded from 'test.ini': NX="
              << reader.GetInteger("input", "NX", -1) << ", name="
              << reader.GetInteger("input", "NY", -1) << ", name="
              << reader.GetInteger("input", "NZ", -1) << ", name=";
              
  Parameter::Setup(reader);

  std::cout<< Parameter::NX<<std::endl;
  
  int eos_type = Parameter::EOS_ID;
  Events event(eos_type);
  event.ReadandWrite();


}

