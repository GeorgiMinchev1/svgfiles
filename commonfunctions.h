

#ifndef __COMMONFUNCTIONS_H
#define __COMMONFUNCTIONS_H

#include<iostream>
#include<string>
#include<sstream>

class Common{
public:
    double parseDouble(char const* numberAsText);
    std::string doubleToString(double number);
};


#endif



