/*
 * Title:    MyPDF
 * Author:   Cameron S. Embree
 * Contact:  CSEmbree@gmail.com
 * Created:  01-Jun-2013
 * Edited:   22-Jun-2013
 * Notes:    
 */

#ifndef __MY_PDF_H
#define __MY_PDF_H

//void getPDF(const double& x, const double& Q, double* xf) {
//    evolvepdf_(&x, &Q, xf);
//}


#include <stdlib.h> // exit()
#include <sstream>  // needed for internal io
#include <iomanip>
//root
#include "root.h"

//appl_grid
#include "appl_grid/appl_grid.h"
#include "appl_grid/generic_pdf.h"

//LHAPDF
#include "LHAPDF/LHAPDF.h"
#include "LHAPDF.h"

#define DEFAULT -1

using namespace std;

class MyPDF {

    public:
        //VARIABLES

        TGraphAsymmErrors *h_PDFBand_results;
        TGraphAsymmErrors *h_PDFBand_results_ratio_to_ref;
        TGraphAsymmErrors *h_AlphaS_results;
        TGraphAsymmErrors *h_AlphaS_results_ratio_to_ref;

        string calc_desc;
        
        bool applgridok;


        //METHODS

        MyPDF(string _steeringFile, int ifl, double q2, TH1D* h1);
        MyPDF(string _gridName, string _steeringFile="steering_mypdf.txt",
              bool _do_PDFBand=true, bool _do_AlphaS=true);

        virtual ~MyPDF() { CleanUpMyPDF(); }; //destructor
        
        // method for PDF standalone plots

        TH1D * FillPdfHisto();

        void CleanUpMyPDF();
        void Initialize();
        void Print();
        void ReadSteering(const string _fileName);

        void InitializeErrorGraphs();
        void CalcSystErrors();
        void CalcPDFBandErrors();
        void CalcAlphaSErrors();
        //void CalcTotErrors();
        void GetRatioToTH1(TH1D* href);
        TH1D* GetPDFRatio(int iset1, int iset2=0);
        void DrawPDFRatio(int iset1, int iset2=0);
        void DrawPDFBand();

        double GetPDFWeight(int iset1, double x1, double x2);

        double GetMaximum(int iset);
        double GetMinimum(int iset);

        TGraphAsymmErrors* MyTGraphErrorsDivide(TGraphAsymmErrors* g1,TGraphAsymmErrors* g2, Int_t noerr=1);
        TGraphAsymmErrors* TH1TOTGraphAsymm(TH1 *h1);
        
        //accessor methods
        bool IsDebugOn() const{return debug;};
        //string GetSteeringFilePath() const{return steeringFilePath;};
        //string GetSteeringFileDir() const{return steeringFileDir;};
        string GetSteeringFileName() const{return steeringFileName;};
        string GetPDFtype() const{return PDFtype;};
        string GetPDFName() const{return PDFname;};
        string GetPDFFullname(){ return default_pdf_set_name;};
        int GetNumPDFMembers() const{return n_PDFMembers;};
        int GetFillStyleCode() const{return fillStyleCode;};
        int GetFillColorCode() const{return fillColorCode;};
	int GetMarkerStyle() const{return markerStyle;};
	int GetMarkerColor() const{return fillColorCode;}; //should be marker color, using fill color as default
        string GetPDFBandType() const{return PDFBandType;};
        string GetPDFErrorType() const{return PDFErrorType;};
        string GetPDFErrorSize() const{return PDFErrorSize;};
        
        bool GetDoPDFBand() const{return do_PDFBand;};
        bool GetDoAlphaS() const{return do_AlphaS;};
        
        int GetAlphaSmemberNumDown() const{return AlphaSmemberNumDown;};
        int GetAlphaSmemberNumUp() const{return AlphaSmemberNumUp;};
        string GetAlphaSPDFSetNameDown() const{return AlphaSPDFSetNameDown;};
        string GetAlphaSPDFSetNameUp() const{return AlphaSPDFSetNameUp;};
        string GetAlphaSPDFSetHistNameDown() const{return AlphaSPDFSetHistNameDown;};
        string GetAlphaSPDFSetHistNameUp() const{return AlphaSPDFSetHistNameUp;};

        TGraphAsymmErrors *GetScaleDependence(double renscale, double facscale, int pdfset);
        
