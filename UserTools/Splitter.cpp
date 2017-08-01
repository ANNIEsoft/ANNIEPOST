#include "Splitter.h"

Splitter::Splitter():Tool(){}


bool Splitter::Initialise(std::string configfile, DataModel &data){

  if(configfile!="")  m_variables.Initialise(configfile);
  //m_variables.Print();

  m_data= &data;

  std::string outpath, suffix;

  m_variables.Get("OutPath",outpath);
  m_variables.Get("Suffix",suffix);

  std::stringstream tmp;
  tmp<<outpath<<m_data->outfile<<suffix;
  m_data->tmpfile= new TFile(tmp.str().c_str(),"RECREATE","test",9);

  // m_data->tmpfile =new TFile("/tmp/tout.root","RECREATE");
  m_data->splittree=new SplitTree("PMTData");
  m_data->tmpfile->cd();
  m_data->AddTTree("PMTData",m_data->splittree->fChain);

  TriggerNum=0;

  
  
  /////Finding trigger info from configuration files
  long entries=m_data->RunInformationData->fChain->GetEntries();
  Store triggerinfo;
  for(long entry=0; entry<entries;entry++){
     
    m_data->RunInformationData->GetEntry(entry);
          
    if(*(m_data->RunInformationData->InfoTitle)=="TriggerVariables"){
      
      triggerinfo.JsonPaser(*(m_data->RunInformationData->InfoMessage));
    
    }
  }

  ////////
  
 
  ///// determining downsample level and number of samples per buffer
  
  int nsamples=0;
  int bufferlength=0;
  int samplelength=0;
  
  triggerinfo.Get("TriggerSamples",samplelength);
  triggerinfo.Get("TotalSamples",bufferlength);
  samplelength*=4;
  bufferlength*=4;
  
  nsamples=bufferlength/samplelength;
  ////
  
  /// looping over raw data splitting by channel and sample
  
  entries=m_data->WaterPMTData->fChain->GetEntries();
  
  for(long entry=0; entry<entries; entry++){
    
    if(entry%100==0)std::cout<<entry<<"/"<<entries<<std::endl;
      
    m_data->WaterPMTData->GetEntry(entry);
    
    for (int channel=0;channel<4;channel++){ //loop over 4 channels of cards
      
      m_data->splittree->LastSync=m_data->WaterPMTData->LastSync;
      m_data->splittree->SequenceID=m_data->WaterPMTData->SequenceID;
      m_data->splittree->StartTimeSec=m_data->WaterPMTData->StartTimeSec;
      m_data->splittree->StartTimeNSec=m_data->WaterPMTData->StartTimeNSec;
      m_data->splittree->StartCount=m_data->WaterPMTData->StartCount;
      m_data->splittree->TriggerNumber=m_data->WaterPMTData->TriggerNumber;
      m_data->splittree->CardID=m_data->WaterPMTData->CardID;
      
      m_data->splittree->Rate=m_data->WaterPMTData->Rates[channel];
      m_data->splittree->Channel=channel;
      m_data->splittree->PMTID=channel;
      
      m_data->splittree->BufferSize=samplelength;
      
      
      for(int sample=0;sample<nsamples; sample++){
	  
	int dataentry=0;
	
	//	  for(int j=(channel*(bufferlength/4))+(sample*(bufferlength/(8*nsamples))); j<(channel*(bufferlength/4))+(bufferlength/8)+(sample*(bufferlength/(8*nsamples)));j++){
	//	std::cout<<"channel="<<channel<<" , sample="<<sample<<" , buffrlength="<<bufferlength<<" , nsamples="<<nsamples<<std::endl;
	for(int j=(channel*(bufferlength))+(sample*(bufferlength/(2*nsamples))); j<(channel*(bufferlength))+(bufferlength/(2*nsamples))+(sample*(bufferlength/(2*nsamples)));j+=2){
	  //	  std::cout<<dataentry<<"->"<<j<<" , "<<(dataentry+1)<<"->"<<(j+1)<<" , "<<(dataentry+2)<<"->"<<(j+(bufferlength/2))<<" , "<<(dataentry+3)<<"->"<<j+1+(bufferlength/2)<<std::endl;	  
	  m_data->splittree->UnCalData[dataentry]=m_data->WaterPMTData->Data[j];
	  m_data->splittree->UnCalData[dataentry+1]=m_data->WaterPMTData->Data[j+1];
	  m_data->splittree->UnCalData[dataentry+2]=m_data->WaterPMTData->Data[j+(bufferlength/2)];
	  m_data->splittree->UnCalData[dataentry+3]=m_data->WaterPMTData->Data[j+1+(bufferlength/2)];
	  
	  dataentry+=4;   
	}
	
	m_data->splittree->Trigger=TriggerNum+sample;
	m_data->splittree->TriggerCount=m_data->WaterPMTData->TriggerCounts[(4*sample)+channel];
	
	m_data->splittree->Fill();

      } 
      
      
    }
    
    
    if(m_data->splittree->CardID==21 && m_data->splittree->Channel==3)TriggerNum+=nsamples;   
 
  }
  
  
  
  return true;
  
}


bool Splitter::Execute(){
  
  return true;
}


bool Splitter::Finalise(){

  
  return true;
}
