#include <string>
#include <iostream>
#include <stdlib.h>

#include "print_functions.hh"

using namespace std; 

string toClassType(int type){
    if(type == 1){
        return "lecture";
    }else if(type == 2){
        return "tutorial";
    }else{
        return "practical";
    }
}

string toDay(int day){
    if(day == 1){
        return "Monday";
    }else if (day == 2){
        return "Tuesday";
    }else if (day == 3){
        return "Wednesday";
    }else if (day ==4){
        return "Thursday";
    }else{
        return "Friday";
    }
}

string toTime(int militaryTime){
    if(militaryTime < 12){
        return to_string(militaryTime) + "AM";
    }else{
        return to_string(militaryTime - 12) + "PM";
    }
}