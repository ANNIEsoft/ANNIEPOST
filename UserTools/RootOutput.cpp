#include "RootOutput.h"

RootOutput::RootOutput():Tool(){}


bool RootOutput::Initialise(std::string configfile, DataModel &data){

  if(configfile!="")  m_variables.Initialise(configfile);
  //m_variables.Print();

  m_data= &data;

  file=m_data->tmpfile;
  /*
  std::string outpath, suffix;

  m_variables.Get("OutPath",outpath);
  m_variables.Get("Suffix",suffix);

  std::stringstream tmp;
  tmp<<outpath<<m_data->outfile<<suffix;
  file= new TFile(tmp.str().c_str(),"RECREATE","test",9);
  
  
  m_data->splittree->b_LastSync->SetFile(file);   //!
  m_data->splittree->b_SequenceID->SetFile(file);   //!
  m_data->splittree->b_StartTimeSec->SetFile(file);   //!
  m_data->splittree->b_StartTimeNSec->SetFile(file);   //!
  m_data->splittree->b_StartCount->SetFile(file);   //!
  m_data->splittree->b_TriggerNumber->SetFile(file);   //!
  m_data->splittree->b_TriggerCount->SetFile(file);   //!
  m_data->splittree->b_CardID->SetFile(file);   //!
  m_data->splittree->b_Channel->SetFile(file);   //!
  m_data->splittree->b_Rate->SetFile(file);   //!
  m_data->splittree->b_BufferSize->SetFile(file);   //!
  m_data->splittree->b_Trigger->SetFile(file);   //!
  //m_data->splittree->b_UnCalData->SetFile(file);   //!
  m_data->splittree->b_Data->SetFile(file);   //!
  m_data->splittree->b_PMTID->SetFile(file);   //!
  m_data->splittree->b_PMTf->SetFile(file);   //!
  m_data->splittree->b_PMTx->SetFile(file);   //!
  m_data->splittree->b_PMTy->SetFile(file);   //!
  m_data->splittree->b_PMTz->SetFile(file);   //!
  m_data->tmpfile =new TFile("/tmp/tout.root","RECREATE");
  m_data->splittree->b_UnCalData->SetFile(m_data->tmpfile); 
  */
 
  return true;
}


bool RootOutput::Execute(){
  
 
  return true;
}


bool RootOutput::Finalise(){
  
  file->cd();  
  //  std::cout<<"writing"<<std::endl;

  for (std::map<std::string,TTree*>::iterator it=m_data->m_trees.begin(); it!=m_data->m_trees.end(); ++it){
    
    it->second->Write();
    
  }
  
  //m_data->splittree->fChain->Write();
  //m_data->RunInformationData->fChain->Write();
  //m_data->MRDData->fChain->Write();
  //m_data->splittree->tree->Print();
  //std::cout<<"written"<<std::endl;

  file->Close();
  //  delete file;
  //  m_data->tmpfile->Close();

  return true;
}
