//
// Created by dmitry on 12.11.22.
//

#pragma once
#include "Header.h"
#include "functions.h"
//bool eventForGame;
class Game {
protected:
    struct ReturnValue{
        int index;
        Vector2f FirstPlace;
        Vector2f SecondPlace;
        std::string Type;
        bool IsWhite;
        int indexPossibleEat;
        bool operator ==(ReturnValue _RV) {
            if (this->FirstPlace == _RV.FirstPlace && this->SecondPlace == _RV.SecondPlace && this->Type == _RV.Type &&this->index==index)return true;
            return false;
        }
    };
    RenderWindow window;
    Matrix Field;
    std::vector<Checker> WhiteCheckers;
    std::vector<Checker> BlackCheckers;
    unsigned int count;
    Event GameEvent;
    bool waitReaction;
    bool MustEat;
    std::vector<Button>PossibleMove;
    std::vector<ReturnValue>_PM;
public:
    Game() {
        count = 0;
        waitReaction = false;
        MustEat = false;
        Checker WhiteCheckers(Color::White);
        Checker BlackCheckers(Color::Black);
        int x_W = 500;
        int y_W = 100;
        int x_B = 400;
        int y_B = 600;
        for (int i = 0; i < 12; i++) {
            WhiteCheckers.setPosition(x_W, y_W);
            BlackCheckers.setPosition(x_B, y_B);
            this->WhiteCheckers.push_back(WhiteCheckers);
            this->BlackCheckers.push_back(BlackCheckers);
            if (i % 4 == 3) {
                y_W += 100;
                y_B += 100;
                if (i % 8 == 3) {
                    x_W = 400;
                    x_B = 500;
                }
                else {
                    x_W = 500;
                    x_B = 400;
                }
            }
            else {
                x_B += 200;
                x_W += 200;
            }
        }
    }
    void MoveChecker(int index, Vector2f place, bool IsWhite) {
        if (IsWhite) {
            WhiteCheckers[index].setPosition(place.x, place.y);
        }
        else {
            BlackCheckers[index].setPosition(place.x, place.y);
        }
    }
    void EatChecker(int index, bool IsWhite) {
        if (IsWhite) {
            BlackCheckers.erase(std::next(BlackCheckers.begin(), index));
        }
        else {
            WhiteCheckers.erase(std::next(WhiteCheckers.begin(), index));
        }
    }
    void Move(int index) {
        if (_PM[index].Type == "eat") {
            EatChecker(_PM[index].indexPossibleEat, _PM[index].IsWhite);
        }
        MoveChecker(_PM[index].index, _PM[index].SecondPlace, _PM[index].IsWhite);
        _PM.clear();
        PossibleMove.clear();
        waitReaction = false;
        MustEat = false;
        count++;
        MustEatChecker();
        King();
    }
    bool PlaceInsideTheField(Vector2f place) {
        if (place.x >= Field[0][0].getPosition().x && place.y >= Field[0][0].getPosition().y && place.x <= Field[0][7].getPosition().x && place.y <= Field[7][0].getPosition().y) {
            return true;
        }
        return false;
    }
    bool MoveIsPossible(Vector2f place) {
        if (PlaceInsideTheField(place)) {
            for (int i = 0; i<BlackCheckers.size(); i++) {
                if (BlackCheckers[i].getPosition() == place) {
                    return false;
                }
            }
            for(int i=0;i<WhiteCheckers.size();i++){
                if (WhiteCheckers[i].getPosition() == place) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }
    bool CanEat(Checker checker, int index, Vector2f(Game::*TransitionFunction)(Vector2f)) {							//åñëè íåëüçÿ âåðíåò -1    ///???
        Game A;
        bool returnValue=false;
        Vector2f NextPosition = (A.*TransitionFunction)(checker.getPosition());
        Vector2f EndPosition = (A.*TransitionFunction)(NextPosition);
        Checker copy = checker;
        if (checker.getColorIsWhite()) {
            for (int i = 0; i < BlackCheckers.size(); i++) {
                if (BlackCheckers[i].getPosition() == NextPosition && MoveIsPossible(EndPosition)) {
                    copy.setPosition(EndPosition.x,EndPosition.y);
                    returnValue = true;
                    MustEat = true;
                    ReturnValue EatCheckers;
                    EatCheckers.FirstPlace = checker.getPosition();
                    EatCheckers.index = index;
                    EatCheckers.indexPossibleEat = i;
                    EatCheckers.IsWhite = checker.getColorIsWhite();
                    EatCheckers.SecondPlace = EndPosition;
                    EatCheckers.Type = "eat";
                    _PM.push_back(EatCheckers);
                }
            }
        }
        else {
            for (int i = 0; i < WhiteCheckers.size(); i++) {
                if (WhiteCheckers[i].getPosition() == NextPosition && MoveIsPossible(EndPosition)) {
                    copy.setPosition(EndPosition.x, EndPosition.y);
                    MustEat = true;
                    returnValue = true;
                    ReturnValue EatCheckers;
                    EatCheckers.FirstPlace = checker.getPosition();
                    EatCheckers.index = index;
                    EatCheckers.indexPossibleEat = i;
                    EatCheckers.IsWhite = checker.getColorIsWhite();
                    EatCheckers.SecondPlace = EndPosition;
                    EatCheckers.Type = "eat";
                    _PM.push_back(EatCheckers);
                }
            }
        }
        //if(!(CanEat(copy,index,&Game::Down_Left)||CanEat(copy,index,&Game::Down_Right),CanEat(copy,index,&Game::Up_Left),CanEat(copy,index,&Game::Up_Right)))
        return returnValue;
    }
    void MustEatChecker() {
        if (count % 2 == 0) {
            for (int i = 0; i < WhiteCheckers.size(); i++) {
                CanEat(WhiteCheckers[i], i, &Game::Up_Left);
                CanEat(WhiteCheckers[i], i, &Game::Up_Right);
                CanEat(WhiteCheckers[i], i, &Game::Down_Left);
                CanEat(WhiteCheckers[i], i, &Game::Down_Right);
            }
        }
        else {
            for (int i = 0; i < BlackCheckers.size(); i++) {
                CanEat(BlackCheckers[i], i, &Game::Up_Left);
                CanEat(BlackCheckers[i], i, &Game::Up_Right);
                CanEat(BlackCheckers[i], i, &Game::Down_Left);
                CanEat(BlackCheckers[i], i, &Game::Down_Right);
            }
        }
        if (!_PM.empty()) {
            FormPossibleMove();
        }
    }
    Vector2f Up_Left(Vector2f place) {
        return Vector2f(place.x - 100, place.y + 100);
    }
    Vector2f Up_Right(Vector2f place) {
        return Vector2f(place.x + 100, place.y + 100);
    }
    Vector2f Down_Left(Vector2f place) {
        return Vector2f(place.x - 100, place.y - 100);
    }
    Vector2f Down_Right(Vector2f place) {
        return Vector2f(place.x + 100, place.y - 100);
    }
    void King() {
        for (int i = 0; i < WhiteCheckers.size(); i++) {
            if (WhiteCheckers[i].getPosition().y == 800) {
                WhiteCheckers[i].makeKing();
                WhiteCheckers[i].setTexture("WhiteKing.jpg");
            }
        }
        for (int i = 0; i < BlackCheckers.size(); i++) {
            if (BlackCheckers[i].getPosition().y == 100) {
                BlackCheckers[i].makeKing();
                BlackCheckers[i].setTexture("BlackKing.jpg");
            }
        }
    }
    std::vector<ReturnValue> WhereTheMoveIsPossible(Checker checker,int index) {				//Åñëè õîä íå âîçìîæåí âåðíåò ïóñòîé âåêòîð, åñëè âîçìîæåí, òî âåêòîð âîçìîæíûõ ìåñò ïåðåõîäà
        std::vector<ReturnValue> PossibleMove;
        Vector2f CheckerPosition = checker.getPosition();
        if (!checker.getTypeIsKing()) {
            Vector2f MoveUL = Up_Left(CheckerPosition);
            Vector2f MoveUR = Up_Right(CheckerPosition);
            Vector2f MoveDL = Down_Left(CheckerPosition);
            Vector2f MoveDR = Down_Right(CheckerPosition);
            if (checker.getColorIsWhite()) {
                if (MoveIsPossible(Up_Left(CheckerPosition))) {
                    ReturnValue _MoveUL;
                    _MoveUL.FirstPlace = CheckerPosition;
                    _MoveUL.SecondPlace = MoveUL;
                    _MoveUL.Type = "simple";
                    _MoveUL.index = index;
                    _MoveUL.IsWhite = (count % 2 == 0);
                    PossibleMove.push_back(_MoveUL);
                }
                if (MoveIsPossible(MoveUR)) {
                    ReturnValue _MoveUR;
                    _MoveUR.FirstPlace = CheckerPosition;
                    _MoveUR.SecondPlace = MoveUR;
                    _MoveUR.Type = "simple";
                    _MoveUR.index = index;
                    _MoveUR.IsWhite = (count % 2 == 0);
                    PossibleMove.push_back(_MoveUR);
                }
            }
            else {
                if (MoveIsPossible(MoveDL)) {
                    ReturnValue _MoveUL;
                    _MoveUL.FirstPlace = CheckerPosition;
                    _MoveUL.SecondPlace = MoveDL;
                    _MoveUL.Type = "simple";
                    _MoveUL.index = index;
                    _MoveUL.IsWhite = (count % 2 == 0);
                    PossibleMove.push_back(_MoveUL);
                }
                if (MoveIsPossible(MoveDR)) {
                    ReturnValue _MoveUR;
                    _MoveUR.FirstPlace = CheckerPosition;
                    _MoveUR.SecondPlace = MoveDR;
                    _MoveUR.Type = "simple";
                    _MoveUR.index = index;
                    _MoveUR.IsWhite = (count % 2 == 0);
                    PossibleMove.push_back(_MoveUR);
                }
            }
        }
        else {
            Vector2f MoveUL, MoveUR, MoveDL, MoveDR;
            MoveUL = CheckerPosition; MoveUR = CheckerPosition; MoveDL = CheckerPosition; MoveDR = CheckerPosition;
            while (true) {
                MoveUL = Up_Left(MoveUL);
                if (MoveIsPossible(MoveUL)) {
                    ReturnValue _Move;
                    _Move.FirstPlace = CheckerPosition;
                    _Move.SecondPlace = MoveUL;
                    _Move.Type = "simple";
                    _Move.index = index;
                    _Move.IsWhite = (count % 2 == 0);
                    PossibleMove.push_back(_Move);
                }
                else {
                    break;
                }
            }while (true) {
                MoveUR = Up_Right(MoveUR);
                if (MoveIsPossible(MoveUR)) {
                    ReturnValue _Move;
                    _Move.FirstPlace = CheckerPosition;
                    _Move.SecondPlace = MoveUR;
                    _Move.Type = "simple";
                    _Move.index = index;
                    _Move.IsWhite = (count % 2 == 0);
                    PossibleMove.push_back(_Move);
                }
                else {
                    break;
                }
            }while (true) {
                MoveDL = Down_Left(MoveDL);
                if (MoveIsPossible(MoveDL)) {
                    ReturnValue _Move;
                    _Move.FirstPlace = CheckerPosition;
                    _Move.SecondPlace = MoveDL;
                    _Move.Type = "simple";
                    _Move.index = index;
                    _Move.IsWhite = (count % 2 == 0);
                    PossibleMove.push_back(_Move);
                }
                else {
                    break;
                }
            }while (true) {
                MoveDR = Down_Right(MoveDR);
                if (MoveIsPossible(MoveDR)) {
                    ReturnValue _Move;
                    _Move.FirstPlace = CheckerPosition;
                    _Move.SecondPlace = MoveDR;
                    _Move.Type = "simple";
                    _Move.index = index;
                    _Move.IsWhite = (count % 2 == 0);
                    PossibleMove.push_back(_Move);
                }
                else {
                    break;
                }
            }
        }
        return PossibleMove;
    }
    void DrawPossibleMove() {
        for (int i = 0; i < PossibleMove.size(); i++) {
            window.draw(PossibleMove[i].getSprite());
        }
    }
    void FormPossibleMove() {
        for (int i = 0; i < _PM.size(); i++) {
            Button PossibleMoveCage("PossibleMoveCage.png", _PM[i].SecondPlace);
            PossibleMove.push_back(PossibleMoveCage);
        }
    }
    void Draw() {
        Images Background("GameTable.png");
        window.draw(Background.getSprite());
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                window.draw(Field[j][i].getSprite());
            }
        }
        for (int i = 0; i < WhiteCheckers.size(); i++) {
            window.draw(WhiteCheckers[i].getSprite());
        }
        for(int i=0;i<BlackCheckers.size();i++){
            window.draw(BlackCheckers[i].getSprite());
        }
    }
    void start(MenuValue menuResult){

        window.create(VideoMode(1600, 1000), "Checkers", Style::Default);
        Field.setMatrix();
        Vector2i MousePos;
        Vector2i WindowPosition;
        unsigned int EpisodeNumber = 0;
        while (window.isOpen()) {
            cout << "first\n";
            if(menuResult.isGame == 0){
                window.close();
            }
            WindowPosition = window.getPosition();
            window.clear(Color::White);
            window.pollEvent(GameEvent);
            if (GameEvent.type == Event::Closed) {
                window.close();
            }
            Draw();
            if (MustEat) {
                DrawPossibleMove();
                if (Mouse::isButtonPressed(Mouse::Right)) {
                    MousePos = Mouse::getPosition();
                    for (int i = 0; i < PossibleMove.size(); i++) {
                        if (PossibleMove[i].SuspicionOfTargeting(MousePos.x - WindowPosition.x, MousePos.y - WindowPosition.y))
                        {
                            Move(i);
                            break;
                        }
                    }
                }
            } else {
                if (waitReaction) {
                    DrawPossibleMove();
                    if (Mouse::isButtonPressed(Mouse::Right)) {
                        MousePos = Mouse::getPosition();
                        bool find = false;
                        for (int i = 0; i < PossibleMove.size(); i++) {
                            if (PossibleMove[i].SuspicionOfTargeting(MousePos.x - WindowPosition.x, MousePos.y - WindowPosition.y))
                            {
                                Move(i);
                                find = true;
                                break;
                            }
                        }
                        if (!find) {
                            _PM.clear();
                            PossibleMove.clear();
                            waitReaction = false;
                        }
                    }
                }
                else {
                    if (count % 2 == 0) {
                        if (Mouse::isButtonPressed(Mouse::Right)) {
                            MousePos = Mouse::getPosition();
                            bool check;
                            for (int i = 0; i < WhiteCheckers.size(); i++) {
                                check = WhiteCheckers[i].SuspicionOfClicking(MousePos.x - WindowPosition.x, MousePos.y - WindowPosition.y);
                                if (check) {
                                    _PM = WhereTheMoveIsPossible(WhiteCheckers[i], i);
                                    if (!_PM.empty()) {
                                        FormPossibleMove();
                                        WhiteCheckers[i].MakeNotActive();
                                        waitReaction = true;
                                    }
                                }
                            }
                        }
                    }
                    if (count % 2 == 1) {
                        if (Mouse::isButtonPressed(Mouse::Right)) {
                            MousePos = Mouse::getPosition();
                            for (int i = 0; i < BlackCheckers.size(); i++) {
                                if (BlackCheckers[i].SuspicionOfClicking(MousePos.x - WindowPosition.x, MousePos.y - WindowPosition.y))
                                {
                                    _PM = WhereTheMoveIsPossible(BlackCheckers[i], i);
                                    if (!_PM.empty()) {
                                        FormPossibleMove();
                                        waitReaction = true;
                                        BlackCheckers[i].MakeNotActive();
                                    }
                                }
                            }
                        }
                    }
                }
            }

            window.display();
        }
    }

};
