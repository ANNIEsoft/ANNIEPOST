#ifndef PulseFinder_H
#define PulseFinder_H

#include <string>
#include <iostream>

#include "Tool.h"
#include "TTree.h"
#include "TTreeIndex.h"

class PulseFinder: public Tool {


 public:

  PulseFinder();
  bool Initialise(std::string configfile,DataModel &data);
  bool Execute();
  bool Finalise();


 private:

  float threshold;
  int pulsewindow;



};


#endif
