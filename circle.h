#ifndef __CIRCLE_H
#define __CIRCLE_H
#include<iostream>
#include "shape.h"

class Circle : public Shape{
    double centreX;
    double centreY;
    double radius;
    std::string _fill;
public:
    Circle(std::string data, bool isForParsing = false);

    Circle(double x = 0, double y = 0, double rad = 1, std::string fill = "none");

    Circle(Circle* circle);

    virtual Circle* clone();

    // void translate(double x, double y);
    void Print(std::ostream& output = std::cout);

    bool Within(Shape* shape);
   /* double getX(){
        return this->centreX;
    }

    double getY(){
        return this->centreY;
    }*/

    double getRadius(){
        return this->radius;
    }

    std::string getFill(){
        return this->_fill;
    }

    std::string type(){
        return "circle";
    }

    /*void setX(double x){
        this->centreX = x;
    }

    void setY(double y){
        this->centreY = y;
    }*/

    void setRadius(double rad){
        this->radius = rad;
    }

    void setFill(std::string color){
        this->_fill = color;
    }

    void parse(std::string data);

    std::string exporrt();

};

#endif // SHAPE

