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
#include "/sphenix/user/danderson/install/include/scorrelatorfolder/SCorrelatorFolder.h"

R__LOAD_LIBRARY(/sphenix/user/danderson/install/lib/libscorrelatorfolder.so)

using namespace std;

// global constants
static const size_t NTrees = 2;



void DoStandaloneCorrelatorFolding() {

  // io parameters
  const string sOutFile("test.root");
  const string sInFiles[NTrees] = {"../SCorrelatorJetTree/output/debug.testingTrkMatching.root", "../SCorrelatorJetTree/output/debug.testingTrkMatching.root"};
  const string sInTrees[NTrees] = {"TruthJetTree", "RecoJetTree"};

  // matching parameters
  const double               minMatchCstPercent = 0.2;
  const pair<double, double> qtJetMatchRange    = {0.2, 1.5};
  const pair<double, double> drJetMatchRange    = {0.,  0.4};

  // misc parameters
  const int  verbosity = 0;
  const bool isComplex = false;
  const bool doDebug   = true;
  const bool inBatch   = false;

  // do folding
  SCorrelatorFolder *folder = new SCorrelatorFolder("SCorrelatorFolder", isComplex, doDebug, inBatch);
  folder -> SetVerbosity(verbosity);
  folder -> SetOutputFile(sOutFile);
  folder -> SetInputFiles(sInFiles[0], sInFiles[1]);
  folder -> SetInputTrees(sInTrees[0], sInTrees[1]);
  folder -> SetJetMatchQtRange(qtJetMatchRange);
  folder -> SetJetMatchDrRange(drJetMatchRange);
  folder -> Init();
  folder -> Analyze();
  folder -> End();

}

#endif

// end ------------------------------------------------------------------------
