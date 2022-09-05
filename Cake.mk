# Package
NAME    = main

# Build
CONFIG ?= BASIC

# Extensions
.cc = .cc
.h  = .hh

# Flags
LDLIBS = -lsqlite3 
CXXFLAGS ?= -Wall -g -std=c++20 
