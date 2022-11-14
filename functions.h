//
// Created by dmitry on 12.10.22.
//

#ifndef UNTITLED1_FUNCTIONS_H
#define UNTITLED1_FUNCTIONS_H
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <iostream>
using namespace std;
using namespace sf;

static bool eventForGame = 0;

class myButton{
    string filename = "";
    double position_x = 0.0;
    double position_y = 0.0;
    double height = 0.0;
    double weight = 0.0;
public:

Image im;
Texture tex;
Sprite spr;
    myButton(string filename, double position_x, double position_y, double weight, double height);

    friend bool Contains(const myButton & button);
double getx() const;
double gety() const;
double getw() const;
double geth() const;
};

void Draw(vector<myButton>vi, RenderWindow &window);
class GameWithMenu{
public:
    bool eventForGame = 0;
};
struct MenuValue{
    int round = 0;
    string rezhim = "";
    bool isWhite = 0;
bool isGame = 1;
};
MenuValue menu(RenderWindow &window);
#endif //UNTITLED1_FUNCTIONS_H
