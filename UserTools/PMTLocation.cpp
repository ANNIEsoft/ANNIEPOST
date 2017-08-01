#include "PMTLocation.h"

PMTLocation::PMTLocation():Tool(){}


bool PMTLocation::Initialise(std::string configfile, DataModel &data){

  if(configfile!="")  m_variables.Initialise(configfile);
  //m_variables.Print();

  m_data= &data;


  try{

    pqxx::connection C("dbname=annie hostaddr=127.0.0.1 port=5432");

    pqxx::nontransaction N(C);
    std::stringstream tmp;
    tmp<<"select * from pmtconnections ";


    /* Execute SQL query */
    R= new pqxx::result( N.exec( tmp.str().c_str() ));


  }
  catch (const std::exception &e){
    std::cout<<"error connecting to psql database"<<std::endl;
    exit(1);
  }

  TBranch *br;
  br=m_data->splittree->fChain->Branch("PMTID", &m_data->splittree->PMTID, "PMTID/I");
  br->SetCompressionLevel(4); 
  BranchVec.push_back(br);
  m_data->splittree->b_PMTID=br;
  br=m_data->splittree->fChain->Branch("PMTf", &m_data->splittree->PMTf, "PMTf/I");
  br->SetCompressionLevel(4);
  BranchVec.push_back(br);
  m_data->splittree->b_PMTf=br;
  br=m_data->splittree->fChain->Branch("PMTx", &m_data->splittree->PMTx, "PMTx/I");
  br->SetCompressionLevel(4);
  BranchVec.push_back(br);
  m_data->splittree->b_PMTx=br;
  br=m_data->splittree->fChain->Branch("PMTy", &m_data->splittree->PMTy, "PMTy/I");
  br->SetCompressionLevel(4);
  BranchVec.push_back(br);
  m_data->splittree->b_PMTy=br;
  br=m_data->splittree->fChain->Branch("PMTz", &m_data->splittree->PMTz, "PMTz/I");
  br->SetCompressionLevel(4);
  BranchVec.push_back(br);
  m_data->splittree->b_PMTz=br;

  return true;

}


bool PMTLocation::Execute(){

  for( pqxx::result::const_iterator c = R->begin(); c!=R->end(); c++){
    
    
    if (c[10].as<int>()==m_data->splittree->CardID && c[11].as<int>()==m_data->splittree->Channel+1){
      
      m_data->splittree->PMTID=c[9].as<int>();
      m_data->splittree->PMTf=c[2].as<int>();
      m_data->splittree->PMTx=c[3].as<int>();
      m_data->splittree->PMTy=c[4].as<int>();
      m_data->splittree->PMTz=c[5].as<int>();
      
      
    }
    
  }
  
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


bool PMTLocation::Finalise(){
  
  delete R;
  R=0;
  
  return true;

}
