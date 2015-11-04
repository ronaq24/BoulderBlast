#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "StudentWorld.h"
// Done
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class Actor : public GraphObject
{
public:
    Actor(int imageID, int startX, int startY, Direction dir, StudentWorld* sw);
    int getHealth() const;
    int getAmmo() const;
    void setHealth(int health);
    void setAmmo(int ammo);
    virtual void doSomething() = 0;
    StudentWorld* getWorld();
    bool isDead() const;
    void setDead();
    int returnID();
    virtual void damage();
    
private:
    int hitPoint;
    int m_ammo;
    bool m_dead;
    StudentWorld* m_world;
    int objectID;
    
};

class Item : public Actor  // all the inanimate objects
{
public:
    Item(int imageID, int startX, int startY, Direction dir,StudentWorld* sw);
    virtual void doSomething() = 0;
};

class Goodie: public Actor
{
public:
    Goodie(int imageID, int startX, int startY, Direction dir,StudentWorld* sw);
    virtual void doSomething();
    virtual void reward() = 0;
};

class Player : public Actor
{
public:
    Player(int imageID, int startX, int startY, Direction dir,StudentWorld* sw);
    virtual void doSomething();
    virtual void damage();
private:
    StudentWorld* world;

};

class Robot : public Actor
{
public:
    Robot(int imageID, int startX, int startY, Direction dir,StudentWorld* sw);
    virtual void doSomething() = 0;
    void hasShot(bool x);
    bool getShot();
    void shoot();
    
private:
    bool shot;

};

class Snarlbot : public Robot
{
public:
    Snarlbot(int imageID, int startX, int startY, Direction dir,StudentWorld* sw);
    virtual void doSomething();
    virtual void shoot() = 0;
    virtual void move() = 0;
    virtual void damage();
};

class HorizontalSnarlbot : public Snarlbot
{
public:
    HorizontalSnarlbot(int imageID, int startX, int startY, Direction dir,StudentWorld* sw);
    virtual void shoot();
    virtual void move();
private:
    StudentWorld* world;
};

class VerticalSnarlbot : public Snarlbot
{
public:
    VerticalSnarlbot(int imageID, int startX, int startY, Direction dir,StudentWorld* sw);
    virtual void shoot();
    virtual void move();
private:
    StudentWorld* world;
    
};
class Kleptobot : public Robot
{
public:
    Kleptobot(int imageID, int startX, int startY, Direction dir,StudentWorld* sw);
    virtual void doSomething();
    virtual void pickUpGoodie();
    virtual void moveKleptobot();
    virtual void damage();
    virtual void reward() = 0;
    virtual void shootBullet() = 0;
    int getDistanceBeforeTurning();
    void setDistanceBeforeTurning(int d);
    void setDistanceCounter(int s);
    void hasPickedUpGoodie(bool x);
    bool didRobotPickUpGoodie();
    void rememberTypeofGoodie(int imageID);
    int getTypeofGoodie();
    StudentWorld* getStWorld();
    void hasRobotMoved(bool m);
    bool didRobotMove();
    bool didRobotShoot();
    void didShoot(bool p);
    
private:
    bool pickedGoodie;
    int goodieID;
    StudentWorld* world;
    int distanceCounter;
    bool m_moved;
    int distanceBeforeTurning;
    bool m_shot;
    
};

class RegularKleptobot : public Kleptobot
{
public:
    RegularKleptobot(int imageID, int startX, int startY, Direction dir,StudentWorld* sw);
    virtual void shootBullet(); // this function will simply return b/c the reg kleptobot does not shoot
    virtual void reward();
};

class AngryKleptobot : public Kleptobot
{
public:
    AngryKleptobot(int imageID, int startX, int startY, Direction dir,StudentWorld* sw);
    virtual void shootBullet();  // will have code b/c angry kleptobot can shoot
    virtual void reward();
};


class Wall : public Item
{
public:
    Wall(int imageID, int startX, int startY, Direction dir,StudentWorld* sw);
    virtual void doSomething();

};

class Hole : public Item
{
public:
    Hole(int imageID, int startX, int startY, Direction dir,StudentWorld* sw);
    virtual void doSomething();
    
};

class Boulder : public Item
{
public:
    Boulder(int imageID, int startX, int startY, Direction dir,StudentWorld* sw);
    virtual void doSomething();
    virtual void damage();
    
};

class Jewel:public Goodie
{
public:
    Jewel(int imageID, int startX, int startY, Direction dir,StudentWorld* sw);
    virtual void reward();
};

class ExtraLifeGoodie: public Goodie
{
public:
    ExtraLifeGoodie(int imageID, int startX, int startY, Direction dir,StudentWorld* sw);
    virtual void reward();
};

class RestoreHealthGoodie: public Goodie
{
public:
    RestoreHealthGoodie(int imageID, int startX, int startY, Direction dir,StudentWorld* sw);
    virtual void reward();
};

class AmmoGoodie : public Goodie
{
public:
    AmmoGoodie(int imageID, int startX, int startY, Direction dir,StudentWorld* sw);
    virtual void reward();
};

class Exit : public Item
{
public:
    Exit(int imageID, int startX, int startY, Direction dir,StudentWorld* sw);
    virtual void doSomething();
};

class Bullet : public Item
{
public:
    Bullet(int imageID, int startX, int startY, Direction dir,StudentWorld* sw);
    virtual void doSomething();
    void attack();
    void moveBullet();
    void didAttack(bool a);
    bool bulletHasAttacked();
private:
    bool m_attack;

};
class Factory : public Item
{
public:
    Factory(int imageID, int startX, int startY, Direction dir,StudentWorld* sw, string type);
    virtual void doSomething();
    int count(int x, int x2, int y, int y2);
private:
    string robotType;
    StudentWorld* n_world;
    
};

#endif // ACTOR_H_
