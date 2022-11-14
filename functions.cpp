//
// Created by dmitry on 12.10.22.
//
#include "functions.h"
#include "vector"

myButton::myButton(string filename, double position_x, double position_y, double weight, double height){//конструктор с параматрами
    this->filename = filename;
    this->position_x = position_x;
    this->position_y = position_y;
    this->height = height;
    this->weight = weight;
    im.loadFromFile(filename);
    tex.loadFromImage(im);
    spr.setTexture(tex);
    spr.setPosition(position_x, position_y);
    cout << filename << " " << position_x << " " << position_y << '\n';
}
void Draw(vector<myButton>vi, RenderWindow &window){//функция для рисования переданных объектов класса myButton
    for(int i = 0; i < vi.size(); i++){
        window.draw(vi[i].spr);
    }
}
double myButton::getx() const{//геттеры
    return position_x;
}
double myButton::gety() const{
    return position_y;
}
double myButton::getw() const{
    return weight;
}
double myButton::geth() const{
    return height;
}
void DrawYellow(vector<myButton>&vi, int menuNumForColor, int numericYellow, MenuValue &value, string name){//хм...сложно объяснить, вообщем когда мы кликаем на одну кнопку в меню - она загорается в жёлтый. Все остальные кнопки в это время принимают обычный цвет. Таким образом мы выбираем 1 вариант из нескольких
    for(int i = 1; i < vi.size() + 1; i++){
        if(i == menuNumForColor && numericYellow%2 == 1){
            vi[i - 1].spr.setColor(Color::Yellow);
            if(name == "round")
                value.round = menuNumForColor;
            else if(name == "rezhim")
                value.rezhim = menuNumForColor;
            else if(name == "isWhite")
                value.isWhite = menuNumForColor;
            cout << "coloryellow\n";
            }


        else{
            vi[i - 1].spr.setColor(Color(152, 79, 11));
        }
        }



}
MenuValue menu(RenderWindow &window) {
    MenuValue value;
    myButton menu1("begin2.png", 70, 310, 300, 60);
    myButton menu2("options2.png", 70, 390, 300, 60);
    myButton menu3("exit.png", 70, 470, 300, 60);
    myButton menuBg("checkers.jpg", 0, 0, 300, 60);
    vector<myButton>menu{menuBg, menu1, menu2, menu3}; //засунул в вектор кнопки начального экрана

    bool isMenu = 1; //переменная, отвечающая за работу меню, когда =0, меню закрывается
    bool isOpt = 1; //аналогично с полем настроек
    bool isExit = 1; //и с полем выхода
    bool truedraw = 1; //равна 1 - что-то рисуется
    bool truecolor1 = 0; //равна 1 - кнопка окрашивается в жёлтый
    bool truecolor2 = 0;
    bool truecolor3 = 0;
    bool truecolor4 = 0;
    int menuNum = 0; //думаю, догадаетесь
    int menuNumForBegin = 0;
    int menuNumForBegin2 = 0;
    int menuNumForBegin3 = 0;
    int menuNumForBegin4 = 0;
    int menuNumForOptions = 0;
    int menuNumForExit = 0;
    int numericYellow1 = 0; //остаток от деления на 2 = 1 - значит, кнопка окрашивается в жёлтый
    int numericYellow2 = 0;
    int numericYellow3 = 0;
    int numericYellow1_ = 0;
    int numericYellow2_ = 0;
    int numericYellow3_ = 0;
    int numericYellow4_ = 0;
    int _numericYellow1 = 0;
    int _numericYellow2 = 0;
    int __numericYellow1 = 0;
    string round = "round";
    string rezhim = "rezhim";
    string isWhite = "isWhite";
    //////////////////////////////МЕНЮ///////////////////
    Event event;

        while (isMenu && window.isOpen()) {

            window.pollEvent(event);
            if(event.type == Event::Closed){
                eventForGame = 1;
                value.isGame = 0;
                window.close();
            }
            for(int i = 1; i < menu.size(); i++){
                menu[i].spr.setColor(Color(152, 79, 11));
            }
            menuNum = 0;
            if (IntRect(menu1.getx(), menu1.gety(), menu1.getw(), menu1.geth()).contains(Mouse::getPosition(window))) {

                menu[1].spr.setColor(Color::Yellow);
                menuNum = 1;
            }
            else if (IntRect(menu2.getx(), menu2.gety(), menu2.getw(), menu2.geth()).contains(Mouse::getPosition(window))) {

                menu[2].spr.setColor(Color::Yellow);
                menuNum = 2;
            }
            else if (IntRect(menu3.getx(), menu3.gety(), menu3.getw(), menu3.geth()).contains(Mouse::getPosition(window))) {

                menu[3].spr.setColor(Color::Yellow);
                menuNum = 3;
            }

            if (Mouse::isButtonPressed(Mouse::Left)) {

                if (menuNum == 1) {
                    //1 вопрос
                    myButton begin1("1round.png", 359, 150, 150, 30), begin2("2rounds.png", 549, 150, 150, 30), begin3("3rounds.png", 739, 150, 150, 30), beginall("forbegin.png", 0, 0, 1280, 822);
                    vector<myButton>vibegin1{beginall, begin1, begin2, begin3}; //засунул в вектор кнопки экрана "начать"
                    //2 вопрос
                    myButton begin1_("russian.png", 409, 330, 150, 30), begin2_("poddavki.png", 689, 330, 150, 30), begin3_("english.png", 409, 400, 150, 30), begin4_("international.png", 689, 400, 1280, 822);
                    vector<myButton>vibegin2{begin1_, begin2_, begin3_, begin4_};//засунул в вектор кнопки экрана "начать"
                    //3 вопрос
                    myButton _begin1("Ellipsewhite.png", 409, 550, 150, 125), _begin2("Ellipseblack.png", 690, 550, 150, 125);
                    vector<myButton>vibegin3{_begin1, _begin2};//засунул в вектор кнопки экрана "начать"
                    //4 вопрос
                    myButton __begin1("begingame.png", 499, 734, 150, 125);


                    while(isMenu){

                        // 1 вопрос

                        menuNumForBegin = 0;

                        if (IntRect(359, 150, 150,30).contains(Mouse::getPosition(window))) {

                            menuNumForBegin = 1;

                        }
                        if (IntRect(549, 150,150,30).contains(Mouse::getPosition(window))) {

                            menuNumForBegin = 2;

                        }
                        if (IntRect(739, 150,150,30).contains(Mouse::getPosition(window))) {

                            menuNumForBegin = 3;

                        }
                        if (Mouse::isButtonPressed(Mouse::Left)){
                            if(menuNumForBegin == 1){

                                numericYellow1++;
                                (numericYellow1%2 == 1)?(truecolor1 = 1):(truecolor1 = 0);
                                DrawYellow(vibegin1, menuNumForBegin + 1, numericYellow1, value, round);
                            }
                            else if(menuNumForBegin == 2){
                                numericYellow2++;
                                (numericYellow2%2 == 1)?(truecolor1 = 2):(truecolor1 = 0);
                                DrawYellow(vibegin1, menuNumForBegin + 1, numericYellow2,value,  round);
                            }
                            else if(menuNumForBegin == 3){
                                numericYellow3++;
                                (numericYellow3%2 == 1)?(truecolor1 = 3):(truecolor1 = 0);
                                DrawYellow(vibegin1, menuNumForBegin + 1, numericYellow3, value, round);
                            }
                        }


                        menuNumForBegin2 = 0;

                        if (IntRect(409, 330, 150,30).contains(Mouse::getPosition(window))) {

                            menuNumForBegin2 = 1;
                        }
                        if (IntRect(689, 330,150,30).contains(Mouse::getPosition(window))) {

                            menuNumForBegin2 = 2;
                        }
                        if (IntRect(409, 400,150,30).contains(Mouse::getPosition(window))) {

                            menuNumForBegin2 = 3;
                        }
                        if (IntRect(689, 400,150,30).contains(Mouse::getPosition(window))) {

                            menuNumForBegin2 = 4;
                        }
                        if (Mouse::isButtonPressed(Mouse::Left)){

                            if(menuNumForBegin2 == 1){
                                // делаем в игре русские шашки
                                numericYellow1_++;
                                (numericYellow1_%2 == 1)?(truecolor2 = 1):(truecolor2 = 0);
                                DrawYellow(vibegin2, menuNumForBegin2, numericYellow1_, value, rezhim);


                            }
                            else if(menuNumForBegin2 == 2){
                                //делаем в игре поддавки
                                numericYellow2_++;
                                (numericYellow2_%2 == 1)?(truecolor2 = 2):(truecolor2 = 0);
                                DrawYellow(vibegin2, menuNumForBegin2, numericYellow2_, value, rezhim);
                            }
                            else if(menuNumForBegin2 == 3){
                                //делаем в игре английские шашки
                                numericYellow3_++;
                                (numericYellow3_%2 == 1)?(truecolor2 = 3):(truecolor2 = 0);
                                DrawYellow(vibegin2, menuNumForBegin2, numericYellow3_, value, rezhim);
                            }
                            else if(menuNumForBegin2 == 4){
                                //делаем в игре международные шашки
                                numericYellow4_++;
                                (numericYellow4_%2 == 1)?(truecolor2 = 4):(truecolor2 = 0);
                                DrawYellow(vibegin2, menuNumForBegin2, numericYellow4_, value, rezhim);
                            }

                        }


                        //3 вопрос

                        menuNumForBegin3 = 0;


                        if (IntRect(409, 550, 150, 125).contains(Mouse::getPosition(window))) {
                            menuNumForBegin3 = 1;
                        }
                        if (IntRect(690, 550,150, 125).contains(Mouse::getPosition(window))) {
                            menuNumForBegin3 = 2;
                        }

                        if (Mouse::isButtonPressed(Mouse::Left)){

                            if(menuNumForBegin3 == 1){
                                // делаем в игре белые шашки
                                _numericYellow1++;
                                (_numericYellow1%2 == 1)?(truecolor3 = 1):(truecolor3 = 0);
                                DrawYellow(vibegin3, menuNumForBegin3, _numericYellow1, value, isWhite);

                            }
                            else if(menuNumForBegin3 == 2){
                                //делаем в игре чёрные шашки
                                _numericYellow2++;
                                (_numericYellow2%2 == 1)?(truecolor3 = 2):(truecolor3 = 0);
                                DrawYellow(vibegin3, menuNumForBegin3, _numericYellow2,value,  isWhite);
                            }


                        }

                        //4 вопрос
                        menuNumForBegin4 = 0;

                        if (IntRect(499, 734, 150, 30).contains(Mouse::getPosition(window))) {
                            menuNumForBegin4 = 1;
                        }

                        if (Mouse::isButtonPressed(Mouse::Left)){
                            //cout << numericYellow1 << " " << numericYellow2 << " " << numericYellow3 << " " << numericYellow1_ << " " << numericYellow2_ << " " << numericYellow3_ << " " << numericYellow4_ << " " << _numericYellow1 << " " << _numericYellow2 << '\n';
                            if(menuNumForBegin4 == 1 &&(truecolor1 == 1 || truecolor1 == 2 || truecolor1 == 3)&&(truecolor2 == 1 || truecolor2 == 2 || truecolor2 == 3 || truecolor2 == 4) && (truecolor3 == 1 || truecolor3 == 2)){

                                isMenu = false;

                            }

                        }

                        if(truedraw == true){
                            Draw(menu, window);
                            Draw(vibegin1, window);
                            Draw(vibegin2, window);
                            Draw(vibegin3, window);
                            window.draw(__begin1.spr);
                            window.display();
                        }
                    }

                }

                if (menuNum == 2) {

                    String playerInput;
                    Text playerText;
                    Image imo, imo2;
                    imo.loadFromFile("deskforoptions.png"); //фон для настроек
                    imo2.loadFromFile("save.png"); //кнопка  сохранить
                    Texture texf, texf2;
                    texf.loadFromImage(imo);
                    texf2.loadFromImage(imo2);
                    Sprite sfr(texf), sfr2(texf2);
                    sfr.setPosition(0,0);
                    sfr2.setPosition(486,690);
                    isOpt =true; // делаем так, чтобы можно было перезапускать окно настроек
                    while(isOpt){
                        menuNumForOptions = 0; //эту штуку надо будет доработать. Это текст, который будет вводить пользователь в настройках
                        /*if (event.type == sf::Event::TextEntered)
                        {
                            if(event.text.unicode < 128)
                            {
                                playerInput +=event.text.unicode;
                                playerText.setString(playerInput);
                            }
                        }*/
                        window.draw(playerText);
                        window.display();

                        if (IntRect(486,690, 250,50).contains(Mouse::getPosition(window))) {

                            menuNumForOptions = 1;
                        }
                        if (Mouse::isButtonPressed(Mouse::Left)){
                            if(menuNumForOptions == 1){
                                isOpt = false; // если нажали сохранить, выходим в главное меню (пока сохранение не реализовал, для этого надо поебаться с классом Text, если найдёшь инфу и сможешь реализовать запись текста пользователем - моё почтение)
                            }
                        }
                        window.draw(sfr);
                        window.draw(sfr2);

                        window.display();
                    }


                }
                if (menuNum == 3) {
                    myButton exit3("deskforexit.png", 0, 0, 1280, 822), exit1("Yes.png", 391, 421, 200, 50), exit2("No.png" , 685, 421, 200, 50);
                    vector<myButton>exit{exit3, exit1, exit2};

                    isExit = true; // делаем так, чтобы могли перезапускать окно выхода
                    while(isExit){
                        exit1.spr.setColor(Color(152, 79, 11));
                        exit2.spr.setColor(Color(152, 79, 11));
                        menuNumForExit = 0;
                        if (IntRect(391, 421, 200, 50).contains(Mouse::getPosition(window))) {
                            exit1.spr.setColor(Color::Yellow);
                            menuNumForExit = 1;
                        }
                        if (IntRect(685, 421, 200, 50).contains(Mouse::getPosition(window))) {
                            exit2.spr.setColor(Color::Yellow);
                            menuNumForExit = 2;
                        }

                        if(Mouse::isButtonPressed(Mouse::Left)){
                            if (menuNumForExit == 1) {

                                window.close(); //если пользователь нажал да, то закрываем окно
                            }
                            else if(menuNumForExit == 2){

                                isExit = false;  //если нет - закрываем текстуру выхода
                            }
                        }
                        Draw(menu, window);
                        Draw(exit, window);
                        window.display();

                    }
                }
            }

            Draw(menu, window);
            window.display();

        }
        return value;


}
