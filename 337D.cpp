#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
    int parent;
    vector<int> linkedNode;
    int affected;
    int distance;
    int dupExist;
    int bestchild;
};

Node tree[100005];

int dp[100005]={0};

vector<int> affectedPoint;

int dfs(int n, int parent) {
    tree[n].parent = parent;

    if(tree[n].linkedNode.size() == 1) {
        cout << "dfs1 in"<< n << " is " << 0 << endl;
        if(tree[n].affected == 1) return 1;
        else return 0; // go back if isleaf
    }

    int ret_val=0;
    for(int i=0;i<tree[n].linkedNode.size();i++) {
        if(tree[n].linkedNode[i] != tree[n].parent) {
            ret_val = max(ret_val, dfs(tree[n].linkedNode[i], n));
        }
    }

    tree[n].distance = ret_val;
    cout << "dfs1 in"<< n << " is " << ret_val << endl;

    if(tree[n].affected == 1) return 1;
    else return ret_val+1;


}

void dfs2(int n) {
    if(tree[n].parent !=0) {
        if(tree[n].distance != tree[tree[n].parent].distance-1) {
            tree[n].distance = max(tree[tree[n].parent].distance+1, tree[n].distance);
        }
        else {
            if(tree[tree[n].parent].dupExist == 1) {
                tree[n].distance = tree[tree[n].parent].distance+1;
            }
        }
    }

    dp[n] = tree[n].distance;

    if(tree[n].linkedNode.size() == 1) {
        cout << "dfs2 in"<< n << " is " << dp[n] << endl;
        return;
    }
    int mx = -1;
    int mx_count = 0;
    for(int i=0;i<tree[n].linkedNode.size();i++) {


        if(tree[n].linkedNode[i] != tree[n].parent) {
            if(mx == max(tree[tree[n].linkedNode[i]].distance, mx)) {
                mx_count++;
            }
            else {
                mx = max(tree[tree[n].linkedNode[i]].distance, mx);
                mx_count = 1;
            }
        }

    }
    if(mx_count>1) tree[n].dupExist = 1;

    for(int i=0;i<tree[n].linkedNode.size();i++) {


        if(tree[n].linkedNode[i] != tree[n].parent) {
            dfs2(tree[n].linkedNode[i]);
        }

    }
    cout << "dfs2 in "<< n << " is " << dp[n] << endl;
}

int main() {

    int n, m, d;
    int max_size_node=0;
    cin >> n >> m >> d;

    for(int i = 0 ; i< m ; i++) {
        int aff;
        cin >> aff;
        affectedPoint.push_back(aff);
        tree[aff].affected = 1;

    }

    for(int i=0; i< n-1; i++) {

        int from, to;
        cin >> from >> to;

        tree[from].linkedNode.push_back(to);
        tree[to].linkedNode.push_back(from);

        if(tree[from].linkedNode.size()>tree[max_size_node].linkedNode.size() || tree[to].linkedNode.size()>tree[max_size_node].linkedNode.size()) {
            if(tree[from].linkedNode.size() >= tree[to].linkedNode.size()) {
                max_size_node = from;
            }
            else max_size_node = to;
        }
    }


    for(int i=0; i<100005; i++) {
        dp[i] = 100005;
    }





    int ans;
    dfs(max_size_node, 0);

    dfs2(max_size_node);


    vector<int> target_node;

    for(int i = 0; i < 100005; i++) {

        if(dp[i]<=d) {
            target_node.push_back(i);
        }

    }
    ans = target_node.size();

    for(int i = 0; i < target_node.size(); i++) {
        cout << target_node[i] <<endl;

    }

    cout << ans <<endl;


    return 0;
}