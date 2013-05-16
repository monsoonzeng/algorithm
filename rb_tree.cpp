#include<stdio.h>
/*
 * rb insert z:
 * z is insert node, y is z's uncle, z is RED
 * while z's father is RED
 * case 1: y is  RED, do something(just color) and repeate while
 * case 2: y is BLACK, z is to his grandfather is left-right, do something and goto case3
 * case 3: y is BLACK, z to his grandfather is ll or rr, do something  and end while
 *
 * rb delete z: if z is not two child node, delete z's successor y , and copy y to z. else delete z
 * x is delete node y's child, x is double black or red black node, x's color is BLACK
 * while x != root and x's color == black: w is x's brother
 * case 1: w is RED, do something and goto case 2,3,4
 * case 2: w is BLACK and w has two BLACK child, do something(just color), and x move to x's father and repeate while
 * case 3: w is BLACK and w's right(w is right child) child is BLACK, do something, and goto case 4.
 * case 4: w is BLACK and w's right child is RED, do something and end while
 *
 */

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
    RBTreeNode(T_KEY k=0, RB c=BLACK, RBTreeNode* l=NULL, 
        RBTreeNode* r=NULL, RBTreeNode* pa=NULL)
            :key(k), color(c),left(l),right(r),p(pa){}
} *RBTree;
RBTreeNode* NIL = new RBTreeNode();


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
                printf("case 1\n");
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            } else {
                if (z == z->p->right) {
                    printf("case 2\n");
                    z=z->p;
                    left_rotate(root, z);
                } 
                printf("case 3\n");
                z->p->color = BLACK;
                z->p->p->color = RED;
                right_rotate(root, z->p->p);
            }
        } else {
            y = z->p->p->left;
            if (y->color == RED) {
                printf("case 1\n");
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            } else {
                if (z == z->p->left) {
                    printf("case 2\n");
                    z = z->p;
                    right_rotate(root, z);
                }
                printf("case 3\n");
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
                printf("case 1\n");
                x->p->color = RED;
                w->color = BLACK;
                left_rotate(root, x->p);
                w = x->p->right;
            } 
            //w->color == BLACK
            if (w->left->color == BLACK and w->right->color == BLACK) {
                //case 2
                printf("case 2\n");
                w->color = RED;
                x = x->p;
            } else {
                if (w->right->color == BLACK) {
                    //case 3
                    printf("case 3\n");
                    w->left->color = BLACK;
                    w->color = RED;
                    right_rotate(root, w);
                    w = w->p; // or w = x->p->right;
                }
                //case 4
                printf("case 4\n");
                w->color = x->p->color;
                x->p->color = BLACK;
                w->right->color = BLACK;
                left_rotate(root, x->p);
                x = root;
            }

        } else {
            w = x->p->left; 
            if (w->color == RED) {
                printf("case 1\n");
                x->p->color = RED;
                w->color = BLACK;
                right_rotate(root, x->p);
                w = x->p->left;
            }
            if (w->left->color == BLACK and w->right->color == BLACK) {
                printf("case 2\n");
                w->color = RED;
                x = x->p;
            } else {
                if (w->left->color = BLACK) {
                    printf("case 3\n");
                    w->right->color = BLACK;
                    w->color = RED;
                    left_rotate(root, w);
                    w = w->p;
                }
                printf("case 4\n");
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

void print_tree(RBTree root) 
{
    if (root == NIL) {
        printf("# ");
        return;
    }
    printf("(%d,%c) ", root->key,root->color);
    print_tree(root->left);
    print_tree(root->right);
}
int main(int argc, char** argv)
{

    RBTreeNode *root = NIL;
    rb_insert(root, new RBTreeNode(1));
    print_tree(root);
    printf("\n");
    rb_insert(root, new RBTreeNode(3));
    print_tree(root);
    printf("\n");
    rb_insert(root, new RBTreeNode(2));
    print_tree(root);
    printf("\n");
    rb_insert(root, new RBTreeNode(10));
    print_tree(root);
    printf("\n");
    rb_insert(root, new RBTreeNode(15));
    print_tree(root);
    printf("\n");
    rb_insert(root, new RBTreeNode(8));
    print_tree(root);
    printf("\n");
    rb_insert(root, new RBTreeNode(13));
    print_tree(root);
    printf("\n");
    printf("Begin to delete----------\n");
    RBTreeNode* d = rb_delete2(root, root->left);
    delete d;
    print_tree(root);
    printf("\n");
    d = rb_delete2(root, root->left->right);
    delete d;
    print_tree(root);
    printf("\n");
    d = rb_delete2(root, root->right);
    delete d;
    print_tree(root);
    printf("\n");
    return 0;
}
