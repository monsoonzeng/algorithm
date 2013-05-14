/*
 * AVLTree.cpp
 *
 *  Created on: 2013-4-23
 *      Author: yunfengzeng
 */
#include <iostream>
#include <queue>
#include <stack>
using namespace std;
enum BF{
    RH = -1,
    EH = 0,
    LH = 1,
};
struct AVLNode {
    int val;	//
    BF bf;		//balance factor
    AVLNode *left;
    AVLNode *right;
    AVLNode() :val(0),bf(EH),left(NULL),right(NULL) {}
    AVLNode(int v) :val(v),bf(EH),left(NULL),right(NULL) {}
};


class AVLTree{
    public:
        static bool insert_avl(AVLNode* &tree, int ele, bool &taller) {
            if (tree == NULL) {
                tree = new AVLNode(ele);
                tree->bf = EH;
                taller = true;
                return true;
            }
            if (tree->val == ele) {
                taller = false;
                return false;
            }
            if (tree->val > ele) {
                //insert to left tree
                if (!insert_avl(tree->left, ele, taller)) {
                    //insert false
                    taller = false;
                    return false;
                } else {
                    //insert true
                    if (!taller) {
                        return true;
                    }
                    if (tree->bf == LH) {
                        //insert left and taller and tree->bf >1
                        left_balance_tree(tree);
                        taller = false;
                    } else if (tree->bf == EH) {
                        taller = true;
                        tree->bf = LH;
                    } else if (tree->bf == RH) {
                        taller = false;
                        tree->bf = EH;
                    }
                }
            } else {
                //todo insert to right tree
                if (!insert_avl(tree->right, ele, taller)) {
                    //insert false
                    taller = false;
                    return false;
                } else {
                    if (!taller) {
                        return true;
                    }
                    if (tree->bf == LH) {
                        taller = false;
                        tree->bf = EH;
                    } else if (tree->bf == EH) {
                        taller = true;
                        tree->bf = RH;
                    } else if (tree->bf == RH) {
                        //new tree->bf >1
                        right_balance_tree(tree);
                        taller = false;
                    }
                }
            }
            return true;
        }

    private:
        static void r_rotate(AVLNode* &tree) {
            AVLNode* lc = tree->left;
            tree->left = lc->right;
            lc->right = tree;
            tree = lc;
        }
        static void l_rotate(AVLNode* &tree) {
            AVLNode* rc = tree->right;
            tree->right = rc->left;
            rc->left = tree;
            tree = rc;
        }
        static void left_balance_tree(AVLNode* &tree) {
            AVLNode* lc = tree->left; //lc not NULL
            switch (lc->bf) {
                case LH:
                    /**
                     *               2
                     *      1        |   d=h-2       ->           1
                     * d=h-1|d=h-2                         d=h-1  |        2
                     *                                               d=h-2 | d=h-2
                     */
                    r_rotate(tree);
                    tree->bf = EH;
                    tree->right->bf = EH;
                    break;
                case RH:
                    /**
                     *                    2
                     *        -1          |       d=h-1
                     * d=h-1   |      rc
                     *           d=h-2|d=h-1
                     *
                     */
                    AVLNode* rc = lc->right;
                    switch (rc->bf) {
                        case LH:
                            //rc: d(left) = h-1, d(right) = h-2
                            lc->bf = EH;
                            tree->bf = RH;
                            rc->bf = EH;
                            break;
                        case EH:
                            //rc: d(left) = h-1, d(right) = h-1
                            //impossible
                            lc->bf = EH;
                            tree->bf =EH;
                            rc->bf = EH;
                            break;
                        case RH:
                            //rc: d(left) = h-2, d(right) = h-1
                            lc->bf = LH;
                            tree->bf = EH;
                            rc->bf = EH;
                            break;
                    }
                    l_rotate(lc);
                    r_rotate(tree);
                    break;
            }
        }

