#ifndef MAPINFO_H
#define MAPINFO_H

#include <set>
#include <vector>
#include <utility>
using namespace std;

const int inf = 0x3f3f3f3f;

class Cost
{
public:
    double dis, tim;
    Cost(){
        this->dis = 0;
        this->tim = 0;
    }
    Cost(double dis, double tim) {
        this->dis = dis;
        this->tim = tim;
    }
};

class SideInfo{
public:
    int u, v;
    double dis, tim;
    SideInfo(int u, int v, double dis, double speed){
        this->u = u;
        this->v = v;
        this->dis = dis;
        this->tim = dis/speed;
    }
};

class MapInfo
{
public:
    int vexnum, arcnum;
    vector<SideInfo> side_info_vec;
    set<pair<int, int> > side_set;
    int st, en;
    MapInfo() {
        vexnum = arcnum = 0;
        st = en = 0;
        side_info_vec.clear();
        side_set.clear();
    }
};

#endif // MAPINFO_H
