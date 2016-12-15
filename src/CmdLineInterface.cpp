#include <string>
#include <algorithm>
#include "Target.hpp"
#include "CmdLineInterface.hpp"

CmdLineInterface::CmdLineInterface(int argc, char* argv[])
{
  std::string arg(argv[1]);
  isTest = arg.find("-t")!=std::string::npos || arg.find("--test")!=std::string::npos;
  if (std::find(argv, argv+argc, "cross") != argv+argc)
  {
	  targetType = TargetType::Cross;
  }
  else if (std::find(argv, argv+argc-1, "rect") != argv+argc-1)
  {
    targetType = TargetType::Rect;
  }
  else
  {
    targetType = TargetType::Cross;
  }
}

bool CmdLineInterface::getIsTest()
{
  return isTest;
}

TargetType CmdLineInterface::getTargetType()
{
  return targetType;
}
