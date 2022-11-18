// File:        param.h
// Author:      Zakhary Kaplan <https://zakhary.dev>
// Created:     12 Nov 2020
// SPDX-License-Identifier: MIT

#pragma once

#include <iosfwd>
#include <string>

namespace clip {

// class Param
class Param {
public:
    // const members
    const std::string name;

private:
    // mut members
    std::string help_;

public:
    // ctors
    Param(const char *name);

    // dtor
    virtual ~Param() = 0;

    // builders
    virtual Param &help(const char *s);

    // accessors
    virtual const char *help() const final;
};

} // namespace clip
