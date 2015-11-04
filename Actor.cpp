#include "Actor.h"
#include "StudentWorld.h"
#include <iostream>
#include <cstdlib>
using namespace std;
//Done
// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp
Actor::Actor(int imageID, int startX, int startY, Direction dir, StudentWorld* sw)
:GraphObject(imageID,startX,startY,dir)
{
    m_world = sw;
    m_dead = false;
    objectID = imageID;
}
int Actor::getHealth() const
{
    return hitPoint;
}
int Actor::getAmmo()const
{
    return  m_ammo;
}
void Actor:: setAmmo(int ammo)
{
    m_ammo = ammo;
}
void Actor::setHealth(int health)
{
    hitPoint = health;
}
StudentWorld* Actor::getWorld()
{
    return m_world;
}
bool Actor::isDead() const
{
    return m_dead;
}
void Actor::setDead()
{
    m_dead=true;
}
int Actor::returnID()
{
    return objectID;
}
void Actor::damage()
{
    return;
}
Item::Item(int imageID, int startX, int startY, Direction dir,StudentWorld* sw)
:Actor(imageID,startX,startY,dir, sw)
{

}
Goodie::Goodie(int imageID, int startX, int startY, Direction dir,StudentWorld* sw)
:Actor(imageID,startX,startY,none,sw)
{
    
}
void Goodie::doSomething()
{
    if(isDead()==true)
        return;
    if(getWorld()->findObjectAt(getX(), getY(), IID_PLAYER) != nullptr)
    {
        reward();
        setDead();
        getWorld()->playSound(SOUND_GOT_GOODIE);
    }
}
Player::Player(int imageID, int startX, int startY, Direction dir,StudentWorld* sw)
:Actor(imageID,startX,startY,dir,sw)
{
    dir = right;
    setVisible(true);
    setHealth(20);
    setAmmo(20);
    world = sw;
}
void Player::damage()
{
    
    setHealth(getHealth() - 2);  // decrement the health by 2
    getWorld()->playSound(SOUND_PLAYER_IMPACT);
    
    if(getHealth() < 1)
    {
        setDead();
        getWorld()->playSound(SOUND_PLAYER_DIE);
        getWorld()->decLives();
        return;
    }
}

