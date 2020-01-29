

#include <iostream>
#include <vector>
#include "shape.h";//./shapes/S
#include "shapefield.h"
#include "rectangle.h";
#include "elipse.h";
#include "circle.h";

ShapeField::ShapeField(){
    count = 0;
}

ShapeField::ShapeField(std::string xmlText){
    parse(xmlText);
}

std::vector<Shape*> ShapeField::parse(std::string xmlText){
    unsigned lastIndex = 0;
    unsigned index = 0;
    unsigned max = 0;

    max = xmlText.find_last_of("/>", lastIndex);

    std::string s = xmlText.substr(lastIndex, max - lastIndex);

    int i = s.find_first_of("/>", 0);
    //std::cout<<i<<std::endl;
    while(i != std::string::npos){
        //std::cout<<s<<std::endl;
        //std::cout<<index<<std::endl;
        if((lastIndex = s.find("<rect", index)) < i){
            std::string data = s.substr(lastIndex, i);
            Rectangle f(data, true);
            this->Create(std::cout, &f);
        }
        else if((lastIndex = s.find("<circle", index)) < i){
            std::string data = s.substr(lastIndex, i);
            Circle f(data, true);
            this->Create(std::cout, &f);
        }
        else if((lastIndex = s.find("<elipse", index)) < i){
            std::string data = s.substr(lastIndex, i);
            Elipse f(data, true);
            this->Create(std::cout, &f);
        }
        index = i + 2;
        i = s.find_first_of("/>", index);

    }

    //Print();
    shapes[0]->Print();
    //Print();
    return shapes;
}

std::string ShapeField::exporrt(){
    std::string output = "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>";
    output += "<svg width=\"391\" height=\"391\" viewBox=\"-70.5 -70.5 391 391\" xmlns=\"http://www.w3.org/2000/svg\"> \n";
    for(int i = 0;i < this->count;i++){
        output += shapes[i]->exporrt();
    }
    output += "</svg>";
    //std::cout<<output<<std::endl;
    return output;
}

void ShapeField::Print(std::ostream& os){
    for(int i = 0;i < this->count;i++){
        os<<i + 1<<". ";
        shapes[i]->Print(os);
    }
    os<<std::endl;
}

/*void ShapeField::partialPrint(std::ostream& os, int indexes[], int n, std::string nZeroMsg){
    if(n == 0){
        os<<nZeroMsg;
    }
    else {
        for(int i = 0;i < n;i++){
            int index = indexes[i] - 1;
            os<<index<<". ";
            shapes[index].Print(os);
        }
    }

}*/

void ShapeField::Create(std::ostream& os, Shape* shape){
    int index = this->count;
    shapes.push_back(shape);
    os<<"Successfully created "<<shapes[index]->type()<<" ("<<index + 1<<")"<<std::endl;
    this->count++;
}

void ShapeField::Erase(std::ostream& os, int index){
    if(index > this->count || index < 1){
        os<<"Invalid index!"<<std::endl;
    }
    else {
        os<<"Erased a "<<shapes[index - 1]->type()<<" ("<<index<<")"<<std::endl;
        if(index != 1) {
            shapes.erase(shapes.begin() + index - 1);
            for(int i = index;i < this->count;i++){
                shapes[i - 1] = shapes[i];
            }
        }
        else shapes.erase(shapes.begin());

        //shapes.erase(shapes.begin() + this->count - 1);
        this->count--;
    }

}

void ShapeField::Empty(){
    shapes.erase(shapes.begin(), shapes.end());
    this->count = 0;
}

void ShapeField::Translate(std::ostream& os, int index, double x, double y){
    if(index > this->count || index < 1){
        for(int i = 0;i < this->count;i++){
            shapes[i]->translate(x, y);
        }
        os<<"Translated all figures"<<std::endl;
    }
    else {
        shapes[index - 1]->translate(x, y);
        os<<"Translated "<<shapes[index - 1]->type()<<" ("<<index<<")"<<std::endl;
    }
}

void ShapeField::Within(std::ostream& os, Shape* shape){
    bool found = false;
    std::string msg = "";
    for(int i = 0;i < this->count;i++){
        if(shapes[i]->Within(shape)){
            found = true;
            os<<i + 1<<". ";
            shapes[i]->Print(os);
        }
    }

    if(!found)msg = "No figures are located within: ";
    else msg = "These are the figures located within ";
    os<<msg;
    shape->Print();
    os<<std::endl;
}



