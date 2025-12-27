#include <bits/stdc++.h>
using namespace std;

struct TreeNode{
    int val; TreeNode* left; TreeNode* right;
    TreeNode(int x):val(x),left(nullptr),right(nullptr){}
};

/* BRUTE: store full levels */
vector<int> rightView_Brute(TreeNode* root){
    vector<int> res;
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
        res.push_back(level.back());
    }
    return res;
}

/* BETTER / OPTIMAL: push last element immediately */
vector<int> rightView_Optimal(TreeNode* root){
    vector<int> res;
    if(!root) return res;
    queue<TreeNode*> q; q.push(root);
    while(!q.empty()){
        int n = q.size();
        for(int i=0;i<n;i++){
            TreeNode* node = q.front(); q.pop();
            if(i==n-1) res.push_back(node->val);
            if(node->left) q.push(node->left);
            if(node->right) q.push(node->right);
        }
    }
    return res;
}

/* MAIN */
int main(){
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2); root->right = new TreeNode(3);
    root->left->right = new TreeNode(5); root->right->right = new TreeNode(4);

    cout << "Right Side View:\n";
    vector<int> res = rightView_Optimal(root);
    for(int v: res) cout << v << " ";
    cout << endl;
}
