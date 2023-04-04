# Package
NAME    = main

# Build
CONFIG ?= BASIC

# Extensions
.cc = .cc
.h  = .hh

# Flags
LDLIBS    = -lsqlite3 -lfmt
CXXFLAGS ?= -Wall -g -std=c++20 -fopenmp

# Linux-only
ifeq ($(shell uname),Linux)
CPPFLAGS += -I./dep/include
LDFLAGS  += -L./dep/lib
else ifeq ($(shell uname),Darwin)
CPPFLAGS += -I$(shell brew --prefix fmt)/include
LDFLAGS  += -L$(shell brew --prefix fmt)/lib
CXX = $(shell brew --prefix llvm)/bin/clang++ 
CC = $(shell brew --prefix llvm)/bin/clang
endif
