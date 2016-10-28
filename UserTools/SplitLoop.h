#ifndef SplitLoop_H
#define SplitLoop_H

#include <string>
#include <iostream>

#include "Tool.h"

class SplitLoop: public Tool {


 public:

  SplitLoop();
  bool Initialise(std::string configfile,DataModel &data);
  bool Execute();
  bool Finalise();


 private:

  long entry;



};


#endif
