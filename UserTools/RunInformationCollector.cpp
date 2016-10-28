#include "RunInformationCollector.h"

RunInformationCollector::RunInformationCollector():Tool(){}


bool RunInformationCollector::Initialise(std::string configfile, DataModel &data){

  if(configfile!="")  m_variables.Initialise(configfile);
  //m_variables.Print();

  m_data= &data;

  setup=true;

  return true;
}


bool RunInformationCollector::Execute(){
  
  if (setup){
    setup=false;
    
    for(int entry=0; entry<m_data->RunInformationData->fChain->GetEntries(); entry++){
      
      m_data->RunInformationData->GetEntry(entry);
      runinfo[*(m_data->RunInformationData->InfoTitle)]=*(m_data->RunInformationData->InfoMessage);
      
    }
        
    delete m_data->RunInformationData;
    m_data->RunInformationData=new RunInformation();
    
    for (std::map<std::string,std::string>::iterator it=runinfo.begin(); it!=runinfo.end(); ++it){
      //      std::cout<<"assigning string "<<m_data->RunInformationData->InfoTitle<<std::endl;
      *(m_data->RunInformationData->InfoTitle)=it->first;
      *(m_data->RunInformationData->InfoMessage)=it->second;
      m_data->RunInformationData->fChain->Fill();
    }
    
  }
    
  
  return true;
}


bool RunInformationCollector::Finalise(){
  
  return true;
}
