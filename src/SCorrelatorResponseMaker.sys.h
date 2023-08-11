// ----------------------------------------------------------------------------
// 'SCorrelatorResponseMaker.sys.h'
// Derek Anderson
// 01.27.2023
//
// A module to match truth to reconstructed
// jets/particles to derive corrections for
// an n-point energy correlation strength
// function.
// ----------------------------------------------------------------------------

#pragma once

using namespace std;



// system methods -------------------------------------------------------------

void SCorrelatorResponseMaker::InitializeAddresses() {

  // print debug statement
  if (m_inDebugMode) PrintDebug(19);

  // initialize input truth tree address members
  m_trueNumJets       = 0;
  m_trueNumChrgPars   = 0;
  m_truePartonID[0]   = 0;
  m_truePartonID[1]   = 0;
  m_truePartonMomX[0] = 0.;
  m_truePartonMomX[1] = 0.;
  m_truePartonMomY[0] = 0.;
  m_truePartonMomY[1] = 0.;
  m_truePartonMomZ[0] = 0.;
  m_truePartonMomZ[1] = 0.;
  m_trueVtxX          = 0.;
  m_trueVtxY          = 0.;
  m_trueVtxZ          = 0.;
  m_trueSumPar        = 0.;
  m_trueJetID         = 0x0;
  m_trueJetNumCst     = 0x0;
  m_trueJetEne        = 0x0;
  m_trueJetPt         = 0x0;
  m_trueJetEta        = 0x0;
  m_trueJetPhi        = 0x0;
  m_trueJetArea       = 0x0;
  m_trueCstID         = 0x0;
  m_trueCstZ          = 0x0;
  m_trueCstDr         = 0x0;
  m_trueCstEne        = 0x0;
  m_trueCstJt         = 0x0;
  m_trueCstEta        = 0x0;
  m_trueCstPhi        = 0x0;

  // input reco. tree address members
  m_recoNumJets    = 0;
  m_recoNumTrks    = 0;
  m_recoVtxX       = 0.;
  m_recoVtxY       = 0.;
  m_recoVtxZ       = 0.;
  m_recoSumECal    = 0.;
  m_recoSumHCal    = 0.;
  m_recoJetID      = 0x0;
  m_recoJetNumCst  = 0x0;
  m_recoJetEne     = 0x0;
  m_recoJetPt      = 0x0;
  m_recoJetEta     = 0x0;
  m_recoJetPhi     = 0x0;
  m_recoJetArea    = 0x0;
  m_recoCstMatchID = 0x0;
  m_recoCstZ       = 0x0;
  m_recoCstDr      = 0x0;
  m_recoCstEne     = 0x0;
  m_recoCstJt      = 0x0;
  m_recoCstEta     = 0x0;
  m_recoCstPhi     = 0x0;

  // initialize output response tree address members
  m_matchNumJets.first     = 0.;
  m_matchNumJets.second    = 0.;
  m_matchNumTrks.first     = 0.;
  m_matchNumTrks.second    = 0.;
  m_matchVtxX.first        = 0.;
  m_matchVtxX.second       = 0.;
  m_matchVtxY.first        = 0.;
  m_matchVtxY.second       = 0.;
  m_matchVtxZ.first        = 0.;
  m_matchVtxZ.second       = 0.;
  m_matchJetID.first       = 0x0;
  m_matchJetID.second      = 0x0;
  m_matchJetNumCst.first   = 0x0;
  m_matchJetNumCst.second  = 0x0;
  m_matchJetEne.first      = 0x0;
  m_matchJetEne.second     = 0x0;
  m_matchJetPt.first       = 0x0;
  m_matchJetPt.second      = 0x0;
  m_matchJetEta.first      = 0x0;
  m_matchJetEta.second     = 0x0;
  m_matchJetPhi.first      = 0x0;
  m_matchJetPhi.second     = 0x0;
  m_matchJetArea.first     = 0x0;
  m_matchJetArea.second    = 0x0;
  m_matchCstMatchID.first  = 0x0;
  m_matchCstMatchID.second = 0x0;
  m_matchCstZ.first        = 0x0;
  m_matchCstZ.second       = 0x0;
  m_matchCstDr.first       = 0x0;
  m_matchCstDr.second      = 0x0;
  m_matchCstEne.first      = 0x0;
  m_matchCstEne.second     = 0x0;
  m_matchCstJt.first       = 0x0;
  m_matchCstJt.second      = 0x0;
  m_matchCstEta.first      = 0x0;
  m_matchCstEta.second     = 0x0;
  m_matchCstPhi.first      = 0x0;
  m_matchCstPhi.second     = 0x0;
  return;

}  // end 'InitializeAddresses()'



