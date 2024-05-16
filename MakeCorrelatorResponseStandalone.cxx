// ----------------------------------------------------------------------------
// 'MakeCorrelatorResponseStandalone.cxx'
// Derek Anderson
// 04.30.2023
//
// Use this to run the SCorrelatorResponseMaker
// class in standalone mode.
// ----------------------------------------------------------------------------

#ifndef MAKECORRELATORRESPONSESTANDALONE_CXX
#define MAKECORRELATORRESPONSESTANDALONE_CXX

// standard c includes
#include <string>
#include <cstdlib>
#include <utility>
// user includes
#include "/sphenix/user/danderson/install/include/scorrelatorresponsemaker/SCorrelatorResponseMaker.h"
#include "/sphenix/user/danderson/install/include/scorrelatorresponsemaker/SCorrelatorResponseMakerConfig.h"
#include "EnergyCorrelatorOptions.h"

// make common namespaces implicit
using namespace std;

// load libraries
R__LOAD_LIBRARY(/sphenix/user/danderson/install/lib/libscorrelatorresponsemaker.so)



// macro body -----------------------------------------------------------------

void MakeCorrelatorResponseStandalone(const bool doBatch = false, const int verbosity = 0) {

  // get module configuration
  SCorrealtorResponseMakerConfig cfg = CorrelatorResponseMakerOptions::GetConfig(doBatch, verbosity);

  // construct correlator response tree
  SCorrelatorResponseMaker* maker = new SCorrelatorResponseMaker(cfg);
  maker -> Init();
  maker -> Analyze();
  maker -> End();
  return;

}

#endif

// end ------------------------------------------------------------------------