void Player::doSomething()
{
    int ch;
    if(getWorld()->getKey(ch))
    {
        switch(ch)   // FILL IN THIS STUFF!!
        {
            case KEY_PRESS_LEFT:
            {
                setDirection(left);
                if((getWorld()->findObjectAt(getX()-1, getY(), IID_BOULDER) != nullptr) && (getWorld()->findAnythingAt(getX()-2, getY())== nullptr || getWorld()->findObjectAt(getX()-2, getY(), IID_HOLE) != nullptr))
                {
                    getWorld()->findObjectAt(getX()-1, getY(), IID_BOULDER)->moveTo(getX()-2, getY());
                    moveTo(getX()-1, getY());
                }
                else if (getWorld()->NoBlockForPlayer(getX()-1, getY())==true)
                {
                    moveTo(getX()-1, getY());
                }
                break;
            }
            case KEY_PRESS_RIGHT:
            {
                setDirection(right);
                if((getWorld()->findObjectAt(getX()+1, getY(), IID_BOULDER) != nullptr) && (getWorld()->findAnythingAt(getX()+2, getY())== nullptr || getWorld()->findObjectAt(getX()+2, getY(), IID_HOLE) != nullptr))
                {
                    getWorld()->findObjectAt(getX()+1, getY(), IID_BOULDER)->moveTo(getX()+2, getY());
                    moveTo(getX()+1, getY());
                }
                else if(getWorld()->NoBlockForPlayer(getX()+1, getY())==true)
                {
                    moveTo(getX()+1, getY());
                }
                break;
            }
            case KEY_PRESS_UP:
            {
                setDirection(up);
                if((getWorld()->findObjectAt(getX(), getY()+1, IID_BOULDER) != nullptr) && (getWorld()->findAnythingAt(getX(), getY()+2)== nullptr || getWorld()->findObjectAt(getX(), getY()+2, IID_HOLE) != nullptr))
                {
                    getWorld()->findObjectAt(getX(), getY()+1, IID_BOULDER)->moveTo(getX(), getY()+2);
                    moveTo(getX(), getY()+1);
                }
                
                else if(getWorld()->NoBlockForPlayer(getX(), getY()+1)==true)
                {
                    moveTo(getX(), getY()+1);
                }
                break;
            }
            case KEY_PRESS_DOWN:
            {
                setDirection(down);
                if((getWorld()->findObjectAt(getX(), getY()-1, IID_BOULDER) != nullptr) && (getWorld()->findAnythingAt(getX(), getY()-2)== nullptr || getWorld()->findObjectAt(getX(), getY()-2, IID_HOLE) != nullptr))
                {
                    getWorld()->findObjectAt(getX(), getY()-1, IID_BOULDER)->moveTo(getX(), getY()-2);
                    moveTo(getX(), getY()-1);
                }
                else if(getWorld()->NoBlockForPlayer(getX(), getY()-1)==true)
                {
                    moveTo(getX(), getY()-1);
                }
                break;
            }
            case KEY_PRESS_ESCAPE:
            {
                setDead();
                getWorld()->decLives();
                break;
            }
            case KEY_PRESS_SPACE:
            {
                if(getAmmo() > 0)
                {
                    setAmmo(getAmmo() -1);
                    if(getDirection() == left)
                    {
                        Actor* p = new Bullet(IID_BULLET,getX()-1,getY(),left,world);
                        getWorld()->playSound(SOUND_PLAYER_FIRE);
                        getWorld()->pushToList(p);
                    }
                    if(getDirection() == right)
                    {
                        Actor* p = new Bullet(IID_BULLET,getX()+1,getY(),right,world);
                        getWorld()->playSound(SOUND_PLAYER_FIRE);
                        getWorld()->pushToList(p);
                    }
                    if(getDirection() == up)
                    {
                        Actor* p = new Bullet(IID_BULLET,getX(),getY()+1,up,world);
                        getWorld()->playSound(SOUND_PLAYER_FIRE);
                        getWorld()->pushToList(p);
                    }
                    if(getDirection() == down)
                    {
                        Actor* p = new Bullet(IID_BULLET,getX(),getY()-1,down,world);
                        getWorld()->playSound(SOUND_PLAYER_FIRE);
                        getWorld()->pushToList(p);
                    }

                }
                
                break;
            }
        }
    }
}
Robot::Robot(int imageID, int startX, int startY, Direction dir,StudentWorld* sw)
:Actor(imageID,startX,startY,dir,sw)
{
    shot = false;
}
void Robot::hasShot(bool x)
{
    shot = x;
}
bool Robot::getShot()
{
    return shot;
}
Snarlbot::Snarlbot(int imageID, int startX, int startY, Direction dir,StudentWorld* sw)
:Robot(imageID,startX,startY,dir,sw)
{

}
void Snarlbot::damage()
{
    setHealth(getHealth() - 2);  // decrement the health by 2
    getWorld()->playSound(SOUND_ROBOT_IMPACT);
    
    if(getHealth() < 1)
    {
        setDead();
        getWorld()->playSound(SOUND_ROBOT_DIE);
        getWorld()->increaseScore(100);
        return;
    }
}
void Snarlbot::doSomething()
{
    if(isDead()==true)
        return;
    if(getWorld()->getTick() % getWorld()->robotTick() == 0)
    {
        shoot();
        if(getShot()==false)
            move();
    }
    hasShot(false);
    return;
}

