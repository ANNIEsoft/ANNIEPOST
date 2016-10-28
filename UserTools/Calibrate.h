#ifndef Calibrate_H
#define Calibrate_H

#include <string>
#include <iostream>

#include "Tool.h"

#include "TTree.h"
#include "TH1I.h"
#include "TF1.h"

class Calibrate: public Tool {


 public:

  Calibrate();
  bool Initialise(std::string configfile,DataModel &data);
  bool Execute();
  bool Finalise();


 private:

  double conversion;
  TBranch *br;

};


#endif
