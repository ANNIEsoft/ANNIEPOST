#ifndef RunInformationCollector_H
#define RunInformationCollector_H

#include <string>
#include <iostream>
#include <map>

#include "Tool.h"

class RunInformationCollector: public Tool {


 public:

  RunInformationCollector();
  bool Initialise(std::string configfile,DataModel &data);
  bool Execute();
  bool Finalise();


 private:

  bool setup;
  std::map<std::string,std::string> runinfo;


};


#endif
