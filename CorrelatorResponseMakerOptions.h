// ----------------------------------------------------------------------------
// 'CorrelatorResponseMakerOptions.h'
// Derek Anderson
// 05.16.2024
//
// Options for the 'SCrrelatorResponseMaker' module.
// ----------------------------------------------------------------------------

#ifndef CORRELATORRESPONSEMAKEROPTIONS_H
#define CORRELATORRESPONSEMAKEROPTIONS_H 

// c++ utilities
#include <string>
#include <utility>
#include <optional>
// analysis utilities
#include "/sphenix/user/danderson/install/include/scorrelatorutilities/Types.h"
#include "/sphenix/user/danderson/install/include/scorrelatorutilities/Constants.h"
#include "/sphenix/user/danderson/install/include/scorrelatorresponsemaker/SCorrealtorResponseMakerConfig.h"

// make common namespaces implicit
using namespace std;
using namespace SColdQcdCorrelatorAnalysis;



namespace CorrelatorResponseMakerOptions {

  // options ------------------------------------------------------------------

  // io options
  const string sOutFile("test.root");
  const vector<string> sInFiles = {
    "../SCorrelatorJetTree/output/test/debug.testingTrkMatching.root",
    "../SCorrelatorJetTree/output/test/debug.testingTrkMatching.root"
  };
  const vector<string> sInTrees = {
    "RecoJetTree"
    "TruthJetTree"
  };

  // matching options
  const double               minMatchCstPercent = 0.2;
  const pair<double, double> qtJetMatchRange    = {0.2, 1.5};
  const pair<double, double> drJetMatchRange    = {0.,  0.4};

  // misc options
  const int  verbosity = 0;
  const bool isComplex = false;
  const bool doDebug   = false;
  const bool inBatch   = false;



  // set up configurations ----------------------------------------------------

  SCorrelatorResponseMakerConfig GetConfig() {

    // TODO simplify options!
    SCorrelatorResponseMaker cfg {
      .verbosity         = verbosity,
      .inDebugMode       = doDebug,
      .inBatchMode       = inBatch,
      .inComplexMode     = inComplexMode,
      .inStandaloneMode  = !inComplexMode,
      .outFileName       = sOutFile,
      .inRecoFileName    = sInFiles[0],
      .inTrueFileName    = sInFiles[1],
      .inRecoTreeName    = sInTrees[0],
      .inTrueTreeName    = sInTrees[1],
      .fracCstMatchRange = make_pair(minMatchCstPercent, 100.),
      .jetMatchQtRange   = qtJetMatchRange,
      .jetMatchDrRange   = drJetMatchRange
    };
    return cfg;

  }  // end 'GetRecoConfig(vector<string>, string, int)'

}

// end ------------------------------------------------------------------------
