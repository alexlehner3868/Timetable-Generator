// File:        flag.cpp
// Author:      Zakhary Kaplan <https://zakhary.dev>
// Created:     01 Dec 2020
// SPDX-License-Identifier: MIT

#include "clip/flag.h"

#include "clip/option.h"
#include "clip/param.h"

namespace clip {

// class Flag
// ctors
Flag::Flag(const char *name) : Param(name), Option(name) {}

// builders (override)
Flag &Flag::help(const char *s) {
    this->Option::help(s);
    return *this;
}

Flag &Flag::longname(const char *s) {
    this->Option::longname(s);
    return *this;
}

Flag &Flag::shortname(char c) {
    this->Option::shortname(c);
    return *this;
}

} // namespace clip
