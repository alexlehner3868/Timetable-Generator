# Package
NAME    = main

# Build
CONFIG ?= BASIC

# Extensions
.cc = .cc
.h  = .hh

# Flags
#LDLIBS = -L/usr/lib/x86_64-linux-gnu -lsqlite3 --verbose
CXXFLAGS ?= -Wall -g -std=c++20 