        //mutator methods
        void SetDebug(bool _debug);
        void SetGridName(string _gridName);
        void SetSteeringFilePath(string _steeringFilePath);
        void SetSteeringFileDir(string _steeringFileDir);
        void SetSteeringFileName(string _steeringFileName);
        void SetPDFtype(string _PDFtype);
        void SetPDFname(string _PDFname);
        void SetNumPDFMembers(int _n_PDFMembers);
        void SetFillStyleCode(int _fillStyleCode);
        void SetFillColorCode(int _fillColorCode);
        void SetPDFBandType(string _PDFBandType);
        void SetPDFErrorType(string _PDFErrorType);
        void SetPDFErrorSize(string _PDFErrorSize);
        
        void SetDoPDFBand(bool _doit);
        void SetDoAplphaS(bool _doit);
        //void SetDoRenormalizationScale(bool _doit);
        //void SetDoFactorizationScale(bool _doit);
        void SetDoTotError(bool _doit);
        
        void SetAlphaSmemberNumDown(int _memberNum);
        void SetAlphaSmemberNumUp(int _memberNum);
        void SetAlphaSPDFSetNameDown(string _name);
        void SetAlphaSPDFSetNameUp(string _name);
        void SetAlphaSPDFSetHistNameDown(string _name);
        void SetAlphaSPDFSetHistNameUp(string _name);

        TH1D * GetPdfdefault(){ return hpdfdefault;};

    private:
        //VARIABLES
        bool debug;

        string default_pdf_set_name;

        int nLoops;                 // order of the theory prediction. L0=0, NLO=1, NNLO=2
        //string steeringFilePath;
        //string steeringFileDir;
        string steeringFileName;    // name of steering file
        string PDFtype;             // general name for PDF, used for printing. EX: "MSTW2008nlo"
        string PDFname;             // specific name for PDF, used for looking up a particular PDF. EX: "MSTW2008nlo68cl"
        string PDFnamevar;          // for variation files like HERAPDF
        int n_PDFMembers;
        int defaultpdfid;           // set number of default PDF
        int defaultpdfidvar;        // set number of default PDF in variation file
        int firsteig;               // first eigenvector component
        int lasteig;                // last eigenvector component
        int firstquadvar;           // first eigenvector in variation sample to be added in quadrature
        int lastquadvar;            // last eigenvector in variation sample to be added in quadrature
        int firstmaxvar;            // first eigenvector to look maximum
        int lastmaxvar;             // last eigenvector  to look for maximum

        int fillStyleCode;
        int fillColorCode;
	int markerStyle;            //optional marker style
        string PDFBandType;
        string PDFErrorType;
        string PDFErrorSize;

        bool f_PDFBandType;
        bool f_PDFErrorSize;
        string pdfSetPath;
        
        // for HERA type PDFS
        bool includeEIG;  // include experimental eigenvectors
        bool includeQUAD; // include model variations added in quadrature
        bool includeMAX;  // include parameterisation variations take maximum among those

 
        int AlphaSmemberNumDown; //needed if do_AlphaS is set. Can be read from steering or set by mutator
        int AlphaSmemberNumUp;
        string AlphaSPDFSetNameDown;
        string AlphaSPDFSetNameUp;
        string AlphaSPDFSetHistNameDown;
        string AlphaSPDFSetHistNameUp;
        
        appl::grid *my_grid;

        std::vector<TH1D*> h_errors_AlphaS;
        std::vector<TH1D*> h_errors_PDFBand;

        TH1D *hpdfdefault;

	/*
        std::vector<TH1D*> h_errors_RenormalizationScale;
        std::vector<TH1D*> h_errors_FactorizationScale;
        */
        string gridName;
        
        //double xscale;
        bool do_PDFBand;
        bool do_AlphaS;
        //bool do_RenormalizationScale;
        //bool do_FactorizationScale;
        //bool do_TotError;
        
        //METHODS
        bool FileExists(const string _fileName);
        void SetVariablesDefault();
        //void SetSteeringFileNameAndDir(const string _path);
        string GetEnv( const string & var);

        // variable for PDF plotting
        int ifl; // flavour as from LHAPDF
        double Q2; // Q2 value used in LHAPDF
        TH1D * hpdf; //histo to store PDS PDF vs x 

};


const string defaultPDFSetPath="PDFsets";


#endif
