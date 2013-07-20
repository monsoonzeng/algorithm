#include <iostream>
#include <cstdio>
#include <stack>

using std::stack;
using std::cout;
using std::endl;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int val) {
        this->val = val;
        left = NULL;
        right = NULL;
    }
};

void preorder_traversal(TreeNode *root) {
    if (root == NULL) {
        return;
    }
    stack<TreeNode*> st;
    TreeNode *cn = root;
    while (cn != NULL || !st.empty()) {
        if (cn != NULL) {
            // visit current node
            cout << cn->val << endl;
            st.push(cn->right);
            cn = cn->left;
        } else {
            cn = st.top();
            st.pop();
        }
    }
}

void midorder_traversal(TreeNode *root) {
    stack<TreeNode*> st;
    TreeNode *cn = root;
    while (cn!=NULL || !st.empty()) {
        if (cn != NULL) {
            st.push(cn);
            cn = cn->left;
        } else {
            cn = st.top();
            st.pop();
            // visit current node
            cout << cn->val << endl;
            cn = cn->right;
        }
    }
}

void midorder_traversal2(TreeNode *root) {
    stack<TreeNode*> st;
    TreeNode *cn = root;
    st.push(cn);
    while (!st.empty()) {
        for (cn = st.top(); cn != NULL; cn = st.top()) {
            st.push(cn->left);
        }
        st.pop();
        if (!st.empty()) {
            // visit top
            cn = st.top();
            st.pop();
            cout << cn->val << endl;
            st.push(cn->right);
        }
    }
}

void postorder_traversal(TreeNode *root) {
    stack<TreeNode*> st;
    TreeNode *cn = root;
    while (true) {
        if (cn != NULL) {
            st.push(cn);
            st.push(cn->right);
            cn = cn->left;
        } else {
            cn = st.top();
            st.pop();
            if (cn == NULL) {
                cn = st.top();
                st.pop();
                // visit current val
                cout << cn->val << endl;
                if (st.empty()) {
                    return;
                }
                cn = st.top();
                st.pop();
            }
            st.push(NULL);
        }
    }
}

int main(int argc, char *argv[]) 
{
    /*
     *        0
     *     1      2
     *       3  4   5
     */
    TreeNode root(0);
    TreeNode node1(1);
    TreeNode node2(2);
    TreeNode node3(3);
    TreeNode node4(4);
    TreeNode node5(5);
    root.left = &node1;
    root.right = &node2;
    node1.right = &node3;
    node2.left = &node4;
    node2.right = &node5;
    cout << "first_order traversal: " << endl;
    preorder_traversal(&root);
    cout << "\nmid_order traversal: " << endl;
    midorder_traversal(&root);
    cout << "\nmid_order traversal2: " << endl;
    midorder_traversal2(&root);
    cout << "\npost_order traversal: " << endl;
    postorder_traversal(&root);
    
    return 0;
}
