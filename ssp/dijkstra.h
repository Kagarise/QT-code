#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "mapinfo.h"

#include <queue>
#include <iostream>

#define N 10010

typedef pair<int, Cost> pic;

class Dijkstra{
public:
    int vexnum, arcnum;
    int st, en;
    Cost cost[N];
    vector<pair<int, Cost> > G[N];
    vector<int> Path[N];

    set<pair<int, int> > side_set;

    void init(MapInfo map);
    void solveByDistance();
    void solveByTime();
    set<pair<int, int> > findWay();
};

#endif // DIJKSTRA_H
