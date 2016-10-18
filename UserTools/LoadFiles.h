#ifndef LoadFiles_H
#define LoadFiles_H

#include <string>
#include <iostream>

#include <TFile.h>
#include <TTree.h>

#include "Tool.h"
#include "PMTData.h"
#include "RunInformation.h"

class LoadFiles: public Tool {


 public:

  LoadFiles();
  bool Initialise(std::string configfile,DataModel &data);
  bool Execute();
  bool Finalise();


 private:





};


#endif