HorizontalSnarlbot::HorizontalSnarlbot(int imageID, int startX, int startY, Direction dir,StudentWorld* sw)
:Snarlbot(imageID,startX,startY,dir,sw)
{
    setHealth(10);
    setVisible(true);
    world = sw;
}
void HorizontalSnarlbot::shoot()
{
    if(getWorld()->getAccessToSpecific(IID_PLAYER)->getY() == getY()) // in the same row
    {
        if(getDirection()== right && getWorld()->getAccessToSpecific(IID_PLAYER)->getX() > getX())   // faces right
           {
               if(getWorld()->checkBtwnPlayerHorizontal(getY(), getX()+1,getWorld()->getAccessToSpecific(IID_PLAYER)->getX()-1)==true)
               {
                   Actor* p = new Bullet(IID_BULLET,getX()+1,getY(),right,world);
                   getWorld()->playSound(SOUND_ENEMY_FIRE);
                   getWorld()->pushToList(p);
                   hasShot(true);
                   return;
               }
           }
    }
    if(getWorld()->getAccessToSpecific(IID_PLAYER)->getY() == getY()) // in the same row
    {
        if(getDirection()== left && getWorld()->getAccessToSpecific(IID_PLAYER)->getX() < getX())   // faces left
        {
            if(getWorld()->checkBtwnPlayerHorizontal(getY(), getWorld()->getAccessToSpecific(IID_PLAYER)->getX()+1,getX()-1)==true)
            {
                Actor* p = new Bullet(IID_BULLET,getX()-1,getY(),left,world);
                getWorld()->playSound(SOUND_ENEMY_FIRE);
                getWorld()->pushToList(p);
                hasShot(true);
                return;
            }
        }
    }
}
void HorizontalSnarlbot::move()
{
    if(getDirection()==right)
    {
        if(getWorld()->NoObstruction(getX()+1, getY())==true)
            moveTo(getX()+1, getY());
        else
            setDirection(left);
    }
    else if(getDirection()==left)
    {
        if(getWorld()->NoObstruction(getX()-1, getY())==true)
            moveTo(getX()-1, getY());
        else
            setDirection(right);
    }
}
VerticalSnarlbot::VerticalSnarlbot(int imageID, int startX, int startY, Direction dir,StudentWorld* sw)
:Snarlbot(imageID,startX,startY,dir,sw)
{
    setHealth(10);
    setVisible(true);
    world = sw;
}
void VerticalSnarlbot::shoot()
{
    if(getWorld()->getAccessToSpecific(IID_PLAYER)->getX() == getX()) // in the same row
    {
        if(getDirection()== up && getWorld()->getAccessToSpecific(IID_PLAYER)->getY() > getY())
        {
            if(getWorld()->checkBtwnPlayerVertical(getX(), getY()+1,getWorld()->getAccessToSpecific(IID_PLAYER)->getY()-1)==true)
            {
                Actor* p = new Bullet(IID_BULLET,getX(),getY()+1,up,world);
                getWorld()->playSound(SOUND_ENEMY_FIRE);
                getWorld()->pushToList(p);
                hasShot(true);
                return;
            }
        }
    }
    if(getWorld()->getAccessToSpecific(IID_PLAYER)->getX() == getX()) // in the same row
    {
        if(getDirection()== down && getWorld()->getAccessToSpecific(IID_PLAYER)->getY() < getY())
        {
            if(getWorld()->checkBtwnPlayerVertical(getX(), getWorld()->getAccessToSpecific(IID_PLAYER)->getY()+1,getY()-1)==true)
            {
                Actor* p = new Bullet(IID_BULLET,getX(),getY()-1,down,world);
                getWorld()->playSound(SOUND_ENEMY_FIRE);
                getWorld()->pushToList(p);
                hasShot(true);
                return;
            }
        }
    }
}
void VerticalSnarlbot::move()
{
    if(getDirection()==up)
    {
        if(getWorld()->NoObstruction(getX(), getY()+1)==true)
            moveTo(getX(), getY()+1);
        else
            setDirection(down);
    }
    else if(getDirection()==down)
    {
        if(getWorld()->NoObstruction(getX(), getY()-1)==true)
            moveTo(getX(), getY()-1);
        else
            setDirection(up);
    }
}

