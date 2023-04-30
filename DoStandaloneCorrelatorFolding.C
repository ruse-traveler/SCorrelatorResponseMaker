// ----------------------------------------------------------------------------
// 'DoStandaloneCorrelatorFolding.C'
// Derek Anderson
// 04.30.2023
//
// Use this to run the SCorrelatorFolder
// class in standalone mode.
// ----------------------------------------------------------------------------

#ifndef DOSTANDALONECORRELATORFOLDING_C
#define DOSTANDALONECORRELATORFOLDING_C

// standard c includes
#include <string>
#include <cstdlib>
#include <utility>
// user includes
#include "/sphenix/user/danderson/install/include/scorrelatorjettree/SCorrelatorFolder.h"

R__LOAD_LIBRARY(/sphenix/user/danderson/install/lib/libscorrelatorfolder.so)

using namespace std;



void DoStandaloneCorrelatorFolding() {

  // matching parameters
  const pair<double, double> qtJetRange = {0.5,  1.3};
  const pair<double, double> drJetRange = {0.,   jetRes};
  const pair<double, double> qtCstRange = {0.15, 1.5};
  const pair<double, double> drCstRange = {0.,   2. * jetRes};

}

#endif

// end ------------------------------------------------------------------------
