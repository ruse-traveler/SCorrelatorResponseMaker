/// ---------------------------------------------------------------------------
/*! \file   SCorrelatorResponseMakerConfig.h
 *  \author Derek Anderson
 *  \date   05.16.2024
 *
 *  Configuration struct for 'SCorrelatorResponseMaker' module.
 */
/// ---------------------------------------------------------------------------

#ifndef SENERGYCORRELATORCONFIG_H
#define SENERGYCORRELATORCONFIG_H

// make common namespaces implicit
using namespace std;



namespace SColdQcdCorrelatorAnalysis {

  // --------------------------------------------------------------------------
  //! User options for module
  // --------------------------------------------------------------------------
  struct SCorrelatorResponseMakerConfig {

    // system members
    int    verbosity      {0};
    bool   inDebugMode    {false};
    bool   inBatchMode    {false};
    bool   isLegacyIO     {true};  // TODO remove when ready
    string moduleName     {"SCorrelatorResponseMaker"};
    string inTrueFileName {""};
    string inRecoFileName {""};
    string inTrueTreeName {""};
    string inRecoTreeName {""};
    string outFileName    {""};

    // matching options
    /* TODO probably need
     *  - toggle cst analysis on/off
     *  - toggle matching via cst ID vs. dr/qt
     *  - toggle matching via jets dr/qt vs. cst
     *    (ID or dr/qt)
     */

    // matching cuts
    pair<double, double> fracCstMatchRange {0., 1.};
    pair<double, double> jetMatchQtRange   {0., 10.};
    pair<double, double> cstMatchQtRange   {0., 10.};
    pair<double, double> jetMatchDrRange   {0., 10.};
    pair<double, double> cstMatchDrRange   {0., 10.};

    // jet/cst cuts
    pair<Types::JetInfo, Types::JetInfo> jetAccept;
    pair<Types::CstInfo, Types::CstInfo> cstAccept;

  };

}  // end SColdQcdCorrelatorAnalysis namespace

#endif

// end ------------------------------------------------------------------------