Kleptobot::Kleptobot(int imageID, int startX, int startY, Direction dir,StudentWorld* sw)
:Robot(imageID,startX,startY,dir,sw)
{
    pickedGoodie = false;
    world = sw;
    distanceCounter = 0;
    m_moved = false;
    m_shot = false;
}
bool Kleptobot::didRobotShoot()
{
    return m_shot;
}
void Kleptobot::didShoot(bool p)
{
    m_shot = p;
}
void Kleptobot::doSomething()
{
    if(isDead()==true)
        return;
    if(getWorld()->getTick() % getWorld()->robotTick() == 0)
    {
        pickUpGoodie();
        shootBullet();
        if(didRobotShoot()==false)
        {
            hasRobotMoved(false); // need this for the move Kleptobot to work
            moveKleptobot();
        }
    }
    didShoot(false);
}
void Kleptobot::pickUpGoodie()
{
    if(getWorld()->findObjectAt(getX(), getY(), IID_EXTRA_LIFE) !=nullptr ||getWorld()->findObjectAt(getX(), getY(), IID_AMMO) !=nullptr||getWorld()->findObjectAt(getX(), getY(), IID_RESTORE_HEALTH) !=nullptr)
    {
        if(didRobotPickUpGoodie() == false)
        {
            if((rand()%10) == 8)  // 1 in 10 chance
            {
                if(getWorld()->findObjectAt(getX(), getY(), IID_EXTRA_LIFE) != nullptr) // its an extra life goodie
                {
                    rememberTypeofGoodie(IID_EXTRA_LIFE);
                    hasPickedUpGoodie(true);
                    getWorld()->findObjectAt(getX(), getY(), IID_EXTRA_LIFE)->setDead();
                    getWorld()->playSound(SOUND_ROBOT_MUNCH);
                }
                else if(getWorld()->findObjectAt(getX(), getY(), IID_AMMO) != nullptr) // its an ammo goodie
                {
                    rememberTypeofGoodie(IID_AMMO);
                    hasPickedUpGoodie(true);
                    getWorld()->findObjectAt(getX(), getY(), IID_AMMO)->setDead();
                    getWorld()->playSound(SOUND_ROBOT_MUNCH);
                }
                else if(getWorld()->findObjectAt(getX(), getY(), IID_RESTORE_HEALTH) != nullptr) // its an restore goodie
                {
                    rememberTypeofGoodie(IID_RESTORE_HEALTH);
                    hasPickedUpGoodie(true);
                    getWorld()->findObjectAt(getX(), getY(), IID_RESTORE_HEALTH)->setDead();
                    getWorld()->playSound(SOUND_ROBOT_MUNCH);
                }
            }
        }
    }
}
void Kleptobot::moveKleptobot()
{
    int rht = 0; int lft = 0; int u = 0; int dwn = 0; int dx =0; int dy =0;
    switch (getDirection())
    {
        case right:
        {
            dx = 1; dy = 0;
            break;
        }
        case left:
        {
            dx = -1; dy = 0;
            break;
        }
        case up:
        {
            dx = 0; dy = 1;
            break;
        }
        case down:
        {
            dx = 0; dy = -1;
            break;
        }
        default:
            break;
    }
            if(distanceCounter<=distanceBeforeTurning&&getWorld()->NoObstruction(getX()+dx, getY()+dy)==true)
            {
                setDirection(getDirection());
                moveTo(getX()+dx, getY()+dy);
                distanceCounter++;
                return;
            }
            if(distanceCounter>distanceBeforeTurning||getWorld()->NoObstruction(getX()+dx,getY()+dy)==false)
            {
                distanceCounter = 0;
                distanceBeforeTurning = (rand()%6)+1;
                while(didRobotMove()==false)  // implement function and initialize in the constructor
                {
                    int dx = 0;
                    int dy = 0;
                    int d = rand() % 4;
                    switch (d)
                    {
                        case 0:  // right
                        {
                            dx = 1;dy = 0;
                            if(getWorld()->NoObstruction(getX()+dx, getY()+dy)==true)
                            {
                                setDirection(right);
                                moveTo(getX()+dx, getY()+dy);
                                distanceCounter++;
                                hasRobotMoved(true);
                            }
                            if(rht ==0)
                                rht++;
                            break;
                        }
                        case 1: // left
                        {
                            dx = -1; dy = 0;
                            if(getWorld()->NoObstruction(getX()+dx, getY()+dy)==true)
                            {
                                setDirection(left);
                                moveTo(getX()+dx, getY()+dy);
                                distanceCounter++;
                                hasRobotMoved(true);
                            }
                            if(lft ==0)
                                lft++;
                            break;
                        }
                        case 2:  // up
                        {
                            dx = 0;dy = 1;
                            if(getWorld()->NoObstruction(getX()+dx, getY()+dy)==true)
                            {
                                setDirection(up);
                                moveTo(getX()+dx, getY()+dy);
                                distanceCounter++;
                                hasRobotMoved(true);
                            }
                            if(u == 0)
                                u++;
                            break;
                        }
                        case 3:  // down
                        {
                            dx = 0; dy = -1;
                            if(getWorld()->NoObstruction(getX()+dx, getY()+dy)==true)
                            {
                                setDirection(down);
                                moveTo(getX()+dx, getY()+dy);
                                distanceCounter++;
                                hasRobotMoved(true);
                            }
                            if(dwn==0)
                                dwn++;
                            break;
                        }
                        default:
                            break;
                    }
                    if(rht+lft+u+dwn == 4)
                        return;
                }
            }
}
void Kleptobot::hasRobotMoved(bool m)
{
    m_moved = m;
}
bool Kleptobot::didRobotMove()
{
    return m_moved;
}
void Kleptobot::damage()
{
    setHealth(getHealth() - 2);  // decrement the health by 2
    getWorld()->playSound(SOUND_ROBOT_IMPACT);
    
    if(getHealth() < 1)
    {
        if(didRobotPickUpGoodie()==true)
        {
            if(getTypeofGoodie()== IID_EXTRA_LIFE)
            {
                Actor* p = new ExtraLifeGoodie(IID_EXTRA_LIFE,getX(),getY(),none,world);
                getWorld()->pushToList(p);
            }
            else if(getTypeofGoodie()== IID_AMMO)
            {
                Actor* p = new AmmoGoodie(IID_AMMO,getX(),getY(),none,world);
                getWorld()->pushToList(p);
            }
            else if(getTypeofGoodie()== IID_RESTORE_HEALTH)
            {
                Actor* p = new RestoreHealthGoodie(IID_RESTORE_HEALTH,getX(),getY(),none,world);
                getWorld()->pushToList(p);
            }
        }
        setDead();
        getWorld()->playSound(SOUND_ROBOT_DIE);
        reward();  // reg kleptobots give 10, angry kleptobots give 20
        return;
    }
}
int Kleptobot::getDistanceBeforeTurning()
{
    return distanceBeforeTurning;
}
void Kleptobot::setDistanceBeforeTurning(int d)
{
    distanceBeforeTurning = d;
}
void Kleptobot::hasPickedUpGoodie(bool x)
{
    pickedGoodie = x;
}
bool Kleptobot::didRobotPickUpGoodie()
{
    return pickedGoodie;
}
void Kleptobot::rememberTypeofGoodie(int imageID)
{
    goodieID = imageID;
}
int Kleptobot::getTypeofGoodie()
{
    return goodieID;
}
StudentWorld* Kleptobot::getStWorld()
{
    return world;
}
RegularKleptobot::RegularKleptobot(int imageID, int startX, int startY, Direction dir,StudentWorld* sw)
:Kleptobot(imageID,startX,startY,dir,sw)
{
    setHealth(5);
    setDistanceBeforeTurning((rand()%6)+1);
    setVisible(true);
}
void RegularKleptobot::reward()
{
    getWorld()->increaseScore(10);
}
void RegularKleptobot::shootBullet()
{
    return; // simply returns b/c reg kleptobot does not ever shoot
}
AngryKleptobot::AngryKleptobot(int imageID, int startX, int startY, Direction dir,StudentWorld* sw)
:Kleptobot(imageID,startX,startY,dir,sw)
{
    setHealth(8);
    setDistanceBeforeTurning((rand()%6)+1);
    setVisible(true);
    
}
void AngryKleptobot::reward()
{
    getWorld()->increaseScore(20);
}
void AngryKleptobot::shootBullet()
{
    if(getWorld()->getAccessToSpecific(IID_PLAYER)->getX() == getX()) // in the same column
    {
        if(getDirection()== up && getWorld()->getAccessToSpecific(IID_PLAYER)->getY() > getY()) // faces up
        {
            if(getWorld()->checkBtwnPlayerVertical(getX(), getY()+1,getWorld()->getAccessToSpecific(IID_PLAYER)->getY()-1)==true)
            {
                Actor* p = new Bullet(IID_BULLET,getX(),getY()+1,up,getStWorld());
                getWorld()->playSound(SOUND_ENEMY_FIRE);
                getWorld()->pushToList(p);
                didShoot(true);
                return;
            }
        }
    }
    else if(getWorld()->getAccessToSpecific(IID_PLAYER)->getX() == getX()) // in the same row
    {
        if(getDirection()== down && getWorld()->getAccessToSpecific(IID_PLAYER)->getY() < getY()) // faces down
        {
            if(getWorld()->checkBtwnPlayerVertical(getX(), getWorld()->getAccessToSpecific(IID_PLAYER)->getY()+1,getY()-1)==true)
            {
                Actor* p = new Bullet(IID_BULLET,getX(),getY()-1,down,getStWorld());
                getWorld()->playSound(SOUND_ENEMY_FIRE);
                getWorld()->pushToList(p);
                didShoot(true);
                return;
            }
        }
    }
    else if(getWorld()->getAccessToSpecific(IID_PLAYER)->getY() == getY()) // in the same row
    {
        if(getDirection()== right && getWorld()->getAccessToSpecific(IID_PLAYER)->getX() > getX())   // faces right
        {
            if(getWorld()->checkBtwnPlayerHorizontal(getY(), getX()+1,getWorld()->getAccessToSpecific(IID_PLAYER)->getX()-1)==true)
            {
                Actor* p = new Bullet(IID_BULLET,getX()+1,getY(),right,getStWorld());
                getWorld()->playSound(SOUND_ENEMY_FIRE);
                getWorld()->pushToList(p);
                didShoot(true);
                return;
            }
        }
    }
    else if(getWorld()->getAccessToSpecific(IID_PLAYER)->getY() == getY()) // in the same row
    {
        if(getDirection()== left && getWorld()->getAccessToSpecific(IID_PLAYER)->getX() < getX())   // faces left
        {
            if(getWorld()->checkBtwnPlayerHorizontal(getY(), getWorld()->getAccessToSpecific(IID_PLAYER)->getX()+1,getX()-1)==true)
            {
                Actor* p = new Bullet(IID_BULLET,getX()-1,getY(),left,getStWorld());
                getWorld()->playSound(SOUND_ENEMY_FIRE);
                getWorld()->pushToList(p);
                didShoot(true);
                return;
            }
        }
    }
    
}
Wall::Wall(int imageID, int startX, int startY, Direction dir,StudentWorld* sw)
:Item(imageID,startX,startY,none,sw)
{
    setVisible(true);
}
void Wall::doSomething()
{
    return;
}
Hole::Hole(int imageID, int startX, int startY, Direction dir,StudentWorld* sw)
:Item(imageID,startX,startY,none,sw)
{
    dir = none;
    setVisible(true);
}
void Hole::doSomething()
{
    if(isDead()==true)
        return;
    if(getWorld()->findObjectAt(getX(), getY(), IID_BOULDER) != nullptr)
    {
        setDead();
        getWorld()->findObjectAt(getX(), getY(), IID_BOULDER)->setDead();
    }
    return;
}

