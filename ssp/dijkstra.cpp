#include "dijkstra.h"

void Dijkstra::init(MapInfo map){
    vexnum = map.vexnum;
    arcnum = map.arcnum;
    st = map.st;
    en = map.en;
    // init cost
    for (int i = 0; i <= vexnum; i++){
        cost[i] = Cost(inf, inf);
    }
    // Read G
    int len = map.side_info_vec.size();
    for(int i = 0; i < len; i++){
        SideInfo s = map.side_info_vec[i];
        G[s.u].push_back(make_pair(s.v, Cost(s.dis, s.tim)));
    }
}

void Dijkstra::solveByDistance(){
    struct cmp{
        bool operator() (pic A, pic B){
            if(A.first == B.first){
                if(A.second.dis == B.second.dis)
                    return A.second.tim > B.second.tim;
                return A.second.dis > B.second.dis;
            }
            return A.first < B.first;
        }
    };
    priority_queue<pic, vector<pic>, cmp > Q;
    cost[st] = Cost(0, 0);
    Q.push(make_pair(st, cost[st]));

    while(!Q.empty()){
        pic tmp = Q.top();
        Q.pop();
        int v = tmp.first;
        if(cost[v].dis < tmp.second.dis)
            continue;
        int len = G[v].size();
        for(int i = 0; i < len; i++){
            pic e = G[v][i];
            if(cost[e.first].dis > cost[v].dis + e.second.dis){
                cost[e.first].dis = cost[v].dis + e.second.dis;
                cost[e.first].tim = cost[v].tim + e.second.tim;
                Q.push(make_pair(e.first, cost[e.first]));
                Path[e.first] = Path[v];
                Path[e.first].push_back(v);
            }
        }
    }
}

void Dijkstra::solveByTime(){
    struct cmp{
        bool operator() (pic A, pic B){
            if(A.first == B.first){
                if(A.second.tim == B.second.tim)
                    return A.second.dis > B.second.dis;
                return A.second.tim > B.second.tim;
            }
            return A.first < B.first;
        }
    };
    priority_queue<pic, vector<pic>, cmp > Q;
    cost[st] = Cost(0, 0);
    Q.push(make_pair(st, cost[st]));
    while(!Q.empty()){
        pic tmp = Q.top();
        Q.pop();
        int v = tmp.first;
        if(cost[v].tim < tmp.second.tim)
            continue;
        int len = G[v].size();
        for(int i = 0; i < len; i++){
            pic e = G[v][i];
            if(cost[e.first].tim > cost[v].tim + e.second.tim){
                cost[e.first].tim = cost[v].tim + e.second.tim;
                cost[e.first].dis = cost[v].dis + e.second.dis;
                Q.push(make_pair(e.first, cost[e.first]));
                Path[e.first] = Path[v];
                Path[e.first].push_back(v);
            }
        }
    }
}

set<pair<int, int> > Dijkstra::findWay(){
    if (cost[en].dis == inf) {
        cout << "No Way!!!" << endl;
    }else{
        cout << "Dijkstra SSP: dis = " << cost[en].dis << " time = " << cost[en].tim << endl;
        int pos = -1;
        int len = Path[en].size();
        for(int i = 0; i < len; i++){
            cout << Path[en][i] << "->";
            side_set.insert(make_pair(pos, Path[en][i]));
            pos = Path[en][i];
        }
        side_set.insert(make_pair(pos, en));
        cout << en << endl;
    }
    return side_set;
}