        static void right_balance_tree(AVLNode* &tree) {
            AVLNode* rc = tree->right; //rc not NULL
            switch (rc->bf) {
                case RH:
                    tree->bf =EH;
                    rc->bf =EH;
                    l_rotate(tree);
                    break;
                case LH:
                    /**
                     *                    -2
                     *        d=h-1       |         rc
                     *                       lc   |      d=h-1
                     *                   d=h-2|d=h-1
                     *
                     */
                    AVLNode* lc = rc->left;
                    switch (lc->bf) {
                        case RH:
                            //lc: d(left) = h-1, d(right) = h-2
                            lc->bf = EH;
                            tree->bf = LH;
                            rc->bf = EH;
                            break;
                        case EH:
                            //Lc: d(left) = h-1, d(right) = h-1
                            //impossible
                            lc->bf = EH;
                            tree->bf =EH;
                            rc->bf = EH;
                            break;
                        case LH:
                            //lc: d(left) = h-1, d(right) = h-2
                            lc->bf = RH;
                            tree->bf = EH;
                            rc->bf = EH;
                            break;
                    }
                    r_rotate(rc);
                    l_rotate(tree);
                    break;
            }
        }
};
void pre_order_travelsal_nonrecursive(AVLNode* tree) {
    if (tree == NULL) return;
    stack<AVLNode*> st;
    st.push(tree);
    cout << tree->val << '\t';
    while(!st.empty()) {
        AVLNode* top = st.top();
        if (top->left != NULL) {
            st.push(top->left);
            cout << top->left->val << '\t';
        } else if (top->right != NULL) {
            st.push(top->right);
            cout << top->right->val << '\t';
        } else {
            //pop
            AVLNode* child = top;
            st.pop();
            if (st.empty()) {
                break;
            }
            AVLNode* father = st.top();
            while(child != father->right && father->right == NULL|| child == father->right) {
                st.pop();
                child = father;
                if (st.empty()) {
                    break;
                }
                father = st.top();
            }
            if (!st.empty()) {
                st.push(father->right);
                cout << father->right->val << '\t';
            }
        }
    }
    return;
}
void pre_order_travelsal_norecursive3(AVLNode* tree) {
    AVLNode* p = tree;
    stack<AVLNode*> st;
    cout << p->val << '\t';
    st.push(p);
    while(!st.empty()) {
        p = st.top();
        while(p!=NULL) {
            st.push(p->left);
            p = p->left;
            if (p!=NULL) {
                cout<< p->val << '\t';
            }
        }
        st.pop();   //exit NULL
        if (!st.empyt()) {
            p = st.top();
            st.pop();
            p = p->right;
            st.push(p);
            if (p!= NULL) {
                cout <<p->val << '\t';
            }
        }
    }
}
void pre_order_travelsal_nonrecursive2(AVLNode* tree) {
    AVLNode* p = tree;
    stack<AVLNode*> st;
    while(p!=NULL || !st.empty()) {
        if (p!=NULL) {
            cout << p->val << '\t';
            st.push(p); //push left until NULL
            p = p->left;
        } else {
            p = st.top();
            st.pop();
            p = p->right;
        }
    }
    cout << endl;
}
void mid_order_travelsal_nonrecursive2(AVLNode* tree) {
    AVLNode* p = tree;
    stack<AVLNode*> st;
    while(p!=NULL || !st.empty()) {
        if (p!=NULL) {
            st.push(p); //push left until NULL
            p = p->left;
        } else {
            p = st.top();
            cout << p->val << '\t';
            st.pop();
            p = p->right;
        }
    }
    cout << endl;
}

void pre_order_travelsal(AVLNode* tree) {
    if (tree == NULL) return;
    cout << tree->val << '\t';
    pre_order_travelsal(tree->left);
    pre_order_travelsal(tree->right);
}
void mid_order_travelsal(AVLNode* tree) {
    if (tree == NULL) return;
    mid_order_travelsal(tree->left);
    cout << tree->val << '\t';
    mid_order_travelsal(tree->right);
}
int main(int argc, char** argv) {
    AVLNode* tree = NULL;
    bool taller = false;
    //random
    for(int i=0; i<10; ++i) {
        AVLTree::insert_avl(tree, 9-i, taller);
    }
    //get tree;
    queue<AVLNode*> q;
    cout << "pre_order" << endl;
    pre_order_travelsal(tree);
    cout << endl << "pre_order" << endl;
    pre_order_travelsal_nonrecursive(tree);
    cout << endl << "pre_order" << endl;
    pre_order_travelsal_nonrecursive2(tree);
    cout << endl;
    cout << "mid_order" << endl;
    mid_order_travelsal(tree);
    cout << endl << "mid_order" << endl;
    mid_order_travelsal_nonrecursive2(tree);
    cout <<endl;
    return 0;
}

