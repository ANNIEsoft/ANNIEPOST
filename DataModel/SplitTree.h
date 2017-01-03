//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Oct 27 04:04:04 2016 by ROOT version 5.34/34
// from TTree PMTData/PMTData
// found on file: test.root
//////////////////////////////////////////////////////////

#ifndef SplitTree_h
#define SplitTree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

#include <sstream>
// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class SplitTree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   TTree          *uncaltree;   
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   ULong64_t       LastSync;
   Int_t           SequenceID;
   Int_t           StartTimeSec;
   Int_t           StartTimeNSec;
   ULong64_t       StartCount;
   Int_t           TriggerNumber;
   ULong64_t       TriggerCount;
   Int_t           CardID;
   Int_t           Channel;
   UInt_t          Rate;
   Int_t           BufferSize;
   Int_t           Trigger;
   UShort_t        UnCalData[40000];   //[BufferSize]
   Float_t         Data[40000];   //[BufferSize]
   Int_t           PMTID;
   Int_t           PMTf;
   Int_t           PMTx;
   Int_t           PMTy;
   Int_t           PMTz;

   // List of branches
   TBranch        *b_LastSync;   //!
   TBranch        *b_SequenceID;   //!
   TBranch        *b_StartTimeSec;   //!
   TBranch        *b_StartTimeNSec;   //!
   TBranch        *b_StartCount;   //!
   TBranch        *b_TriggerNumber;   //!
   TBranch        *b_TriggerCount;   //!
   TBranch        *b_CardID;   //!
   TBranch        *b_Channel;   //!
   TBranch        *b_Rate;   //!
   TBranch        *b_BufferSize;   //!
   TBranch        *b_Trigger;   //!
   TBranch        *b_UnCalData;   //!
   TBranch        *b_Data;   //!
   TBranch        *b_PMTID;   //!
   TBranch        *b_PMTf;   //!
   TBranch        *b_PMTx;   //!
   TBranch        *b_PMTy;   //!
   TBranch        *b_PMTz;   //!

   SplitTree(TTree *tree=0);
   SplitTree(std::string name);
   virtual ~SplitTree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   virtual void    Fill();
};

#endif

#ifdef SplitTree_cxx

SplitTree::SplitTree(std::string name){

  fChain=new TTree(name.c_str(),name.c_str());
  uncaltree=new TTree("tmp","tmp");
  // TBranch* br;
  b_LastSync=fChain->Branch("LastSync",&LastSync,"LastSync/l");
  b_LastSync->SetCompressionLevel(4);
  b_SequenceID=fChain->Branch("SequenceID", &SequenceID, "SequenceID/I");
  b_SequenceID->SetCompressionLevel(4);
  b_StartTimeSec=fChain->Branch("StartTimeSec", &StartTimeSec, "StartTimeSec/I");
  b_StartTimeSec->SetCompressionLevel(4);
  b_StartTimeNSec=fChain->Branch("StartTimeNSec", &StartTimeNSec, "StartTimeNSec/I");
  b_StartTimeNSec->SetCompressionLevel(4);
  b_StartCount=fChain->Branch("StartCount", &StartCount, "StartCount/l");
  b_StartCount->SetCompressionLevel(4);
  b_TriggerNumber=fChain->Branch("TriggerNumber", &TriggerNumber, "TriggerNumber/I");
  b_TriggerNumber->SetCompressionLevel(4);
  b_TriggerCount=fChain->Branch("TriggerCount", &TriggerCount, "TriggerCount/l");
  b_TriggerCount->SetCompressionLevel(4);
  b_CardID=fChain->Branch("CardID", &CardID, "CardID/I");
  b_CardID->SetCompressionLevel(4);
  b_Channel=fChain->Branch("Channel", &Channel, "Channel/I");
  b_Channel->SetCompressionLevel(4);
  b_Rate=fChain->Branch("Rate", &Rate, "Rate/i");
  b_Rate->SetCompressionLevel(4);
  b_BufferSize=fChain->Branch("BufferSize", &BufferSize, "BufferSize/I");
  b_BufferSize->SetCompressionLevel(4);
  b_Trigger=fChain->Branch("Trigger", &Trigger, "Trigger/I");
  b_Trigger->SetCompressionLevel(4);
  //    b_PMTf=fChain->Branch("PMTf", &PMTf, "PMTf/I");                                                                                                                                                                 //b_PMTf->SetCompressionLevel(4);                                                                                                                                                                           
  //b_PMTx=fChain->Branch("PMTx", &PMTx, "PMTx/I");                                                                                                                                                                     //b_PMTx->SetCompressionLevel(4);                                                                                                                                                                           
  //b_PMTy=fChain->Branch("PMTy", &PMTy, "PMTy/I");                                                                                                                                                                     //b_PMTy->SetCompressionLevel(4);                                                                                                                                                                           
  //b_PMTz=fChain->Branch("PMTz", &PMTz, "PMTz/I");                                                                                                                                                                     //b_PMTz->SetCompressionLevel(4);                                                                                                                                                                           
  //    b_Data=fChain->Branch("Data", Data, "Data[BufferSize]/F");                                                                                                                                                      //b_Data->SetCompressionLevel(4);                                                                  
  b_UnCalData=uncaltree->Branch("UnCalData", UnCalData, "UnCalData[40000]/s");                                                                                                        
  //  b_UnCalData=uncaltree->Branch("UnCalData", UnCalData, "UnCalData[40000]/s");
  b_UnCalData->SetCompressionLevel(4);
}


