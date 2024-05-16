// ----------------------------------------------------------------------------
// 'SCorrelatorResponseMakerConfig.h'
// Derek Anderson
// 05.16.2024
//
// Configuration struct for 'SCorrelatorResponseMaker' module.
// ----------------------------------------------------------------------------

#ifndef SENERGYCORRELATORCONFIG_H
#define SENERGYCORRELATORCONFIG_H

// make common namespaces implicit
using namespace std;



namespace SColdQcdCorrelatorAnalysis {

  // SCorrelatorResponseMakerConfig definition --------------------------------

  struct SCorrelatorResponseMakerConfig {

    // system members
    int    verbosity        = 0;
    bool   inDebugMode      = false;
    bool   inBatchMode      = false;
    bool   inComplexMode    = false;
    bool   inStandaloneMode = true;
    string moduleName       = "";
    string inTrueFileName   = "";
    string inRecoFileName   = "";
    string inTrueNodeName   = "";
    string inRecoNodeName   = "";
    string inTrueTreeName   = "";
    string inRecoTreeName   = "";
    string outFileName      = "";

    // matching options
    pair<float, float>   fracCstMatchRange = {0., 1.};
    pair<double, double> jetMatchQtRange   = {0., 10.};
    pair<double, double> jetMatchDrRange   = {0., 10.};

  };

}  // end SColdQcdCorrelatorAnalysis namespace

#endif

// end ------------------------------------------------------------------------
