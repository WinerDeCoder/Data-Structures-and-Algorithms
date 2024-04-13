#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H
#include "main.h"

struct Node {
    string identifier; // holds the id
    int level;  // holds level
    string type;  //holds type
    Node *parent; // point to the parent
    Node *left; // point to left child
    Node *right; // point to right child
};

typedef Node *TreePtr;

// class SplayTree
class SplayTree {
private:

    TreePtr root;

    void preOrder(TreePtr node,string* rrr) {
        if (node != nullptr) {
           // cout<<node->identifier<<"//"<< node->level<<" ";
            *rrr += node->identifier;
            *rrr+= "//";
            string ee= to_string(node->level);
            *rrr+= ee;
            *rrr+=" ";
            preOrder(node->left,rrr);
            preOrder(node->right,rrr);
        }
    }

    TreePtr searchVIPP(TreePtr node, string id,int level,int *compare,int* splaytime) {
        if (node == nullptr || (node->identifier == id && level == node->level)) {      // node = nullptr or root is id
            *compare = *compare +1;
            return node;
        }
        if (level > node->level || (level == node->level && (node->identifier).compare(id) < 0)) {
          //  *compare = *compare +1;
            if(node->right == nullptr){
                return node;
            }
            *compare = *compare +1;
            return searchVIPP(node->right, id,level,compare,splaytime);
        }
        else if(level < node->level || (level == node->level && (node->identifier).compare(id) > 0)) {

            if (node->left == nullptr) {
                return node;
            }
            *compare = *compare +1;
            return searchVIPP(node->left, id,level,compare,splaytime);
        }
        return node;
    }

    void destroy(TreePtr x){
        if(x == nullptr){
            return;
        }
        else{
            destroy(x->left);
            destroy(x->right);
            delete(x);
        }
    }

    void deleteNode(TreePtr node, string id,int level,int* splaytime) {
        TreePtr x = nullptr;
        TreePtr n, m;
        while (node != nullptr){        // find id in tree
            if ( node->identifier == id && node->level == level) {
                x = node;
            }
            if ( node->level < level || (node->level == level && (node->identifier).compare(id) <= 0 ) ) {
                node = node->right;
            }
            else if(node->level > level || (node->level == level && (node->identifier).compare(id) > 0 )) {
                node = node->left;
            }
        }
        if (x == nullptr) {    // not exist
            return;
        }
        split(x, m, n,splaytime); // split the tree
        if (m->left){ // remove x
            m->left->parent = nullptr;
        }
        root = join(m->left, n,splaytime);
        delete(m);
        m = nullptr;
    }

    // rotate right
    void rightRotate(TreePtr x) {
        TreePtr y = x->left;
        x->left = y->right;
        if (y->right != nullptr) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        }
        else if (x == x->parent->right) {
            x->parent->right = y;
        }
        else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    // rotate left
    void leftRotate(TreePtr x) {
        TreePtr y = x->right;
        x->right = y->left;
        if (y->left != nullptr) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        }
        else if (x == x->parent->left) {
            x->parent->left = y;
        }
        else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }
    
    void splay(TreePtr x, int* splaytime) {
        *splaytime = *splaytime +1;
        while (x->parent) {
            if (!x->parent->parent) {
                if (x == x->parent->left) {
                    // zig 
                  //  *splaytime = *splaytime +1;
                    rightRotate(x->parent);
                }
                else {
                    // zag 
                   // *splaytime = *splaytime +1;
                    leftRotate(x->parent);
                }
            }
            else if (x == x->parent->left && x->parent == x->parent->parent->left) {
                // zig-zig 
                //*splaytime = *splaytime +1;
                rightRotate(x->parent->parent);
                rightRotate(x->parent);
            }
            else if (x == x->parent->right && x->parent == x->parent->parent->right) {
                // zag-zag 
               // *splaytime = *splaytime +1;
                leftRotate(x->parent->parent);
                leftRotate(x->parent);
            }
            else if (x == x->parent->right && x->parent == x->parent->parent->left) {
                // zig-zag 
              //  *splaytime = *splaytime +1;
                leftRotate(x->parent);
                rightRotate(x->parent);
            }
            else {
                // zag-zig 
              //  *splaytime = *splaytime +1;
                rightRotate(x->parent);
                leftRotate(x->parent);
            }
        }
    }

    // joins two trees 
    TreePtr join(TreePtr m, TreePtr n,int *splaytime){
        if (!m) {
            return n;
        }
        if (!n) {
            return m;
        }
        TreePtr x = max(m);   // lay max cua left subtree
        splay(x,splaytime);   //splay max len
        x->right = n;
        n->parent = x;
        return x;
    }

    // splits the tree into 2 news
    void split(TreePtr &x, TreePtr &m, TreePtr &n, int* splaytime) {
        splay(x,splaytime);
        if (x->right) {
            n = x->right;
            n->parent = nullptr;
        }
        else {
            n = nullptr;
        }
        m = x;
        m->right = nullptr;
        x = nullptr;
    }

