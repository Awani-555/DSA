#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val; TreeNode* left; TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

/* BRUTE: Reverse alternate levels after BFS */
vector<vector<int>> zigzag_Brute(TreeNode* root){
    vector<vector<int>> res;
    if(!root) return res;
    queue<TreeNode*> q; q.push(root);
    while(!q.empty()){
        int n = q.size();
        vector<int> level;
        for(int i=0;i<n;i++){
            TreeNode* node = q.front(); q.pop();
            level.push_back(node->val);
            if(node->left) q.push(node->left);
            if(node->right) q.push(node->right);
        }
        if(res.size()%2==1) reverse(level.begin(),level.end());
        res.push_back(level);
    }
    return res;
}

/* BETTER / OPTIMAL: Fill values directly */
vector<vector<int>> zigzag_Optimal(TreeNode* root){
    vector<vector<int>> res;
    if(!root) return res;
    queue<TreeNode*> q; q.push(root);
    bool leftToRight = true;
    while(!q.empty()){
        int n = q.size();
        vector<int> level(n);
        for(int i=0;i<n;i++){
            TreeNode* node = q.front(); q.pop();
            int idx = leftToRight ? i : n-1-i;
            level[idx] = node->val;
            if(node->left) q.push(node->left);
            if(node->right) q.push(node->right);
        }
        res.push_back(level);
        leftToRight = !leftToRight;
    }
    return res;
}

/* MAIN */
int main(){
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2); root->right = new TreeNode(3);
    root->left->left = new TreeNode(4); root->left->right = new TreeNode(5);
    root->right->right = new TreeNode(6);

    cout << "Zigzag Level Order Traversal:\n";
    vector<vector<int>> res = zigzag_Optimal(root);
    for(auto &level: res){
        for(int v: level) cout << v << " "; cout << endl;
    }
}
