// ----------------------------------------------------------------------------
// 'SCorrelatorResponseMaker.h'
// Derek Anderson
// 04.30.2023
//
// A module to match truth to reconstructed
// jets/particles to derive corrections for
// an n-point energy correlation strength
// function.
// ----------------------------------------------------------------------------

#ifndef SCORRELATORRESPONSEMAKER_H
#define SCORRELATORRESPONSEMAKER_H

// c++ utilities
#include <cmath>
#include <string>
#include <vector>
#include <cassert>
#include <sstream>
#include <cstdlib>
#include <utility>
// root libraries
#include <TH1.h>
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TMath.h>
#include <TString.h>
#include <TDirectory.h>
#include <Math/Vector3D.h>
// f4a libraries
#include <fun4all/SubsysReco.h>
#include <fun4all/Fun4AllReturnCodes.h>
#include <fun4all/Fun4AllHistoManager.h>
// phool utilities
#include <phool/phool.h>
#include <phool/getClass.h>
#include <phool/PHIODataNode.h>
#include <phool/PHNodeIterator.h>
#include <phool/PHCompositeNode.h>
// analysis utilities
#include "/sphenix/user/danderson/install/include/scorrelatorutilities/Tools.h"
#include "/sphenix/user/danderson/install/include/scorrelatorutilities/Types.h"
#include "/sphenix/user/danderson/install/include/scorrelatorutilities/Constants.h"
#include "/sphenix/user/danderson/install/include/scorrelatorutilities/Interfaces.h"
// analysis definitions
#include "SCorrelatorResponseMakerConfig.h"
#include "SCorrelatorResponseMakerInput.h"
#include "SCorrelatorResponseMakerOutput.h"

// make common namespaces
using namespace std;
using namespace SCorrelatorUtilities;



namespace SColdQcdCorrelatorAnalysis {

  // SCorrelatorResponseMaker definition --------------------------------------

  class SCorrelatorResponseMaker : public SubsysReco {

    public:

      // ctor/dtor
      SCorrelatorResponseMaker(const string &name = "SCorrelatorResponseMaker", const bool isComplex = false, const bool doDebug = false, const bool inBatch = false);
      ~SCorrelatorResponseMaker() override;

      // F4A methods
      int Init(PHCompositeNode*)          override;
      int process_event(PHCompositeNode*) override;
      int End(PHCompositeNode*)           override;

      // standalone-only methods
      void Init();
      void Analyze();
      void End();

      // setters
      void SetConfig(const SCorrelatorResponseMakerConfig& config) {m_config = config;}

      // getters
      SCorrelatorResponseMakerConfig GetConfig() {return m_config;}

    private:

      // constants
      //   - TODO remove
      enum CONST {
        NRANGE   = 2,
        NLEVELS  = 2,
        NPARTONS = 2
      };

      // io methods (*.io.h)
      void GrabInputNodes();
      void OpenInputFiles();
      void OpenOutputFile();
      void OpenFile(const string& fileName, TFile*& file);
      void SaveOutput();

      // analysis methods (*.ana.h)
      void DoMatching();

      // system methods (*.sys.h)
      void    InitializeAddresses();
      void    InitializeTrees();
      void    PrintMessage(const uint32_t code, const uint64_t iEvt = 0, const pair<uint64_t, uint64_t> nEvts = {0, 0});
      void    PrintDebug(const uint32_t code);
      void    PrintError(const uint32_t code, const uint64_t iEvt = 0);
      bool    CheckCriticalParameters();
      int64_t GetEntry(const uint64_t entry, TTree* tree);
      int64_t LoadTree(const uint64_t entry, TTree* tree, int& fCurrent);

      // io members
      TFile* m_outFile    = NULL;
      TFile* m_inTrueFile = NULL;
      TFile* m_inRecoFile = NULL;
      TTree* m_inTrueTree = NULL;
      TTree* m_inRecoTree = NULL;
      TTree* m_matchTree  = NULL;

      // system members
      int m_fTrueCurrent = 0;
      int m_fRecoCurrent = 0;

      // configuration
      SCorrelatorResponseMakerConfig m_config; 

      // inputs
      SCorrelatorResponseMakerInput       m_input;
      SCorrelatorResponseMakerLegacyInput m_legacy;

