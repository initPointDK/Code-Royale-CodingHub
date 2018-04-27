#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <climits>
#include <math.h> 


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

class Structure{

private:
    Point* pos;
    int id;
public:
    Structure(Point* pos, int id){
        this->pos = pos;
        this->id = id;
    }
    
    Point* getPos(){
        return pos;    
    }
    
    int getId(){
        return id;
    }
};

class Barrack : Structure{
private:
    int creepType; // 0 for KNIGHTS 1 for ARCHER
public:
    Barrack(Point *pos, int creepType, int id) : Structure(pos, id){
        this->creepType = creepType;
    }
    
};


class Site{
    
private:
    Point* pos;
    int radius;
    int id;
    bool available;
public:
    Site(Point* pos, int radius, int id, bool available = false){
        this->pos = pos;
        this->radius = radius;
        this->id = id;
        this->available = available;
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
    
    bool isAvailable(){
        return available;    
    }
    
    void setAvailable(bool available){
        this->available = available;
    }
};


class GameBot{
    public:
        static vector<Site*> sites;
        static vector<Barrack*> myBrks;
        static vector<Barrack*> enemyBrks;
        
        
        

        static Site* getNearestSite(Point *pos){
            Site* nerst = NULL;
            float minDist = 20000;
            for (int i = 0; i < sites.size(); i++) {
                Point* p = sites[i]->getPos();
        
                long long distX = p->getX() - pos->getX();
                long long distY = p->getY() - pos->getY();
                float dist = sqrt(distX*distX + distY*distY);
                if(minDist > dist && sites[i]->isAvailable()){
                    minDist = dist;
                    nerst = sites[i];
                }
            }
            
            return nerst;
        }
        
        static Site* getSiteById(int id){
            for (int i = 0; i < sites.size(); i++) {
                if(sites[i]->getId() == id)
                    return sites[i];
            }
        }
        
};


vector<Site*> GameBot::sites;
vector<Barrack*> GameBot::myBrks;
vector<Barrack*> GameBot::enemyBrks;

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
        
        GameBot::sites.push_back(new Site(new Point(x, y),
                              radius, siteId));
        
        //cerr << GameBot::sites.size()  << " " << x << "  " << y << endl;
    }
    
    
    // game loop
    vector<int> barracks;
    while (1) {
        int gold;
        int touchedSite; // -1 if none
        cin >> gold >> touchedSite; cin.ignore();
        for (int i = 0; i < numSites; i++) {
            int siteId;
            int ignore1; // used in future leagues
            int ignore2; // used in future leagues
            int structureType; // -1 = No structure, 2 = Barracks
            int owner; // -1 = No structure, 0 = Friendly, 1 = Enemy
            int param1;
            int param2;
            cin >> siteId >> ignore1 >> ignore2 >> structureType >> owner >> param1 >> param2; cin.ignore();
            
            if(structureType != -1){
                GameBot::sites[i]->setAvailable(false);
                if(owner == 0){
                    
                }else{
                    
                }
            }else{
                GameBot::sites[i]->setAvailable(true); 
            }
            
            
        }
        int numUnits;
        cin >> numUnits; cin.ignore();
    
        Point* queenMove;
        for (int i = 0; i < numUnits; i++) {
            int x;
            int y;
            int owner;
            int unitType; // -1 = QUEEN, 0 = KNIGHT, 1 = ARCHER
            int health;
            cin >> x >> y >> owner >> unitType >> health; cin.ignore();
            
            if(unitType == -1 && owner == 0){
                Site* s = GameBot::getNearestSite(new Point(x, y));
                if(s != NULL){
                    queenMove = s->getPos();
                }
            }
        }

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;


        // First line: A valid queen action
        // Second line: A set of training instructions
        
        if(touchedSite != -1 && GameBot::getSiteById(touchedSite)->isAvailable()){
            if(barracks.size() < 1)
                cout << "BUILD " << touchedSite << " BARRACKS-ARCHER" << endl; 
            else
                cout << "BUILD " << touchedSite << " BARRACKS-KNIGHT" << endl;
            barracks.push_back(touchedSite);
            cout << "TRAIN" << endl;
        }else{
            cout << "MOVE " << queenMove->getX() << " " << queenMove->getY() << endl;
            string s = "TRAIN";
            if(gold >= 100){
                 if(barracks.size() >= 1)
                    s += " " + to_string(barracks[0]);
            }else{
                if(barracks.size() >= 2)
                    s += " " + to_string(barracks[barracks.size() - 1]);
            }
            // for (int i = 0; i < barracks.size(); i++) {
            //     s += " " + to_string(barracks[0]);
            // }
            cout << s << endl;
        }
    }
}