public:
    SplayTree() {
        root = nullptr;
    }
    // search the tree for the id
    TreePtr searchVIP(string id, int level, int* compare, int* splaytime){
        if(this->root ==nullptr){
            return nullptr;
        }
        int i=level;
        TreePtr x;
        int k= 0;
        while(i>=0){
            x = searchVIPP(this->root,id,i,&k,splaytime);

            if((x->identifier) == id && x->level == i){
                *compare +=k;
                if(x == getRoot()){
                    return x;
                }
                splay(x,splaytime);
              //  *splaytime = *splaytime +1;
                return x;
            }
            k=0;
            i--;
        }
        splay(x,splaytime);
        return x;
    }

    int searchVIPPP(string id, int level, int* t, int* j){
        if(this->root ==nullptr){
            return 0;
        }
        int i=level;
        while(i>=0){
            TreePtr x = searchVIPP(this->root,id,i,t,j);
            if((x->identifier) == id && x->level == level){
                return 1;
            }
            i--;
        }
        return 0;
    }

    int searchROOT(string id,string type){
        TreePtr x = this->root;
        if ((x->identifier)== id && (x->type) == type) {  // correct
            return 0;
        }
        else if ((x->identifier) == id && (x->type)!= type) {   // different type
            return -1;
        }
        else {
            return 1;  // undeclared
        }
    }

    // find the node with the maximum id
    TreePtr max(TreePtr node) {
        while (node->right != nullptr) {
            node = node->right;
        }
        return node;
    }

    // insert the id to the tree
    void insert(string id,string type, int level,string line,int* compare,int* splaytime) {
        // normal splay insert
        TreePtr node = new Node;
        node->parent = nullptr;
        node->left = nullptr;
        node->right = nullptr;
        node->identifier = id;
        node->level = level;
        node->type = type;
        TreePtr y = nullptr;
        TreePtr x = this->root;
        while (x != nullptr) {
            *compare = *compare +1;
            y = x; //yy
            if ( node->level < x->level || (node->level == x->level  && (x->identifier).compare(id) > 0)) {
                x = x->left;
            }
            else {
                x = x->right;
            }
        }
        // y is parent of x
        node->parent = y;
        if (y == nullptr) {
            root = node;

        }
        else if (node->level < y->level || (node->level == y->level  && (y->identifier).compare(id) > 0)) {
            y->left = node;
            splay(node, splaytime);
        }
        else if(node->level > y->level || (node->level == y->level  && (y->identifier).compare(id) < 0)) {
            y->right = node;
            splay(node, splaytime);
        }

    }

    // Pre-Order traversal
    void preorder(string* rrr) {
        preOrder(this->root,rrr);
    }

    TreePtr getRoot(){
        return this->root;
    }

    // delete the node from the tree
    void deleteNode(string identifier,int level,int*splaytime) {
        deleteNode(this->root, identifier,level,splaytime);
    }

    string RootID(){
        if(this->root == nullptr){
            return "@(06&^^&*()%$)(_+$%^&**!@!@!@!@!@WEWWEWEDWDWDUWDUWDH  __++_)(*&";
        }
        return this->root->identifier;
    }

    string RootType(){
        if(this->root == nullptr){
            return "@(06&^^&*()%$)(_+$%^&**!@!@!@!@!@WEWWEWEDWDWDUWDUWDH  __++_)(*&";
        }
        return this->root->type;
    }
    // print the tree structure on the screen
    int Empty(){
        if(this->root == nullptr){
            return 0;
        }
        return 1;
    }

    void destroytree(){
        destroy(this->root);
    }
    friend class SymbolTable;
    friend class node;
};

class node{  // new linked li to store position when deleting
    string idd;
    int block_level;
    node* next;
public:
    node(string key,int level){
        this->idd = key;
        this->block_level = level;
        this->next = nullptr;
    }
    friend class SplayTree;
    friend class SymbolTable;
};

class SymbolTable
{
    node* head[100];
public:

    void insertt(node** head, string key, int level);  // insert vao 1 cai linked de xoa node theo thu tu

    int check_type(string value) ;

    bool check_iden(string iden);

    void deletenode(node** head);

    void run(string filename);
};
#endif