Boulder::Boulder(int imageID, int startX, int startY, Direction dir,StudentWorld* sw)
:Item(imageID,startX,startY,none,sw)
{
    dir = none;
    setVisible(true);
    setHealth(10);
}
void Boulder::doSomething()
{
    return;
}
void Boulder::damage()
{
    setHealth(getHealth() - 2);
    if(getHealth() < 1)
    {
        setDead();
        return;
    }
}
Jewel::Jewel(int imageID, int startX, int startY, Direction dir,StudentWorld* sw)
:Goodie(imageID,startX,startY,none,sw)
{
    dir = none;
    setVisible(true);
}
void Jewel::reward()
{
    getWorld()->increaseScore(50);
}


ExtraLifeGoodie::ExtraLifeGoodie(int imageID, int startX, int startY, Direction dir,StudentWorld* sw)
:Goodie(imageID,startX,startY,none,sw)
{
    dir=none;
    setVisible(true);
}
void ExtraLifeGoodie::reward()
{
    getWorld()->increaseScore(1000);
    getWorld()->incLives();
}

RestoreHealthGoodie::RestoreHealthGoodie(int imageID, int startX, int startY, Direction dir,StudentWorld* sw)
:Goodie(imageID,startX,startY,none,sw)
{
    dir = none;
    setVisible(true);
}
void RestoreHealthGoodie::reward()
{
    getWorld()->increaseScore(500);
    getWorld()->findObjectAt(getX(), getY(), IID_PLAYER)->setHealth(20);
}

