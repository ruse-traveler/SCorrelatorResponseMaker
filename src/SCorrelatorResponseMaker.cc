/// ---------------------------------------------------------------------------
/*! \file   SCorrelatorResponseMaker.cc
 *  \author Derek Anderson
 *  \date   04.30.2023
 *
 * A module to match truth to reconstructed
 * jets/particles to derive corrections for
 * an n-point energy correlation strength
 * function.
 */
/// ---------------------------------------------------------------------------

#define SCORRELATORRESPONSEMAKER_CC

// user includes
#include "SCorrelatorResponseMaker.h"
#include "SCorrelatorResponseMaker.io.h"
#include "SCorrelatorResponseMaker.sys.h"
#include "SCorrelatorResponseMaker.ana.h"

using namespace std;



namespace SColdQcdCorrelatorAnalysis {

  // ctor/dtor ================================================================

  // --------------------------------------------------------------------------
  //! Module ctor
  // --------------------------------------------------------------------------
  SCorrelatorResponseMaker::SCorrelatorResponseMaker(
    const string &name,
    const bool isComplex,
    const bool doDebug,
    const bool inBatch
  ) : SubsysReco(name) {

    // set standalone/complex mode
    if (isComplex) {
      m_inComplexMode    = true;
      m_inStandaloneMode = false; 
    } else {
      m_inComplexMode    = false;
      m_inStandaloneMode = true;
    }

    // set verbosity in complex mode
    if (m_inComplexMode) {
      m_verbosity = Verbosity();
    }

    // set debug/batch mode & print debug statement
    m_inDebugMode = doDebug;
    m_inBatchMode = inBatch;
    if (m_inDebugMode) PrintDebug(0);

    // set module name & announce start of folding
    m_moduleName = name;
    if (m_inStandaloneMode) PrintMessage(0);

  }  // end ctor(string, bool, bool)



  // --------------------------------------------------------------------------
  //! Module dtor
  // --------------------------------------------------------------------------
  SCorrelatorResponseMaker::~SCorrelatorResponseMaker() {

    // print debug statement
    if (m_inDebugMode) PrintDebug(1);

    // delete pointers to files
    if (!m_inTrueTree || !m_inRecoTree) {
      if (!m_inTrueTree) {
        delete m_inTrueFile;
        m_inTrueFile = NULL;
      }
      if (!m_inRecoTree) {
        delete m_inRecoFile;
        m_inRecoFile = NULL;
      }
      delete m_outFile;
      m_outFile = NULL;
    }

  }  // end dtor



  // F4A methods ==============================================================

  // --------------------------------------------------------------------------
  //! F4A module initialization
  // --------------------------------------------------------------------------
  int SCorrelatorResponseMaker::Init(PHCompositeNode*) {

    /* TODO init will go here */
    return Fun4AllReturnCodes::EVENT_OK;

  }  // end 'Init(PHCompositeNode*)'



  // --------------------------------------------------------------------------
  //! Process an event inside F4A
  // --------------------------------------------------------------------------
  int SCorrelatorResponseMaker::process_event(PHCompositeNode*) {

    /* TODO event processing will go here */
    return Fun4AllReturnCodes::EVENT_OK;

  }  // end 'process_event(PHCompositeNode*)'



  // --------------------------------------------------------------------------
  //! F4A module wind-down
  // --------------------------------------------------------------------------
  int SCorrelatorResponseMaker::End(PHCompositeNode*) {

    /* TODO end will go here */
    return Fun4AllReturnCodes::EVENT_OK;

  }  // end 'End(PHCompositeNode*)'



  // standalone-only methods ==================================================

  // --------------------------------------------------------------------------
  //! Standalone module initialization
  // --------------------------------------------------------------------------
  void SCorrelatorResponseMaker::Init() {

    // print debug statement
    if (m_inDebugMode) PrintDebug(2);

    // make sure standalone mode is on & open files
    if (m_inComplexMode) {
      PrintError(0);
      assert(m_inStandaloneMode);
    } else {
      OpenInputFiles();
    }
    OpenOutputFile();

    // announce files
    PrintMessage(1);

    // initialize input and output
    InitializeTrees();
    return;

  }  // end 'StandaloneInit()'



  // --------------------------------------------------------------------------
  //! Run analysis on input trees
  // --------------------------------------------------------------------------
  void SCorrelatorResponseMaker::Analyze() {

    // print debug statement
    if (m_inDebugMode) PrintDebug(3);

    // make sure standalone mode is on
    if (m_inComplexMode) {
      PrintError(0);
      assert(m_inStandaloneMode);
    }

    // announce start of analysis
    PrintMessage(2);

    DoMatching();
    return;

  }  // end 'StandaloneAnalyze()'



  // --------------------------------------------------------------------------
  //! Standalone module wind-down
  // --------------------------------------------------------------------------
  void SCorrelatorResponseMaker::End() {

    // print debug statement
    if (m_inDebugMode) PrintDebug(4);

    // make sure standalone mode is on & save output
    if (m_inComplexMode) {
      PrintError(0);
      assert(m_inStandaloneMode);
    } else {
      SaveOutput();
    }

    // announce end
    PrintMessage(3);
    return;

  }  // end 'StandaloneEnd()'

}  // end SColdQcdCorrelatorAnalysis namespace

// end ------------------------------------------------------------------------
