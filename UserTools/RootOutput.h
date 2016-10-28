#ifndef RootOutput_H
#define RootOutput_H

#include <string>
#include <iostream>

#include "Tool.h"

class RootOutput: public Tool {


 public:

  RootOutput();
  bool Initialise(std::string configfile,DataModel &data);
  bool Execute();
  bool Finalise();


 private:

  TFile* file;



};


#endif
