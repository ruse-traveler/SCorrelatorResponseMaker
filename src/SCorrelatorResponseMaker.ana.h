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

/* TODO fill in skeleton
  // for matching
  vector<fastjet::PseudoJet> trueCsts;
  vector<fastjet::PseudoJet> recoCsts;
  trueCsts.clear();
  recoCsts.clear();

  // loop over true jets
  for (size_t iTruJet = 0; iTruJet < m_trueJets.size(); iTruJet++) {

    // clear matching variables
    trueCsts.clear();
    recoCsts.clear();

    // grab truth jet info
    const double ptTrue = m_trueJetPt[iTruJet];
    const double hTrue  = m_trueJetEta[iTruJet];
    const double fTrue  = m_trueJetPhi[iTruJet];

    // loop over reco jets
    bool   isTrueMatched = false;
    size_t iRecoMatchJet = -1;
    for (size_t iRecJet = 0; iRecJet < m_recoJets.size(); iRecJet++) {

      const bool isGoodJetMatch = IsJetGoodMatch(qtJet, drJet);
      if (isGoodJetMatch) {
        isTrueMatched = true;
        iRecoMatchJet = iRecJet;
        break;
      }
    }  // end reco jet loop

    // loop over true cst.s
    trueCsts = m_trueJets[iTruJet].constituents();
    for (size_t iTruCst = 0; iTruCst < trueCsts.size(); iTruCst++) {

      // only match cst.s if jet is matched
      if (!isTrueMatched) continue;

      // loop over reco cst.s
      recoCsts = m_recoJets[iRecoMatchJet].constituents();
      for (size_t iRecCst = 0; iRecCst < recoCsts.size(); iRecCst++) {

        const bool isGoodCstMatch = IsCstGoodMatch(qtCst, drCst);
        if (isGoodCstMatch) {
          // fill output vectors here //
          break;
        }

      }  // end reco cst loop

    }  // end true cst loop
  }  // end true jet loop
*/
  return;

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