AmmoGoodie::AmmoGoodie(int imageID, int startX, int startY, Direction dir,StudentWorld* sw)
:Goodie(imageID,startX,startY,none,sw)
{
    dir = none;
    setVisible(true);
}
void AmmoGoodie::reward()
{
    getWorld()->increaseScore(100);
    getWorld()->findObjectAt(getX(), getY(), IID_PLAYER)->setAmmo(20);
    
}

Exit::Exit(int imageID, int startX, int startY, Direction dir,StudentWorld* sw)
:Item(imageID,startX,startY,none,sw)
{
    dir = none;
    setVisible(false);
}
void Exit::doSomething()
{
    if(getWorld()->findObjectAt(getX(), getY(), IID_PLAYER) != nullptr  && isVisible()==true)
    {
        getWorld()->playSound(SOUND_FINISHED_LEVEL);
        getWorld()->increaseScore(2000);
        getWorld()->setLevelComplete(true); // tells the student world that the level is done
        getWorld()->increaseScore(getWorld()->getBonusPoints());
        
    }
}
Bullet::Bullet(int imageID, int startX, int startY, Direction dir,StudentWorld* sw)
:Item(imageID,startX, startY,dir,sw)
{
    setVisible(true);
    m_attack = false;
}
void Bullet::doSomething()
{
    if(isDead()==true)
        return;
    attack();
    if(bulletHasAttacked()==false)
    {
        moveBullet();
        attack();
    }
    didAttack(false);
    return;
}
bool Bullet::bulletHasAttacked()
{
    return m_attack;
}
void Bullet::didAttack(bool a)
{
    m_attack = a;
}
void Bullet::moveBullet()
{
    if(getDirection() == left)
    {
        moveTo(getX()-1, getY());
        return;
    }
    if(getDirection() == right)
    {
        moveTo(getX()+1, getY());
        return;
    }
    if(getDirection() == up)
    {
        moveTo(getX(), getY()+1);
        return;
    }
    if(getDirection() == down)
    {
        moveTo(getX(), getY()-1);
        return;
    }
    return;
}

