#ifndef CMD_LINE_INTERFACE_HPP
#define CMD_LINE_INTERFACE_HPP

#include "Target.hpp"

class CmdLineInterface
{
public:
  CmdLineInterface(int argc, char* argv[]);
  bool getIsTest();
  TargetType getTargetType();
private:
  bool isTest;
  TargetType targetType; // if we are testing, what TargetType are we testing?
};

#endif
