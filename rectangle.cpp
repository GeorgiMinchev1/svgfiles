
#include<iostream>
#include <string>
#include <cmath>
#include "shape.h"
#include "rectangle.h"
#include "circle.h"
#include "shapeField.h"
#include "commonfunctions.h"
//#include "./CommonFunctions.cpp"

Rectangle::Rectangle(std::string data, bool isForParsing){
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
        this->width = cm.parseDouble(s.c_str());
        lastIndex = index + 1;

        index = data.find(" ", lastIndex);
        s = data.substr(lastIndex, index - lastIndex);
        this->height = cm.parseDouble(s.c_str());
        lastIndex = index + 1;

        index = data.find(" ", lastIndex);
        s = data.substr(lastIndex, index - lastIndex);
        this->_fill = s;
    }
}

Rectangle::Rectangle(double x, double y, double width, double height, std::string fill){
    setX(x);
    setY(y);
    setWidth(width);
    setHeight(height);
    setFill(fill);
}

Rectangle::Rectangle(Rectangle* rect){
    setX(rect->getX());
    setY(rect->getY());
    setWidth(rect->getWidth());
    setHeight(rect->getHeight());
    setFill(rect->getFill());
}


Rectangle* Rectangle::clone(){
    return new Rectangle(*this);
}


void Rectangle::Print(std::ostream& output){
    output<<"rectangle x = "<<getX()<<", y = "<<getY()<<" and width = "<<width<<", height = "<<height<<" with fill "<<_fill<<"."<<std::endl;
}

bool Rectangle::Within(Shape* shape){
    if(shape->type() == "rectangle"){
        Shape* s = shape;
        /*Rectangle re;
        s = &re;*/
        Rectangle* rec;
        rec = (Rectangle*)s;
        double finalX = rec->getX() + rec->getWidth();
        double finalY = rec->getY() + rec->getHeight();
        double fX = getX() + getWidth();
        double fY = getY() + getHeight();
        double MinX = fmin(rec->getX(), finalX);
        double MinY = fmin(rec->getY(), finalY);
        double MaxX = fmax(rec->getX(), finalX);
        double MaxY = fmax(rec->getY(), finalY);
        if(abs(finalX - rec->getX()) > abs(getX() - rec->getX()) && abs(rec->getX() - finalX) > abs(getX() - finalX) &&
           abs(finalX - rec->getX()) > abs(getY() - rec->getY()) && abs(rec->getY() - finalY) > abs(getY() - finalY)){
             if( (width + getX()) > MinX && (width + getX()) < MaxX &&
              (height + getY()) > MinY && (height + getY()) < MaxY){
                 return true;
             }
             return false;
        }
        return false;
    }
    else if(shape->type() == "circle"){
        Shape* s1 = shape;
        Circle* circle = (Circle*)s1;
        double finalX = getX() + width;
        double finalY = getY() + height;
        if(abs(getX() - circle->getX()) < circle->getRadius() &&
           abs(getY() - circle->getY()) < circle->getRadius() &&
           abs(finalX - circle->getX()) < circle->getRadius() &&
           abs(finalY - circle->getY()) < circle->getRadius()){
              return true;
           }
    }
    else {
        return false;
    }
}
void Rectangle::parse(std::string data){
    Common cm;
    unsigned lastIndex = 0;
    unsigned index = 0;
    unsigned lastBracket = 0;

    //std::cout<<data<<std::endl;

    index = data.find("x=\"", 0);
    std::string query("x=\"");
    lastBracket = data.find("\"", index + query.length());
    std::string s = data.substr(index + query.length(), lastBracket - query.length() - index);
    setX(cm.parseDouble(s.c_str()));


    index = data.find("y=\"", 0);
    query = "y=\"";
    lastBracket = data.find("\"", index + query.length());
    s = data.substr(index + query.length(), lastBracket - query.length() - index);
    setY(cm.parseDouble(s.c_str()));

    index = data.find("width=\"", 0);
    query = "width=\"";
    lastBracket = data.find("\"", index + query.length());
    s = data.substr(index + query.length(), lastBracket - query.length() - index);
    this->width = cm.parseDouble(s.c_str());


    index = data.find("height=\"", 0);
    query = "height=\"";
    lastBracket = data.find("\"", index + query.length());
    s = data.substr(index + query.length(), lastBracket - query.length() - index);
    this->height = cm.parseDouble(s.c_str());


    index = data.find("fill=\"", 0);
    query = "fill=\"";
    lastBracket = data.find("\"", index + query.length());
    s = data.substr(index + query.length(), lastBracket - index - query.length());
    this->_fill = s;
    this->Print(std::cout);
}

std::string Rectangle::exporrt() {
    Common cm;
    std::string output;
    output = "<rect x=\"";
    output += cm.doubleToString(getX());

    output += "\" y=\"";
    output += cm.doubleToString(getY());

    output += "\" width=\"";
    output += cm.doubleToString(this->width);

    output += "\" height=\"";
    output += cm.doubleToString(this->height);

    output += "\" fill=\"";
    output += this->_fill;

    output += "\" /> \n";
    return output;
}
