#include<iostream>
/*
1. Initialize current as root 
2. While current is not NULL
   If current does not have left child
      a) Print current¡¯s data
      b) Go to the right, i.e., current = current->right
   Else
      a) Make current as right child of the rightmost node in current's left subtree
      b) Go to this left child, i.e., current = current->left
*/
using namespace std;
/**
 Definition for binary tree
*/
 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };

//
void morris_travelsal(TreeNode *root) 
{
    TreeNode *current = root;
    TreeNode *pre;

    while(current!=NULL) {
        if (current->left == NULL) {
	    cout<<current->val<<" ";
	    current = current->right;
	} else {
	    pre = current->left;
	    //find predecessor of current
	    while(pre->right != NULL && pre->right != current) {
	        pre = pre->right;
	    }
	    if (pre->right == NULL) {
	        //first find predecessor
		pre->right = current;
		current = current->left;
	    } else {
	       //left tree has traveled; revert the predecessor's right child
	       cout << current->val << " ";
	       pre->right = NULL;
	       current = current->right;
	    }
	}
    }
}

TreeNode* newtNode(int val) 
{
    TreeNode* result = new TreeNode(val);
    return result;
}

int main()
{
  /* Constructed binary tree is
            1
          /   \
        2      3
      /  \
    4     5
  */
  TreeNode *root = newtNode(1);
  root->left        = newtNode(2);
  root->right       = newtNode(3);
  root->left->left  = newtNode(4);
  root->left->right = newtNode(5); 
 
  morris_travelsal(root);
  return 0;
}

