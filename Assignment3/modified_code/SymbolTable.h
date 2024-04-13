#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H
#include "main.h"

class hashing{
private:
    long long index;
    long long key;
 //   string value;
    int size ;
    long long* aray = new long long[size];
public:

 /*   hashing(){
        for(int i=0;i<20;i++){
            aray[i] = -1;
        }
    }
 */
    void create_aray( int size){
       //  aray[size];
         for(int i=0;i<size;i++) {
             aray[i] = -1;
         }
    }

    void delete_array(){
        delete[] aray;
    }

    void Size(int sizee){
        size = sizee;
        create_aray(size);
    }

    long long Converter(string value,int block_level){
        string keyy;
        keyy += to_string(block_level);
        int v = value.length();
        for(int i=0;i<v;i++){
            keyy+= to_string(int(value[i])-48);
        }
        int f = keyy.length();
        long long con=(keyy[0]-48);
        //   int x=0;
        for(int a=1;a<f;a++){
            con = con*10 + (keyy[a]-48);
        }
        key = con;
        return key;
        return key ; // k mod m
    }

    int find_id(string id,int block_level,int constant, int constant2, int type){
        index = (Converter(id,block_level)) % size;  // h(k)
        long long temp = index;
        int k=size+11;  // out of size
        int c=1;  // probing progress
        int b=0;
        if(type ==1) {  // type linear probing
            while ( k != 0) {

                if(aray[temp] == key){  // if key already exist
                    return b;
                }
                temp = index + c * constant;  // h(x) + c*i
                temp = temp % size;
                c++;
                b++;
                k--;
            }
        }
        else if(type ==2){  // type quadratic probing
            while (aray[temp] != -1 && k != 0) {

                if(aray[temp] == key){  // if key already exist
                    return b;
                }
                temp = index + c * constant + c*c*constant2;  // h(x) + c*i + c^2*i
                temp = temp % size;
                k--;
                b++;
                c++;
            }
        }
        else if(type == 3){  //type double probing
            /* h2(k) = 1 + (k mod (m − 2))
             hp(k, i) = (h1(k) + cih2(k)) mod m  */
            int h2 = 1+(Converter(id,block_level) % (size-2)); // h2(k) = 1 + (k mod (m − 2))
            while (aray[temp] != -1 && k != 0) {

                if(aray[temp] == key){  // if key already exist
                    return b;
                }
                temp = index + c * constant*h2;  // hhp(k, i) = (h1(k) + cih2(k)) mod m
                temp = temp % size;
                k--;
                c++;
                b++;
            }
        }
        return 0;
    }

    int find_index(string value,int block_level){
        key = (Converter(value,block_level));
        int n=0;
        while(n<size){
            if(aray[n] == key){
                return n;
            }
            n++;
        }
        return -1;
    }

    int insert(string value, int block_level, int constant, int constant2, int type, int * step){
        index = (Converter(value,block_level)) % size;  // h(k)
        long long temp = index;
        int k=size +4;  // out of size
        int c=1;  // probing progress
        if(type ==1) {  // type linear probing
            while (aray[temp] != -1 && k != 0) {
                if(aray[temp] == key){  // if key already exist
                   // cout<<value<<endl;
                    return -4;
                }
                temp = index + c * constant;  // h(x) + c*i
                temp = temp % size;
                k--;
                c++;
                *step = *step +1;
            }
        }
        else if(type ==2){  // type quadratic probing
            while (aray[temp] != -1 && k != 0) {
                if(aray[temp] == key){  // if key already exist
                  //  cout<<"2"<<endl;
                    return -4;
                }
                temp = index + c * constant + c*c*constant2;  // h(x) + c*i + c^2*i
                temp = temp % size;
                k--;
                c++;
                *step = *step +1;
            }
        }
        else if(type == 3){  //type double probing
           /* h2(k) = 1 + (k mod (m − 2))
            hp(k, i) = (h1(k) + cih2(k)) mod m  */
           int h2 = 1+(Converter(value,block_level) % (size-2)); // h2(k) = 1 + (k mod (m − 2))
            while (aray[temp] != -1 && k != 0) {
                if(aray[temp] == key){  // if key already exist
                   // cout<<"3"<<endl;
                    return -4;
                }
                temp = index + c * constant*h2;  // hhp(k, i) = (h1(k) + cih2(k)) mod m
                temp = temp % size;
                k--;
                c++;
                *step = *step +1;
            }
        }
        if(k==0){
            return (int)-999;
        }
        else{
            aray[temp] = key;
            return temp;
        }
       // key = -1;
    }


