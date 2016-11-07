#include "LoadFiles.h"

LoadFiles::LoadFiles():Tool(){}


bool LoadFiles::Initialise(std::string configfile, DataModel &data){

  if(configfile!="")  m_variables.Initialise(configfile);
  //m_variables.Print();

  m_data= &data;

  std::string filelist;

  m_variables.Get("FileList",filelist);

  m_data->PMTDataChain=new TChain("PMTData");
  m_data->RunInformationChain=new TChain("RunInformation");
  m_data->MRDChain= new TChain("CCData");

  std::string line;
  ifstream myfile (filelist.c_str());
  
    if (myfile.is_open()){
    
    m_data->outfile="";

    while ( getline (myfile,line) ){
    
      if(m_data->outfile==""){
	char * pch;
	char *elements=new char[line.length()];
	strcpy(elements, line.c_str());
	pch = strtok (elements,"/");
	while (pch != NULL)
	  {
	    m_data->outfile=pch;
	    pch = strtok(NULL,"/");
	  }
      }

      std::cout<<"Loading file "<<line<<std::endl;	
      m_data->PMTDataChain->Add(line.c_str());
      m_data->RunInformationChain->Add(line.c_str());
      m_data->MRDChain->Add(line.c_str());
      
    }
    myfile.close();
  }
  
  
  m_data->WaterPMTData=new PMTData(m_data->PMTDataChain);
  m_data->RunInformationData=new RunInformation(m_data->RunInformationChain);
  m_data->MRDData=new MRDTree(m_data->MRDChain);  
  m_data->MRDData->fChain->SetName("MRDData");
  m_data->AddTTree("MRDData",m_data->MRDData->fChain);
 
  return true;
}


bool LoadFiles::Execute(){
  
  return true;
}


bool LoadFiles::Finalise(){

  return true;
}
