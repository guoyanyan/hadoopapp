#!/bin/sh

set -x
HADOOP_HOME=/usr/local/hadoop
INCLUDE_PATH=${HADOOP_HOME}/c++/Linux-i386-32/include/hadoop
LIB_PATH=${HADOOP_HOME}/c++/Linux-i386-32/lib
export HADOOP_HOME
export INCLUDE_PATH
export LIB_PATH

CXXFLAGS="-g -Wall"
LDFLAGS="-lpthread -lssl"

export CXXFLAGS
export LDFLAGS

g++ $CXXFLAGS -I$INCLUDE_PATH -o WordCount WordCount.cc $LDFLAGS -L${LIB_PATH} -lhadooppipes -lhadooputils 