void Bullet::attack()
{
    // checks the type of object and calls the damage function
    if(getWorld()->findObjectAt(getX(), getY(), IID_PLAYER) != nullptr)
    {
        didAttack(true);
        getWorld()->findObjectAt(getX(), getY(), IID_PLAYER)->damage();
        setDead();
        return;
    }
    else if(getWorld()->findObjectAt(getX(), getY(), IID_BOULDER) != nullptr)
    {
        didAttack(true);
        getWorld()->findObjectAt(getX(), getY(), IID_BOULDER)->damage();
        setDead();
        return;
    }
    else if(getWorld()->findObjectAt(getX(), getY(), IID_SNARLBOT) != nullptr)
    {
        didAttack(true);
        getWorld()->findObjectAt(getX(), getY(), IID_SNARLBOT)->damage();
        setDead();
        return;
    }
    else if(getWorld()->findObjectAt(getX(), getY(), IID_KLEPTOBOT) != nullptr)
    {
        didAttack(true);
        getWorld()->findObjectAt(getX(), getY(), IID_KLEPTOBOT)->damage();
        setDead();
        return;
    }
    else if(getWorld()->findObjectAt(getX(), getY(), IID_ANGRY_KLEPTOBOT) != nullptr)
    {
        didAttack(true);
        getWorld()->findObjectAt(getX(), getY(), IID_ANGRY_KLEPTOBOT)->damage();
        setDead();
        return;
    }
    else if(getWorld()->findObjectAt(getX(), getY(), IID_WALL) != nullptr)
    {
        didAttack(true);
        setDead();
        return;
    }
    else if(getWorld()->findObjectAt(getX(), getY(), IID_ROBOT_FACTORY) != nullptr)
    {
        didAttack(true);
        setDead();
        return;
    }
    else
        return;
}
Factory::Factory(int imageID, int startX, int startY, Direction dir,StudentWorld* sw, string type)
:Item(imageID,startX,startY,dir,sw)
{
    robotType = type;
    setVisible(true);
    n_world = sw;
}
void Factory::doSomething()
{
    if(count(getX()-3,getX()+3,getY()-3,getY()+3) < 3)
    {
        if(getWorld()->findObjectAt(getX(), getY(), IID_KLEPTOBOT) ==nullptr && getWorld()->findObjectAt(getX(), getY(), IID_ANGRY_KLEPTOBOT) ==nullptr)
        {
            if(rand()%50 == 24)
            {
                if(robotType == "regular")
                {
                    Actor* p = new RegularKleptobot(IID_KLEPTOBOT,getX(),getY(),right,n_world);
                    getWorld()->pushToList(p);
                }
                else if(robotType == "angry")
                {
                    Actor* p = new AngryKleptobot(IID_ANGRY_KLEPTOBOT,getX(),getY(),right,n_world);
                    getWorld()->pushToList(p);
                }
                getWorld()->playSound(SOUND_ROBOT_BORN);
            }
        }
    }
}
int Factory::count(int x, int x2, int y, int y2)
{
    int counter = 0;
    for(int i = x; i <x2 +1; i++)
    {
        if(i>=0 && i < VIEW_WIDTH)
        {
            for(int j = y; j<y2+1;j++)
            {
                if(j >=0 && j<VIEW_HEIGHT)
                {
                    if(getWorld()->findObjectAt(i, j, IID_KLEPTOBOT)!=nullptr)
                        counter++;
                    else if(getWorld()->findObjectAt(i, j, IID_ANGRY_KLEPTOBOT)!=nullptr)
                        counter++;
                }
            }
        }
    }
    return counter;
}

