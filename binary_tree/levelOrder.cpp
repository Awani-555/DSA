#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val; TreeNode* left; TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

/* -----------------------------------------------------------
   BRUTE FORCE APPROACH
----------------------------------------------------------- */
vector<vector<int>> levelOrder_Brute(TreeNode* root) {
    vector<vector<int>> res;
    if(!root) return res;
    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()) {
        vector<int> level;
        int sz = q.size();
        for(int i=0;i<sz;i++) {
            TreeNode* node = q.front(); q.pop();
            level.push_back(node->val);
            if(node->left) q.push(node->left);
            if(node->right) q.push(node->right);
        }
        res.push_back(level);
    }
    return res;
}

/* BETTER and OPTIMAL are the same for Level Order (BFS) */

vector<vector<int>> levelOrder_Optimal(TreeNode* root){
    return levelOrder_Brute(root);
}

/* MAIN */
int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2); root->right = new TreeNode(3);
    root->left->left = new TreeNode(4); root->left->right = new TreeNode(5);

    cout << "Level Order Traversal:\n";
    vector<vector<int>> res = levelOrder_Optimal(root);
    for(auto &level: res){
        for(int v: level) cout << v << " "; cout << endl;
    }
}