SplitTree::SplitTree(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
  uncaltree=0;
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("test.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("test.root");
      }
      f->GetObject("PMTData",tree);

   }
   Init(tree);
}

SplitTree::~SplitTree()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t SplitTree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   if(uncaltree)uncaltree->GetEntry(entry);
   return fChain->GetEntry(entry);
   
}
Long64_t SplitTree::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void SplitTree::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("LastSync", &LastSync, &b_LastSync);
   fChain->SetBranchAddress("SequenceID", &SequenceID, &b_SequenceID);
   fChain->SetBranchAddress("StartTimeSec", &StartTimeSec, &b_StartTimeSec);
   fChain->SetBranchAddress("StartTimeNSec", &StartTimeNSec, &b_StartTimeNSec);
   fChain->SetBranchAddress("StartCount", &StartCount, &b_StartCount);
   fChain->SetBranchAddress("TriggerNumber", &TriggerNumber, &b_TriggerNumber);
   fChain->SetBranchAddress("TriggerCount", &TriggerCount, &b_TriggerCount);
   fChain->SetBranchAddress("CardID", &CardID, &b_CardID);
   fChain->SetBranchAddress("Channel", &Channel, &b_Channel);
   fChain->SetBranchAddress("Rate", &Rate, &b_Rate);
   fChain->SetBranchAddress("BufferSize", &BufferSize, &b_BufferSize);
   fChain->SetBranchAddress("Trigger", &Trigger, &b_Trigger);
   //   fChain->SetBranchAddress("UnCalData", UnCalData, &b_UnCalData);
   fChain->SetBranchAddress("Data", Data, &b_Data);
   fChain->SetBranchAddress("PMTID", &PMTID, &b_PMTID);
   fChain->SetBranchAddress("PMTf", &PMTf, &b_PMTf);
   fChain->SetBranchAddress("PMTx", &PMTx, &b_PMTx);
   fChain->SetBranchAddress("PMTy", &PMTy, &b_PMTy);
   fChain->SetBranchAddress("PMTz", &PMTz, &b_PMTz);
   Notify();
}

Bool_t SplitTree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void SplitTree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}

void SplitTree::Fill()
{
  fChain->Fill();
  if (uncaltree) uncaltree->Fill();
}


Int_t SplitTree::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef SplitTree_cxx
