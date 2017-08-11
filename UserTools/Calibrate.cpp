#include "Calibrate.h"

Calibrate::Calibrate():Tool(){}


bool Calibrate::Initialise(std::string configfile, DataModel &data){

  if(configfile!="")  m_variables.Initialise(configfile);
  //m_variables.Print();

  m_data= &data;

  conversion=2.415/pow(2.0, 12.0);
  
 
  //  br=m_data->splittree->tree->GetBranch("Data");
  //br->Reset();
  std::stringstream tmp;
  tmp<<"Data["<<m_data->splittree->BufferSize<<"]/F";
  br=m_data->splittree->fChain->Branch("Data", m_data->splittree->Data,tmp.str().c_str());
  br->SetCompressionLevel(4);
  m_data->splittree->b_Data=br;

  return true;
}


bool Calibrate::Execute(){

  TH1I tmp("test","test",10000,0,9999);

  for(int i=0; i<m_data->splittree->BufferSize; i++){
    tmp.Fill(m_data->splittree->UnCalData[i]);
  }
  tmp.Fit("gaus","q");
  TF1 *gaus = tmp.GetFunction("gaus");
  int offset=gaus->GetParameter(1);
 
  
  for(int i=0; i<m_data->splittree->BufferSize; i++){
    
    m_data->splittree->Data[i]=((m_data->splittree->UnCalData[i])-offset)*conversion;
    // m_data->outtree->Data[i]=((m_data->splittree->UnCalData[i])-offset)*conversion;
    //  m_data->outtree->UnCalData[i]=m_data->splittree->UnCalData[i];
  }
  
  br->Fill();
  
  
  return true;
}


bool Calibrate::Finalise(){
  
  return true;
}
