#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;

class TreeNode
{
public:
    short id;
    vector<TreeNode*> children;
public:
    TreeNode() {}
    TreeNode(int id) {this->id = id;}
    ~TreeNode() {}
public:
    void addChild(TreeNode* node){
        children.push_back(node);
    }
};

class Tree
{
public:
    TreeNode* root;
    map<short, TreeNode*> nodes_map;
public:
    Tree(/* args */) {}
    ~Tree() {}
public:
    void setRoot(TreeNode* node) {this->root = node;}
};

class Solution
{
private:
    /* data */
    int nodes_num = 0;
    int non_leaf_nodes_num = 0;
    Tree familTree;
public:
    Solution(/* args */);
    ~Solution();
};

Solution::Solution(/* args */)
{
    // get input
    cin >> nodes_num >> non_leaf_nodes_num;
    if (nodes_num == 0)
        return;
    familTree = Tree();
    short curr_id, n;
    TreeNode* curr_node;
    for (int i = 0; i < non_leaf_nodes_num; i++) {
        cin >> curr_id >> n;
        int child_id;
        if (familTree.nodes_map.count(curr_id) != 0) {
            curr_node = familTree.nodes_map[curr_id];
        }
        else {
            curr_node = new TreeNode(curr_id);
            familTree.nodes_map[curr_id] = curr_node;
        }

        if (curr_id == 1)
            familTree.setRoot(curr_node);

        TreeNode* child_node;
        for (int j = 0; j < n; j++) {
            cin >> child_id;
            
            if (familTree.nodes_map.count(child_id) != 0) {
                child_node = familTree.nodes_map[child_id];
            }
            else {
                child_node = new TreeNode(child_id);
                familTree.nodes_map[child_id] = child_node;
            }                
            curr_node->addChild(child_node);
        }
    }

    // counting logic
    queue<TreeNode*> q;
    q.push(familTree.root);
    TreeNode* flag_node = new TreeNode(-1);
    q.push(flag_node);
    int non_child_num = 0;
    while (!q.empty()) {
        TreeNode* curr = q.front();
        // cout << "curr: " << curr->id << endl;
        if (curr == flag_node) { // new level
            cout << non_child_num;
            non_child_num = 0;
            q.pop();
            if (q.empty())
                break;  
            cout << " ";
            q.push(flag_node);
        }
        else {
            if (curr->children.empty()) {
                non_child_num++;
            }
            for (TreeNode* child : curr->children) {
                q.push(child);
            }
            q.pop();// pop curr node
        }
    }
}

Solution::~Solution()
{
}


int main(int argc, char const *argv[])
{
    Solution s = Solution();
    return 0;
}
