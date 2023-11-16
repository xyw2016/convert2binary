#ifndef READER_CPP
#define READER_CPP

#include "reader.h"

Events::Events(int use_eos):NX(Parameter::NX), NY(Parameter::NY),NZ(Parameter::NZ),
                DX(Parameter::DX), DY(Parameter::DY),DZ(Parameter::DZ),
                TAU0(Parameter::TAU0), TAU1(Parameter::TAU1), NT(Parameter::NT),eos(use_eos){

}

Events::~Events(){  
}


void Events::ReadandWrite(){
  
  double DT = (TAU1-TAU0)/(NT);

  std::string filename = Parameter::PATHOUT  + "evolution_all_xyeta_kompost.dat";   
  std::cout<<" "<<filename<<std::endl; 

  for(int tid = 0; tid< NT-1; tid++ )
  {
    
    std::string out_open_mode;

    if (tid == 0) {
        out_open_mode = "wb";
    } else {
        out_open_mode = "ab";
    }


    FILE *out_file_xyz;
    out_file_xyz = fopen(filename.c_str(), out_open_mode.c_str());


    const int nVar_per_cell = (11 + Parameter::turn_on_rhob *2 + Parameter::turn_on_shear*5
                                  + Parameter::turn_on_bulk*1 + Parameter::turn_on_diff*3);
    
    const int output_nx        = NX;
    const int output_ny        = NY;
    const int output_nz        = NZ;
    const double output_dx     = DX;
    const double output_dy     = DY;
    const double output_dz     = DZ;
    const double output_xmin   = - (NX)*DX/2.;
    const double output_ymin   = - (NY)*DY/2.;
    const double output_zmin   = - (NZ)*DZ/2.;

     if (tid == 0) {
        float header[] = {
            static_cast<float>(0), static_cast<float>(DT),
            static_cast<float>(output_nx), static_cast<float>(output_dx),
            static_cast<float>(output_xmin),
            static_cast<float>(output_ny), static_cast<float>(output_dy),
            static_cast<float>(output_ymin),
            static_cast<float>(output_nz), static_cast<float>(output_dz),
            static_cast<float>(output_zmin),
            static_cast<float>(Parameter::turn_on_rhob),
            static_cast<float>(Parameter::turn_on_shear),
            static_cast<float>(Parameter::turn_on_bulk),
            static_cast<float>(Parameter::turn_on_diff),
            static_cast<float>(nVar_per_cell)};
        fwrite(header, sizeof(float), 16, out_file_xyz);
    }




    double tau = TAU0  + (tid)*DT;
    
    std::stringstream fnameinput;
    fnameinput<<Parameter::PATHIN<<"/kompost_EKT_"<<tid<<".music_init_flowNonLinear_pimunuTransverse_pimunuNS.txt";
    
    std::ifstream profile(fnameinput.str());
    if(profile.is_open()){
      std::cout <<" Start to read "<< fnameinput.str()<< std::endl;
    for(int iz = 0; iz < NZ; iz ++){
        std::string dummy;
        // read the information line
        std::getline(profile, dummy);
        std::vector<double> temp_profile_ed(NX*NY, 0.0);
        std::vector<double> temp_profile_pressure(NX*NY, 0.0);
        std::vector<double> temp_profile_T(NX*NY, 0.0);
        std::vector<double> temp_profile_cs2(NX*NY, 0.0);
        std::vector<double> temp_profile_utau(NX*NY, 0.0);
        std::vector<double> temp_profile_ux(NX*NY, 0.0);
        std::vector<double> temp_profile_uy(NX*NY, 0.0);
        std::vector<double> temp_profile_ueta(NX*NY, 0.0);
        std::vector<double> temp_profile_pitautau(NX*NY, 0.0);
        std::vector<double> temp_profile_pitaux(NX*NY, 0.0);
        std::vector<double> temp_profile_pitauy(NX*NY, 0.0);
        std::vector<double> temp_profile_pitaueta(NX*NY, 0.0);
        std::vector<double> temp_profile_pixx(NX*NY, 0.0);
        std::vector<double> temp_profile_pixy(NX*NY, 0.0);
        std::vector<double> temp_profile_pixeta(NX*NY, 0.0);
        std::vector<double> temp_profile_piyy(NX*NY, 0.0);
        std::vector<double> temp_profile_piyeta(NX*NY, 0.0);
        std::vector<double> temp_profile_pietaeta(NX*NY, 0.0);


           
        double density, dummy1, dummy2, dummy3;
        double ux, uy, utau, ueta;
        double pitautau, pitaux, pitauy, pitaueta;
        double pixx, pixy, pixeta, piyy, piyeta, pietaeta;
        for (int ix = 0; ix < NX; ix++) {
            for (int iy = 0; iy < NY; iy++) {
                int idx = iy + ix*NY;
                std::getline(profile, dummy);
                std::stringstream ss(dummy);
                ss >> dummy1 >> dummy2 >> dummy3
                   >> density >> utau >> ux >> uy >> ueta
                   >> pitautau >> pitaux >> pitauy >> pitaueta
                   >> pixx >> pixy >> pixeta >> piyy >> piyeta >> pietaeta;
                   ueta = ueta*tau;
                   temp_profile_ed    [idx] = density; //GeV/fm^3
                   temp_profile_ux    [idx] = ux;
                   temp_profile_uy    [idx] = uy;
                   temp_profile_ueta  [idx] = ueta; //tau*ueta
                   temp_profile_utau  [idx] = sqrt(1. + ux*ux + uy*uy + ueta*ueta);
                   temp_profile_pixx  [idx] = pixx;
                   temp_profile_pixy  [idx] = pixy;
                   temp_profile_pixeta[idx] = pixeta*tau; //fm^-4
                   temp_profile_piyy  [idx] = piyy;
                   temp_profile_piyeta[idx] = piyeta*tau;
                  
                   utau = temp_profile_utau[idx];
                  
                   double rhob=0.0;
                   temp_profile_pressure    [idx]=eos.get_pressure(density/HBARC,rhob)*HBARC; //GeV/fm^3
                   temp_profile_T           [idx]=eos.get_temperature(density/HBARC,rhob)*HBARC;//GeV
                   temp_profile_cs2         [idx]=eos.get_cs2(density/HBARC,rhob);
                 
                   temp_profile_pietaeta[idx] = (
                    (2.*(  ux*uy*temp_profile_pixy[idx]
                     + ux*ueta*temp_profile_pixeta[idx]
                     + uy*ueta*temp_profile_piyeta[idx])
                     - (utau*utau - ux*ux)*temp_profile_pixx[idx]
                     - (utau*utau - uy*uy)*temp_profile_piyy[idx])
                     /(utau*utau - ueta*ueta));
                   temp_profile_pitaux  [idx] = (1./utau
                     *(  temp_profile_pixx[idx]*ux
                     + temp_profile_pixy[idx]*uy
                     + temp_profile_pixeta[idx]*ueta));
                   temp_profile_pitauy  [idx] = (1./utau
                     *(  temp_profile_pixy[idx]*ux
                     + temp_profile_piyy[idx]*uy
                     + temp_profile_piyeta[idx]*ueta));
                   temp_profile_pitaueta[idx] = (1./utau
                     *(  temp_profile_pixeta[idx]*ux
                     + temp_profile_piyeta[idx]*uy
                     + temp_profile_pietaeta[idx]*ueta));
                   temp_profile_pitautau[idx] = (1./utau
                     *(  temp_profile_pitaux[idx]*ux
                     + temp_profile_pitauy[idx]*uy
                     + temp_profile_pitaueta[idx]*ueta));
        }
    }
    profile.close();

    

     for (int ix = 0; ix < NX; ix++) {
            for (int iy = 0; iy < NY; iy++) {
                int idx = iy + ix*NY;

                 float ideal[] = {static_cast<float>(tid),
                            static_cast<float>(ix),
                            static_cast<float>(iy),
                            static_cast<float>(iz),
                            static_cast<float>(temp_profile_ed[idx]),
                            static_cast<float>(temp_profile_pressure[idx]),
                            static_cast<float>(temp_profile_T[idx]),
                            static_cast<float>(temp_profile_cs2[idx]),
                            static_cast<float>(temp_profile_ux[idx]),
                            static_cast<float>(temp_profile_uy[idx]),
                            static_cast<float>(temp_profile_ueta[idx])};
                  
                  fwrite(ideal, sizeof(float), 11, out_file_xyz);

            
            
            }
     }
    }

    fclose(out_file_xyz);
    }
    else{
      std::cout <<" Can't find "<< fnameinput.str()<< std::endl;
    }



  }
  

}







#endif
