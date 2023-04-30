// ----------------------------------------------------------------------------
// 'SCorrelatorFolder.h'
// Derek Anderson
// 04.30.2023
//
// A module to unfold, backfold, and/or
// perform corrections on an n-point
// energy correlation strength function.
// ----------------------------------------------------------------------------

#ifndef SCORRELATORFOLDER_H
#define SCORRELATORFOLDER_H

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



// SCorrelatorFolder definition -----------------------------------------------

class SCorrelatorFolder : public SubsysReco {

  public:

    // ctor/dtor
    SCorrelatorFolder(const string &name = "SCorrelatorFolder", const bool isComplex = false, const bool doDebug = false, const bool inBatch = false);
    ~SCorrelatorFolder() override;

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
    void SetInputNode(const string &iNodeName)  {m_inNodeName  = iNodeName;}
    void SetInputFile(const string &iFileName)  {m_inFileName  = iFileName;}
    void SetOutputFile(const string &oFileName) {m_outFileName = oFileName;}
    void SetJetMatchQtRange(const pair<double, double> qtRange);
    void SetJetMatchDrRange(const pair<double, double> drRange);
    void SetCstMatchQtRange(const pair<double, double> qtRange);
    void SetCstMatchDrRange(const pair<double, double> drRange);

    // setters (*.io.h)
    void SetInputTree(const string &iTreeName, const bool isTruthTree = false);

    // matching getters
    double GetJetMatchMinQt() {return m_jetMatchQtRange[0];}
    double GetJetMatchMaxQt() {return m_jetMatchQtRange[1];}
    double GetJetMatchMinDr() {return m_jetMatchDrRange[0];}
    double GetJetMatchMaxDr() {return m_jetMatchDrRange[1];}
    double GetCstMatchMinQt() {return m_cstMatchQtRange[0];}
    double GetCstMatchMaxQt() {return m_cstMatchQtRange[1];}
    double GetCstMatchMinDr() {return m_cstMatchDrRange[0];}
    double GetCstMatchMaxDr() {return m_cstMatchDrRange[1];}

    // system getters
    int      GetVerbosity()        {return m_verbosity;}
    bool     GetInDebugMode()      {return m_inDebugMode;}
    bool     GetInComplexMode()    {return m_inComplexMode;}
    bool     GetInStandaloneMode() {return m_inStandaloneMode;}
    string   GetInputFileName()    {return m_inFileName;}
    string   GetInputNodeName()    {return m_inNodeName;}
    string   GetInputTreeName()    {return m_inTreeName;}
    string   GetOutputFileName()   {return m_outFileName;} 

  private:

    // io methods (*.io.h)
    void GrabInputNode();
    void OpenInputFile();
    void OpenOutputFile();
    void SaveOutput();

    // analysis methods (*.ana.h)
    void DoMatching();
    bool IsJetGoodMatch(const double qtJet, const double drJet);
    bool IsCstGoodMatch(const double qtCst, const double drCst);

    // system methods (*.sys.h)
    void    InitializeMembers();
    void    InitializeTree();
    void    PrintMessage(const uint32_t code, const uint64_t nEvts = 0, const uint64_t event = 0);
    void    PrintDebug(const uint32_t code);
    void    PrintError(const uint32_t code, const size_t nDrBinEdges = 0, const size_t iDrBin = 0);
    bool    CheckCriticalParameters();
    int64_t LoadTree(const uint64_t entry);
    int64_t GetEntry(const uint64_t entry);

    // io members
    TFile *m_outFile;
    TFile *m_inFile;
    TTree *m_inTree;

    // system members
    int    m_fCurrent;
    int    m_verbosity;
    bool   m_inDebugMode;
    bool   m_inBatchMode;
    bool   m_inComplexMode;
    bool   m_inStandaloneMode;
    bool   m_isInputTreeTruth;
    string m_moduleName;
    string m_inFileName;
    string m_inNodeName;
    string m_inTreeName;
    string m_outFileName;

    // matching parameters
    double m_jetMatchQtRange[NRange];
    double m_jetMatchDrRange[NRange];
    double m_cstMatchQtRange[NRange];
    double m_cstMatchDrRange[NRange];

    // input truth tree address members
    int    m_truParton3_ID;
    int    m_truParton4_ID;
    double m_truParton3_MomX;
    double m_truParton3_MomY;
    double m_truParton3_MomZ;
    double m_truParton4_MomX;
    double m_truParton4_MomY;
    double m_truParton4_MomZ;
    // input reco. tree address members
    int    m_recParton3_ID;
    int    m_recParton4_ID;
    double m_recParton3_MomX;
    double m_recParton3_MomY;
    double m_recParton3_MomZ;
    double m_recParton4_MomX;
    double m_recParton4_MomY;
    double m_recParton4_MomZ;

    // generic input tree address members
    int                     m_evtNumJets;
    vector<unsigned long>  *m_jetNumCst;
    vector<unsigned int>   *m_jetID;
    vector<unsigned int>   *m_jetTruthID;
    vector<double>         *m_jetEnergy;
    vector<double>         *m_jetPt;
    vector<double>         *m_jetEta;
    vector<double>         *m_jetPhi;
    vector<double>         *m_jetArea;
    vector<vector<double>> *m_cstZ;
    vector<vector<double>> *m_cstDr;
    vector<vector<double>> *m_cstEnergy;
    vector<vector<double>> *m_cstJt;
    vector<vector<double>> *m_cstEta;
    vector<vector<double>> *m_cstPhi;

    // input truth tree branch members
    TBranch *m_brTruParton3_ID;
    TBranch *m_brTruParton4_ID;
    TBranch *m_brTruParton3_MomX;
    TBranch *m_brTruParton3_MomY;
    TBranch *m_brTruParton3_MomZ;
    TBranch *m_brTruParton4_MomX;
    TBranch *m_brTruParton4_MomY;
    TBranch *m_brTruParton4_MomZ;
    // input reco. tree branch members
    TBranch *m_brRecParton3_ID;
    TBranch *m_brRecParton4_ID;
    TBranch *m_brRecParton3_MomX;
    TBranch *m_brRecParton3_MomY;
    TBranch *m_brRecParton3_MomZ;
    TBranch *m_brRecParton4_MomX;
    TBranch *m_brRecParton4_MomY;
    TBranch *m_brRecParton4_MomZ;

    // generic input tree branch members
    TBranch *m_brEvtNumJets;
    TBranch *m_brJetNumCst;
    TBranch *m_brJetID;
    TBranch *m_brJetTruthID;
    TBranch *m_brJetEnergy;
    TBranch *m_brJetPt;
    TBranch *m_brJetEta;
    TBranch *m_brJetPhi;
    TBranch *m_brJetArea;
    TBranch *m_brCstZ;
    TBranch *m_brCstDr;
    TBranch *m_brCstEnergy;
    TBranch *m_brCstJt;
    TBranch *m_brCstEta;
    TBranch *m_brCstPhi;

};

#endif

// end ------------------------------------------------------------------------
