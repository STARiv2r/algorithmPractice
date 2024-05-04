#include <iostream>
#include <vector>

using namespace std;



struct Link {
    int from;
    int to;
};

struct Node {
    int parent;
    vector<int> linkedNode;
    int val;
};

Node tree[200005];
vector<Link> link[200005];
int dp[200005]={0};

int isRoadReverse(int parent, int child){
    for(int i=0;i<link[parent].size(); i++) {
        if(link[parent][i].from == parent && link[child][i].to) {//parent from->child to
            return 0;
        }
        else if(link[parent][i].to == parent && link[child][i].from) {
            //parent to -> child from
            return 1;
        }
        else return -1;
    }

}

int dfs(int n) {
    if(tree[n].linkedNode.size() == 1) {
        int v = isRoadReverse(tree[n].parent, n);
        tree[n].val = v;
        return v; // go back if isleaf
    }

    int ret_val=0;
    for(int i=0;i<tree[n].linkedNode.size();i++) {
        if(tree[n].linkedNode[i] != tree[n].parent) {
            ret_val = dfs(tree[n].linkedNode[i]);
        }
    }

    if(isRoadReverse(tree[n].parent, n) == 1) {
        ret_val++;
    }

    tree[n].val = ret_val;
    return ret_val;
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

        if(link[from].size()>max_size_node || link[to].size()>max_size_node) {
            if(link[from].size() > link[to].size()) {
                max_size_node = from;
            }
            else max_size_node = to;
        }
    }
    int ans;
    ans = dfs(max_size_node);




    cout << ans <<endl;



    return 0;
}
