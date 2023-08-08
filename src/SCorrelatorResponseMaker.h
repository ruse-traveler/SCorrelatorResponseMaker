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
    enum CONSTANTS {
      NRANGE   = 2,
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
    void    InitializeMembers();
    void    InitializeTrees();
    void    PrintMessage(const uint32_t code);
    void    PrintDebug(const uint32_t code);
    void    PrintError(const uint32_t code);
    bool    CheckCriticalParameters();
    int64_t GetEntry(const uint64_t entry, TTree *tree);
    int64_t LoadTree(const uint64_t entry, TTree *tree, int &fCurrent);

    // io members
    TFile *m_outFile;
    TFile *m_inTrueFile;
    TFile *m_inRecoFile;
    TTree *m_inTrueTree;
    TTree *m_inRecoTree;

    // system members
    int    m_fTrueCurrent;
    int    m_fRecoCurrent;
    int    m_verbosity;
    bool   m_inDebugMode;
    bool   m_inBatchMode;
    bool   m_inComplexMode;
    bool   m_inStandaloneMode;
    string m_moduleName;
    string m_inTrueFileName;
    string m_inRecoFileName;
    string m_inTrueNodeName;
    string m_inRecoNodeName;
    string m_inTrueTreeName;
    string m_inRecoTreeName;
    string m_outFileName;

    // matching parameters
    double m_minPercentMatchCsts;
    double m_jetMatchQtRange[CONSTANTS::NRANGE];
    double m_jetMatchDrRange[CONSTANTS::NRANGE];

    // input truth tree address members
    int                     m_trueNumJets;
    int                     m_trueNumChrgPars;
    int                     m_truePartonID[CONSTANTS::NPARTONS];
    double                  m_truePartonMomX[CONSTANTS::NPARTONS];
    double                  m_truePartonMomY[CONSTANTS::NPARTONS];
    double                  m_truePartonMomZ[CONSTANTS::NPARTONS];
    double                  m_trueVtxX;
    double                  m_trueVtxY;
    double                  m_trueVtxZ;
    double                  m_trueSumPar;
    vector<unsigned int>   *m_trueJetID;
    vector<unsigned long>  *m_trueJetNumCst;
    vector<double>         *m_trueJetEne;
    vector<double>         *m_trueJetPt;
    vector<double>         *m_trueJetEta;
    vector<double>         *m_trueJetPhi;
    vector<double>         *m_trueJetArea;
    vector<vector<int>>    *m_trueCstID;
    vector<vector<double>> *m_trueCstZ;
    vector<vector<double>> *m_trueCstDr;
    vector<vector<double>> *m_trueCstEne;
    vector<vector<double>> *m_trueCstJt;
    vector<vector<double>> *m_trueCstEta;
    vector<vector<double>> *m_trueCstPhi;

    // input reco. tree address members
    int                     m_recoNumJets;
    int                     m_recoNumTrks;
    double                  m_recoVtxX;
    double                  m_recoVtxY;
    double                  m_recoVtxZ;
    double                  m_recoSumECal;
    double                  m_recoSumHCal;
    vector<unsigned int>   *m_recoJetID;
    vector<unsigned long>  *m_recoJetNumCst;
    vector<double>         *m_recoJetEne;
    vector<double>         *m_recoJetPt;
    vector<double>         *m_recoJetEta;
    vector<double>         *m_recoJetPhi;
    vector<double>         *m_recoJetArea;
    vector<vector<int>>    *m_recoCstMatchID;
    vector<vector<double>> *m_recoCstZ;
    vector<vector<double>> *m_recoCstDr;
    vector<vector<double>> *m_recoCstEne;
    vector<vector<double>> *m_recoCstJt;
    vector<vector<double>> *m_recoCstEta;
    vector<vector<double>> *m_recoCstPhi;

    // input truth tree branch members
    TBranch *m_brTrueNumJets;
    TBranch *m_brTrueNumChrgPars;
    TBranch *m_brTruePartonID[CONSTANTS::NPARTONS];
    TBranch *m_brTruePartonMomX[CONSTANTS::NPARTONS];
    TBranch *m_brTruePartonMomY[CONSTANTS::NPARTONS];
    TBranch *m_brTruePartonMomZ[CONSTANTS::NPARTONS];
    TBranch *m_brTrueVtxX;
    TBranch *m_brTrueVtxY;
    TBranch *m_brTrueVtxZ;
    TBranch *m_brTrueSumPar;
    TBranch *m_brTrueJetID;
    TBranch *m_brTrueJetNumCst;
    TBranch *m_brTrueJetEne;
    TBranch *m_brTrueJetPt;
    TBranch *m_brTrueJetEta;
    TBranch *m_brTrueJetPhi;
    TBranch *m_brTrueJetArea;
    TBranch *m_brTrueCstID;
    TBranch *m_brTrueCstZ;
    TBranch *m_brTrueCstDr;
    TBranch *m_brTrueCstEne;
    TBranch *m_brTrueCstJt;
    TBranch *m_brTrueCstEta;
    TBranch *m_brTrueCstPhi;

    // input reco. tree branch members
    TBranch *m_brRecoNumJets;
    TBranch *m_brRecoNumTrks;
    TBranch *m_brRecoVtxX;
    TBranch *m_brRecoVtxY;
    TBranch *m_brRecoVtxZ;
    TBranch *m_brRecoSumECal;
    TBranch *m_brRecoSumHCal;
    TBranch *m_brRecoJetID;
    TBranch *m_brRecoJetNumCst;
    TBranch *m_brRecoJetEne;
    TBranch *m_brRecoJetPt;
    TBranch *m_brRecoJetEta;
    TBranch *m_brRecoJetPhi;
    TBranch *m_brRecoJetArea;
    TBranch *m_brRecoCstMatchID;
    TBranch *m_brRecoCstZ;
    TBranch *m_brRecoCstDr;
    TBranch *m_brRecoCstEne;
    TBranch *m_brRecoCstJt;
    TBranch *m_brRecoCstEta;
    TBranch *m_brRecoCstPhi;

};

#endif

// end ------------------------------------------------------------------------
