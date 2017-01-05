#include "OfflinePMTLocation.h"

OfflinePMTLocation::OfflinePMTLocation():Tool(){}


bool OfflinePMTLocation::Initialise(std::string configfile, DataModel &data){

  if(configfile!="")  m_variables.Initialise(configfile);
  //m_variables.Print();

  m_data= &data;

  
  int ca3[20]={0,0,0,3,1,0,0,0,2,2,0,0,0,1,3,0,1,0,0,4};
  Location *c3=new Location(ca3);
  locations[3]=c3;

  int ca4[20]={0,2,0,0,5,0,3,0,0,6,0,4,0,0,7,0,5,0,0,8};
  Location *c4=new Location(ca4);
  locations[4]=c4;

  int ca5[20]={0,6,0,0,9,0,7,0,1,10,0,7,0,2,11,0,7,0,3,12};
  Location *c5=new Location(ca5);
  locations[5]=c5;

  int ca6[20]={0,1,0,1,13,0,2,0,1,14,0,2,0,2,15,0,1,0,2,16};
  Location *c6=new Location(ca6);
  locations[6]=c6;

  int ca8[20]={0,3,0,1,17,0,4,0,1,18,0,4,0,2,19,0,3,0,2,20};
  Location *c8=new Location(ca8);
  locations[8]=c8;

  int ca9[20]={0,5,0,1,21,0,6,0,1,22,0,6,0,2,23,0,5,0,2,24};
  Location *c9=new Location(ca9);
  locations[9]=c9;

  int ca10[20]={0,1,0,3,25,0,2,0,3,26,0,2,0,4,27,0,1,0,4,28};
  Location *c10=new Location(ca10);
  locations[10]=c10;

  int ca11[20]={0,3,0,3,29,0,4,0,3,30,0,4,0,4,31,0,3,0,4,32};
  Location *c11=new Location(ca11);
  locations[11]=c11;

  int ca13[20]={0,5,0,3,33,0,6,0,3,34,0,6,0,4,35,0,5,0,4,36};
  Location *c13=new Location(ca13);
  locations[13]=c13;

  int ca14[20]={0,1,0,5,37,0,2,0,5,38,0,2,0,6,39,0,1,0,6,40};
  Location *c14=new Location(ca14);
  locations[14]=c14;

  int ca15[20]={0,3,0,5,41,0,4,0,5,42,0,4,0,6,43,0,3,0,6,44};
  Location *c15=new Location(ca15);
  locations[15]=c15;

  int ca16[20]={0,5,0,5,45,0,6,0,5,46,0,6,0,6,47,0,5,0,6,48};
  Location *c16=new Location(ca16);
  locations[16]=c16;

  int ca18[20]={0,0,0,4,49,0,0,0,5,50,0,0,0,6,51,0,1,0,7,52};
  Location *c18=new Location(ca18);
  locations[18]=c18;

  int ca19[20]={0,2,0,7,53,0,3,0,7,54,0,4,0,7,55,0,5,0,7,56};
  Location *c19=new Location(ca19);
  locations[19]=c19;

  int ca20[20]={0,6,0,7,57,0,7,0,6,58,0,7,0,5,59,0,7,0,4,60};
  Location *c20=new Location(ca20);
  locations[20]=c20;

  int ca21[20]={0,-10,-10,-10,99,0,-10,-10,-10,99,0,-10,-10,-10,99,0,-10,-10,-10,99};
  Location *c21=new Location(ca21);
  locations[21]=c21;

  //stuff

  TBranch *br;
  br=m_data->splittree->fChain->Branch("PMTID", &m_data->splittree->PMTID, "PMTID/I");
  br->SetCompressionLevel(4); 
  BranchVec.push_back(br);
  br=m_data->splittree->fChain->Branch("PMTf", &m_data->splittree->PMTf, "PMTf/I");
  br->SetCompressionLevel(4);
  BranchVec.push_back(br);
  br=m_data->splittree->fChain->Branch("PMTx", &m_data->splittree->PMTx, "PMTx/I");
  br->SetCompressionLevel(4);
  BranchVec.push_back(br);
  br=m_data->splittree->fChain->Branch("PMTy", &m_data->splittree->PMTy, "PMTy/I");
  br->SetCompressionLevel(4);
  BranchVec.push_back(br);
  br=m_data->splittree->fChain->Branch("PMTz", &m_data->splittree->PMTz, "PMTz/I");
  br->SetCompressionLevel(4);
  BranchVec.push_back(br);

  return true;

}


bool OfflinePMTLocation::Execute(){

  //  for( pqxx::result::const_iterator c = R->begin(); c!=R->end(); c++){
    
    
  // if (c[10].as<int>()==m_data->splittree->CardID && c[11].as<int>()==m_data->splittree->Channel+1){
  
  m_data->splittree->PMTID= locations[m_data->splittree->CardID]->channel.at(m_data->splittree->Channel)[4];
  m_data->splittree->PMTf= locations[m_data->splittree->CardID]->channel.at(m_data->splittree->Channel)[0];
  m_data->splittree->PMTx= locations[m_data->splittree->CardID]->channel.at(m_data->splittree->Channel)[1];
  m_data->splittree->PMTy= locations[m_data->splittree->CardID]->channel.at(m_data->splittree->Channel)[2];
  m_data->splittree->PMTz= locations[m_data->splittree->CardID]->channel.at(m_data->splittree->Channel)[3];
  
  
  //}
  
  // }
  
  if (m_data->splittree->PMTx==0 && m_data->splittree->PMTz==0){
    
    std::cout<<"error reconstructing"<<std::endl;    
    std::cout<<"cardid= "<<m_data->splittree->CardID<<std::endl;
    std::cout<<"channel= "<<m_data->splittree->Channel<<std::endl;
    
  }
  
  
  for(int branch=0; branch<BranchVec.size(); branch++){
    
    BranchVec.at(branch)->Fill();
  }
  
  return true;
}


bool OfflinePMTLocation::Finalise(){
  
  locations.clear();
  
  return true;

}
