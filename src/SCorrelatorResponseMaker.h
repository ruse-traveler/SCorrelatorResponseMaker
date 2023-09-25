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

// standard c includes
#include <cmath>
#include <string>
#include <vector>
#include <cassert>
#include <sstream>
#include <cstdlib>
#include <utility>
// root includes
#include "TH1.h"
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TMath.h"
#include "TString.h"
#include "TVector3.h"  // TODO update to XYZvector
#include "TDirectory.h"
// f4a include
#include <fun4all/SubsysReco.h>
#include <fun4all/Fun4AllReturnCodes.h>
#include <fun4all/Fun4AllHistoManager.h>
// phool includes
#include <phool/phool.h>
#include <phool/getClass.h>
#include <phool/PHIODataNode.h>
#include <phool/PHNodeIterator.h>
#include <phool/PHCompositeNode.h>
// analysis-specific includes
#include "/sphenix/user/danderson/eec/SCorrelatorUtilities/SCorrelatorUtilities.h"

using namespace std;
using namespace SCorrelatorUtilities;



// SCorrelatorResponseMaker definition -----------------------------------------------

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

    // setters (inline)
    void SetVerbosity(const int verb)           {m_verbosity   = verb;}
    void SetOutputFile(const string &oFileName) {m_outFileName = oFileName;}

    // setters (*.io.h)
    void SetInputNodes(const string &iTrueNodeName, const string &iRecoNodeName);
    void SetInputFiles(const string &iTrueFileName, const string &iRecoFileName);
    void SetInputTrees(const string &iTrueTreeName, const string &iRecoTreeName);
    void SetJetMatchQtRange(const pair<double, double> qtRange);
    void SetJetMatchDrRange(const pair<double, double> drRange);

    // system getters
    int    GetVerbosity()         {return m_verbosity;}
    bool   GetInDebugMode()       {return m_inDebugMode;}
    bool   GetInComplexMode()     {return m_inComplexMode;}
    bool   GetInStandaloneMode()  {return m_inStandaloneMode;}
    string GetInputTrueFileName() {return m_inTrueFileName;}
    string GetInputRecoFileName() {return m_inRecoFileName;}
    string GetInputTrueNodeName() {return m_inTrueNodeName;}
    string GetInputRecoNodeName() {return m_inRecoNodeName;}
    string GetInputTrueTreeName() {return m_inTrueTreeName;}
    string GetInputRecoTreeName() {return m_inRecoTreeName;}
    string GetOutputFileName()    {return m_outFileName;}

    // matching getters
    pair<double, double> GetJetMatchQtRange() {return m_jetMatchQtRange;}
    pair<double, double> GetJetMatchDrRange() {return m_jetMatchDrRange;}

  private:

    // constants
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
    int    m_fTrueCurrent     = 0;
    int    m_fRecoCurrent     = 0;
    int    m_verbosity        = 0;
    bool   m_inDebugMode      = false;
    bool   m_inBatchMode      = false;
    bool   m_inComplexMode    = false;
    bool   m_inStandaloneMode = true;
    string m_moduleName       = "";
    string m_inTrueFileName   = "";
    string m_inRecoFileName   = "";
    string m_inTrueNodeName   = "";
    string m_inRecoNodeName   = "";
    string m_inTrueTreeName   = "";
    string m_inRecoTreeName   = "";
    string m_outFileName      = "";

    // matching members
    pair<float, float>   m_fracCstMatchRange = {0., 1.};
    pair<double, double> m_jetMatchQtRange   = {0., 10.};
    pair<double, double> m_jetMatchDrRange   = {0., 10.};

    // input address members
    EvtInfo m_evtInfo;
    JetInfo m_jetInfo;
    CstInfo m_cstInfo;

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
