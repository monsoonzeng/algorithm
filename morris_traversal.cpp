#include<iostream>

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