void SCorrelatorResponseMaker::InitializeTrees() {

  // print debug statement
  if (m_inDebugMode) PrintDebug(20);

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

  // set truth tree branch addresses
  m_inTrueTree -> SetBranchAddress("EvtNumJets",     &m_trueNumJets,       &m_brTrueNumJets);
  m_inTrueTree -> SetBranchAddress("EvtNumChrgPars", &m_trueNumChrgPars,   &m_brTrueNumChrgPars);
  m_inTrueTree -> SetBranchAddress("Parton3_ID",     &m_truePartonID[0],   &m_brTruePartonID[0]);
  m_inTrueTree -> SetBranchAddress("Parton4_ID",     &m_truePartonID[1],   &m_brTruePartonID[1]);
  m_inTrueTree -> SetBranchAddress("Parton3_MomX",   &m_truePartonMomX[0], &m_brTruePartonMomX[0]);
  m_inTrueTree -> SetBranchAddress("Parton3_MomY",   &m_truePartonMomY[0], &m_brTruePartonMomY[0]);
  m_inTrueTree -> SetBranchAddress("Parton3_MomZ",   &m_truePartonMomZ[0], &m_brTruePartonMomZ[0]);
  m_inTrueTree -> SetBranchAddress("Parton4_MomX",   &m_truePartonMomX[1], &m_brTruePartonMomX[1]);
  m_inTrueTree -> SetBranchAddress("Parton4_MomY",   &m_truePartonMomY[1], &m_brTruePartonMomY[1]);
  m_inTrueTree -> SetBranchAddress("Parton4_MomZ",   &m_truePartonMomZ[1], &m_brTruePartonMomZ[1]);
  m_inTrueTree -> SetBranchAddress("EvtVtxX",        &m_trueVtxX,          &m_brTrueVtxX);
  m_inTrueTree -> SetBranchAddress("EvtVtxY",        &m_trueVtxY,          &m_brTrueVtxY);
  m_inTrueTree -> SetBranchAddress("EvtVtxZ",        &m_trueVtxZ,          &m_brTrueVtxZ);
  m_inTrueTree -> SetBranchAddress("JetID",           m_trueJetID,         &m_brTrueJetID);
  m_inTrueTree -> SetBranchAddress("JetNumCst",       m_trueJetNumCst,     &m_brTrueJetNumCst);
  m_inTrueTree -> SetBranchAddress("JetEnergy",       m_trueJetEne,        &m_brTrueJetEne);
  m_inTrueTree -> SetBranchAddress("JetPt",           m_trueJetPt,         &m_brTrueJetPt);
  m_inTrueTree -> SetBranchAddress("JetEta",          m_trueJetEta,        &m_brTrueJetEta);
  m_inTrueTree -> SetBranchAddress("JetPhi",          m_trueJetPhi,        &m_brTrueJetPhi);
  m_inTrueTree -> SetBranchAddress("JetArea",         m_trueJetArea,       &m_brTrueJetArea);
  m_inTrueTree -> SetBranchAddress("CstID",           m_trueCstID,         &m_brTrueCstID);
  m_inTrueTree -> SetBranchAddress("CstZ",            m_trueCstZ,          &m_brTrueCstZ);
  m_inTrueTree -> SetBranchAddress("CstDr",           m_trueCstDr,         &m_brTrueCstDr);
  m_inTrueTree -> SetBranchAddress("CstEnergy",       m_trueCstEne,        &m_brTrueCstEne);
  m_inTrueTree -> SetBranchAddress("CstJt",           m_trueCstJt,         &m_brTrueCstJt);
  m_inTrueTree -> SetBranchAddress("CstEta",          m_trueCstEta,        &m_brTrueCstEta);
  m_inTrueTree -> SetBranchAddress("CstPhi",          m_trueCstPhi,        &m_brTrueCstPhi);

  // set reco tree branch addresses
  m_inRecoTree -> SetBranchAddress("EvtNumJets",    &m_recoNumJets,    &m_brRecoNumJets);
  m_inRecoTree -> SetBranchAddress("EvtNumTrks",    &m_recoNumTrks,    &m_brRecoNumTrks);
  m_inRecoTree -> SetBranchAddress("EvtVtxX",       &m_recoVtxX,       &m_brRecoVtxX);
  m_inRecoTree -> SetBranchAddress("EvtVtxY",       &m_recoVtxY,       &m_brRecoVtxY);
  m_inRecoTree -> SetBranchAddress("EvtVtxZ",       &m_recoVtxZ,       &m_brRecoVtxZ);
  m_inRecoTree -> SetBranchAddress("EvtSumECalEne", &m_recoSumECal,    &m_brRecoSumECal);
  m_inRecoTree -> SetBranchAddress("EvtSumHCalEne", &m_recoSumHCal,    &m_brRecoSumHCal);
  m_inRecoTree -> SetBranchAddress("JetID",          m_recoJetID,      &m_brRecoJetID);
  m_inRecoTree -> SetBranchAddress("JetNumCst",      m_recoJetNumCst,  &m_brRecoJetNumCst);
  m_inRecoTree -> SetBranchAddress("JetEnergy",      m_recoJetEne,     &m_brRecoJetEne);
  m_inRecoTree -> SetBranchAddress("JetPt",          m_recoJetPt,      &m_brRecoJetPt);
  m_inRecoTree -> SetBranchAddress("JetEta",         m_recoJetEta,     &m_brRecoJetEta);
  m_inRecoTree -> SetBranchAddress("JetPhi",         m_recoJetPhi,     &m_brRecoJetPhi);
  m_inRecoTree -> SetBranchAddress("JetArea",        m_recoJetArea,    &m_brRecoJetArea);
  m_inRecoTree -> SetBranchAddress("CstMatchID",     m_recoCstMatchID, &m_brRecoCstMatchID);
  m_inRecoTree -> SetBranchAddress("CstZ",           m_recoCstZ,       &m_brRecoCstZ);
  m_inRecoTree -> SetBranchAddress("CstDr",          m_recoCstDr,      &m_brRecoCstDr);
  m_inRecoTree -> SetBranchAddress("CstEnergy",      m_recoCstEne,     &m_brRecoCstEne);
  m_inRecoTree -> SetBranchAddress("CstJt",          m_recoCstJt,      &m_brRecoCstJt);
  m_inRecoTree -> SetBranchAddress("CstEta",         m_recoCstEta,     &m_brRecoCstEta);
  m_inRecoTree -> SetBranchAddress("CstPhi",         m_recoCstPhi,     &m_brRecoCstPhi);

  // announce tree setting
  if (m_inStandaloneMode) PrintMessage(5);
  return;

}  // end 'InitializeTree()'



