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



// public i/o methods ---------------------------------------------------------

void SCorrelatorFolder::SetInputNodes(const string &iTrueNodeName, const string &iRecoNodeName) {

  // print debug statemet
  if (m_inDebugMode) PrintDebug();

  m_inTrueNodeName = iTrueNodeName;
  m_inRecoNodeName = iRecoNodeName;
  return;

}  // end 'SetInputNodes(string&, string&)'



void SCorrelatorFolder::SetInputFiles(const string &iTrueFileName, const string &iRecoFileName) {

  // print debug statemet
  if (m_inDebugMode) PrintDebug();

  m_inTrueFileName = iTrueFileName;
  m_inRecoFileName = iRecoFileName;
  return;

}  // end 'SetInputFiles(string&, string&)'



void SCorrelatorFolder::SetInputTrees(const string &iTrueTreeName, const string &iRecoTreeName) {

  // print debug statemet
  if (m_inDebugMode) PrintDebug();
  
  m_inTrueTreeName = iTrueTreeName;
  m_inRecoTreeName = iRecoTreeName;
  return;

}  // end 'SetInputTrees(string&, string&)'



void SCorrelatorFolder::SetJetMatchQtRange(const pair<double, double> qtRange) {

  // print debug statemet
  if (m_inDebugMode) PrintDebug();

  m_jetMatchQtRange[0] = qtRange.first;
  m_jetMatchQtRange[1] = qtRange.second;
  return;

}  // end 'SetJetMatchQtRange(pair<double, double>)'



void SCorrelatorFolder::SetJetMatchDrRange(const pair<double, double> drRange) {

  // print debug statemet
  if (m_inDebugMode) PrintDebug();

  m_jetMatchDrRange[0] = drRange.first;
  m_jetMatchDrRange[1] = drRange.second;
  return;

}  // end 'SetJetMatchDrRange(pair<double, double>)'



pair<double, double> SCorrelatorFolder::GetJetMatchQtRange() {

  // print debug statemet
  if (m_inDebugMode) PrintDebug();

  const pair<double, double> qtRange(m_jetMatchQtRange[0], m_jetMatchQtRange[1]);
  return qtRange;  

}  // end 'GetJetMatchQtRange()'



pair<double, double> SCorrelatorFolder::GetJetMatchDrRange() {

  // print debug statemet
  if (m_inDebugMode) PrintDebug();

  const pair<double, double> drRange(m_jetMatchDrRange[0], m_jetMatchDrRange[1]);
  return drRange;  

}  // end 'GetJetMatchDrRange()'



// private i/o methods --------------------------------------------------------

void SCorrelatorFolder::GrabInputNodes() {

  // print debug statement
  if (m_inDebugMode) PrintDebug(3);

  /* TODO method goes here */
  return;

}  // end 'GrabInputNodes()'



void SCorrelatorFolder::OpenInputFiles() {

  // print debug statement
  if (m_inDebugMode) PrintDebug(11);

  // open files
  const bool isTrueTreeNotLoaded = (m_inTrueTree == 0);
  const bool isRecoTreeNotLoaded = (m_inRecoTree == 0);
  if (isTrueTreeNotLoaded) OpenFile(m_inTrueFileName, m_inTrueFile);
  if (isRecoTreeNotLoaded) OpenFile(m_inRecoFileName, m_inRecoFile);

  // grab trees
  m_inTrueFile -> GetObject(m_inTrueTreeName.data(), m_inTrueTree);
  m_inRecoFile -> GetObject(m_inRecoTreeName.data(), m_inRecoTree);
  if (!m_inTrueTree) {
    PrintError(7);
    assert(m_inTrueTree);
  }
  if (!m_inRecoTree) {
    PrintError(7);
    assert(m_inRecoTree);
  }
  return;

}  // end 'OpenInputFiles()'



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



void SCorrelatorFolder::OpenFile(const string &fileName, TFile *file) {

  // print debug statement
  if (m_inDebugMode) PrintDebug();

  file = (TFile*) gROOT -> GetListOfFiles() -> FindObject(fileName.data());
  if (!file || !(file -> IsOpen())) {
    file = new TFile(fileName.data(), "read");
    if (!file) {
      PrintError(6);
      assert(file);
    }
  }  // end if (file dne or isn't open)
  return;

}  // end 'OpenFile(string&, TFile*)'



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
