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
CPPFLAGS += -I$(shell brew --prefix fmt)/include
LDFLAGS  += -L$(shell brew --prefix fmt)/lib
endif
