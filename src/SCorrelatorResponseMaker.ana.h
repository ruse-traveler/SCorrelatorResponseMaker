/// ---------------------------------------------------------------------------
/*! \file   SCorrelatorResponseMaker.ana.h
 *  \author Derek Anderson
 *  \date   02.14.2023
 *
 * A module to match truth to reconstructed
 * jets/particles to derive corrections for
 * an n-point energy correlation strength
 * function.
 */
/// ---------------------------------------------------------------------------

#pragma once

using namespace std;



// analysis methods ===========================================================

namespace SColdQcdCorrelatorAnalysis {

  // --------------------------------------------------------------------------
  //! Match truth and reconstructed jets
  // --------------------------------------------------------------------------
  void SCorrelatorResponseMaker::DoMatching() {

    // print debug statement
    if (m_config.inDebugMode && (m_config.verbosity > 1)) {
      PrintDebug(10);
    }

    // get no. of events
    const uint64_t                 nTrueEvts = m_inTrueTree -> GetEntriesFast();
    const uint64_t                 nRecoEvts = m_inRecoTree -> GetEntriesFast();
    const pair<uint64_t, uint64_t> nEvts     = {nTrueEvts, nRecoEvts};
    PrintMessage(6, 0, nEvts);

    // loop over true events
    uint64_t nTrueBytes = 0;
    uint64_t nRecoBytes = 0;
    for (uint64_t iTrueEvt = 0; iTrueEvt < nTrueEvts; iTrueEvt++) {

      // load true entry
      //   - FIXME event loop should go into the top-level analysis method
      const uint64_t trueEntry = Interfaces::LoadTree(m_inTrueTree, iTrueEvt, m_fTrueCurrent);
      if (trueEntry < 0) break;

      const uint64_t trueBytes = Interfaces::GetEntry(m_inTrueTree, iTrueEvt);
      if (trueBytes < 0) {
        PrintError(4, iTrueEvt);
        break;
      } else {
        nTrueBytes += trueBytes;
        PrintMessage(7, iTrueEvt + 1, nEvts);
      }

      // load reco entry
      //   - n.b. since this is simulation,
      //     events are assumed to be 1-to-1
      const uint64_t recoEntry = Interfaces::LoadTree(m_inRecoTree, iTrueEvt, m_fRecoCurrent);
      if (recoEntry < 0) break;

      const uint64_t recoBytes = Interfaces::GetEntry(m_inRecoTree, iTrueEvt);
      if (recoBytes < 0) {
        PrintError(5, iTrueEvt);
        break;
      } else {
        nRecoBytes += recoBytes;
      }

      // is uing legacy input, fill container
      if (m_config.isLegacyIO) {
        m_recoLegacy.SetInput(m_recoInput);
        m_trueLegacy.SetInput(m_trueInput);
      }

      // clear output addresses
      ResetOutVariables();

      // grab evt-level info
      m_output.evtRec = m_recoInput.evt;
      m_output.evtGen = m_trueInput.evt;

      // loop over true jets
      for (size_t iTrueJet = 0; iTrueJet < m_trueInput.jets.size(); ++iTrueJet) {

        // check if good
        const auto genJet       = m_trueInput.jets[iTrueJet]; 
        const bool isGoodGenJet = IsGoodJet( genJet );
        if (!isGoodGenJet) continue;

        // grab truth jet info
        m_output.jetGen.push_back( genJet );
        m_output.cstGen.push_back( {} );

        // grab truth cst info
        const uint64_t nTrueCsts = m_trueInput.csts.at(iTrueJet).size();
        for (Types::CstInfo& genCst : m_trueInput.csts.at(iTrueJet)) {

          // check if good
          const bool isGoodTrueCst = IsGoodCst( genCst );
          if (!isGoodTrueCst) continue;

          // add to output
          m_output.cstGen.back().push_back( genCst );

        }  // end true cst loop

        // loop over reco jets
        //   - TODO need bookkeeping container to keep track of matched
        //     reco jets...
        bool     wasJetMatched    = false;
        double   bestFracCstMatch = 0.;
        uint64_t nMatchCst        = 0;
        for (size_t iRecoJet = 0; iRecoJet < m_recoInput.jets.size(); ++iRecoJet) {

          // check if good
          const auto recJet       = m_recoInput.jets[iRecoJet]; 
          const bool isGoodRecJet = IsGoodJet( recJet );
          if (!isGoodRecJet) continue;

          // get matching variables
          const double drJet = GetDeltaR(recJet, genJet);
          const double qtJet = recJet.GetPT() / genJet.GetPT();


          // loop over true constituents
          //   - TODO need bookkeeping container to keep track of matched
          //     reco constituents...
          for (size_t iTrueCst = 0; iTrueCst < m_output.cstGen.back().size(); ++iTrueCst) {

            // grab true cst info
            const auto genCst = m_output.cstGen.back()[iTrueCst];

            // loop over reco constituents
            bool wasCstMatched = false;
            for (size_t iRecoCst = 0; iRecoCst < m_recoInput.csts[iRecoJet].size(); ++iRecoCst) {

              // check if good
              const auto recCst       = m_recoInput.csts[iRecoJet][iRecoCst];
              const bool isGoodRecCst = IsGoodCst( recCst );
              if (!isGoodRecCst) continue;

              // check ids
              const bool isMatchedCst = (genCst.GetCstID() == recCst.GetCstID());
              if (isMatchedCst) {

                // set map, increment counters
                wasCstMatched      = true;
                m_cstMap[iTrueCst] = iRecoCst;
                ++nMatchCst;
                break;

              }
            }  // end reco cst loop
          }  // end true cst loop

          // if jet is best match so far, store values
          const double fracCstMatch = nMatchCst / nTrueCsts;
          const bool   isBetterMatch = IsBetterMatch(fracCstMatch, bestFracCstMatch);
          if (isBetterMatch) {
            wasJetMatched = true;
          }
        }  // end reco jet loop

        // add matched reco jet values to vectors
        if (wasJetMatched) {
          /* TODO set matched reco jet values here */
        } else {
          /* TODO set placeholder values if not matched */
        }
      }  // end true jet loop

      // fill output tree
      FillTree();

    }  // end true event loop
    PrintMessage(8);

  }  // end 'DoMatching()'



