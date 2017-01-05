#ifndef OfflinePMTLocation_H
#define OfflinePMTLocation_H

#include <string>
#include <iostream>
#include <vector>
#include <map>

#include "Tool.h"

struct Location{

  Location(int in[]){
    for(int ch=0;ch<4;ch++){
      std::vector<int> tmp;
      tmp.push_back(in[(ch*5)]);
      tmp.push_back(in[(ch*5)+1]);
      tmp.push_back(in[(ch*5)+2]);
      tmp.push_back(in[(ch*5)+3]);
      tmp.push_back(in[(ch*5)+4]);
      channel.push_back(tmp);
    }
  }
  
  std::vector<std::vector<int> > channel;
  
};

class OfflinePMTLocation: public Tool {
  
  
 public:

  OfflinePMTLocation();
  bool Initialise(std::string configfile,DataModel &data);
  bool Execute();
  bool Finalise();


 private:

  std::vector<TBranch*> BranchVec;
  std::map<int,Location* > locations;

};


#endif
