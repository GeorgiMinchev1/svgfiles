

#include <iostream>
#include "shape.h"

void Shape::translate(double x, double y){
    centreX += x;
    centreY += y;
}

/*void Shape::Print(std::ostream& output) = 0;
bool Shape::Within(Shape* shape) = 0;
std::string Shape::type() = 0;*/
