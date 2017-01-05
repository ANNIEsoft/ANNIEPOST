#include "RootOutput.h"

RootOutput::RootOutput():Tool(){}


bool RootOutput::Initialise(std::string configfile, DataModel &data){

  if(configfile!="")  m_variables.Initialise(configfile);
  //m_variables.Print();

  m_data= &data;

  std::string outpath, suffix;

  m_variables.Get("OutPath",outpath);
  m_variables.Get("Suffix",suffix);

  std::stringstream tmp;
  tmp<<outpath<<m_data->outfile<<suffix;
  file= new TFile(tmp.str().c_str(),"RECREATE","test",9);
 

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

  return true;
}
