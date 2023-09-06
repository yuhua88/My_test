#include<iostream>
#include<vector>
#include<map>
#include<cstdlib>
#include<algorithm>
#include<math.h>
#include<stdlib.h>
#include<regex>
#include<set>
#include<stack>
#include<queue>
#include <unordered_map>
#include <unordered_set>
using namespace std;
#pragma warning(disable:4996)
struct DLinkedNode {
    int val, key;
    DLinkedNode* next;
    DLinkedNode* front;
    DLinkedNode() : val(0), key(0), front(nullptr), next(nullptr) {}
    DLinkedNode(int _key, int _value) : key(_key), 
       val(_value), front(nullptr), next(nullptr) {}
};
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {} 
};
struct ListNode {
      int val;
     ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
};
class Solution {
public:
    int deep = 0;
    unordered_map<int, TreeNode*> map;
    unordered_map<int, int> parents;
    unordered_map<int, int> dep;
    vector<TreeNode*> leaf;
    int dfs(TreeNode* root) {
        if (root == nullptr)
            return -1;

        map[root->val] = root;
      
        if (root->left != nullptr)
            parents[root->left->val] = root->val;
            
        if (root->right != nullptr)
            parents[root->right->val] = root->val;

        int l = dfs(root->left) + 1;
        int r = dfs(root->right) + 1;
        
        return max(l, r);
    }
    void ans_dfs(TreeNode* root, int depth) {
        if (root == nullptr)
            return ;

        dep[root->val] = depth;

        if (depth == deep)
        {
            leaf.push_back(root);
            return;
        }

        ans_dfs(root->left,depth+1);
        ans_dfs(root->right,depth+1);
        
        return;

    }
    TreeNode* lcaDeepestLeaves(TreeNode* root) {
        deep = dfs(root);
        
        ans_dfs(root, 0);
        if (leaf.size() == 1)
            return leaf[0];
        
        TreeNode* ascent = new TreeNode();
        parents[root->val] = root->val;

        for (int i = 0; i < leaf.size(); i++)
        {
            int parent_a = leaf[0]->val, parent_b = leaf[i]->val;
            int level = min(dep[parent_a], dep[parent_b]);
            
            while (dep[parent_a] > level)
                parent_a = parents[parent_a];
            while (dep[parent_b] > level)
                parent_b = parents[parent_b];
            while (parent_a != parent_b)
            {
                parent_a = parents[parent_a];
                parent_b = parents[parent_b];
            }
            
            ascent = map[parent_a];
            leaf[0] = ascent;
        }
        
        return ascent;
    }
};
int main() {
    Solution A;
    vector<int> nums1 = { 7, 5, 6 }, nums2 = { 1, 4 };
    cout<<A.minNumber(nums1, nums2);

    return 0;
}