// ----------------------------------------------------------------------------
// 'SCorrelatorFolder.io.h'
// Derek Anderson
// 04.30.2023
//
// A module to unfold, backfold, and/or
// perform corrections on an n-point
// energy correlation strength function.
// ----------------------------------------------------------------------------

#pragma once

using namespace std;



// i/o methods ----------------------------------------------------------------

void SCorrelatorFolder::SetInputTree(const string &iTreeName, const bool isTruthTree) {

  // print debug statemet
  if (m_inDebugMode) PrintDebug(18);
  
  m_inTreeName       = iTreeName;
  m_isInputTreeTruth = isTruthTree; 
  return;

}  // end 'SetInputTree(string&, bool)'



void SCorrelatorFolder::SetJetParameters(const vector<pair<double, double>> &pTjetBins, const double minEta, const double maxEta) {

  // print debug statement
  if (m_inDebugMode) PrintDebug(20);

  m_etaJetRange[0] = minEta;
  m_etaJetRange[1] = maxEta;
  m_nBinsJetPt     = pTjetBins.size();
  for (uint32_t iPtBin = 0; iPtBin < m_nBinsJetPt; iPtBin++) {
    const double               minPt = pTjetBins.at(iPtBin).first;
    const double               maxPt = pTjetBins.at(iPtBin).second;
    const pair<double, double> ptBin = {minPt, maxPt};
    m_ptJetBins.push_back(ptBin);
  }
  m_ptJetRange[0] = m_ptJetBins[0].first;
  m_ptJetRange[1] = m_ptJetBins[m_nBinsJetPt - 1].second;

  // announce jet parameters
  if (m_inStandaloneMode) PrintMessage(6);
  return;

}  // end 'SetJetParameters(vector<pair<double, double>>&, double, double)'



void SCorrelatorFolder::SetConstituentParameters(const double minMom, const double maxMom, const double minDr, const double maxDr) {

  // print debug statement
  if (m_inDebugMode) PrintDebug(24);

  m_momCstRange[0] = minMom;
  m_momCstRange[1] = maxMom;
  m_drCstRange[0]  = minDr;
  m_drCstRange[1]  = maxDr;

  // announce cst parameters
  if (m_inStandaloneMode) PrintMessage(12);
  return;

}  // end 'SetConstituentParameters(double, double, double, double)'



void SCorrelatorJetTree::SetJetMatchQtRange(const pair<double, double> qtRange) {

  m_jetMatchQtRange[0] = qtRange.first;
  m_jetMatchQtRange[1] = qtRange.second;
  return;

}  // end 'SetJetMatchQtRange(pair<double, double>)'



void SCorrelatorJetTree::SetJetMatchDrRange(const pair<double, double> drRange) {

  m_jetMatchDrRange[0] = drRange.first;
  m_jetMatchDrRange[1] = drRange.second;
  return;

}  // end 'SetJetMatchDrRange(pair<double, double>)'



void SCorrelatorJetTree::SetCstMatchQtRange(const pair<double, double> qtRange) {

  m_cstMatchQtRange[0] = qtRange.first;
  m_cstMatchQtRange[1] = qtRange.second;
  return;

}  // end 'SetJetMatchQtRange(pair<double, double>)'



void SCorrelatorJetTree::SetCstMatchDrRange(const pair<double, double> drRange) {

  m_cstMatchDrRange[0] = drRange.first;
  m_cstMatchDrRange[1] = drRange.second;
  return;

}  // end 'SetJetMatchDrRange(pair<double, double>)'



void SCorrelatorFolder::GrabInputNode() {

  // print debug statement
  if (m_inDebugMode) PrintDebug(3);

  /* TODO method goes here */
  return;

}  // end 'GrabInputNode()'



void SCorrelatorFolder::OpenInputFile() {

  // print debug statement
  if (m_inDebugMode) PrintDebug(11);

  // open file
  const bool isTreeNotLoaded = (m_inTree == 0);
  if (isTreeNotLoaded) {

    // check list of files & open if needed
    m_inFile = (TFile*) gROOT -> GetListOfFiles() -> FindObject(m_inFileName.data());
    if (!m_inFile || !(m_inFile -> IsOpen())) {
      m_inFile = new TFile(m_inFileName.data(), "read");
      if (!m_inFile) {
        PrintError(6);
        assert(m_inFile);
      }
    }
  }

  // grab tree
  m_inFile -> GetObject(m_inTreeName.data(), m_inTree);
  if (!m_inTree) {
    PrintError(7);
    assert(m_inTree);
  }
  return;

}  // end 'OpenInputFile()'



void SCorrelatorFolder::OpenOutputFile() {

  // print debug statement
  if (m_inDebugMode) PrintDebug(15);

  // open file
  m_outFile = new TFile(m_outFileName.data(), "recreate");
  if (!m_outFile) {
    PrintError(11);
    assert(m_outFile);
  }
  return;

}  // end 'OpenOutputFile()'



void SCorrelatorFolder::SaveOutput() {

  // print debug statement
  if (m_inDebugMode) PrintDebug(9);

  m_outFile -> cd();
  /* TODO saving goes here */

  // announce saving
  if (m_inStandaloneMode) PrintMessage(10);
  return;

}  // end 'SaveOutput()'

// end ------------------------------------------------------------------------
