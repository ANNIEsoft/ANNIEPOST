#ifndef Spliter_H
#define Spliter_H

#include <string>
#include <iostream>

#include "Tool.h"

class Spliter: public Tool {


 public:

  Spliter();
  bool Initialise(std::string configfile,DataModel &data);
  bool Execute();
  bool Finalise();


 private:

  bool Split;



};


#endif
