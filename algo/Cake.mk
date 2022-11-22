# Package
NAME    = main

# Build
CONFIG ?= BASIC

# Extensions
.cc = .cc
.h  = .hh

# Flags
LDLIBS    = -lsqlite3 -lfmt
CXXFLAGS ?= -Wall -g -std=c++20

# Linux-only
ifeq ($(shell uname),Linux)
CPPFLAGS += -I./dep/include -I../dep/ug/fmt/include
LDFLAGS  += -L./dep/lib     -L../dep/ug/fmt/lib
else ifeq ($(shell uname),Darwin)
CPPFLAGS += -I../dep/m1/fmt/include
LDFLAGS  += -L../dep/m1/fmt/lib
endif
