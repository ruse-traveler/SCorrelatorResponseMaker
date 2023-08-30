// ----------------------------------------------------------------------------
// 'DoStandaloneCorrelatorResponseMaking.C'
// Derek Anderson
// 04.30.2023
//
// Use this to run the SCorrelatorResponseMaker
// class in standalone mode.
// ----------------------------------------------------------------------------

#ifndef DOSTANDALONECORRELATORRESPONSEMAKING_C
#define DOSTANDALONECORRELATORRESPONSEMAKING_C

// standard c includes
#include <string>
#include <cstdlib>
#include <utility>
// user includes
#include "/sphenix/user/danderson/install/include/scorrelatorresponsemaker/SCorrelatorResponseMaker.h"

R__LOAD_LIBRARY(/sphenix/user/danderson/install/lib/libscorrelatorresponsemaker.so)

using namespace std;

// global constants
static const size_t NTrees = 2;



void DoStandaloneCorrelatorResponseMaking() {

  // io parameters
  const string sOutFile("test.root");
  const string sInFiles[NTrees] = {
    "../SCorrelatorJetTree/output/test/debug.testingTrkMatching.root",
    "../SCorrelatorJetTree/output/test/debug.testingTrkMatching.root"
  };
  const string sInTrees[NTrees] = {
    "TruthJetTree",
    "RecoJetTree"
  };

  // matching parameters
  const double               minMatchCstPercent = 0.2;
  const pair<double, double> qtJetMatchRange    = {0.2, 1.5};
  const pair<double, double> drJetMatchRange    = {0.,  0.4};

  // misc parameters
  const int  verbosity = 0;
  const bool isComplex = false;
  const bool doDebug   = false;
  const bool inBatch   = false;

  // do folding
  SCorrelatorResponseMaker *maker = new SCorrelatorResponseMaker("SCorrelatorResponseMaker", isComplex, doDebug, inBatch);
  maker -> SetVerbosity(verbosity);
  maker -> SetOutputFile(sOutFile);
  maker -> SetInputFiles(sInFiles[0], sInFiles[1]);
  maker -> SetInputTrees(sInTrees[0], sInTrees[1]);
  maker -> SetJetMatchQtRange(qtJetMatchRange);
  maker -> SetJetMatchDrRange(drJetMatchRange);
  maker -> Init();
  maker -> Analyze();
  maker -> End();

}

#endif

// end ------------------------------------------------------------------------
