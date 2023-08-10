#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <sstream>

struct TreeNode {
    int val;
    std::vector<TreeNode*> children;
    
    TreeNode(int v) : val(v) {}
};

TreeNode* deserialize(const std::string& s) {
    std::stack<TreeNode*> stack;
    int i = 0;
    
    while (i < s.size()) {
        if (s[i] == '(') {
            i++;
        } else if (s[i] == ')') {
            stack.pop();
            i++;
        } else {
            int j = i;
            while (j < s.size() && s[j] != '(' && s[j] != ')' && s[j] != ',') {
                j++;
            }
            int val;
            std::istringstream(s.substr(i, j - i)) >> val;
            TreeNode* curr_node = new TreeNode(val);
            if (!stack.empty()) {
                stack.top()->children.push_back(curr_node);
            }
            stack.push(curr_node);
            i = j;
        }
    }
    
    return stack.top();
}

void printGraph(TreeNode* node) {
    if (!node) return;
    
    std::cout << node->val << " [";
    for (const auto& child : node->children) {
        printGraph(child);
    }
    std::cout << "] ";
}

int main() {
    std::string serialized = "-20(5,6(4,4)6,7,8,9(2,4)-5)";
    TreeNode* root = deserialize(serialized);
    
    std::cout << "Deserialized graph structure:" << std::endl;
    printGraph(root);    
    return 0;
}
