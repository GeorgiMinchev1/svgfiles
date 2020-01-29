
#include<iostream>
#include<fstream>
#include<string>
#include "shape.h"
#include "shapeField.h"
#include "svgparser.h"

SVGParser::SVGParser(){
    this->openedFile = "";
}

std::string SVGParser::open(std::string path){
    std::ifstream inputStream(path, std::ios::in);
    this->openedFile = path;
    std::string fileText;
    std::string singleEntry;
    bool hasFigure = false;
    do
    {
        inputStream>>singleEntry;
        //std::cout<<singleEntry<<std::endl;
        if(hasFigure || singleEntry == "<rect" || singleEntry == "<circle" || singleEntry == "<elipse"){
            hasFigure = true;
            fileText += " " + singleEntry;
            if(singleEntry == "/>"){
                hasFigure = false;
                fileText += "\n";
            }
        }

    }
    while(!(singleEntry == "</svg>"));

    return fileText;
    //std::cout<<fileText<<std::endl;
    /*ShapeField sf;
    sf.parse(fileText);
    std::cout<<"Check1"<<std::endl;
    sf.Print();
    inputStream.close();
    return sf;*/
}

bool SVGParser::save(ShapeField shapes){
    std::ofstream outputStream(openedFile, std::ios::out | std::ios::trunc);
    std::string outputXmlText = shapes.exporrt();
    std::cout<<"Successfuly imported data to file."<<std::endl;
    outputStream<<outputXmlText;
    outputStream.close();
}

bool SVGParser::saveAs(ShapeField shapes, std::string newFilePath){
    std::ofstream outputStream(openedFile, std::ios::out | std::ios::trunc);
    std::string outputXmlText = shapes.exporrt();
    std::ofstream newOutputStream(newFilePath, std::ios::out | std::ios::trunc);
    std::cout<<"Successfuly made a new file"<<std::endl;
    newOutputStream<<outputXmlText;
    outputStream.close();
}

void SVGParser::close(std::ostream& os){
    os<<"Closed file: "<<this->openedFile<<"."<<std::endl;
    this->openedFile = "";
}

bool SVGParser::hasOpenedFile(){
    return this->openedFile != "";
}
