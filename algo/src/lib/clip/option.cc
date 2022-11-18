// File:        option.cpp
// Author:      Zakhary Kaplan <https://zakhary.dev>
// Created:     23 Dec 2020
// SPDX-License-Identifier: MIT

#include "clip/option.h"

#include <cctype>
#include <regex>
#include <stdexcept>
#include <string>

#include "clip/param.h"

namespace clip {

// class Option
// ctors
Option::Option(const char *name) : Param(name), longname_(""), shortname_('\0'), count_(0) {
    // Set default longname
    this->longname(name);
}

// dtor
Option::~Option() = default;

// builders
Option &Option::longname(const char *s) {
    // Ensure longname is valid
    if (!std::regex_match(name, std::regex("^[A-Za-z0-9][A-Za-z0-9-]*$")))
        throw std::invalid_argument("invalid longname");
    this->longname_ = std::string(s);
    return *this;
}

Option &Option::shortname(char c) {
    // Ensure shortname is valid
    if (!std::isalnum(c))
        throw std::invalid_argument("invalid shortname");
    this->shortname_ = c;
    return *this;
}

// builders (override)
Option &Option::help(const char *s) {
    this->Param::help(s);
    return *this;
}

// accessors
const char *Option::longname() const {
    return this->longname_.data();
}

char Option::shortname() const {
    return this->shortname_;
}

unsigned int Option::count() const {
    return this->count_;
}

// methods
void Option::match() {
    this->count_++;
}

} // namespace clip
