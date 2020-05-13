#include"floyd.h"

void Floyd::init(MapInfo map){
    vexnum = map.vexnum;
    arcnum = map.arcnum;
    st = map.st;
    en = map.en;
    // init G ans Path
    for (int i = 0; i <= vexnum; i++)
        for (int j = 0; j <= vexnum; j++)
            if (i == j)
                G[i][j] = Cost(0, 0), Path[i][j] = -1;
            else
                G[i][j] = Cost(inf, inf), Path[i][j] = j;
    // Read G
    int len = map.side_info_vec.size();
    for(int i = 0; i < len; i++){
        SideInfo s = map.side_info_vec[i];
        G[s.u][s.v] = Cost(s.dis, s.tim);
    }
}

void Floyd::solveByDistance(){
    for (int k = 1; k <= vexnum; k++)
        for (int i = 1; i <= vexnum; i++)
            for (int j = 1; j <= vexnum; j++)
                if (G[i][k].dis + G[k][j].dis < G[i][j].dis){
                    G[i][j].dis = G[i][k].dis + G[k][j].dis;
                    G[i][j].tim = G[i][k].tim + G[k][j].tim;
                    Path[i][j] = Path[i][k];
                }
}

void Floyd::solveByTime(){
    for (int k = 1; k <= vexnum; k++)
        for (int i = 1; i <= vexnum; i++)
            for (int j = 1; j <= vexnum; j++)
                if (G[i][k].tim + G[k][j].tim < G[i][j].tim){
                    G[i][j].dis = G[i][k].dis + G[k][j].dis;
                    G[i][j].tim = G[i][k].tim + G[k][j].tim;
                    Path[i][j] = Path[i][k];
                }
}

set<pair<int, int> > Floyd::findWay(){
    if (G[st][en].dis == inf) {
        cout << "No Way!!!" << endl;
    }else{
        cout << "Floyd SSP: dis = " << G[st][en].dis << " time = " << G[st][en].tim << endl;
        int pos = Path[st][en];
        cout << st;
        side_set.insert(make_pair(st, pos));
        while (pos != en) {
            int cas = pos;
            cout << "->" << pos;
            pos = Path[pos][en];
            side_set.insert(make_pair(cas, pos));
        }
        cout << "->" << en << endl;
    }
    return side_set;
}
