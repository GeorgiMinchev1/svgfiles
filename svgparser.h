#include<iostream>
#include<string>
#include "shape.h"
#include "shapeField.h"

class SVGParser {
    std::string openedFile;

public:
    SVGParser();

    std::string open(std::string path);

    bool save(ShapeField shapes);

    bool saveAs(ShapeField shapes, std::string newFilePath);

    void close(std::ostream& os = std::cout);

    bool hasOpenedFile();
};



