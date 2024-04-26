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

  Parameter::Setup(reader);

  
  int eos_type = Parameter::EOS_ID;
  Events event(eos_type);
  std::cout <<"1" <<std::endl;
  event.ReadandWrite();
  std::cout <<"2" <<std::endl;


}

