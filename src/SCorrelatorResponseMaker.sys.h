/// ---------------------------------------------------------------------------
/*! \file   SCorrelatorResponseMaker.sys.h
 *  \author Derek Anderson
 *  \date   04.30.2023
 *
 * A module to match truth to reconstructed
 * jets/particles to derive corrections for
 * an n-point energy correlation strength
 * function.
 */
/// ---------------------------------------------------------------------------

#pragma once

using namespace std;



// system methods =============================================================

namespace SColdQcdCorrelatorAnalysis {

  // --------------------------------------------------------------------------
  //! Initialize input/output trees
  // --------------------------------------------------------------------------
  void SCorrelatorResponseMaker::InitializeTrees() {

    // print debug statement
    if (m_config.inDebugMode) PrintDebug(20);

    // check for trees
    if (!m_inTrueTree) {
      PrintError(1);
      assert(m_inTrueTree);
    }
    if (!m_inRecoTree) {
      PrintError(2);
      assert(m_inRecoTree);
    }
    m_fTrueCurrent = -1;
    m_fRecoCurrent = -1;
    m_inTrueTree   -> SetMakeClass(1);
    m_inRecoTree   -> SetMakeClass(1);

    /* TODO use structs instead */

    // initialize response tree
    m_matchTree = new TTree("ResponseTree", "A tree of matched truth-reco. events");
    /* TODO initialize tree with struct */

    // announce tree setting
    if (m_config.isStandalone) PrintMessage(5);
    return;

  }  // end 'InitializeTree()'



  // --------------------------------------------------------------------------
  //! Print standard operation messages
  // --------------------------------------------------------------------------
  void SCorrelatorResponseMaker::PrintMessage(const uint32_t code, const uint64_t iEvt, const pair<uint64_t, uint64_t> nEvts) {

    // print debug statement
    if (m_config.inDebugMode && (m_config.verbosity > 5)) PrintDebug(21);

    switch (code) {
      case 0:
        cout << "\n  Beginning correlator folding..." << endl;
        break;
      case 1:
        cout << "    Initializing folder:\n"
             << "      input truth file = " << m_config.inTrueFileName << "\n"
             << "      input reco file  = " << m_config.inRecoFileName
             << endl;
        break;
      case 2:
        cout << "    Beginning analysis." << endl;
        break;
      case 3:
        cout << "  Correlator folding complete!\n" << endl;
        break;
      case 4:
        cout << "      Saved output." << endl;
        break;
      case 5:
        cout << "    Initialized input trees:\n"
             << "      input truth tree = " << m_config.inTrueTreeName << "\n"
             << "      input reco tree  = " << m_config.inRecoTreeName
             << endl;
        break;
      case 6:
        cout << "    Beginning event loop: " << nEvts.first << " truth events and " << nEvts.second << " reconstructed events to process." << endl;
        break;
      case 7:
        if (iEvt == nEvts.first) {
          cout << "      Processing event " << iEvt << "/" << nEvts.first << "..." << endl;
        } else {
          cout << "      Processing event " << iEvt << "/" << nEvts.first << "...\r" << flush;
        }
        break;
      case 8:
        cout << "    Finished event loop." << endl;
        break;
      default:
        PrintError(code);
        break;
    }
    return;

  }  // end 'PrintMessage(uint32_t, uint64_t, pair<uint64_t, uint64_t>)'



