
#include <iostream>
#include <string>
#include <cmath>
#include "rectangle.h"
#include "circle.h"
#include "elipse.h"
#include "commonfunctions.h"
//#include "./CommonFunctions.cpp"


Elipse::Elipse(std::string data, bool isForParsing){
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
        this->radiusX = cm.parseDouble(s.c_str());
        lastIndex = index + 1;

        index = data.find(" ", lastIndex);
        s = data.substr(lastIndex, index - lastIndex);
        this->radiusY = cm.parseDouble(s.c_str());
        lastIndex = index + 1;

        index = data.find(" ", lastIndex);
        s = data.substr(lastIndex, index - lastIndex);
        this->_fill = s;
    }
}

Elipse::Elipse(double x, double y, double radX, double radY, std::string fill){
    setX(x);
    setY(y);
    this->radiusX = abs(radX);
    this->radiusY = abs(radY);
    this->_fill = fill;
}

Elipse::Elipse(Elipse* elipse){
    setX(elipse->getX());
    setY(elipse->getY());
    setRadiusX(elipse->getRadiusX());
    setRadiusY(elipse->getRadiusY());
    setFill(elipse->getFill());
}


Elipse* Elipse::clone(){
    return new Elipse(*this);
}


void Elipse::Print(std::ostream& output){
    output<<"elipse  x = "<<getX()<<" and  y = "<<getY()<<" and has rx "<<radiusX<<" and ry = "<<radiusY<<" with fill "<<_fill<<"."<<std::endl;
}

bool Elipse::Within(Shape* shape){
    if(shape->type() == "rectangle"){
        Shape* s = shape;
        Rectangle* rec = (Rectangle*)s;
        double finalX = rec->getX() + rec->getWidth();
        double finalY = rec->getY() + rec->getHeight();
        double MinX = fmin(rec->getX(), finalX);
        double MinY = fmin(rec->getY(), finalY);
        double MaxX = fmax(rec->getX(), finalX);
        double MaxY = fmax(rec->getY(), finalY);
        if(abs(finalX - rec->getX()) > abs(getX() - rec->getX()) && abs(rec->getX() - finalX) > abs(getX() - finalX) &&
           abs(finalY - rec->getY()) > abs(getY() - rec->getY()) && abs(rec->getY() - finalY) > abs(getY() - finalY)){
             if(  getX() - radiusX > MinX && (radiusX + getX()) < MaxX &&
               getY() - radiusY > MinY && (radiusY + getY()) < MaxY){
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
        if(abs(getX() - circle->getX()) + radiusX < circle->getRadius() &&
           abs(getY() - circle->getY()) + radiusY < circle->getRadius() &&
           abs(getX() - circle->getX()) - radiusX > -circle->getRadius() &&
           abs(getY() - circle->getY()) - radiusY > -circle->getRadius()){
              return true;
           }
    }
    else {
        return false;
    }
}
void Elipse::parse(std::string data){
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

    index = data.find("rx=\"", 0);
    query = "rx=\"";
    lastBracket = data.find("\"", index + query.length());
    s = data.substr(index + query.length(), lastBracket - query.length() - index);
    this->radiusX = cm.parseDouble(s.c_str());
    lastIndex = index + 1;

    index = data.find("ry=\"", 0);
    query = "ry=\"";
    lastBracket = data.find("\"", index + query.length());
    s = data.substr(index + query.length(), lastBracket - query.length() - index);
    this->radiusY = cm.parseDouble(s.c_str());
    lastIndex = index + 1;

    index = data.find("fill=\"", 0);
    query = "fill=\"";
    lastBracket = data.find("\"", index + query.length());
    s = data.substr(index + query.length(), lastBracket - query.length() - index);
    this->_fill = s;
    lastIndex = index + 1;
    this->Print();
}

std::string Elipse::exporrt(){
    Common cm;
    std::string output;
    output = "<elipse cx=\"";
    output += cm.doubleToString(getX());

    output += "\" cy=\"";
    output += cm.doubleToString(getY());

    output += "\" rx=\"";
    output += cm.doubleToString(this->radiusX);

    output += "\" ry=\"";
    output += cm.doubleToString(this->radiusY);

    output += "\" fill=\"";
    output += this->_fill;

    output += "\" /> \n";
    return output;
}


