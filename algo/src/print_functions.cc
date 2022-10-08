#include "print_functions.hh"

#include <stdlib.h>

#include <iostream>
#include <string>

using namespace std;

string toClassType(int type) {
    if (type == 1) {
        return "lecture";
    } else if (type == 2) {
        return "tutorial";
    } else if (type == 3) {
        return "practical";
    } else if (type == 4) {
        return "Constraint";
    } else {
        // do something if this is an error
        return "Error";
    }
}

string toDay(int day) {
    if (day == 1 || day == 6) {
        return "Monday";
    } else if (day == 2 || day == 7) {
        return "Tuesday";
    } else if (day == 3 || day == 8) {
        return "Wednesday";
    } else if (day == 4 || day == 9) {
        return "Thursday";
    } else if (day == 5 || day == 10) {
        return "Friday";
    } else {
        // do something if this is an error
        return "Error";
    }
}

string toTime(int militaryTime) {
    if (militaryTime < 12) {
        return to_string(militaryTime) + "AM";
    } else if (militaryTime == 12) {
        return "12PM";
    } else if (militaryTime > 12 && militaryTime < 25) {
        return to_string(militaryTime - 12) + "PM";
    } else {
        return "Error Time";
    }
}