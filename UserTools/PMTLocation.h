#ifndef PMTLocation_H
#define PMTLocation_H

#include <string>
#include <iostream>
#include <vector>

#include <pqxx/pqxx>

#include "Tool.h"


class PMTLocation: public Tool {


 public:

  PMTLocation();
  bool Initialise(std::string configfile,DataModel &data);
  bool Execute();
  bool Finalise();


 private:

  pqxx::result *R;
  std::vector<TBranch*> BranchVec;


};


#endif
