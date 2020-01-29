

#include<iostream>
#include<sstream>
#include "commonfunctions.h"

double Common::parseDouble(char const* numberAsText){
    double number;
    std::istringstream iss(numberAsText);
    iss>>number;
    return number;
}

std::string Common::doubleToString(double number){
    std::ostringstream oss;
    oss<<number;
    return oss.str();
}