void SCorrelatorResponseMaker::PrintMessage(const uint32_t code) {

  // print debug statement
  if (m_inDebugMode && (m_verbosity > 5)) PrintDebug(21);

  switch (code) {
    case 0:
      cout << "\n  Beginning correlator folding..." << endl;
      break;
    case 1:
      cout << "    Initializing folder:\n"
           << "      input truth file = " << m_inTrueFileName << "\n"
           << "      input reco file  = " << m_inRecoFileName
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
           << "      input truth tree = " << m_inTrueTreeName << "\n"
           << "      input reco tree  = " << m_inRecoTreeName
           << endl;
      break;
    default:
      PrintError(code);
      break;
  }
  return;

}  // end 'PrintMessage(uint32_t)'



void SCorrelatorResponseMaker::PrintDebug(const uint32_t code) {

  // print debug statement
  if (m_inDebugMode && (m_verbosity > 7)) {
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



void SCorrelatorResponseMaker::PrintError(const uint32_t code) {

  // print debug statement
  if (m_inDebugMode && (m_verbosity > 5)) PrintDebug(22);

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
    default:
      cerr << "WARNING: unknown status code!\n"
           << "         code = " << code
           << endl;
      break;
  }
  return;

}  // end 'PrintError(unint32_t)'



bool SCorrelatorResponseMaker::CheckCriticalParameters() {

  // print debugging statement
  if (m_inDebugMode) PrintDebug(23); 

  /* TODO checking goes here */
  return true;

}  // end 'CheckCriticalParameters()'



int64_t SCorrelatorResponseMaker::GetEntry(const uint64_t entry, TTree *tree) {

  // print debugging statemet
  if (m_inDebugMode && (m_verbosity > 5)) PrintDebug(24);

  int64_t entryStatus(-1);
  if (!tree) {
    entryStatus = 0;
  } else {
    entryStatus = tree -> GetEntry(entry);
  }
  return entryStatus;

}  // end 'GetEntry(uint64_t, TTree*)'



int64_t SCorrelatorResponseMaker::LoadTree(const uint64_t entry, TTree *tree, int &fCurrent) {

  // print debugging statemet
  if (m_inDebugMode && (m_verbosity > 5)) PrintDebug(25);

  // check for tree & load
  int     treeNumber(-1);
  int64_t treeStatus(-1);
  if (!tree) {
    treeStatus = -5;
  } else {
    treeNumber = tree -> GetTreeNumber();
    treeStatus = tree -> LoadTree(entry);
  }

  // update current tree number if need be
  const bool isTreeStatusGood = (treeStatus >= 0);
  const bool isNotCurrentTree = (treeNumber != fCurrent);
  if (isTreeStatusGood && isNotCurrentTree) {
    fCurrent = tree -> GetTreeNumber();
  }
  return treeStatus;

}  // end 'LoadTree(uint64_t, TTree*)'

// end ------------------------------------------------------------------------
