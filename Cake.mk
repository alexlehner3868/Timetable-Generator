# Package
NAME    = main

# Build
CONFIG ?= BASIC

# Extensions
.cc = .cc
.h  = .hh

# Flags
LDLIBS    = -lsqlite3
CXXFLAGS ?= -Wall -g -std=c++20

# Linux-only
ifeq ($(shell uname),Linux)
CPPFLAGS += -I./dep/include
LDFLAGS  += -L./dep/lib
endif
