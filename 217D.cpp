#include <iostream>
#include <vector>

using namespace std;



struct Link {
    int from;
    int to;
    int direction;
};

struct Node {
    int parent;
    vector<int> linkedNode;
    int val;
};

Node tree[200005];
vector<Link> link[200005];
int dp[200005]={0};
int dp2[200005]={0};
int roadName = 0;
void nodeDirectionInit(int parent) {
    if(link[parent].empty()) return;


    for(int i=0;i<link[parent].size(); i++) {//방향 하나 찾는데 너무 많은 회전
        if(link[parent][i].from == parent) {//parent from->child to
            link[parent][i].direction = 1;

        }
        else if(link[parent][i].to == parent) {
            //parent to -> child from
            link[parent][i].direction = -1;

        }

    }

}
int isRoadReverse(int parent, int child, int ind){
    if(link[parent].empty()) return 0;

    if(link[parent][ind].direction == 1) {
        return 0;
    }
    else if(link[parent][ind].direction == -1) return 1;




}

int dfs(int n, int parent, int ind) {
    tree[n].parent = parent;
    nodeDirectionInit(n);
    if(tree[n].linkedNode.size() == 1) {
        int v = isRoadReverse(tree[n].parent, n, ind);
        tree[n].val = 0;
        return v; // go back if isleaf
    }

    int ret_val=0;
    for(int i=0;i<tree[n].linkedNode.size();i++) {
        if(tree[n].linkedNode[i] != tree[n].parent) {
            ret_val += dfs(tree[n].linkedNode[i], n, i);
        }
    }



    tree[n].val = ret_val;
    //cout << "dfs1 in"<< n << "is" <<ret_val << endl;
    if(isRoadReverse(tree[n].parent, n, ind) == 1) {
        return ret_val+1;
    }
    else return ret_val;
}

void dfs2(int n, int ind) {
    if(tree[n].parent !=0) {
        int parent= tree[n].parent;
        dp[n] = dp[parent];

        if(isRoadReverse(parent, n, ind) == 0) {
            dp[n]++;
        }
        else dp[n]--;
    }
    else dp[n] = tree[n].val;

    if(tree[n].linkedNode.size() == 1) {
        //cout << "dfs2 in"<< n << "is" << dp[n] << endl;
        return;
    }

    for(int i=0;i<tree[n].linkedNode.size();i++) {
        if(tree[n].linkedNode[i] != tree[n].parent) {
            dfs2(tree[n].linkedNode[i], i);
        }
    }
    //cout << "dfs2 in"<< n << "is" << dp[n] << endl;

}
int main() {

    int n;
    int max_size_node=0;
    cin >> n;

    for(int i=0; i< n-1; i++) {
        int from, to;
        Link l;
        cin >> from >> to;
        l.from = from;
        l.to = to;

        link[from].push_back(l);
        link[to].push_back(l);

        tree[from].linkedNode.push_back(to);
        tree[to].linkedNode.push_back(from);

        if(link[from].size()>link[max_size_node].size() || link[to].size()>link[max_size_node].size()) {
            if(link[from].size() >= link[to].size()) {
                max_size_node = from;
            }
            else max_size_node = to;
        }
    }


    for(int i=0; i<200005; i++) {
        dp[i] = 200005;
    }





    int ans;
    dfs(max_size_node, 0, 0);

    dfs2(max_size_node, 0);

    int min=200005;
    vector<int> min_node;

    for(int i = 0; i < 200005; i++) {

        if(dp[i] < min) {
            min_node.clear();
            min = dp[i];
            min_node.push_back(i);
        }
        else if(dp[i] == min) min_node.push_back(i);

    }

    ans = min;

    cout << ans <<endl;
    for(int i=0; i < min_node.size(); i++) {
        cout << min_node[i] << " ";
    }

    return 0;
}
