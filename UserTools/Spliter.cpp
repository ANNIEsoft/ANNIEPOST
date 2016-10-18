#include "Spliter.h"

Spliter::Spliter():Tool(){}


bool Spliter::Initialise(std::string configfile, DataModel &data){

  if(configfile!="")  m_variables.Initialise(configfile);
  //m_variables.Print();

  m_data= &data;

  m_data->splittree=new SplitTree();

  TriggerNum=0;

  Split=false;
  return true;
}


bool Spliter::Execute(){

  if (!Split){
    Split=true;
    
    /////Finding trigger info from configuration files
    long entries=RunInformationData->fChain->GetEntriesFast();
    Store triggerinfo;
    for(long entry=0; entry<entries;entry++){
      
      RunInformation->fChain->GetEntry(entry);
      
      if(RunInformationData0->InfoTitle=="TriggerConfig"){
	triggerinfo.Jsonparser(RunInformaionData.InfoMessage);
      }
    }
    ////////
    
    ///// determining downsample level and number of samples per buffer
    //int DownSamplingMode=0;
    int nsamples=0;
    int bufferlength=0;
    int samplelength=0;
    //trggerinfo.Get("",DownSamplingMode);
    triggerinfo.Get("",samplelength);
    triggerinfo.Get("",bufferlength);
    nsamples=bufferlength/samplelength;
    ////
    
    /// looping over raw data splitting by channel and sample
    
    entries=WaterPMTData->fChain->GetEntriesFast();
    
    for(long entry=0; entry<entries; entry++){
      
      WaterPMTData->fChain->GetEntry(entry);
      
      for (int channel=0;channel<4;channel++){ //loop over 4 channels of cards
	
	m_data->splittree->LastSync=m_data->WaterPMTData->LastSync;
	m_data->splittree->SequenceID=m_data->WaterPMTData->SequenceID;
	m_data->splittree->StartTimeSec=m_data->WaterPMTData->StartTimeSec;
	m_data->splittree->StartTimeNSec=m_data->WaterPMTData->StartTimeSec;
	m_data->splittree->StartCount=m_data->WaterPMTData->startCcount;
	m_data->splittree->TriggerNumber=m_data->PMTdata->TriggerNumber;
	m_data->splittree->CardID=m_data->WaterPMTData->CardID;
	
	m_data->splittree->Rate=m_data->WaterPMTData->Rates[channel];
	m_data->splittree->Channel=channel;
	m_data->splittree->PMTID=channel;
	m_data->splittree->BufferSize=m_data->WaterPMTData->BufferSize/(4*nsamples);
	
	
	
	
	for(int sample=0;sample<nsamples; sample++){
	  
	  int dataentry=0;
	  
	  for(int j=(channel*(bufferlength/4))+(sample*(bufferlength/(8*nsamples))); j<(channel*(bufferlength/4))+(bufferlength/8)+(sample*(bufferlength/(8*nsamples)));j++){
	    
	    
	    m_data->splittree->Data[dataentry]=m_data->WaterPMTData->Data[j];
	    m_data->splittree->Data[dataentry+1]=m_data->WaterPMTData->Data[j+1];
	    m_data->splittree->Data[dataentry+2]=m_data->WaterPMTData->Data[j+(bufferlength/8)];
	    m_data->splittree->Data[dataentry+3]=m_data->WaterPMTData->Data[j+1+(bufferlength/8)];
	    
	    dataentry+=4;   
	  }
	  
	  m_data->splittree->Trigger=TriggerNum+sample;
	  m_data->splittree->TriggerCounts=m_data->WaterPMTData->TriggerCouts[(4*sample)+channel];
	  m_data->splittree->Fill();
	  
	  TriggerNum+=nsamples;
	}
      }
      
      
      
    
    return true;
  }


bool Spliter::Finalise(){

  return true;
}
