#ifndef __RECTANGLE_H
#define __RECTANGLE_H
#include <iostream>
#include <string>
#include "shape.h"
class Rectangle : public Shape{
    double centreX;
    double centreY;
    double width;
    double height;
    std::string _fill;
public:
    Rectangle(std::string data, bool isForParsing = false);

    Rectangle(double x = 0, double y = 0, double width = 1, double height = 1, std::string fill = "none");

    Rectangle(Rectangle* rect);

    //void translate(double x, double y);
    void Print(std::ostream& output = std::cout);

    bool Within(Shape* shape);

    virtual Rectangle* clone();

    double getWidth(){
        return this->width;
    }

    double getHeight(){
        return this->height;
    }

    std::string getFill(){
        return this->_fill;
    }

    std::string type(){
        return "rectangle";
    }

    void setWidth(double x){
        this->width = x;
    }

    void setHeight(double y){
        this->height = y;
    }

    void setFill(std::string color){
        this->_fill = color;
    }

    void parse(std::string data);

    std::string exporrt();
};

#endif // SHAPE

