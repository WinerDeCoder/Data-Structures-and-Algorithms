#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H
#include "main.h"

const int MAX = 100;
class Node {            // main linked l to store symbol table

    string identifier, value, type;
    int block_level;
    Node* next;

public:
    
    Node(string id, string type,int block_level, string value)
    {
        this->identifier = id;       // identifier
        this->type = type;               
        this->block_level = block_level;         
        this->value = value;          
        next = NULL;
    }  
    friend class SymbolTable;
    friend class Node2;
};
class Node2 {         // linked l to use PRINT
public:

    string id;
    int level;
    Node2* nextt;

public:

    Node2(string id, int level) {
        this->id = id;
        this->level = level;
        nextt = NULL;
    }

    friend class SymbolTabale;
    
};

class SymbolTable
{
    Node* head[MAX];
    Node2* head2[MAX];

public:

    SymbolTable() {
        for (int i = 0; i < MAX; i++) {
            head[i] = NULL;
        }
        for (int j = 0; j < MAX; j++) {
            head2[j] = NULL;
        }
    }

    bool check_id(string id, int block_level, Node** head);      // check id for inserting

    bool check_idd(string id, int block, Node** head);          // check id 

    int check_id_type(string id, int block, string type, Node** head);       // check id and type for assigning

    bool check_number(string id, int block, Node** head);          // check type is number or not

    bool check_block(Node* tmp, Node** head);            // check block level

    string get_type(string id, int block, Node** head);        // return string of type

    void assign_value(string id, string value, int level, Node** head);           //  assign value to an id

    void assign_value2(string id, string idd, int block_level, Node** head);       // assign value to an id of Node2

    void insert(string id,string Type, int block_level, Node** head);               // Inserting new node

    void insert2(string name, int block, Node2** head2);                        //  Inserting new node of Node2

    bool find(string id, Node2** head2);                                  // Find in the second linked  exist a node with the same id or not

    void del_node2(string id, Node2** head2);                           // delete a node in linked l 2 when inserting a new node that has same id

    void print_linkednist2(Node2** head2, int index);                       // PRINT / RPRINT

    void call_print(Node** head, Node2** head2,int level) ;                     //  Call this function when see PRINT/RPRINT

    void insert_else(string id, string type, int block_level, Node** head);        // insert node BEGIN, END and ASSIGN for checking

    void lookup(string id, int block, Node** head, string line,int countp);           // LOOKUP

    void deletenist(Node** head);                                   // Delete main linked l

    void deletenist2(Node2** head2);                        // Delete second linked l

    void run(string filename);   
};
#endif



