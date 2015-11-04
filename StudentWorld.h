#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include <string>
#include <list>
using namespace std;

class Actor;
//Done
// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetDir);
    ~StudentWorld();
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    Actor* findObjectAt(int x, int y, int object);
    Actor* findAnythingAt(int x, int y);
    void removeDeadObjects();
    bool playerCollectedAllJewels();
    void exposeTheExit();
    void reduceLevelBonusByOne();
    unsigned int getBonusPoints();
    void pushToList(Actor* p);
    int robotTick();
    void increaseTicks();
    int getTick();
    Actor* getAccessToSpecific(int imageID);
    bool checkBtwnPlayerHorizontal(int a, int b , int c);
    bool checkBtwnPlayerVertical(int a, int b , int c);
    bool NoObstruction(int dx,int dy);
    bool NoBlockForPlayer(int x, int y);
    void setDisplayText();
    string FormatStringNicely(int score,int level,int lives,int health, int ammo, int bonus);
    bool PlayerCompletedLevel();
    void setLevelComplete(bool d);
    string FormatLevel();

private:
    list <Actor*> objectList;  // list of pointers to actors
    unsigned int bonusPoints;
    int m_ticks;
    Actor* m_player;
    bool LevelComplete;
};

#endif // STUDENTWORLD_H_
