#include<stdio.h>

typedef int T_KEY;

enum RB{
    RED='R',
    BLACK='B',
};
typedef struct RBTreeNode{
    T_KEY key;
    RB	color;
    RBTreeNode* left;
    RBTreeNode* right;
    RBTreeNode* p;
} *RBTree;

RBTreeNode* NIL = NULL;

void left_rotate(RBTree &root, RBTreeNode *x)
{
    if (x== NULL || x->right==NIL) {
        return;
    }
    RBTreeNode *y = x->right;
    x->right = y->left;
    if (y->left != NIL) {
        y->left->p = x;
    }
    if (root != x) {
        if (x==x->p->left) {
            x->p->left = y;
        } else {
            x->p->right = y;
        }
    } else {
        root = y;
    }
    y->p = x->p;
    y->left = x;
    x->p = y;
}

void right_rotate(RBTree &root, RBTreeNode *x)
{
    if (x==NULL || x->left == NIL) {
        return;
    }
    RBTreeNode *y = x->left;
    x->left = y->right;
    if (y->right != NIL) {
        y->right->p = x;
    }
    if (root != x) {
        if (x==x->p->left) {
            x->p->left = y;
        } else {
            x->p->right = y;
        }
    } else {
        root =y;
    }
    y->p = x->p;
    y->right = x;
    x->p = y;
}
void rb_insert_fixup(RBTree &root, RBTreeNode *z)
{
    RBTreeNode *y = NIL;    //y is z's uncle
    while (z->p->color == RED) {
        //z->p is not root , so z->p->p is not nil
        if (z->p == z->p->p->left) {
            //z->p is left child
            y = z->p->p->right;
            if (y->color == RED) {
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            } else {
                if (z == z->p->right) {
                    z=z->p;
                    left_rotate(root, z);
                } 
                z->p->color = BLACK;
                z->p->p->color = RED;
                right_rotate(root, z->p->p);
            }
        } else {
            y = z->p->p->left;
            if (y->color == RED) {
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            } else {
                if (z == z->p->left) {
                    z = z->p;
                    right_rotate(root, z);
                }
                z->p->color = BLACK;
                z->p->p->color = RED;
                left_rotate(root, z->p->p);
            }
        }
    }
    root->color = BLACK;
}
bool rb_insert(RBTree &root, RBTreeNode *z)
{
    RBTreeNode *x = root;
    RBTreeNode *y = NIL;
    for(; x!=NIL; ) {
        y = x;
        if (x->key > z->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    z->p = y;
    if (y==NIL) {
        root = z;
    } else if(z->key < y->key) {
        y->left = z;
    } else {
        y->right = z;
    }
    z->left = NIL;
    z->right = NIL;
    z->color = RED; 
    rb_insert_fixup(root, z);
    return true;
}

void rb_delete_fixup(RBTree &root, RBTreeNode *x)
{
    RBTreeNode *w;
    while (x!=root and x->color == BLACK) {
        if (x == x->p->left) {
            w = x->p->right; //w is not nil, because x is double black
            if (w->color==RED) {
                //case 1
                x->p->color = RED;
                w->color = BLACK;
                left_rotate(root, x->p);
                w = x->p->right;
            } 
            //w->color == BLACK
            if (w->left->color == BLACK and w->right->color == BLACK) {
                //case 2
                w->color = RED;
                x = x->p;
            } else {
                if (w->right->color == BLACK) {
                    //case 3
                    w->left->color = BLACK;
                    w->color = RED;
                    right_rotate(root, w);
                    w = w->p; // or w = x->p->right;
                }
                //case 4
                w->color = x->p->color;
                x->p->color = BLACK;
                w->right->color = BLACK;
                left_rotate(root, x->p);
                x = root;
            }

        } else {
            //TODO
            w = x->p->left; 
            if (w->color == RED) {
                x->p->color = RED;
                w->color = BLACK;
                right_rotate(root, x->p);
                w = x->p->left;
            }
            if (w->left->color == BLACK and w->right->color == BLACK) {
                w->color = RED;
                x = x->p;
            } else {
                if (w->left->color = BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    left_rotate(root, w);
                    w = w->p;
                }
                w->color = x->p->color;
                x->p->color = BLACK;
                w->left->color = BLACK;
                right_rotate(root, x->p);
                x = root;
            }

        }
    }
    x->color = BLACK;
}
RBTreeNode* tree_successor(RBTreeNode *x) 
{
    RBTreeNode *right = x->right;
    if (right != NIL) {
        while(right->left != NIL) {
            right = right->left;
        }
        return right;
    }
    RBTreeNode *y = x->p;
    while(y!=NIL and x == y->right) {
        x = y;
        y = y->p;
    }
    return y;
}
RBTreeNode* rb_delete2(RBTree &root, RBTreeNode *z) 
{
    RBTreeNode *x;
    RBTreeNode *y;
    if (z->left == NIL || z->right == NIL) {
        x = (z->left == NIL)? z->right : z->left;
        if (z == z->p->left) {
            z->p->left = x;
        } else {
            z->p->right = x;
        }
        //important: not use if (x!= NIL), because rb_delete_fixup use it
        x->p = z->p;
        if (root == z) {
            root = x;
        }
        if (z->color == BLACK) {
            rb_delete_fixup(root, x);
        }
        return z;
    }
    y = tree_successor(z);
    x = y->right;
    //important: not use if (x!= NIL), because rb_delete_fixup use it
    x->p = y->p;
    if (y->p->left = y) {
        y->p->left = x;
    } else {
        y->p->right = x;
    }
    //copy y data to z
    z->key = y->key;
    //copy satellite data into z;
    if (y->color == BLACK) {
        rb_delete_fixup(root, x);
    }
    return y;
}
RBTreeNode* rb_delete(RBTree &root, RBTreeNode *z) {
    RBTreeNode *x, *y;
    if (z->left == NIL  || z->right == NIL) {
        y = z;
    } else {
        y = tree_successor(z);
    }
    if (y->left != NIL) {
        x = y->left;
    } else {
        x = y->right;
    }
    //important: not use if (x!= NIL), because rb_delete_fixup use it
    x->p = y->p;
    if (y->p == NIL) {
        root = x;
    } else if(y==y->p->left) {
        y->p->left = x;
    } else {
        y->p->right = x;
    }
    if (y != z) {
        z->key = y->key;
        //copy satellite data into z;
    }
    if (y->color == BLACK) {
        rb_delete_fixup(root, x);
    }
    return y;


    
}

int main(int argc, char** argv)
{
    return 0;
}
