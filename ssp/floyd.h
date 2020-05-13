#ifndef FLOYD_H
#define FLOYD_H

#include "mapinfo.h"

#include <iostream>

#define F 110

class Floyd{
public:
    int vexnum, arcnum;
    int st, en;
    Cost G[F][F];
    int Path[F][F];

    set<pair<int, int> > side_set;

    void init(MapInfo map);
    void solveByDistance();
    void solveByTime();
    set<pair<int, int> > findWay();
};

#endif // FLOYD_H
