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

using namespace std;



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
    void SetJetMatchQtRange(const pair<double, double>);
    void SetJetMatchDrRange(const pair<double, double>);

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

    // matching getters (*.io.h)
    pair<double, double> GetJetMatchQtRange();
    pair<double, double> GetJetMatchDrRange();

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
    bool IsJetGoodMatch(const double qtJet, const double drJet);

    // system methods (*.sys.h)
    void    InitializeAddresses();
    void    InitializeTrees();
    void    PrintMessage(const uint32_t code);
    void    PrintDebug(const uint32_t code);
    void    PrintError(const uint32_t code);
    bool    CheckCriticalParameters();
    int64_t GetEntry(const uint64_t entry, TTree *tree);
    int64_t LoadTree(const uint64_t entry, TTree *tree, int &fCurrent);

    // io members
    TFile* m_outFile    = 0x0;
    TFile* m_inTrueFile = 0x0;
    TFile* m_inRecoFile = 0x0;
    TTree* m_inTrueTree = 0x0;
    TTree* m_inRecoTree = 0x0;

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

    // matching parameters
    double m_minPercentMatchCsts            = 0;
    double m_jetMatchQtRange[CONST::NRANGE] = {0., 0.};
    double m_jetMatchDrRange[CONST::NRANGE] = {0., 0.};

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

    // output response tree address members
    pair<int, int>                                         m_matchNumJets;
    pair<int, int>                                         m_matchNumTrks;
    pair<double, double>                                   m_matchVtxX;
    pair<double, double>                                   m_matchVtxY;
    pair<double, double>                                   m_matchVtxZ;
    pair<vector<uint32_t>*, vector<uint32_t>*>             m_matchJetID;
    pair<vector<uint64_t>*, vector<uint64_t>*>             m_matchJetNumCst;
    pair<vector<double>*, vector<double>*>                 m_matchJetEne;
    pair<vector<double>*, vector<double>*>                 m_matchJetPt;
    pair<vector<double>*, vector<double>*>                 m_matchJetEta;
    pair<vector<double>*, vector<double>*>                 m_matchJetPhi;
    pair<vector<double>*, vector<double>*>                 m_matchJetArea;
    pair<vector<vector<int>>*, vector<vector<int>>*>       m_matchCstMatchID;
    pair<vector<vector<double>>*, vector<vector<double>>*> m_matchCstZ;
    pair<vector<vector<double>>*, vector<vector<double>>*> m_matchCstDr;
    pair<vector<vector<double>>*, vector<vector<double>>*> m_matchCstEne;
    pair<vector<vector<double>>*, vector<vector<double>>*> m_matchCstJt;
    pair<vector<vector<double>>*, vector<vector<double>>*> m_matchCstEta;
    pair<vector<vector<double>>*, vector<vector<double>>*> m_matchCstPhi;

    // input truth tree branch members
    TBranch* m_brTrueNumJets                     = 0x0;
    TBranch* m_brTrueNumChrgPars                 = 0x0;
    TBranch* m_brTruePartonID[CONST::NPARTONS]   = {0x0, 0x0};
    TBranch* m_brTruePartonMomX[CONST::NPARTONS] = {0x0, 0x0};
    TBranch* m_brTruePartonMomY[CONST::NPARTONS] = {0x0, 0x0};
    TBranch* m_brTruePartonMomZ[CONST::NPARTONS] = {0x0, 0x0};
    TBranch* m_brTrueVtxX                        = 0x0;
    TBranch* m_brTrueVtxY                        = 0x0;
    TBranch* m_brTrueVtxZ                        = 0x0;
    TBranch* m_brTrueSumPar                      = 0x0;
    TBranch* m_brTrueJetID                       = 0x0;
    TBranch* m_brTrueJetNumCst                   = 0x0;
    TBranch* m_brTrueJetEne                      = 0x0;
    TBranch* m_brTrueJetPt                       = 0x0;
    TBranch* m_brTrueJetEta                      = 0x0;
    TBranch* m_brTrueJetPhi                      = 0x0;
    TBranch* m_brTrueJetArea                     = 0x0;
    TBranch* m_brTrueCstID                       = 0x0;
    TBranch* m_brTrueCstZ                        = 0x0;
    TBranch* m_brTrueCstDr                       = 0x0;
    TBranch* m_brTrueCstEne                      = 0x0;
    TBranch* m_brTrueCstJt                       = 0x0;
    TBranch* m_brTrueCstEta                      = 0x0;
    TBranch* m_brTrueCstPhi                      = 0x0;

    // input reco. tree branch members
    TBranch* m_brRecoNumJets    = 0x0;
    TBranch* m_brRecoNumTrks    = 0x0;
    TBranch* m_brRecoVtxX       = 0x0;
    TBranch* m_brRecoVtxY       = 0x0;
    TBranch* m_brRecoVtxZ       = 0x0;
    TBranch* m_brRecoSumECal    = 0x0;
    TBranch* m_brRecoSumHCal    = 0x0;
    TBranch* m_brRecoJetID      = 0x0;
    TBranch* m_brRecoJetNumCst  = 0x0;
    TBranch* m_brRecoJetEne     = 0x0;
    TBranch* m_brRecoJetPt      = 0x0;
    TBranch* m_brRecoJetEta     = 0x0;
    TBranch* m_brRecoJetPhi     = 0x0;
    TBranch* m_brRecoJetArea    = 0x0;
    TBranch* m_brRecoCstMatchID = 0x0;
    TBranch* m_brRecoCstZ       = 0x0;
    TBranch* m_brRecoCstDr      = 0x0;
    TBranch* m_brRecoCstEne     = 0x0;
    TBranch* m_brRecoCstJt      = 0x0;
    TBranch* m_brRecoCstEta     = 0x0;
    TBranch* m_brRecoCstPhi     = 0x0;

   // output response tree branch members
   TBranch* m_brMatchNumJets[CONST::NLEVELS]     = {0x0, 0x0};
   TBranch* m_brMatchNumChrgPars[CONST::NLEVELS] = {0x0, 0x0};
   TBranch* m_brMatchVtxX[CONST::NLEVELS]        = {0x0, 0x0};
   TBranch* m_brMatchVtxY[CONST::NLEVELS]        = {0x0, 0x0};
   TBranch* m_brMatchVtxZ[CONST::NLEVELS]        = {0x0, 0x0};
   TBranch* m_brMatchJetID[CONST::NLEVELS]       = {0x0, 0x0};
   TBranch* m_brMatchJetNumCst[CONST::NLEVELS]   = {0x0, 0x0};
   TBranch* m_brMatchJetEne[CONST::NLEVELS]      = {0x0, 0x0};
   TBranch* m_brMatchJetPt[CONST::NLEVELS]       = {0x0, 0x0};
   TBranch* m_brMatchJetEta[CONST::NLEVELS]      = {0x0, 0x0};
   TBranch* m_brMatchJetPhi[CONST::NLEVELS]      = {0x0, 0x0};
   TBranch* m_brMatchJetArea[CONST::NLEVELS]     = {0x0, 0x0};
   TBranch* m_brMatchCstZ[CONST::NLEVELS]        = {0x0, 0x0};
   TBranch* m_brMatchCstDr[CONST::NLEVELS]       = {0x0, 0x0};
   TBranch* m_brMatchCstEne[CONST::NLEVELS]      = {0x0, 0x0};
   TBranch* m_brMatchCstJt[CONST::NLEVELS]       = {0x0, 0x0};
   TBranch* m_brMatchCstEta[CONST::NLEVELS]      = {0x0, 0x0};
   TBranch* m_brMatchCstPhi[CONST::NLEVELS]      = {0x0, 0x0};

};

#endif

// end ------------------------------------------------------------------------
