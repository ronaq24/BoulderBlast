#include "StudentWorld.h"
#include <string>
#include "Level.h"
#include "GameConstants.h"
#include "Actor.h"
#include <list>
#include <iostream> // defines the overloads of the << operator
#include <sstream>  // defines the type std::ostringstream
#include <iomanip>  // defines the manipulator setw
using namespace std;
using namespace std;
//Done
GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(std::string assetDir)
: GameWorld(assetDir),m_ticks(0)
{
}

StudentWorld::~StudentWorld()
{
    list<Actor*>::iterator ptr;
    ptr = objectList.begin();
    
    while(ptr != objectList.end())
    {
        Actor* act = *ptr;
        delete act;
        objectList.erase(ptr);
        ptr++;
    }
}

int StudentWorld::init()
{
    string curLevel = FormatLevel();
    bonusPoints = 1000;
    LevelComplete = false;
    Level lev(assetDirectory());
    Level::LoadResult result = lev.loadLevel(curLevel);
    if (result == Level::load_fail_file_not_found || getLevel() ==100)
    {
        cerr << "Could not find level00.dat data file\n";
        return GWSTATUS_PLAYER_WON;
    }
    
    else if (result == Level::load_fail_bad_format)
    {
        cerr << "Your level was improperly formatted\n";
        return GWSTATUS_LEVEL_ERROR;
    }
    for(int i=0; i < VIEW_WIDTH; i++)
    {
        for(int k=0; k < VIEW_HEIGHT; k++)
        {
            Level::MazeEntry ge = lev.getContentsOf(i,k);
            switch (ge)
            {
                case Level::player:
                {
                    Actor* ptr = new Player(IID_PLAYER,i,k,Actor::right,this);
                    objectList.push_back(ptr);
                    m_player = ptr;
                    break;
                }
                case Level::wall:
                {
                    Actor* ptr = new Wall(IID_WALL,i,k,Actor::none,this);
                    objectList.push_back(ptr);
                    break;
                }
                case Level::hole:
                {
                    Actor* ptr = new Hole(IID_HOLE,i,k,Actor::none,this);
                    objectList.push_back(ptr);
                    break;
                }
                case Level::boulder:
                {
                    Actor* ptr = new Boulder(IID_BOULDER,i,k,Actor::none,this);
                    objectList.push_back(ptr);
                    break;
                }
                case Level::jewel:
                {
                    Actor* ptr = new Jewel(IID_JEWEL,i,k,Actor::none,this);
                    objectList.push_back(ptr);
                    break;
                }
                case Level::extra_life:
                {
                    Actor* ptr= new ExtraLifeGoodie(IID_EXTRA_LIFE,i,k,Actor::none,this);
                    objectList.push_back(ptr);
                    break;
                }
                case Level::restore_health:
                {
                    Actor* ptr = new RestoreHealthGoodie(IID_RESTORE_HEALTH,i,k,Actor::none,this);
                    objectList.push_back(ptr);
                    break;
                }
                case Level::ammo:
                {
                    Actor* ptr = new AmmoGoodie(IID_AMMO,i,k,Actor::none,this);
                    objectList.push_back(ptr);
                    break;
                }
                case Level::exit:
                {
                    Actor* ptr = new Exit(IID_EXIT,i,k,Actor::none,this);
                    objectList.push_back(ptr);
                    break;
                }
                case Level::horiz_snarlbot:
                {
                    Actor* ptr = new HorizontalSnarlbot(IID_SNARLBOT,i,k,Actor::right,this);
                    objectList.push_back(ptr);
                    break;
                }
                case Level::vert_snarlbot:
                {
                    Actor* ptr = new VerticalSnarlbot(IID_SNARLBOT,i,k,Actor::down,this);
                    objectList.push_back(ptr);
                    break;
                }
                case Level::kleptobot_factory:
                {
                    Actor* ptr = new Factory(IID_ROBOT_FACTORY,i,k,Actor::none,this,"regular");
                    objectList.push_back(ptr);
                    break;
                }
                case Level:: angry_kleptobot_factory:
                {
                    Actor* ptr = new Factory(IID_ROBOT_FACTORY,i,k,Actor::none,this,"angry");
                    objectList.push_back(ptr);
                    break;
                }
                default:
                    break;
            }
        }
    }
    return GWSTATUS_CONTINUE_GAME;
}
string StudentWorld::FormatLevel()
{
    int levelOn = getLevel();
    ostringstream oss;
    oss<<"level";
    oss.fill('0');
    oss<<setw(2)<<levelOn;
    oss<<".dat";
    string st = oss.str();
    return st;
}

