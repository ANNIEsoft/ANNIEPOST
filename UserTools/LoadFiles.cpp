#include "LoadFiles.h"

LoadFiles::LoadFiles():Tool(){}


bool LoadFiles::Initialise(std::string configfile, DataModel &data){

  if(configfile!="")  m_variables.Initialise(configfile);
  //m_variables.Print();

  m_data= &data;

  //load list of trees loop over them
  
  // TTree *WaterTTree;
  // TTree *RunInformationTTree;
  /*
  TFile *f = new TFile("DataR248S1p0.root");

  TTree *WaterTTree;
  TTree *RunInformationTTree;

    if (!f || !f->IsOpen()) {
      //error
    }

    f->GetObject("PMTData",WaterTTree);
    f->GetObject("RunInformation",RunInformationTTree);

    PMTData* tmpPMTData=new PMTData(WaterTTree->CloneTree());
    RunInformation* tmpRI=new RunInformation(RunInformationTTree->CloneTree());

    m_data->WaterPMTVec.push_back(tmpPMTData);
    m_data->RunInformationVec.push_back(tmpRI);       

    std::cout<< m_data->RunInformationVec.at(0)->fChain->GetEntriesFast()<<std::endl;
      f->Close();
  */

  m_data->PMTDataChain=new TChain("PMTData");
  m_data->PMTDataChain->Add("../converstiontmp/DataR248S1p0.root");
  //  m_data->PMTDataChain->Add("../converstiontmp/DataR248S1p1.root");
  //ch->GetEntry(12000);
  m_data->RunInformationChain=new TChain("RunInformationc");
  m_data->RunInformationChain->Add("../converstiontmp/DataR248S1p0.root");
  // m_data->RunInformationChain->Add("../converstiontmp/DataR248S1p1.root");

  m_data->WaterPMTData=new PMTData(m_data->PMTDataChain);
  m_data->RunInformationData=new RunInformation(m_data->RunInformationChain);

  // m_data->WaterPMTData->GetEntry(8000);
  //m_data->RunInformationData->GetEntry(6);
  //std::cout<<m_data->WaterPMTData->CardID<<std::endl;
  //std::cout<<m_data->RunInformationData->InfoTitle<<std::endl;

  return true;
}


bool LoadFiles::Execute(){
  /*
  std::cout<<m_data->RunInformationChain->GetEntries()<<std::endl;
  for (int i=0;i<m_data->RunInformationChain->GetEntries();i++){
    m_data->RunInformationData->GetEntry(i);
    std::cout<< *(m_data->RunInformationData->InfoTitle)<<" : "<<*(m_data->RunInformationData->InfoMessage)<<std::endl<<std::endl<<std::endl;
  }
  */
  return true;
}


bool LoadFiles::Finalise(){

  return true;
}
