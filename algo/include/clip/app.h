// File:        app.h
// Author:      Zakhary Kaplan <https://zakhary.dev>
// Created:     20 Dec 2020
// SPDX-License-Identifier: MIT

#pragma once

#include <iosfwd>
#include <string>

namespace clip {

class App final {
public:
    // const members
    const std::string name;

private:
    // mut members
    std::string about_;
    std::string author_;
    std::string version_;

public:
    // ctors
    App(const char *name);

    // builders
    App &about(const char *s);
    App &author(const char *s);
    App &version(const char *s);

    // accessors
    const std::string &about() const;
    const std::string &author() const;
    const std::string &version() const;
};

} // namespace clip
