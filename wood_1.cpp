#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <math.h>
#include <set>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
 
 class Point{

private:    
    int x;
    int y;
    
public:
    Point(int x, int y){
        this->x = x;
        this->y = y;
    }
    int getX(){
        return x;
    }
    int getY(){
        return y;    
    }
};


class Site{
    
private:
    Point* pos;
    int radius;
    int id;
    int owner;
    int type;
    int gold;
    int maxExRate;
public:
   
    Site(Point* pos, int radius, int id, int type = -1, int owner = -1){
        this->pos = pos;
        this->radius = radius;
        this->id = id;
        this->type = type;
    }
    
    Point* getPos(){
        return pos;
    }
    
    int getRadius(){
        return radius;    
    }
    
    int getId(){
        return id;
    }
    
    int isMine(){
        return owner;    
    }
    
    void setOwner(int available){
        this->owner = available;
    }
    
    void setGold(int gold){
        this->gold = gold;
    }
    
    int getGold(){
        return gold;    
    }
    
    void setMaxExRate(int rate){
        this->maxExRate = rate;    
    }
    
    int getMaxExRate(){
        return maxExRate;    
    }
    
    int getType(){
        return type;    
    }
    
    void setType(int type){
        this->type = type;
    }
};


class GameBot{
    public:
        static Site* getTheNearestSite(){
                
        }
};

map<int, Site*> sites;
vector<int> myBarracks;
set<int> myMins;
map<int, Site*> enemySites;


Site* getNearestEmptySite(Point *pos){
    float minDist = 200000;
    Site* nearst = NULL;
    
    for(map<int, Site*>::iterator i = sites.begin(); 
                        i != sites.end(); i++){
        Site* iSite = i->second;
        
        if(iSite->getType() != -1)
            continue;
            
        Point *iSitePos = iSite->getPos();
        int distX = iSitePos->getX() - pos->getX();
        int distY = iSitePos->getY() - pos->getY();
        
        float dist = sqrt(distX*distX + distY*distY);
        
        if(dist < minDist){
            minDist = dist;
            nearst = iSite;    
        }
        
    }
    
    return nearst;
}


Site* getNearestGoldSite(Point *pos){
    float minDist = 200000;
    Site* nearst = NULL;
    
    for(map<int, Site*>::iterator i = sites.begin(); 
                        i != sites.end(); i++){
        Site* iSite = i->second;
        
        if(iSite->getType() != -1 && iSite->getGold() < 1)
            continue;
            
        Point *iSitePos = iSite->getPos();
        int distX = iSitePos->getX() - pos->getX();
        int distY = iSitePos->getY() - pos->getY();
        
        float dist = sqrt(distX*distX + distY*distY);
        
        if(dist < minDist){
            minDist = dist;
            nearst = iSite;    
        }
        
    }
    
    return nearst;
}



int main()
{
    int numSites;
    cin >> numSites; cin.ignore();
    for (int i = 0; i < numSites; i++) {
        int siteId;
        int x;
        int y;
        int radius;
        cin >> siteId >> x >> y >> radius; cin.ignore();
        sites[siteId] = new Site(new Point(x, y), 
                            radius, siteId);
    }

    // game loop
    int turn = 0;
    bool midFlage = false;
    int lastMinetryal = -1;
    while (1) {
        turn++;
        int gold;
        int touchedSite; // -1 if none
        cin >> gold >> touchedSite; cin.ignore();
        for (int i = 0; i < numSites; i++) {
            int siteId;
            int goldRemaining; // -1 if unknown
            int maxMineSize; // -1 if unknown
            int structureType; // -1 = No structure, 0 = Goldmine, 1 = Tower, 2 = Barracks
            int owner; // -1 = No structure, 0 = Friendly, 1 = Enemy
            int param1;
            int param2;
            cin >> siteId >> goldRemaining >> maxMineSize >> structureType >> owner >> param1 >> param2; cin.ignore();
            
            sites[siteId]->setGold(goldRemaining);
            sites[siteId]->setMaxExRate(maxMineSize);
            sites[siteId]->setType(structureType);
            sites[siteId]->setOwner(owner);
            
            if(owner == 1){
                enemySites[siteId] = sites[siteId];
            }
        }
        int numUnits;
        cin >> numUnits; cin.ignore();
        
        Point* queenPos;
        int hp;
        for (int i = 0; i < numUnits; i++) {
            int x;
            int y;
            int owner;
            int unitType; // -1 = QUEEN, 0 = KNIGHT, 1 = ARCHER, 2 = GIANT
            int health;
            cin >> x >> y >> owner >> unitType >> health; cin.ignore();
            
            // get my queen
            if(unitType == -1 && owner == 0){
                queenPos = new Point(x, y);
                hp = health;
            }
        }

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;
        Site *nearestEmptySite = getNearestEmptySite(queenPos);
        Site *nearestGoldSite = getNearestGoldSite(queenPos);
        
        
        cerr << myBarracks.size() << " " << myMins.size() << endl;
        bool awayFromMiddle = abs(queenPos->getX() - 900) > 200 && abs(queenPos->getY() - 500) > 50;
        if(!awayFromMiddle)
            midFlage = true;
        if(awayFromMiddle && !midFlage && myBarracks.size() >= 2 && myMins.size() >= 2){            
            cout << "MOVE " << 900 << " " << 500 << endl;
        }
        else if(touchedSite != -1 && sites[touchedSite]->getType() == -1){
            if(sites[touchedSite]->getMaxExRate() >= 4 && myMins.size() < 4 && lastMinetryal != touchedSite){
                cout << "BUILD " << touchedSite << " MINE" << endl;  
                lastMinetryal = touchedSite;
                myMins.insert(touchedSite);
            }
            else if(myBarracks.empty()){
                cout << "BUILD " << touchedSite << " BARRACKS-KNIGHT" << endl;  
                myBarracks.push_back(touchedSite);
            }else if(myMins.size() < 4 && lastMinetryal != touchedSite){
                cout << "BUILD " << touchedSite << " MINE" << endl;
                lastMinetryal = touchedSite;
                myMins.insert(touchedSite);
            }
            else if(myBarracks.size() == 1){
                cout << "BUILD " << touchedSite << " BARRACKS-ARCHER" << endl;  
                myBarracks.push_back(touchedSite)  
;
            }else if(myBarracks.size() == 2){
                cout << "BUILD " << touchedSite << " BARRACKS-GIANT" << endl;  
                myBarracks.push_back(touchedSite);
            }else {
                cout << "BUILD " << touchedSite << " TOWER" << endl; 
            }
        }else if(nearestEmptySite != NULL){
            Point *pos = nearestEmptySite->getPos();
            cout << "MOVE " << pos->getX() << " " << pos->getY() << endl;
        }else{
            cout << "WAIT" <<endl;
        }
    
        // First line: A valid queen action
        // Second line: A set of training instructions
        string s = "TRAIN";
        if(gold >= 100 && myBarracks.size() >= 2){
            s += " " + to_string(myBarracks[1]);
        }else if(gold >= 80 && myBarracks.size() >= 1){
            s += " " + to_string(myBarracks[0]);                
        }
        cout << s << endl;
    }
}