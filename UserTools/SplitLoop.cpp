#include "SplitLoop.h"

SplitLoop::SplitLoop():Tool(){}


bool SplitLoop::Initialise(std::string configfile, DataModel &data){

  if(configfile!="")  m_variables.Initialise(configfile);
  //m_variables.Print();

  m_data= &data;

  entry=-1;

  return true;
}


bool SplitLoop::Execute(){

  entry++; 
  
  if(entry<m_data->splittree->fChain->GetEntries()){
    
    if(entry%1000==0) std::cout<<entry<<"/"<<m_data->splittree->fChain->GetEntries()<<std::endl;
    
    m_data->splittree->GetEntry(entry);
    
  }
  else {
    std::cout<<"causing error to end loop (Ignore Error)"<<std::endl;
    return false;
  }
  
  return true;
  
}


bool SplitLoop::Finalise(){
  
  return true;
}
