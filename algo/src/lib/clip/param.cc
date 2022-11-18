// File:        param.cpp
// Author:      Zakhary Kaplan <https://zakhary.dev>
// Created:     12 Nov 2020
// SPDX-License-Identifier: MIT

#include "clip/param.h"

#include <string>

namespace clip {

// class Param
// ctors
Param::Param(const char *name) : name(name), help_("") {}

// dtor
Param::~Param() = default;

// builders
Param &Param::help(const char *s) {
    this->help_ = std::string(s);
    return *this;
}

// accessors
const char *Param::help() const {
    return this->help_.data();
}

} // namespace clip
