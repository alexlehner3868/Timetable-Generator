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
CPPFLAGS += -I./dep/include
LDFLAGS  += -L./dep/lib
else ifeq ($(shell uname),Darwin)
CPPFLAGS += -I/opt/homebrew/opt/fmt/include
LDFLAGS  += -L/opt/homebrew/opt/fmt/lib
endif