void StudentWorld::setDisplayText()
{
    int score = getScore();
    int level = getLevel();
    unsigned int bonus = getBonusPoints();
    int livesLeft = getLives();
    int health = (m_player->getHealth())*5; // because need to make this a percentage
    int ammo = m_player->getAmmo();
    
    string str1 =FormatStringNicely(score, level,livesLeft, health, ammo, bonus);
    setGameStatText(str1);
}

string StudentWorld::FormatStringNicely(int score,int level,int lives,int health, int ammo, int bonus)
{
    ostringstream oss;
    oss <<"Score: ";
    oss.fill('0');
    oss<<setw(7) << score;
    oss<<"  Level: ";
    oss.fill('0');
    oss<<setw(2) << level;
    oss<<"  Lives: ";
    oss.fill(' ');
    oss<<setw(2) << lives;
    oss<<"  Health: ";
    oss.fill(' ');
    oss<<setw(3)<<health<<'%';
    oss<<"  Ammo: ";
    oss.fill(' ');
    oss<<setw(3)<<ammo;
    oss<<"  Bonus: ";
    oss.fill(' ');
    oss<<setw(4)<<bonus;
    string s = oss.str();
    return s;
}

bool StudentWorld::PlayerCompletedLevel()
{
    return LevelComplete;
}
void StudentWorld::setLevelComplete(bool d)
{
    LevelComplete = d;
}
void StudentWorld::pushToList(Actor* x)
{
    objectList.push_front(x);
}
void StudentWorld::removeDeadObjects()
{
    list<Actor*>:: iterator it;
    it = objectList.begin();
    
    while(it != objectList.end())
    {
        if((*it)->isDead()== true)
        {
            delete *it;
            objectList.erase(it);
        }
        it++;
    }
}
int StudentWorld::move()
{
    increaseTicks();
    setDisplayText();
    list<Actor*>:: iterator p;
    p = objectList.begin();
    
    while(p != objectList.end())
    {
        Actor* act = *p;
        if(act->isDead()== false)
        {
            act->doSomething();
            if(m_player->isDead()==true)
            {
                return GWSTATUS_PLAYER_DIED;
            }
            if(PlayerCompletedLevel() == true)
            {
                return GWSTATUS_FINISHED_LEVEL;
            }
        }
        p++;
    }
    
    removeDeadObjects();
    reduceLevelBonusByOne();
    if(playerCollectedAllJewels() == true)
    {
        exposeTheExit();
    }
    if(m_player->isDead()==true)
        return GWSTATUS_PLAYER_DIED;
    if(PlayerCompletedLevel() == true)
        return GWSTATUS_FINISHED_LEVEL;
    
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::reduceLevelBonusByOne()
{
    if(bonusPoints > 0)
        bonusPoints--;
    return;
}
unsigned int StudentWorld::getBonusPoints()
{
    return bonusPoints;
}
Actor* StudentWorld::findObjectAt(int x, int y, int object)
{
    list<Actor*>:: iterator it;
    it = objectList.begin();
    
    while(it != objectList.end())
    {
        if((*it)->getX() == x && (*it)->getY() == y && (*it)->getID() == object)
        {
            return *it;
        }
        it++;
    }
    
    return nullptr; // object that you are looking for is not there
}

int StudentWorld::robotTick()
{
    int ticks = (28 - getLevel()) / 4;
    if (ticks < 3)
        ticks = 3;
    
    return ticks;
}
void StudentWorld::increaseTicks()
{
    m_ticks++;
}
int StudentWorld::getTick()
{
    return m_ticks;
}

Actor* StudentWorld::findAnythingAt(int x, int y)
{
    list<Actor*>:: iterator it;
    it = objectList.begin();
    
    while(it != objectList.end())
    {
        if((*it)->getX() == x && (*it)->getY() == y)
        {
            return *it;
        }
        
        it++;
    }
    
    return nullptr;
}

bool StudentWorld::NoObstruction(int x, int y)
{
    
    if(findObjectAt(x, y, IID_WALL)==nullptr && findObjectAt(x, y, IID_BOULDER)==nullptr &&findObjectAt(x, y, IID_PLAYER)==nullptr&& findObjectAt(x, y, IID_SNARLBOT)==nullptr && findObjectAt(x, y, IID_KLEPTOBOT)==nullptr && findObjectAt(x, y, IID_ROBOT_FACTORY)==nullptr && findObjectAt(x, y, IID_HOLE)==nullptr && findObjectAt(x, y, IID_ANGRY_KLEPTOBOT) == nullptr)
    {
        return true;
    }
    
    return false;
}
bool StudentWorld::NoBlockForPlayer(int x, int y)
{
    if(findObjectAt(x, y,IID_WALL) == nullptr && findObjectAt(x, y,IID_HOLE) == nullptr &&findObjectAt(x, y, IID_BOULDER) == nullptr && findObjectAt(x, y, IID_SNARLBOT) == nullptr && findObjectAt(x, y, IID_KLEPTOBOT) == nullptr && findObjectAt(x, y, IID_ROBOT_FACTORY) == nullptr && findObjectAt(x, y, IID_ANGRY_KLEPTOBOT) == nullptr)
    {
        return true;
    }
    return false;
}
Actor* StudentWorld:: getAccessToSpecific(int imageID)
{
    list<Actor*>:: iterator it;
    it = objectList.begin();
    
    while(it != objectList.end())
    {
        if((*it)->getID() == imageID)
        {
            return *it;
        }
        
        it++;
    }
    
    return nullptr;
}
bool StudentWorld::checkBtwnPlayerHorizontal(int a, int b, int c)
{
    for(int i = b; i < c+1; i++)
    {
        if(findObjectAt(i, a, IID_WALL) != nullptr || findObjectAt(i, a, IID_BOULDER) != nullptr || findObjectAt(i, a, IID_SNARLBOT) != nullptr || findObjectAt(i, a, IID_KLEPTOBOT) != nullptr || findObjectAt(i,a, IID_ROBOT_FACTORY) != nullptr || findObjectAt(i,a, IID_ANGRY_KLEPTOBOT) != nullptr)
            return false;
    }
    return true;
}
bool StudentWorld::checkBtwnPlayerVertical(int a, int b, int c)
{
    for(int i = b; i < c+1; i++)
    {
        if(findObjectAt(a, i, IID_WALL) != nullptr || findObjectAt(a, i, IID_BOULDER) != nullptr || findObjectAt(a, i, IID_SNARLBOT) != nullptr || findObjectAt(a, i, IID_KLEPTOBOT) != nullptr || findObjectAt(a,i, IID_ROBOT_FACTORY) != nullptr || findObjectAt(a,i, IID_ANGRY_KLEPTOBOT) != nullptr)
            return false;
    }
    return true;
}
bool StudentWorld::playerCollectedAllJewels()
{
    list<Actor*>:: iterator it;
    it = objectList.begin();
    
    
    while(it != objectList.end())
    {
        if((*it)->returnID()==IID_JEWEL)
        {
            return false;
        }
        
        it++;
    }
    return true;

}

void StudentWorld::exposeTheExit()
{
    list<Actor*>:: iterator it;
    it = objectList.begin();
    
    while(it != objectList.end())
    {
        if((*it)->returnID()==IID_EXIT && (*it)->isVisible()==false)
        {
            (*it)->setVisible(true);
            playSound(SOUND_REVEAL_EXIT);
        }
        
        it++;
    }
    return;
}


void StudentWorld::cleanUp()
{
    list<Actor*>::iterator ptr;
    ptr = objectList.begin();
    
    while(ptr != objectList.end())
    {
        Actor* act = *ptr;
        delete act;
        objectList.erase(ptr);
        ptr++;
        
        
    }
}