

#include <iostream>
#include <string>
#include <cmath>
#include "rectangle.h"
#include "circle.h"
#include "shapeField.h"
#include "commonfunctions.h"
//#include "./CommonFunctions.cpp"

Circle::Circle(std::string data, bool isForParsing){
    if(isForParsing){
        parse(data);
    }
    else {
        Common cm;
        unsigned lastIndex = 0;
        unsigned index = 0;

        index = data.find(" ", 0);
        std::string s = data.substr(lastIndex, index - lastIndex);
        setX(cm.parseDouble(s.c_str()));
        lastIndex = index + 1;

        index = data.find(" ", lastIndex);
        s = data.substr(lastIndex, index - lastIndex);
        setY(cm.parseDouble(s.c_str()));
        lastIndex = index + 1;

        index = data.find(" ", lastIndex);
        s = data.substr(lastIndex, index - lastIndex);
        this->radius = cm.parseDouble(s.c_str());
        lastIndex = index + 1;

        index = data.find(" ", lastIndex);
        s = data.substr(lastIndex, index - lastIndex);
        this->_fill = s;
    }
}

Circle::Circle(double x, double y, double rad, std::string fill){
    setX(x);
    setY(y);
    radius = abs(rad);
    _fill = fill;
}

Circle::Circle(Circle* circle){
    setX(circle->getX());
    setY(circle->getY());
    setRadius(circle->getRadius());
    setFill(circle->getFill());
}

Circle* Circle::clone(){
    return new Circle(*this);
}

void Circle::Print(std::ostream& output){
    output<<"circle with cenre X = "<<getX()<<" and  Y = "<<getY()<<" and has radius "<<radius<<" with fill "<<_fill<<"."<<std::endl;
}

bool Circle::Within(Shape* shape){
    if(shape->type() == "rectangle"){
        Shape* s = shape;
        Rectangle* rec = (Rectangle*)s;
        double finalX = rec->getX() + rec->getWidth();
        double finalY = rec->getY() + rec->getHeight();
        double MinX = fmin(rec->getX(), finalX);
        double MinY = fmin(rec->getY(), finalY);
        double MaxX = fmax(rec->getX(), finalX);
        double MaxY = fmax(rec->getY(), finalY);//centreX
        if(abs(finalX - rec->getX()) > abs(getX() - rec->getX()) && abs(rec->getX() - finalX) > abs(getX() - finalX) &&
           abs(finalX - rec->getX()) > abs(getY() - rec->getY()) && abs(rec->getY() - finalY) > abs(getY() - finalY)){
             if( (getX() - radius) > MinX && (getX() + radius) < MaxX &&
              (getY() - radius) > MinY && (getY() + radius) < MaxY){
                 return true;
             }
             return false;
        }
        return false;
    }
    else if(shape->type() == "circle"){
        Shape* s = shape;
        Circle* circle = (Circle*)s;
        //double finalX = getX() + width;
        //double finalY = getY() + height;
        if(abs(getX() - circle->getX()) + radius < circle->getRadius() &&
           abs(getY() - circle->getY()) + radius < circle->getRadius() &&
           abs(getX() - circle->getX()) - radius > -circle->getRadius() &&
           abs(getY() - circle->getY()) - radius > -circle->getRadius()){
              return true;
           }
    }
    else {
        return false;
    }
}
void Circle::parse(std::string data){
    Common cm;
    unsigned lastIndex = 0;
    unsigned index = 0;
    //std::cout<<data<<std::endl;

    index = data.find("cx=\"", 0);
    std::string query("cx=\"");
    unsigned lastBracket = data.find("\"", index + query.length());
    std::string s = data.substr(index + query.length(), lastBracket - query.length() - index);
    setX(cm.parseDouble(s.c_str()));
    lastIndex = index + 1;

    index = data.find("cy=\"", 0);
    query = "cy=\"";
    lastBracket = data.find("\"", index + query.length());
    s = data.substr(index + query.length(), lastBracket - query.length() - index);
    setY(cm.parseDouble(s.c_str()));
    lastIndex = index + 1;

    index = data.find("r=\"", 0);
    query = "r=\"";
    lastBracket = data.find("\"", index + query.length());
    s = data.substr(index + query.length(), lastBracket - query.length() - index);
    this->radius = cm.parseDouble(s.c_str());
    lastIndex = index + 1;

    index = data.find("fill=\"", 0);
    query = "fill=\"";
    lastBracket = data.find("\"", index + query.length());
    s = data.substr(index + query.length(), lastBracket - query.length() - index);
    this->_fill = s;
    lastIndex = index + 1;
    this->Print();
}

std::string Circle::exporrt(){
    Common cm;
    std::string output;
    output = "<circle cx=\"";
    output += cm.doubleToString(getX());

    output += "\" cy=\"";
    output += cm.doubleToString(getY());

    output += "\" radius=\"";
    output += cm.doubleToString(this->radius);

    output += "\" fill=\"";
    output += this->_fill;

    output += "\" /> \n";
    return output;
}
