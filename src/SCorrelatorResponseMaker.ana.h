// ----------------------------------------------------------------------------
// 'SCorrelatorResponseMaker.ana.h'
// Derek Anderson
// 02.14.2023
//
// A module to match truth to reconstructed
// jets/particles to derive corrections for
// an n-point energy correlation strength
// function.
// ----------------------------------------------------------------------------

#pragma once

using namespace std;



// analysis methods -----------------------------------------------------------

void SCorrelatorResponseMaker::DoMatching() {

  // print debug statement
  if (m_inDebugMode) PrintDebug(17);

  // for constituent matching
  pair<vector<int>,    vector<int>>    vecCstID;
  pair<vector<double>, vector<double>> vecCstZ;
  pair<vector<double>, vector<double>> vecCstDr;
  pair<vector<double>, vector<double>> vecCstEne;
  pair<vector<double>, vector<double>> vecCstJt;
  pair<vector<double>, vector<double>> vecCstEta;
  pair<vector<double>, vector<double>> vecCstPhi;

  // get no. of events
  const uint64_t                 nTrueEvts = m_inTrueTree -> GetEntriesFast();
  const uint64_t                 nRecoEvts = m_inRecoTree -> GetEntriesFast();
  const pair<uint64_t, uint64_t> nEvts     = {nTrueEvts, nRecoEvts};
  PrintMessage(6, 0, nEvts);

  // loop over true events
  uint64_t nTrueBytes = 0;
  uint64_t nRecoBytes = 0;
  for (uint64_t iTrueEvt = 0; iTrueEvt < nTrueEvts; iTrueEvt++) {

    // clear constituent matching vectors
    vecCstID.first.clear();
    vecCstID.second.clear();
    vecCstZ.first.clear();
    vecCstZ.second.clear();
    vecCstDr.first.clear();
    vecCstDr.second.clear();
    vecCstEne.first.clear();
    vecCstEne.second.clear();
    vecCstJt.first.clear();
    vecCstJt.second.clear();
    vecCstEta.first.clear();
    vecCstEta.second.clear();
    vecCstPhi.first.clear();
    vecCstPhi.second.clear();

    // clear input/output addresses
    InitializeAddresses();

    // load true entry
    const uint64_t trueEntry = LoadTree(iTrueEvt, m_inTrueTree, m_fTrueCurrent);
    if (trueEntry < 0) break;

    const uint64_t trueBytes = GetEntry(iTrueEvt, m_inTrueTree);
    if (trueBytes < 0) {
      PrintError(4, iTrueEvt);
      break;
    } else {
      nTrueBytes += trueBytes;
      PrintMessage(7, iTrueEvt + 1, nEvts);
    }

    // load reco entry
    // FIXME should the reco event be located via event ID first?
    const uint64_t recoEntry = LoadTree(iTrueEvt, m_inRecoTree, m_fRecoCurrent);
    if (recoEntry < 0) break;

    const uint64_t recoBytes = GetEntry(iTrueEvt, m_inRecoTree);
    if (recoBytes < 0) {
      PrintError(5, iTrueEvt);
      break;
    } else {
      nRecoBytes += recoBytes;
    }

    // set event info
    m_matchNumJets = make_pair(m_trueNumJets,     m_recoNumJets);
    m_matchNumTrks = make_pair(m_trueNumChrgPars, m_recoNumTrks);
    m_matchVtxX    = make_pair(m_trueVtxX,        m_recoVtxX);
    m_matchVtxY    = make_pair(m_trueVtxY,        m_recoVtxY);
    m_matchVtxZ    = make_pair(m_trueVtxZ,        m_trueVtxZ);

    // loop over true jets
    for (int iTrueJet = 0; iTrueJet < m_trueNumJets; iTrueJet++) {

      /* TODO jet matching goes here */

    }  // end true jet loop

    // fill tree
    m_matchTree -> Fill();

  }  // end true event loop
  PrintMessage(8);

}  // end 'DoMatching()'



bool SCorrelatorResponseMaker::IsJetGoodMatch(const double qtJet, const double drJet) {

  // print debug statement
  if (m_inDebugMode && (Verbosity() > 2)) PrintDebug(18);

  const bool isInQtRange = ((qtJet > m_jetMatchQtRange[0]) && (qtJet < m_jetMatchQtRange[1]));
  const bool isInDrRange = ((drJet > m_jetMatchDrRange[0]) && (drJet < m_jetMatchDrRange[1]));
  const bool isGoodMatch = (isInQtRange && isInDrRange);
  return isGoodMatch;

}  // end 'IsJetGoodMatch(double, double)'

// end ------------------------------------------------------------------------
