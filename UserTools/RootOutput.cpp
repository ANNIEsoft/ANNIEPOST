#include "RootOutput.h"

RootOutput::RootOutput():Tool(){}


bool RootOutput::Initialise(std::string configfile, DataModel &data){

  if(configfile!="")  m_variables.Initialise(configfile);
  //m_variables.Print();

  m_data= &data;

  file= new TFile("test.root","RECREATE","test",9);
  // m_data->outtree = new SplitTree("PMTData");

  return true;
}


bool RootOutput::Execute(){
  
  /*  m_data->outtree->LastSync = m_data->splittree->LastSync;
  m_data->outtree->SequenceID = m_data->splittree->SequenceID;
  m_data->outtree->StartTimeSec = m_data->splittree->StartTimeSec;
  m_data->outtree->StartCount = m_data->splittree->StartCount;
  m_data->outtree->TriggerNumber = m_data->splittree->TriggerNumber;
  m_data->outtree->TriggerCount = m_data->splittree->TriggerCount;
  m_data->outtree->Rate = m_data->splittree->Rate;
  m_data->outtree->CardID = m_data->splittree->CardID;
  m_data->outtree->Channel = m_data->splittree->Channel;
  m_data->outtree->BufferSize = m_data->splittree->BufferSize;
  m_data->outtree->Trigger = m_data->splittree->Trigger;

  m_data->outtree->Fill();
  */
  return true;
}


bool RootOutput::Finalise(){
  
  //TFile file("test.root","RECREATE");
  file->cd();
  //  TBranch* b= m_data->splittree->tree->GetBranch("UnCalData");
  //m_data->splittree->tree->GetListOfBranches()->Remove(b);
  //m_data->splittree->tree->GetListOfBranches()->Compress();
  //  b->Reset();
  //  m_data->splittree->tree->Print();
  // TLeaf* l= m_data->splittree->tree.GetLeaf("UnCalData");
  //m_data->splittree->tree.GetListOfLeaves()->Remove(l);
  file->cd();  
  //  std::cout<<"writing"<<std::endl;
  //  m_data->outtree->tree->Print();
  m_data->splittree->fChain->Write();
  m_data->RunInformationData->fChain->Write();
  m_data->MRDData->fChain->Write();
  //m_data->splittree->tree->Print();
  //std::cout<<"written"<<std::endl;

  //  file->Write();
  file->Close();
  //  delete file;

  return true;
}
