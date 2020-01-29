

#include<iostream>
#include<fstream>
//#include<cstring>
#include<string>
#include<sstream>
#include<vector>
#include "shape.h"
#include "rectangle.h"
#include "circle.h"
#include "elipse.h"
#include "shapefield.h"
#include "svgparser.h"
#include "commonfunctions.h"

const std::string INVALID_OPERATION = "Invalid operation";
std::vector<std::string> proccessInput(std::string input){
    int pos = 0;
    //int previous = 0;
    std::vector<std::string> result;
    //previous = pos;
    pos = input.find_first_of(' ', pos);
    result.push_back(input.substr(0, pos));

    result.push_back(input.substr(pos + 1, input.length() - pos - 1));
    return result;
}

void userInteraction(){

}

int main(){
    std::string input;
    SVGParser parser;
    std::vector<Rectangle> rectangles(10);
    int countRects = 0;
    std::vector<Circle> circles(10);
    int countCircs = 0;
    std::vector<Elipse> elipses(10);
    int countElips = 0;
    ShapeField shapes;
    do
    {
        std::getline(std::cin, input);
        std::vector<std::string> data = proccessInput(input);
        if(data[0] == "open"){

            std::string text = parser.open(data[1]);
            unsigned lastIndex = 0;
            unsigned index = 0;
            unsigned max = 0;

            max = text.find_last_of("/>", lastIndex);

            std::string s = text.substr(lastIndex, max - lastIndex);

            int i = s.find_first_of("/>", 0);
            //std::cout<<i<<std::endl;
            while(i != std::string::npos){
                //std::cout<<s<<std::endl;
                //std::cout<<index<<std::endl;
                if((lastIndex = s.find("<rect", index)) < i){
                    std::string data = s.substr(lastIndex, i);
                    Rectangle f(data, true);
                    rectangles[countRects] = f;
                    shapes.Create(std::cout, &rectangles[countRects]);
                    countRects++;
                }
                else if((lastIndex = s.find("<circle", index)) < i){
                    std::string data = s.substr(lastIndex, i);
                    Circle f(data, true);
                    circles[countCircs] = f;
                    shapes.Create(std::cout, &circles[countCircs]);
                    countCircs++;
                }
                else if((lastIndex = s.find("<elipse", index)) < i){
                    std::string data = s.substr(lastIndex, i);
                    Elipse f(data, true);
                    elipses[countElips] = f;
                    shapes.Create(std::cout, &elipses[countElips]);
                    countElips++;
                }
                index = i + 2;
                i = s.find_first_of("/>", index);

            }
            do{
                std::getline(std::cin, input);
                std::vector<std::string> data = proccessInput(input);
                if(data[0] == "print" || data[1] == "print"){
                    //rectangles[1].Print();
                    shapes.Print();
                }
                else if(data[0] == "create" || data[1] == "create"){
                    std::vector<std::string> figure = proccessInput(data[1]);
                    if(figure[0] == "rect" || figure[0] == "rectangle"){
                        Rectangle r1(figure[1]);
                        rectangles[countRects] = r1;
                        shapes.Create(std::cout, &rectangles[countRects]);
                        countRects++;
                    }
                    else if(figure[0] == "circle"){
                        Circle c1(figure[1]);
                        circles[countCircs] = c1;
                        shapes.Create(std::cout, &circles[countCircs]);
                        countCircs++;
                    }
                    else if(figure[0] == "elipse"){
                        Elipse e1(figure[1]);
                        Elipse e2 = e1.clone();
                        elipses[countElips] = e1;
                        shapes.Create(std::cout, &elipses[countElips]);
                        countElips++;
                    }
                    else {
                        std::cout<<"Invalid shape name."<<std::endl;
                    }
                }
                else if(data[0] == "within"){
                    std::vector<std::string> figure = proccessInput(data[1]);
                    if(figure[0] == "rect" || figure[0] == "rectangle"){
                        Rectangle r1(figure[1]);
                        //rectangles.push_back(r1);
                        shapes.Within(std::cout, &r1);
                        //countRects++;
                    }
                    else if(figure[0] == "circle"){
                        Circle c1(figure[1]);
                        //circles.push_back(c1);
                        shapes.Within(std::cout, &c1);
                        //countCircs++;
                    }
                    else if(figure[0] == "elipse"){
                        Elipse e1(figure[1]);
                        //elipses[countElips] = e1;
                        shapes.Within(std::cout, &e1);
                        //countElips++;
                    }
                    else {
                        std::cout<<"Invalid shape name."<<std::endl;
                    }
                }
                else if(data[0] == "erase" || data[1] == "erase"){
                    int n;
                    std::istringstream iss(data[1]);
                    iss>>n;
                    shapes.Erase(std::cout, n);
                }
                else if(data[0] == "close" || data[1] == "close"){
                    parser.close();
                    shapes.Empty();
                    rectangles.erase(rectangles.begin(), rectangles.end());
                    circles.erase(circles.begin(), circles.end());
                    elipses.erase(elipses.begin(), elipses.end());
                    break;
                }
                else if(data[0] == "loop" || data[1] == "loop"){
                    parser.close();
                    break;
                }
                else if(data[0] == "translate"){
                    std::string text = data[1];
                    Common cm;
                    int shape = 0;
                    std::string query;
                    int lastBracket = 0;
                    std::string s;

                    //geting the index value
                    int index = text.find("index=", 0);
                    if(index != std::string::npos){
                        query = "index=";
                        lastBracket = text.find(" ", index + query.length());
                        s = text.substr(index + query.length(), lastBracket - query.length() - index);
                        shape = cm.parseDouble(s.c_str());
                    }

                    //geting the vertical value
                    index = text.find("vertical=", 0);
                    query = "vertical=";
                    lastBracket = text.find(" ", index + query.length());
                    s = text.substr(index + query.length(), lastBracket - query.length() - index);
                    double vertical = cm.parseDouble(s.c_str());

                    //geting the horizontal value
                    index = text.find("horizontal=", 0);
                    query = "horizontal=";
                    lastBracket = text.find(" ", index + query.length());
                    s = text.substr(index + query.length(), lastBracket - query.length() - index);
                    double horizontal = cm.parseDouble(s.c_str());

                    shapes.Translate(std::cout, shape, horizontal, vertical);
                }
                else if(data[0] == "save" || data[1] == "save"){
                    parser.save(shapes);
                }
                else if(data[0] == "saveas" || data[1] == "saveas") {
                    parser.saveAs(shapes, data[1]);
                }
                else if(data[0] == "exit" || data[1] == "exit") {
                    return 0;
                }
                else {
                    std::cout<<"Invalid operation."<<std::endl;
                }
            }
            while(true);
        }
        else if(data[1] == "open" || data[1] == "nopen"){
            //Rectangle r1("0 1 1 2 lime");
            //rectangles.push_back(r1);
            //shapes.Create(std::cout, &r1);
            do{
                std::getline(std::cin, input);
                std::vector<std::string> data = proccessInput(input);
                if(data[0] == "print" || data[1] == "print"){
                    //rectangles[1].Print();
                    std::cout<<"Before print."<<std::endl;
                    shapes.Print();
                }
                else if(data[0] == "create" || data[1] == "create"){
                    std::vector<std::string> figure = proccessInput(data[1]);
                    if(figure[0] == "rect" || figure[0] == "rectangle"){
                        Rectangle r1(figure[1]);
                        rectangles[countRects] = r1;
                        shapes.Create(std::cout, &rectangles[countRects]);
                        countRects++;
                    }
                    else if(figure[0] == "circle"){
                        Circle c1(figure[1]);
                        circles[countCircs] = c1;
                        shapes.Create(std::cout, &circles[countCircs]);
                        countCircs++;
                    }
                    else if(figure[0] == "elipse"){
                        Elipse e1(figure[1]);
                        elipses[countElips] = e1;
                        shapes.Create(std::cout, &elipses[countElips]);
                        countElips++;
                    }
                    else {
                        std::cout<<"Invalid shape name."<<std::endl;
                    }
                }
                else if(data[0] == "within"){
                    std::vector<std::string> figure = proccessInput(data[1]);
                    if(figure[0] == "rect" || figure[0] == "rectangle"){
                        Rectangle r1(figure[1]);
                        //rectangles.push_back(r1);
                        shapes.Within(std::cout, &r1);
                        //countRects++;
                    }
                    else if(figure[0] == "circle"){
                        Circle c1(figure[1]);
                        //circles.push_back(c1);
                        shapes.Within(std::cout, &c1);
                        //countCircs++;
                    }
                    else if(figure[0] == "elipse"){
                        Elipse e1(figure[1]);
                        //elipses.push_back(e1);
                        shapes.Within(std::cout, &e1);
                        //countElips++;
                    }
                    else {
                        std::cout<<"Invalid shape name."<<std::endl;
                    }
                }
                else if(data[0] == "erase" || data[1] == "erase"){
                    int n;
                    std::istringstream iss(data[1]);
                    iss>>n;
                    shapes.Erase(std::cout, n);
                }
                else if(data[0] == "translate"){
                    std::string text = data[1];
                    Common cm;
                    int shape = 0;
                    std::string query;
                    int lastBracket = 0;
                    std::string s;

                    //geting the index value
                    int index = text.find("index=", 0);
                    if(index != std::string::npos){
                        query = "index=";
                        lastBracket = text.find(" ", index + query.length());
                        s = text.substr(index + query.length(), lastBracket - query.length() - index);
                        shape = cm.parseDouble(s.c_str());
                    }

                    //geting the vertical value
                    index = text.find("vertical=", 0);
                    query = "vertical=";
                    lastBracket = text.find(" ", index + query.length());
                    s = text.substr(index + query.length(), lastBracket - query.length() - index);
                    double vertical = cm.parseDouble(s.c_str());

                    //geting the horizontal value
                    index = text.find("horizontal=", 0);
                    query = "horizontal=";
                    lastBracket = text.find(" ", index + query.length());
                    s = text.substr(index + query.length(), lastBracket - query.length() - index);
                    double horizontal = cm.parseDouble(s.c_str());

                    shapes.Translate(std::cout, shape, horizontal, vertical);
                }
                else if(data[0] == "close" || data[1] == "close"){
                    std::cout<<"You have no opened file."<<std::endl;
                    shapes.Empty();
                    rectangles.erase(rectangles.begin(), rectangles.end());
                    circles.erase(circles.begin(), circles.end());
                    elipses.erase(elipses.begin(), elipses.end());
                    break;
                }
                else if(data[0] == "loop" || data[1] == "loop"){
                    break;
                }
                else if(data[0] == "save" || data[1] == "save"){
                    std::cout<<"You have no opened file."<<std::endl;
                    //parser.save(shapes);
                }
                else if(data[0] == "saveas" || data[1] == "saveas") {
                    parser.saveAs(shapes, data[1]);
                }
                else if(data[0] == "exit" || data[1] == "exit") {
                    return 0;
                }
                else {
                    std::cout<<"Invalid operation."<<std::endl;
                }
            }
            while(true);
        }
        else if(data[0] == "exit" || data[1] == "exit"){
            return 0;
        }
    }
    while(true);
    return 0;
}