    int search(int index){
        if(aray[index] != -1){
            return index;
        }
        return -1;
    }

    void delete_level(string value, int block_level, int constant, int constant2, int type, int * step){
        index = (Converter(value,block_level)) % size;  // h(k)
        int temp = index;
        int k=size +11;  // out of size
        int c=1;  // probing progress
        if(type ==1) {  // type linear probing
            while (aray[temp] != -1 && k != 0) {
                if(aray[temp] == key){  // if key already exist
                    // cout<<value<<endl;
                    aray[temp] = -1;
                }
                temp = index + c * constant;  // h(x) + c*i
                temp = temp % size;
                k--;
                c++;
                *step = *step +1;
            }
        }
        else if(type ==2){  // type quadratic probing
            while (aray[temp] != -1 && k != 0) {
                if(aray[temp] == key){  // if key already exist
                    aray[temp] = -1;
                }
                temp = index + c * constant + c*c*constant2;  // h(x) + c*i + c^2*i
                temp = temp % size;
                k--;
                c++;
                *step = *step +1;
            }
        }
        else if(type == 3){  //type double probing
            /* h2(k) = 1 + (k mod (m − 2))
             hp(k, i) = (h1(k) + cih2(k)) mod m  */
            int h2 = 1+(Converter(value,block_level) % (size-2)); // h2(k) = 1 + (k mod (m − 2))
            while (aray[temp] != -1 && k != 0) {
                if(aray[temp] == key){  // if key already exist
                    aray[temp] = -1;
                }
                temp = index + c * constant*h2;  // hhp(k, i) = (h1(k) + cih2(k)) mod m
                temp = temp % size;
                k--;
                c++;
                *step = *step +1;
            }
        }
        return ;
    }

    void print(){
        for(int i=0;i<size;i++){
            cout<<"Number "<<i<<" :"<<aray[i]<<endl;
        }
    }
    friend class node;
    friend class SymbolTable;
};

class node{  // new linked li to store position when deleting
    string id;
    int block_level;
    string type;
    node* next;
    string parameter;
    int type_for_ham;
public:
    node(string key,int level,string type,string parameter,int type_for_ham){
        this->id = key;
        this->block_level = level;
        this->type = type;
        this->parameter = parameter;
        this->type_for_ham = type_for_ham;   // 1 la number , 2 la string,  ---- kieu tra ve cua ham
        this->next = nullptr;
    }

    friend class hashing;
    friend class SymbolTable;
};
#define MAX 9999
class SymbolTable
{
    node* head[MAX];
public:
    SymbolTable() {}
    void putvalue(node** head, string value,int index,int block_level,string type,int type_for_ham);
    void makeit(node**head,int number);  // tao 1 size linked
    void printed(node** head,int index,int end);
    void count(node**head);    // dem so linked va in ra cac hold
    int findnodetype(node** head,string id,int block_level);   //
    void sect_type(node** head,string id,int block_level,string type);   // sect type cho 1 node
    node* get_node(node**head, string id,int block_level);   // take out a node
    void deletenode(node** head);
    bool check_iden(string iden);
 // bool check_number(string value);
    int check_type(string value);
    void run(string filename);

    friend class node;
    friend class hashing;
};
#endif