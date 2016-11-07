#include "PulseFinder.h"

PulseFinder::PulseFinder():Tool(){}


bool PulseFinder::Initialise(std::string configfile, DataModel &data){

  if(configfile!="")  m_variables.Initialise(configfile);
  //m_variables.Print();

  m_data= &data;
  
  m_variables.Get("Threshold",threshold); //assining threshold dynamically from file
  m_variables.Get("PulseWindow",pulsewindow); //assining pulse capture window dynamically from file
  
  m_data->PulseData=new PulseTree("annie"); // creating your output tree in data model (we could ahve made a local copy but i think youwant to acess it in another tool) [this is just a make class done on the output tree with a new constructor that you will ahve to fill out how ever you normally make your ttree]
  m_data->AddTTree("PulseTree",m_data->PulseData->fChain); // this adds the ttree to a map stored in the data model (anny ttree added to this map will automatically be written into the output)
  
  m_data->PulseData->TrigNo=0;
  m_data->PulseData->fPmts_=0;

  return true;
}


bool PulseFinder::Execute(){

  // Your oulse finding algoritm would go here. Each time execute is run a new channel output is laded into the m_data->splittree class and its data members can be acessed like acessing a root makeclass.

  //I have written a very crude example below however whilst writing this i noticed that it appears you ahve grouped pulses beloning to the same trigger together in a single root entry. 

  //If your algorithm comes in two stages (ie finding the pulses first and then ordedring them all later) and can handel one pulse at a time (possible out of trigger order if the downsampleing is on) then you can write it here in the execute function.

  //However if you require pulses in trigger order (or didnt realise know how to sort them and thefore have reailsed that you could turn a two stage process into a 1 stage process and speed up the algorithm gately) then i would suggest you possibly instead write your algorithm in the finalise method or at least put the writing stage of a two stage procecss in the finalise method.

  //In the finalise method i ahve put an example of how to sort a ttree into trigger order

  //If that is the case you will not be able to perform 

  if(m_data->splittree->Trigger>m_data->PulseData->TrigNo){ //conditional to find if we have started
    
    if(m_data->PulseData->fPmts_>0) m_data->GetTTree("PulseTree")->Fill();
  
    //fill your non channel specific data here
    //e.g.

    m_data->PulseData->TrigNo = m_data->splittree->Trigger;
    m_data->PulseData->BufferSize = m_data->splittree->BufferSize;
    //... etc.
    
  }
  
  for(int point=0; point<m_data->splittree->BufferSize ; point++){
    
    if(m_data->splittree->Data[point] > threshold ){
      
      //fill your pulse channel data here
      //e.g.
   
      m_data->PulseData->fPmts_++;
      m_data->PulseData->fPmts_x[m_data->PulseData->fPmts_ -1] = m_data->splittree->PMTx;
      //... etc.
      
      int windowmax=point+(pulsewindow/2);
      int windowmin=point-(pulsewindow/2);

      if(windowmin<0) windowmin=0;
      if(windowmax > m_data->splittree->BufferSize); windowmax=m_data->splittree->BufferSize;

      for (int value=windowmin;value<=windowmax;value++){


	//fill your apecific captured window data here (its not obvious to me what you do with it but looks liek you decouple charge or something)

	//m_data->PulseData->??? = m_data->splittree->Data[value]


      }

    }
  }

  


  return true;
}


bool PulseFinder::Finalise(){

  // Example of sorting a finnished ttree (this will not work in execute as the tree is not filled completly until all execute loop is finnished

  m_data->GetTTree("PMTData")->BuildIndex("Trigger");
  TTreeIndex *index = (TTreeIndex*)m_data->GetTTree("PMTData")->GetTreeIndex();
  for( int i = 0; i<index->GetN() ;i++) {
    Long64_t local = m_data->GetTTree("PMTData")->LoadTree( index->GetIndex()[i] );
    m_data->splittree->GetEntry(local);
    

    // do stuff with ordered entries


  }
  
  
  return true;
}
