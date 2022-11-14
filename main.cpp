

#include <SFML/Graphics.hpp>
#include <iostream>
#include "map.h"
#include "view.h"
#include <sstream>
#include "functions.h"
#include "Header.h"
using namespace sf;



////////////////////////////////////////////////////КЛАСС ИГРОКА////////////////////////
class Player {
private:
public:
    float x, y ;
    float w, h, dx, dy, speed;
    int dir, playerScore, health;
    String File;
    Image image;
    Texture texture;
    Sprite sprite;
    Player(String F, float X, float Y, float W, float H){
        dx=0; dy=0; speed=0; dir =0; playerScore = 0; health = 60;
        File = F;
        w = W; h = H;
        image.loadFromFile(File);
        image.createMaskFromColor(Color(41, 33, 59));
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        x = X; y = Y;
        sprite.setTextureRect(IntRect(0, 0, w, h));
    }
    void update(float time)
    {
        switch (dir)
        {
            case 0: dx = speed; dy = 0; break;
            case 1: dx = -speed; dy = 0; break;
            case 2: dx = 0; dy = speed; break;
            case 3: dx = 0; dy = -speed; break;
            case 41: dx = 2*speed; dy = 0; break;
            case 42: dx = -2*speed; dy = 0; break;
            case 43: dx = 0; dy = 2* speed; break;
            case 44: dx = 0; dy = -2* speed; break;
            case 51: sprite.setScale(0.4, 0.4); break;
        }

        x += dx*time;
        y += dy*time;

        speed = 0;
        sprite.setPosition(x,y);
        interactionWithMap();//вызываем функцию, отвечающую за взаимодействие с картой
    }


    void interactionWithMap()//ф-ция взаимодействия с картой
    {

        for (int i = y / 32; i < (y + h) / 32; i++)//проходимся по тайликам, контактирующим с игроком,, то есть по всем квадратикам размера 32*32, которые мы окрашивали в 9 уроке. про условия читайте ниже.
            for (int j = x / 32; j<(x + w) / 32; j++)//икс делим на 32, тем самым получаем левый квадратик, с которым персонаж соприкасается. (он ведь больше размера 32*32, поэтому может одновременно стоять на нескольких квадратах). А j<(x + w) / 32 - условие ограничения координат по иксу. то есть координата самого правого квадрата, который соприкасается с персонажем. таким образом идем в цикле слева направо по иксу, проходя по от левого квадрата (соприкасающегося с героем), до правого квадрата (соприкасающегося с героем)
            {
                if (TileMap[i][j] == '0')//если наш квадратик соответствует символу 0 (стена), то проверяем "направление скорости" персонажа:
                {
                    if (dy>0)//если мы шли вниз,
                    {
                        y = i * 32 - h;//то стопорим координату игрек персонажа. сначала получаем координату нашего квадратика на карте(стены) и затем вычитаем из высоты спрайта персонажа.
                    }
                    else if (dy<0)
                    {
                        y = i * 32 + 32;//аналогично с ходьбой вверх. dy<0, значит мы идем вверх (вспоминаем координаты паинта)
                    }
                    else if (dx>0)
                    {
                        x = j * 32 - w;//если идем вправо, то координата Х равна стена (символ 0) минус ширина персонажа
                    }
                    else if (dx < 0)
                    {
                        x = j * 32 + 32;//аналогично идем влево
                    }
                }

                else if (TileMap[i][j] == 's') { //если символ равен 's' (камень)
                    playerScore++;

                    TileMap[i][j] = ' ';//убираем камень, типа взяли бонус. можем и не убирать, кстати.
                }
                else if(TileMap[i][j] == 'h'){TileMap[i][j] = ' '; health++;

                    }

            }
    }


    float getplayercoordinateX(){
        return x;
    }
    float getplayercoordinateY(){
        return y;
    }

};


int main() {
    MenuValue menuResult;
    RenderWindow window(sf::VideoMode(1280, 822), "Checkers");
    menuResult=menu(window);
    Game game;
    game.start(menuResult);
}