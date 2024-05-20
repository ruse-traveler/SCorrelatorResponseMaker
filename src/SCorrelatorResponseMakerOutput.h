/// ---------------------------------------------------------------------------
/*! \file   SCorrelatorResponseMakerOutput.h
 *  \author Derek Anderson
 *  \date   05.20.2024
 *
 *  Outputs for the `SCorrelatorResponseMaker' module.
 */
/// ---------------------------------------------------------------------------

#ifndef SCORRELATORJETTREEMAKEROUTPUT_H
#define SCORRELATORJETTREEMAKEROUTPUT_H



namespace SColdQcdCorrelatorAnalysis {

  // --------------------------------------------------------------------------
  //! Response tree output
  // --------------------------------------------------------------------------
  struct SCorrelatorResponseMakerOutput {

    /* TODO fill in */

  };  // end SCorrelatorResponseMakerOutput



  // --------------------------------------------------------------------------
  //! Legacy response tree output
  // --------------------------------------------------------------------------
  struct SCorrelatorResponseMakerLegacyOutput {

    // output response tree event-level address members
    //   - FIXME should be consolidated into a single class/struct for ease-of-maintenance
    //   - TODO add non-pair values (e.g. sum of particle energy, fraction of cst.s matched)
    pair<int,    int>    m_matchNumJets;
    pair<int,    int>    m_matchNumTrks;
    pair<double, double> m_matchVtxX;
    pair<double, double> m_matchVtxY;
    pair<double, double> m_matchVtxZ;
    // output response tree jet-level address members
    pair<vector<uint32_t>, vector<uint32_t>> m_matchJetID;
    pair<vector<uint64_t>, vector<uint64_t>> m_matchJetNumCst;
    pair<vector<double>,   vector<double>>   m_matchJetEne;
    pair<vector<double>,   vector<double>>   m_matchJetPt;
    pair<vector<double>,   vector<double>>   m_matchJetEta;
    pair<vector<double>,   vector<double>>   m_matchJetPhi;
    pair<vector<double>,   vector<double>>   m_matchJetArea;
    // output response tree cst-level address members
    pair<vector<vector<int>>,    vector<vector<int>>>    m_matchCstID;
    pair<vector<vector<double>>, vector<vector<double>>> m_matchCstZ;
    pair<vector<vector<double>>, vector<vector<double>>> m_matchCstDr;
    pair<vector<vector<double>>, vector<vector<double>>> m_matchCstEne;
    pair<vector<vector<double>>, vector<vector<double>>> m_matchCstJt;
    pair<vector<vector<double>>, vector<vector<double>>> m_matchCstEta;
    pair<vector<vector<double>>, vector<vector<double>>> m_matchCstPhi;


    // ------------------------------------------------------------------------
    //! Reset variables
    // ------------------------------------------------------------------------
    void Reset() {

      /* TODO fill in */
      return;

    }  // end 'Reset()'


    // ------------------------------------------------------------------------
    //! Set tree addresses
    // ------------------------------------------------------------------------
    void SetTreeAddresses(TTree* tree) {

      /* TODO fill in */
      return;

    }  // end 'SetTreeAddresses(TTree* tree)'



    // ------------------------------------------------------------------------
    //! Translate normal output into legacy output
    // ------------------------------------------------------------------------
    void GetOutput(const SCorrelatorResponseMakerOutput& output) {

      /* TODO fill in */
      return;

    }  // end 'GetOutput(SCorrelatorResponseMakerOutput&)'

  };  // end SCorrelatorResponseMakerLegacyOutput

}  // end SColdQcdCorrelatorAnalysis namespace

#endif

// end ------------------------------------------------------------------------