      // input truth tree address members
      int                     m_trueNumJets;
      int                     m_trueNumChrgPars;
    int                     m_truePartonID[CONST::NPARTONS];
    double                  m_truePartonMomX[CONST::NPARTONS];
    double                  m_truePartonMomY[CONST::NPARTONS];
    double                  m_truePartonMomZ[CONST::NPARTONS];
    double                  m_trueVtxX;
    double                  m_trueVtxY;
    double                  m_trueVtxZ;
    double                  m_trueSumPar;
    vector<uint32_t>*       m_trueJetID;
    vector<uint64_t>*       m_trueJetNumCst;
    vector<double>*         m_trueJetEne;
    vector<double>*         m_trueJetPt;
    vector<double>*         m_trueJetEta;
    vector<double>*         m_trueJetPhi;
    vector<double>*         m_trueJetArea;
    vector<vector<int>>*    m_trueCstID;
    vector<vector<double>>* m_trueCstZ;
    vector<vector<double>>* m_trueCstDr;
    vector<vector<double>>* m_trueCstEne;
    vector<vector<double>>* m_trueCstJt;
    vector<vector<double>>* m_trueCstEta;
    vector<vector<double>>* m_trueCstPhi;

    // input reco. tree address members
    int                     m_recoNumJets;
    int                     m_recoNumTrks;
    double                  m_recoVtxX;
    double                  m_recoVtxY;
    double                  m_recoVtxZ;
    double                  m_recoSumECal;
    double                  m_recoSumHCal;
    vector<uint32_t>*       m_recoJetID;
    vector<uint64_t>*       m_recoJetNumCst;
    vector<double>*         m_recoJetEne;
    vector<double>*         m_recoJetPt;
    vector<double>*         m_recoJetEta;
    vector<double>*         m_recoJetPhi;
    vector<double>*         m_recoJetArea;
    vector<vector<int>>*    m_recoCstMatchID;
    vector<vector<double>>* m_recoCstZ;
    vector<vector<double>>* m_recoCstDr;
    vector<vector<double>>* m_recoCstEne;
    vector<vector<double>>* m_recoCstJt;
    vector<vector<double>>* m_recoCstEta;
    vector<vector<double>>* m_recoCstPhi;

    // output response tree event-level address members
    // FIXME should be consolidated into a single class/struct for ease-of-maintenance
    // TODO add non-pair values (e.g. sum of particle energy, fraction of cst.s matched)
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

    // input truth tree branch members
    TBranch* m_brTrueNumJets                     = NULL;
    TBranch* m_brTrueNumChrgPars                 = NULL;
    TBranch* m_brTruePartonID[CONST::NPARTONS]   = {NULL, NULL};
    TBranch* m_brTruePartonMomX[CONST::NPARTONS] = {NULL, NULL};
    TBranch* m_brTruePartonMomY[CONST::NPARTONS] = {NULL, NULL};
    TBranch* m_brTruePartonMomZ[CONST::NPARTONS] = {NULL, NULL};
    TBranch* m_brTrueVtxX                        = NULL;
    TBranch* m_brTrueVtxY                        = NULL;
    TBranch* m_brTrueVtxZ                        = NULL;
    TBranch* m_brTrueSumPar                      = NULL;
    TBranch* m_brTrueJetID                       = NULL;
    TBranch* m_brTrueJetNumCst                   = NULL;
    TBranch* m_brTrueJetEne                      = NULL;
    TBranch* m_brTrueJetPt                       = NULL;
    TBranch* m_brTrueJetEta                      = NULL;
    TBranch* m_brTrueJetPhi                      = NULL;
    TBranch* m_brTrueJetArea                     = NULL;
    TBranch* m_brTrueCstID                       = NULL;
    TBranch* m_brTrueCstZ                        = NULL;
    TBranch* m_brTrueCstDr                       = NULL;
    TBranch* m_brTrueCstEne                      = NULL;
    TBranch* m_brTrueCstJt                       = NULL;
    TBranch* m_brTrueCstEta                      = NULL;
    TBranch* m_brTrueCstPhi                      = NULL;

    // input reco. tree branch members
    TBranch* m_brRecoNumJets    = NULL;
    TBranch* m_brRecoNumTrks    = NULL;
    TBranch* m_brRecoVtxX       = NULL;
    TBranch* m_brRecoVtxY       = NULL;
    TBranch* m_brRecoVtxZ       = NULL;
    TBranch* m_brRecoSumECal    = NULL;
    TBranch* m_brRecoSumHCal    = NULL;
    TBranch* m_brRecoJetID      = NULL;
    TBranch* m_brRecoJetNumCst  = NULL;
    TBranch* m_brRecoJetEne     = NULL;
    TBranch* m_brRecoJetPt      = NULL;
    TBranch* m_brRecoJetEta     = NULL;
    TBranch* m_brRecoJetPhi     = NULL;
    TBranch* m_brRecoJetArea    = NULL;
    TBranch* m_brRecoCstMatchID = NULL;
    TBranch* m_brRecoCstZ       = NULL;
    TBranch* m_brRecoCstDr      = NULL;
    TBranch* m_brRecoCstEne     = NULL;
    TBranch* m_brRecoCstJt      = NULL;
    TBranch* m_brRecoCstEta     = NULL;
    TBranch* m_brRecoCstPhi     = NULL;

};

#endif

// end ------------------------------------------------------------------------