  // --------------------------------------------------------------------------
  //! Print debugging messages
  // --------------------------------------------------------------------------
  void SCorrelatorResponseMaker::PrintDebug(const uint32_t code) {

    // print debug statement
    if (m_config.inDebugMode && (m_config.verbosity > 7)) {
      cout << "SCorrelatorResponseMaker::PrintDebug(uint32_t) printing a debugging statement..." << endl;
    }

    switch (code) {
      case 0:
        cout << "SCorrelatorResponseMaker::SCorrelatorResponseMaker() constructing folder..." << endl;
        break;
      case 1:
        cout << "SCorrelatorResponseMaker::~SCorrelatorResponseMaker() destructing folder..." << endl;
        break;
      case 2:
        cout << "SCorrelatorResponseMaker::Init() initializing in standalone mode..." << endl;
        break;
      case 3:
        cout << "SCorrelatorResponseMaker::Analyze() running analysis in standalone mode..." << endl;
        break;
      case 4:
        cout << "SCorrelatorResponseMaker::End() ending in standalone mode..." << endl;
        break;
      case 5:
        cout << "SCorrelatorResponseMaker::SetInputNodes(string&, string&) setting input node names..." << endl;
        break;
      case 6:
        cout << "SCorrelatorResponseMaker::SetInputFiles(string&, string&) setting input file names..." << endl;
        break;
      case 7:
        cout << "ScorrelatorResponseMaker::SetInputTrees(string&, string&) setting input tree names..." << endl;
        break;
      case 8:
        cout << "SCorrelatorResponseMaker::SetJetMatchQtRange(pair<double, double>) setting jet-matching qT range..." << endl;
        break;
      case 9:
        cout << "SCorrelatorResponseMaker::SetJetMatchDrRange(pair<double, double>) setting jet-matching dR range..." << endl;
        break;
      case 10:
        cout << "SCorrelatorResponseMaker::GetJetMatchQtRange() grabbing jet-matching qT range..." << endl;
        break;
      case 11:
        cout << "SCorrelatorResponseMaker::GetJetMatchDrRange() grabbing jet-matching dR range..." << endl;
        break;
      case 12:
        cout << "SCorrelatorResponseMaker::GrabInputNodes() grabbing input nodes..." << endl;
        break;
      case 13:
        cout << "SCorrelatorResponseMaker::OpenInputFiles() opening input files..." << endl;
        break;
      case 14:
        cout << "SCorrelatorResponseMaker::OpenOutputFile() opening output file..." << endl;
        break;
      case 15:
        cout << "SCorrelatorResponseMaker::OpenFile() opening a single file..." << endl;
        break;
      case 16:
        cout << "SCorrelatorResponseMaker::SaveOutput() saving output..." << endl;
        break;
      case 17:
        cout << "SCorrelatorResponseMaker::DoMatching() matching jets..." << endl;
        break;
      case 18:
        cout << "SCorrelatorResponseMaker::IsJetGoodMatch(double, double) checking if jet match is good..." << endl;
        break;
      case 19:
        cout << "SCorrelatorResponseMaker::InitializeAddresses() initializing members..." << endl;
        break;
      case 20:
        cout << "SCorrelatorResponseMaker::InitializeTrees() initializing trees..." << endl;
        break;
      case 21:
        cout << "SCorrelatorResponseMaker::PrintMessage(uint32_t) printing a message..." << endl;
        break;
      case 22:
        cout << "SCorrelatorResponseMaker::PrintError(uint32_t) printing an error..." << endl;
        break;
      case 23:
        cout << "SCorrelatorResponseMaker::CheckCriticalParameters() checking critical parameters..." << endl;
        break;
      case 24:
        cout << "SCorrelatorResponseMaker::GetEntry(uint64_t, TTree*) grabbing entry from a tree..." << endl;
        break;
      case 25:
        cout << "SCorrelatorResponseMaker::LoadTree(uint64_t, TTree*, int) loading a tree..." << endl;
        break;
      default:
        PrintError(code);
        break;
    }
    return;

  }  // end 'PrintDebug(uint32_t)'



  // --------------------------------------------------------------------------
  //! Print error messages
  // --------------------------------------------------------------------------
  void SCorrelatorResponseMaker::PrintError(const uint32_t code, const uint64_t iEvt) {

    // print debug statement
    if (m_config.inDebugMode && (m_config.verbosity > 5)) PrintDebug(22);

    switch (code) {
      case 0:
        cerr << "PANIC: trying to call standalone method in complex mode! Aborting!\n" << endl;
        break;
      case 1:
        cerr << "PANIC: couldn't open input file! Aborting!\n" << endl;
        break;
      case 2:
        cerr << "PANIC: no input truth tree! Aborting!\n" << endl;
        break;
      case 3:
        cerr << "PANIC: no input reco tree! Aborting!\n" << endl;
        break;
      case 4:
        cerr << "WARNING: issue with entry " << iEvt << " in truth tree! Aborting event loop!" << endl;
        break;
      case 5:
        cerr << "WARNING: issue with entry " << iEvt << " in reco tree! Aborting event loop!" << endl;
        break;
      default:
        cerr << "WARNING: unknown status code!\n"
             << "         code = " << code
             << endl;
        break;
    }
    return;

  }  // end 'PrintError(unint32_t, uint64_t)'



  // --------------------------------------------------------------------------
  //! Check critical parameters to ensure they were set
  // --------------------------------------------------------------------------
  bool SCorrelatorResponseMaker::CheckCriticalParameters() {

    // print debugging statement
    if (m_config.inDebugMode) PrintDebug(23); 

    /* TODO checking goes here */
    return true;

  }  // end 'CheckCriticalParameters()'

}  // end SColdQcdCorrelatorAnalysis namespace

// end ------------------------------------------------------------------------
