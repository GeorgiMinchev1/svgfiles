

#include<iostream>
#include "rectangle.h"
#include "circle.h"
#include "elipse.h"
#include "shapefield.h"

void testRectangle(){
    Rectangle r(10.0, 10.0, 10.0, 50.0);
    Rectangle r1(10.0, 10.0, -10.0, -50.0, "green");
    Shape* rect1 = &r;
    Shape* rect2 = &r1;
    Rectangle a(0.0, 0.0, 30.0, 80.0);
    Rectangle a1(20, 20, -50, -80);
    Circle a2(0, 0, 41);
    Circle a3(0, 0, 39);
    Shape* test1 = &a;
    Shape* test2 = &a1;
    Shape* test3 = &a2;
    Shape* test4 = &a3;
    rect1->Print(std::cout);
    //rect1->translate(10, 0);
    //rect1->Print();
    //rect2->translate(100, 2);
    rect2->Print();
    std::cout<<rect1->Within(rect2)<<" "<<0<<std::endl;//0
    std::cout<<rect1->Within(test1)<<" "<<1<<std::endl;//1
    std::cout<<rect2->Within(test2)<<" "<<1<<std::endl;//1
    std::cout<<rect2->Within(test3)<<" "<<1<<std::endl;//1
    std::cout<<rect2->Within(test4)<<" "<<0<<std::endl;//0
}

void testCircle(){
    Circle c1(0, 0, 10);
    Circle c2(0, 0, 50, "blue");
    Shape* circ1 = &c1;
    Shape* circ2 = &c2;
    Rectangle a(0, 0, 5, 10);
    Rectangle a1(20, 20, -50, -80);
    Circle a2(0, 0, 51);
    Circle a3(0, 0, 20);
    Rectangle a4(0, 0, 130, 120);
    Shape* test1 = &a;
    Shape* test2 = &a1;
    Shape* test3 = &a2;
    Shape* test4 = &a3;
    Shape* test5 = &a4;
    circ1->Print(std::cout);
    //circ1->translate(10, 0);
    //circ1->Print();
    circ2->Print();
    std::cout<<circ1->Within(test1)<<" "<<0<<std::endl;//0
    std::cout<<circ1->Within(test2)<<" "<<1<<std::endl;//1
    std::cout<<circ2->Within(test3)<<" "<<1<<std::endl;//1
    std::cout<<circ2->Within(test4)<<" "<<0<<std::endl;//0
    circ2->translate(51, 51);
    std::cout<<circ2->Within(test5)<<" "<<1<<std::endl;//1
}

void testElipse(){
    Elipse e1(0, 0, 10, 40, "blue");
    Shape* elipse1 = &e1;
    Elipse e2(13, 11, 12, 5);
    Shape* elipse2 = &e2;
    Rectangle a(-15, -50, 40, 100);
    std::cout<<a.exporrt();
    Rectangle a1(11, 41, -22, -82);
    Circle a2(0, 0, 50);
    std::cout<<a2.exporrt();
    std::cout<<e2.exporrt();
    Circle a3(0, 0, 20);
    Rectangle a4(0, 0, 30, 80);
    Shape* test1 = &a;
    Shape* test2 = &a1;
    Shape* test3 = &a2;
    Shape* test4 = &a3;
    Shape* test5 = &a4;
    elipse1->Print(std::cout);
    //elipse1->translate(10, 0);
    //elipse1->Print();
    //elipse2->translate(100, 2);
    elipse2->Print();
    std::cout<<elipse1->Within(test1)<<" r "<<1<<std::endl;//1
    std::cout<<elipse1->Within(test2)<<" r "<<1<<std::endl;//1
    std::cout<<elipse2->Within(test3)<<" circle "<<1<<std::endl;//1
    std::cout<<elipse2->Within(test4)<<" circle "<<0<<std::endl;//0
    std::cout<<elipse2->Within(test5)<<" r "<<1<<std::endl;//1
}

void testShapeField(){
    Rectangle a1(21, 21, -50, -80);

    ShapeField sf;
    Rectangle r1(10.0, 10.0, -10.0, -50.0, "green");
    Circle a3("0 0 20 lime");
    Elipse e2(13, 11, 12, 5);


    sf.Create(std::cout, &r1);
    sf.Create(std::cout, &a3);
    sf.Create(std::cout, &e2);
    std::string input;
    std::getline(std::cin, input);
    Circle c1(input);
    sf.Create(std::cout, &c1);

    sf.Within(std::cout, &a1);
    sf.Print();
}
/*
int main(){
    //testRectangle();
    //testCircle();
    //testElipse();
    testShapeField();
    return 0;
}
*/
