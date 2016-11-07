#include "../Unity.cpp"

Tool* Factory(std::string tool){
Tool* ret=0;

// if (tool=="Type") tool=new Type;
if (tool=="DummyTool") ret=new DummyTool;

if (tool=="LoadFiles") ret=new LoadFiles;
if (tool=="Splitter") ret=new Splitter;
if (tool=="SplitLoop") ret=new SplitLoop;
if (tool=="Calibrate") ret=new Calibrate;
if (tool=="PMTLocation") ret=new PMTLocation;
if (tool=="RootOutput") ret=new RootOutput;

if (tool=="RunInformationCollector") ret=new RunInformationCollector;
  if (tool=="PulseFinder") ret=new PulseFinder;
return ret;
}