  // --------------------------------------------------------------------------
  //! Check if current match is best so far
  // --------------------------------------------------------------------------
  bool SCorrelatorResponseMaker::IsBetterMatch(const double frac, const double best) {

    // print debug statement
    if (m_config.inDebugMode && (m_config.verbosity > 2)) {
      PrintDebug(15);
    }

    const bool isMatch  = ((frac > m_config.fracCstMatchRange.first) && (frac < m_config.fracCstMatchRange.second));
    const bool isBetter = (frac > best);
    return (isMatch && isBetter);

  }  // end 'IsBetterMatch(double, double)'



  // --------------------------------------------------------------------------
  //! Check if jet satisfies cuts
  // --------------------------------------------------------------------------
  bool SCorrelatorResponseMaker::IsGoodJet(const Types::JetInfo& jet) {

    // print debug statement
    //   - FIXME give actual code
    if (m_config.inDebugMode && (m_config.verbosity > 2)) {
      PrintDebug(777);
    }

    return jet.IsInAcceptance(m_config.jetAccept);

  }  // end 'IsGoodJet(Types::JetInfo&)'



  // --------------------------------------------------------------------------
  //! Check if cst satisfies cuts
  // --------------------------------------------------------------------------
  bool SCorrelatorResponseMaker::IsGoodCst(const Types::CstInfo& cst) {

    // print debug statement
    //   - FIXME give actual code
    if (m_config.inDebugMode && (m_config.verbosity > 2)) {
      PrintDebug(777);
    }

    return cst.IsInAcceptance(m_config.cstAccept);

  }  // end 'IsGoodCst(Types::CstInfo&)'



  // templated analysis methods ===============================================

  // --------------------------------------------------------------------------
  //! Calculate delta r
  // --------------------------------------------------------------------------
  template <typename T> double SCorrelatorResponseMaker::GetDeltaR(const T& lhs, const T& rhs) {

    // print debug statement
    //   - FIXME give actual code
    if (m_config.inDebugMode && (m_config.verbosity > 2)) {
      PrintDebug(777);
    }

    return std::hypot(
      lhs.GetEta() - rhs.GetEta(),
      std::remainder(lhs.GetPhi() - rhs.GetPhi(), 2. * M_PI)
    );

  }  // end 'GetDeltaR(T&, T&)'

  // specific instantiations of 'GetDeltaR()'
  template double SCorrelatorResponseMaker::GetDeltaR(const Types::JetInfo& lhs, const Types::JetInfo& rhs);
  template double SCorrelatorResponseMaker::GetDeltaR(const Types::CstInfo& lhs, const Types::CstInfo& rhs);

}  // end SColdQcdCorrelatorAnalysis namespace

// end ------------------------------------------------------------------------
