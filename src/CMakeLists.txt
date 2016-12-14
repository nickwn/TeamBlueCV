cmake_minimum_required(VERSION 2.8)
project(mock-2016)

set (BOOST_ROOT "C:/Users/The/Documents/Programming/C++/boost_1_62_0")

add_executable(mock-2016 main1.cpp TargetProcessor.cpp TargetDetector.cpp Target.cpp NetworkController.cpp GUIManager.cpp CmdLineInterface.cpp)
find_package(OpenCV REQUIRED)
find_package(Boost REQUIRED COMPONENTS system thread)
target_link_libraries(mock-2016 ${OpenCV_LIBS} ${Boost_LIBRARIES})
