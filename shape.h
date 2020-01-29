#ifndef __SHAPE_H
#define __SHAPE_H
#include <iostream>

class Shape{
    double centreX;
    double centreY;
public:
    void translate(double x, double y);
    virtual void Print(std::ostream& output = std::cout) = 0;
    virtual bool Within(Shape* shape) = 0;
    virtual std::string type() = 0;
    //virtual Shape* clone();
    double getX(){
        return this->centreX;
    }

    double getY(){
        return this->centreY;
    }

    void setX(double x){
        this->centreX = x;
    }

    void setY(double y){
        this->centreY = y;
    }

    virtual void parse(std::string text) = 0;

    virtual std::string exporrt() = 0;

};

#endif // SHAPE

