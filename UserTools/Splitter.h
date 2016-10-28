#ifndef Splitter_H
#define Splitter_H

#include <string>
#include <iostream>

#include "Tool.h"

class Splitter: public Tool {


 public:

  Splitter();
  bool Initialise(std::string configfile,DataModel &data);
  bool Execute();
  bool Finalise();


 private:

  long TriggerNum;


};


#endif
