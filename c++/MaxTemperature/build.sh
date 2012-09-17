#!/bin/sh

set -x

PLATFORM=Linux-i386-32
export PLATFORM

HADOOP_INSTALL=/usr/local/hadoop
INCLUDE_PATH=${HADOOP_INSTALL}/c++/${PLATFORM}/include
LIB_PATH=${HADOOP_INSTALL}/c++/${PLATFORM}/lib
export HADOOP_INSTALL
export INCLUDE_PATH
export LIB_PATH

CXXFLAGS="-m32 -g -O2 -Wall"
LDFLAGS="-lpthread -lssl"

export CXXFLAGS
export LDFLAGS

g++ -I$INCLUDE_PATH $CXXFLAGS -o MaxTemperature MaxTemperature.cc $LDFLAGS -L${LIB_PATH} -lhadooppipes -lhadooputils 
