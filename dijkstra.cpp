#include <iostream>
#include <queue>
#include <vector>
#define MAX INT_MAX

int V;
using namespace std;
vector<pair<int, int> > adj[MAX];

vector <int> dijkstra(int src) {
    vector<int> dist(V, MAX);
    dist[src] = 0;
    priority_queue<pair<int, int>> pq;
    pq.push(make_pair(0, src));
    while(!pq.empty()) {
        int cost = -pq.top().first;
        int here = pq.top().second;
        pq.pop();
        if(dist[here] < cost) continue;;

        for(int i= 0; i< adj[here].size(); ++i) {
            int there = adj[here][i].first;
            int nextDist = cost + adj[here][i].second;

            if(dist[there] > nextDist) {
                dist[there] = nextDist;
                pq.push(make_pair(-nextDist, there));
            }
        }
    }
}
int main() {

}