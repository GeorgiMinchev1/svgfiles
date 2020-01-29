#ifndef __SHAPEFIELD_H
#define __SHAPEFIELD_H

#include<iostream>
#include<vector>
#include "shape.h";
//#include "./shapes/Rectangle.h";
//#include "./shapes/Elipse.h";
//#include "./shapes/Circle.h";

class ShapeField{
    std::vector<Shape*> shapes;
    std::vector<std::string> shapeNames;
    int count;
public:
    ShapeField();
    ShapeField(std::string xmlText);

    std::vector<Shape*> parse(std::string xmlText);

    std::string exporrt();

    void setShapes(std::vector<Shape*> vec){
        this->shapes = vec;
    }

    void Print(std::ostream& os = std::cout);

    void partialPrint(std::ostream& os, int indexes[], int n, std::string nZeroMsg);

    void Create(std::ostream& os, Shape* shape);

    void Erase(std::ostream& os, int index);

    void Empty();

    void Translate(std::ostream& os, int index, double x, double y);

    void Within(std::ostream& os, Shape* shape);
};

#endif

