
#ifndef __ELIPSE_H
#define __ELIPSE_H

#include <iostream>
#include <string>
#include "shape.h"

class Elipse : public Shape {
    double centreX;
    double centreY;
    double radiusX;
    double radiusY;
    std::string _fill;
public:
    Elipse(std::string data, bool isForParsing = false);

    Elipse(double x = 0, double y = 0, double radX = 1, double radY = 1, std::string fill = "none");

    Elipse(Elipse* elipse);

    virtual Elipse* clone();

    //void translate(double x, double y);
    void Print(std::ostream& output = std::cout);

    bool Within(Shape* shape);

    /*double getX(){
        return this->centreX;
    }

    double getY(){
        return this->centreY;
    }*/

    double getRadiusX(){
        return this->radiusX;
    }

    double getRadiusY(){
        return this->radiusY;
    }

    std::string getFill(){
        return this->_fill;
    }

    std::string type(){
        return "elipse";
    }

    /*void setX(double x){
        this->centreX = x;
    }

    void setY(double y){
        this->centreY = y;
    }*/

    void setRadiusX(double rad){
        this->radiusX = rad;
    }

    void setRadiusY(double rad){
        this->radiusY = rad;
    }

    void setFill(std::string color){
        this->_fill = color;
    }

    void parse(std::string data);

    std::string exporrt();
};

#endif // SHAPE

