#include "SymbolTable.h"

void SymbolTable::makeit(node** head, int number) {
    *head = new node("", -1, "", "", -1);
    node* start = *head;
    //   node* temp = head;
    while (number > 1) {
        start->next = new node("", -1, "", "", -1);
        start = start->next;
        number--;
    }
}

void SymbolTable::printed(node** head,int index,int end){
    int temp =0;
    node* start = *head;
    while(temp < index){
        start = start->next;
        temp++;
    }
    if(end==0) {
        cout << index << " " << start->id << "//" << start->block_level << ";";
    }
    else{
        cout << index << " " << start->id << "//" << start->block_level;
    }
}

void SymbolTable::putvalue(node** head, string value, int index, int block_level, string type, int type_for_ham) {
    node* start = *head;
    while (index > 0) {             // quy uoc 0 la chua co type, 1 la num, 2 la string
        start = start->next;
        index--;
    }
    start->id = value;
    start->block_level = block_level;
    start->type = type;
    start->type_for_ham = type_for_ham;
    if (type != "number" || type != "string") {  // gan cac kieu parameter cho ham only
        int  num = 0;
        int k = type.length();
        int n = 3;
        while (n< k) {
            //   a = a*10 + (int(sizee[i])-48);
            num = num * 10 + (int(type[n]) - 48);
            n++;
        }
        string paramete ;
        while (num > 0) {
            paramete += "0";
            num--;
        }
        paramete += "0";
        start->parameter = paramete;
    }
}
/*
void SymbolTable::count(node** head) {
    node* start = *head;
    int cou = 0;
    while (start != nullptr) {
        cout << "Linked " << cou << ": " << start->id << "//" << start->block_level << "//" << start->type << "//" << start->type_for_ham << "//" << start->parameter << endl;
        cou++;
        start = start->next;
    }
    cout << "Number of linked: " << cou << endl;
}
*/
int SymbolTable::findnodetype(node** head, string id, int block_level) {
    node* start = *head;
    while (start != nullptr) {
        if (start->id == id && start->block_level == block_level) {
            if (start->type.empty()) {   // sect new type
                // start->type = type;
                return 1;
            }
            else if (start->type == "number") {  // number
                return 2;
            }
            else if (start->type == "string") {  // string
                return 3;
            }
            else {
                return 4;   // ham
            }
        }
        start = start->next;
    }
    return 0;   // dont have
}

void SymbolTable::sect_type(node** head, string id, int block_level, string type) {
    node* start = *head;
    while (start != nullptr) {
        if (start->id == id && start->block_level == block_level) {
            start->type = type;
            return;
        }
        start = start->next;
    }
    return;
}

node* SymbolTable::get_node(node** head, string id, int block_level) {  // lay 1 node ra

    while (block_level >= 0) {
        node* start = *head;

        while (start != nullptr) {
            if (start->id == id && start->block_level == block_level) {
                return start;
            }
            start = start->next;
        }
        block_level--;
    }
    return nullptr;
}

void SymbolTable::deletenode(node** head)
{
    if (*head == nullptr) {
    }
    else {
        node* current = *head;
        node* next = nullptr;

        while (current != nullptr)
        {
            next = current->next;
            delete(current);
            current = next;
        }
        *head = nullptr;
    }
}


bool SymbolTable::check_iden(string iden) {
    /*  if(iden == "number" || iden == "string" || iden == "true" || iden == "false" ||  iden == "for" || iden == "else" || iden == "while"||iden=="return"){
          return false;
      }
      else if(iden=="int"||iden=="double" || iden=="cout"||iden =="bool"||iden =="void" ||iden =="throw"||iden =="class"|| iden =="struct"||iden =="char"){
          return false;
      }
      else if(iden =="continue"||iden=="break"||iden=="switch"||iden =="case"||iden=="enum"||iden=="register"||iden=="typedef"||iden=="union"){
          return false;
      }
      else if(iden=="const"||iden=="float"||iden=="short"||iden=="unsigned"||iden=="signed"||iden=="default"||iden=="goto"||iden=="volatile"||iden=="do"){
          return false;
      }
      else if(iden=="if"||iden=="static"||iden=="private"||iden=="protected"||iden=="try"||iden=="catch"||iden=="dynamic_cash"||iden=="reinterpret_cast"||iden=="public"||iden=="const_cast"||iden=="explicit"||iden=="new"||iden=="asm"||iden=="static_cast"||iden=="this"||iden=="operator"||iden=="namespace"||iden=="typeid"||iden=="typename"||iden=="friend"||iden=="template"||iden=="using"||iden=="virtual"||iden=="delete"||iden=="inline"||iden=="mutable"||iden=="wchar_t"||iden=="bool"||iden=="And"||iden=="bitor"||iden=="not_eq"||iden=="xor"||iden=="and_eq"){
          return false;
      }
      else if(iden=="compl"||iden=="or"||iden=="xor_eq"||iden=="bitand"||iden=="not"||iden=="or_eq"||iden=="export"||iden=="explicit"){
          return false;
      }
      else if(iden=="short"||iden=="co_await"||iden=="constexpr"||iden=="char43_t"||iden=="char16_t"||iden=="co_return"||iden=="co_yield"||iden=="decltype"||iden=="nullptr"||iden=="thread_local"||iden=="wchar_t"||iden=="static_assert"||iden=="requires"||iden=="noexcept"){
          return false;
      } */
    int t = iden.length();
    if (t == 1) {
        if (iden[0] < 'a' || iden[0] > 'z') {
            return false;
        }
    }
    else {
        if (iden[0] < 'a' || iden[0] > 'z') {
            return false;
        }
        for (int i = 1; i < t; i++) {
            if ((iden[i] >= 'a' && iden[i] <= 'z') || (iden[i] >= 'A' && iden[i] <= 'Z') || iden[i] == '_' || (iden[i] >= '0' && iden[i] <= '9')) {

            }
            else {
                return false;
            }
        }
    }
    return true;
}

/* bool SymbolTable::check_number(string value) {
    int len = value.length();
    for (int i = 0; i < len; i++) {
        if (value[i] < '0' && value[i] > '9') {
            return false;
        }
    }
    return true;
}
 */

int SymbolTable::check_type(string value) {
    int r = value.length();
    if (r == 0) {
        return 6;  // empty
    }
    int count_number = 0;
    int count_word = 0;
    int count_nhay = 0;
    int count_ngoac = 0;
    int b = value.length() - 1;
    if (value[0] == '\'') {
        count_nhay++;
    }
    if (value[b] == '\'') {
        count_nhay++;
    }
    if (value[b] == ')') {
        count_ngoac++;
    }
    if (count_ngoac == 1) {
        if (value[0] >= 'a' && value[0] <= 'z') {
            int a = 1;
            while (value[a] != '\0') {
                if (value[a] == '(') {
                    count_ngoac++;
                }
                a++;
            }
            if (count_ngoac == 2) {
                return 5;  // ham
            }
        }
    }
    if (count_nhay == 0) {
        for (int i = 0; i < b + 1; i++) {
            if (value[i] >= '0' && value[i] <= '9') {
                count_number++;
            }
            else if ((value[i] >= 'a' && value[i] <= 'z') || (value[i] >= 'A' && value[i] <= 'Z') || value[i] == '_') {
                count_word++;
            }
        }
        if (count_number == (b + 1)) {
            return 1;  //number
        }
        else if (count_word + count_number == (b + 1) && (value[0] >= 'a' && value[0] <= 'z')) {
            return 4;    // iden
        }
        else {
            return 3;    // nothing
        }
    }
    else if (count_nhay == 2) {
        for (int i = 1; i < b; i++) {
            if ((value[i] >= '0' && value[i] <= '9') || (value[i] >= 'a' && value[i] <= 'z') || (value[i] >= 'A' && value[i] <= 'Z') || value[i] == ' ') {
                count_number++;
            }
        }
        if (count_number == (b - 1)) {
            return 2;  // string
        }
        else {
            return 3;   // nothing
        }
    }
    return 3;

}

void SymbolTable::run(string filename)
{
    ifstream fileInput(filename);
    hashing table;
    node* head = nullptr;
    int block_level = 0; // int countp = 0;
    int first = 0;
    int type_probing;
    int constant1=0, constant2=0;
    int size;
    while (!fileInput.eof()) {
        string line;
        getline(fileInput, line);
        char insert[] = "INSERT ";
        char assign[] = "ASSIGN ";
        char begin[] = "BEGIN";
        char end[] = "END";
        char lookup[] = "LOOKUP ";
        char print[] = "PRINT";
        char linear[] = "LINEAR";
        char quadratic[] = "QUADRATIC";
        char doublehash[] = "DOUBLE";
        char call[] = "CALL";
        int search_insert = line.find(insert);
        int search_assign = line.find(assign);
        int search_begin = line.find(begin);
        int search_end = line.find(end);
        int search_lookup = line.find(lookup);
        int search_print = line.find(print);
        int search_linear = line.find(linear);
        int search_quadratic = line.find(quadratic);
        int search_doublehash = line.find(doublehash);
        int search_call = line.find(call);
        int step = 0;
        if (search_linear != -1) {
            if (first != 0) {
                deletenode(&head);
                throw InvalidInstruction(line);
            }
            type_probing = 1;
            int n = 7;
            string sizee;
            string constantt1;
            while (line[n] != ' ') {
                sizee += line[n];
                n++;
                if(n>=(int)line.length()){
                    deletenode(&head);
                    throw InvalidInstruction(line);
                }
            }
            n++;
            line += "@";
            while (line[n] != '@') {
                constantt1 += line[n];
                n++;
            }
            line.pop_back();
            int len1 = sizee.length();
            int len2 = constantt1.length();
            int a = 0;  // bien tam
            for (int i = 0; i < len1; i++) {  // lay so size
                a = a * 10 + (int(sizee[i]) - 48);
            }
            size = a;
            makeit(&head, size);
            a = 0;
            for (int i = 0; i < len2; i++) {  // lay so constant
                a = a * 10 + (int(constantt1[i]) - 48);
            }
            constant1 = a;
            table.Size(size);
            first++;
        }
        else if (search_quadratic != -1) {
            if (first != 0) {
                deletenode(&head);
                throw InvalidInstruction(line);
            }
            type_probing = 2;
            int n = 10;
            string sizee;
            string constantt1;
            string constantt2;
            while (line[n] != ' ') {
                sizee += line[n];
                n++;
                if(n>=(int)line.length()){
                    deletenode(&head);
                    throw InvalidInstruction(line);
                }
            }
            n++;
            while (line[n] != ' ') {
                constantt1 += line[n];
                n++;
                if(n>=(int)line.length()){
                    deletenode(&head);
                    throw InvalidInstruction(line);
                }
            }
            n++;
            line += "@";
            while (line[n] != '@') {
                constantt2 += line[n];
                n++;
            }
            line.pop_back();
            int len1 = sizee.length();
            int len2 = constantt1.length();
            int len3 = constantt2.length();
            int a = 0;  // bien tam
            for (int i = 0; i < len1; i++) {  // lay so size
                a = a * 10 + (int(sizee[i]) - 48);
            }
            size = a;
            makeit(&head, size);
            a = 0;
            for (int i = 0; i < len2; i++) {  // lay so constant
                a = a * 10 + (int(constantt1[i]) - 48);
            }
            constant1 = a;
            a = 0;
            for (int i = 0; i < len3; i++) {  // lay so constant
                a = a * 10 + (int(constantt2[i]) - 48);
            }
            constant2 = a;
            table.Size(size);
            first++;
        }
        else if (search_doublehash != -1) {
            if (first != 0) {
                deletenode(&head);
                throw InvalidInstruction(line);
            }
            type_probing = 3;
            int n = 7;
            string sizee;
            string constantt1;
            while (line[n] != ' ') {
                sizee += line[n];
                n++;
                if(n>=(int)line.length()){
                    deletenode(&head);
                    throw InvalidInstruction(line);
                }
            }
            n++;
            line += "@";
            while (line[n] != '@') {
                constantt1 += line[n];
                n++;

            }
            line.pop_back();
            int len1 = sizee.length();
            int len2 = constantt1.length();
            int a = 0;  // bien tam
            for (int i = 0; i < len1; i++) {  // lay so size
                a = a * 10 + (int(sizee[i]) - 48);
            }
            size = a;
            makeit(&head, size);
            a = 0;
            for (int i = 0; i < len2; i++) {  // lay so constant
                a = a * 10 + (int(constantt1[i]) - 48);
            }
            constant1 = a;
            table.Size(size);
            first++;
        }
        else if (search_insert != -1) {
            if (first == 0) {
                deletenode(&head);
                throw InvalidInstruction(line);
            }
            int n = 7;
            int count_space = 0;
            int d = 0;
            line += "@";
            while (line[d] != '@') {
                if (line[d] == ' ') {
                    count_space++;
                }
                d++;
            }
            line.pop_back();
            if (count_space == 2) {
                string id;
                string parameter;
                while (line[n] != ' ') {
                    id += line[n];
                    n++;
                    if(n>=(int)line.length()){
                        deletenode(&head);
                        throw InvalidInstruction(line);
                    }
                }
                n++;
                line += "@";
                while (line[n] != '@') {
                    parameter += line[n];
                    n++;
                }
                line.pop_back();
                if(!check_iden(id)){
                    deletenode(&head);
                    throw InvalidInstruction(line);
                }
                if(check_type(parameter) != 1){
                    deletenode(&head);
                    throw InvalidInstruction(line);
                }
                if(block_level != 0){
                    deletenode(&head);
                    throw InvalidDeclaration(id);
                }
                int index = table.insert(id, block_level, constant1, constant2, type_probing, &step);
                if(index == -999){
                    deletenode(&head);
                    throw Overflow(line);
                }
                if(index ==-4){
                    deletenode(&head);
                    throw Redeclared(id);
                }
                putvalue(&head, id, index, block_level, "ham" + parameter, 0);
                //   cout<<"hu"<<endl;
                cout << step << endl;
            }
            else {
                string id;
                line+= "@";
                while (line[n] != '@') {
                    id += line[n];
                    n++;
                }
                line.pop_back();
                //  cout<<id<<endl;
                if(!check_iden(id)){
                    deletenode(&head);
                    throw InvalidInstruction(line);
                }
                int index = table.insert(id, block_level, constant1, constant2, type_probing, &step);
                if(index == -999){
                    deletenode(&head);
                    throw Overflow(line);
                }
                if(index ==-4){
                    deletenode(&head);
                    throw Redeclared(id);
                }
                putvalue(&head, id, index, block_level, "", -1);
                cout << step << endl;
            }
        }
        else if (search_assign != -1) {
            if (first == 0) {
                deletenode(&head);
                throw InvalidInstruction(line);
            }
            string id;
            string value;
            int n = 7;
            while (line[n] != ' ') {   // take id
                id += line[n];
                n++;
                if(n>=(int)line.length()){
                    deletenode(&head);
                    throw InvalidInstruction(line);
                }
            }
            n++;
            line += "@";
            while (line[n] != '@') {  // take value behind
                value += line[n];
                n++;
            }
            line.pop_back();
            if(!check_iden(id)){
                deletenode(&head);
                throw InvalidInstruction(line);
            }
            //  cout<<value<<endl;
            int type = check_type(value);
            //  cout<<value<<endl;
            if (type == 1) {   //number
                int temp_level = block_level;
                int num;
                while (temp_level >= 0) {  // find each level
                    num = findnodetype(&head, id, temp_level);
                    //  cout<<"fuck";
                    if (num == 1) {  // Empty
                        // cout<<"you";
                        step = table.find_id(id, temp_level, constant1, constant1, type_probing);
                        //   cout<<"bif";
                        sect_type(&head, id, temp_level, "number");
                        //  cout<<"dam";
                        cout << step << endl;
                        break;
                    }
                    else if (num == 2) {    // number
                        step = table.find_id(id, temp_level, constant1, constant1, type_probing);
                       // sect_type(&head, id, temp_level, "number");
                        cout << step << endl;
                        break;
                    }
                    else if (num == 3 || num == 4) {  // string or ham
                        deletenode(&head);
                        throw TypeMismatch(line);
                    }
                    if(temp_level==0){
                        deletenode(&head);
                        throw Undeclared(id);
                    }
                    temp_level--;
                }


            }
            else if (type == 2) {   // string
                int temp_level = block_level;
                int num;
                while (temp_level >= 0) {
                    num = findnodetype(&head, id, temp_level);

                    if (num == 1) {  // Empty
                        step = table.find_id(id, temp_level, constant1, constant1, type_probing);
                        sect_type(&head, id, temp_level, "string");
                        cout << step << endl;
                        break;
                    }
                    else if (num == 3) {    // string
                        step = table.find_id(id, temp_level, constant1, constant1, type_probing);
                        cout << step << endl;
                        break;
                    }
                    else if (num == 2 || num == 4) {
                        deletenode(&head);
                        throw TypeMismatch(line);
                    }
                    if(temp_level==0){
                        deletenode(&head);
                        throw Undeclared(id);
                    }
                    temp_level--;
                }
            }
            else if (type == 3) {   // nothing
                deletenode(&head);
                throw InvalidInstruction(line);
            }
            else if (type == 4) {   // identifier
                int temp_level = block_level;
                int num;
                if(!check_iden(value)){
                    deletenode(&head);
                    throw InvalidInstruction(value);
                }
                while (temp_level >= 0) {
                    num = findnodetype(&head, value, temp_level); // lay kieu cua value
                    if (num != 0) {
                        break;
                    }
                    temp_level--;
                }
                if ( num == 0) {
                    deletenode(&head);
                    throw Undeclared(value);
                }
                int numdu;
                int temp_level1 = block_level;
                while (temp_level1 >= 0) {
                    numdu = findnodetype(&head, id, temp_level1); // lay kieu cua id
                    if (numdu != 0) {
                        break;
                    }
                    temp_level1--;
                }
                if (numdu == 0 ) {
                    deletenode(&head);
                    throw Undeclared(id);
                }
                if (num == numdu && (num == 2 || num == 3)) {    // case same number // string
                    int firstt = table.find_id(value, temp_level, constant1, constant2, type_probing);
                    int second = table.find_id(id, temp_level1, constant1, constant2, type_probing);
                    cout << firstt + second << endl;
                }
                else if (num == 1 && numdu == 2) {   // number - empty
                    int firstt = table.find_id(value, temp_level, constant1, constant2, type_probing);
                    int second = table.find_id(id, temp_level1, constant1, constant2, type_probing);
                    sect_type(&head, value, temp_level, "number");
                    cout << firstt + second << endl;
                }
                else if (num == 1 && numdu == 3) {  //string empty
                    int firstt = table.find_id(value, temp_level, constant1, constant2, type_probing);
                    int second = table.find_id(id, temp_level1, constant1, constant2, type_probing);
                    sect_type(&head, value, temp_level, "string");
                    cout << firstt + second << endl;
                }
                else if (num == 2 && numdu == 1) {   //empty - number
                    int firstt = table.find_id(value, temp_level, constant1, constant2, type_probing);
                    int second = table.find_id(id, temp_level1, constant1, constant2, type_probing);
                    sect_type(&head, id, temp_level1, "number");
                    cout << firstt + second << endl;
                }
                else if (num == 3 && numdu == 1) {  //empty - string
                    int firstt = table.find_id(value, temp_level, constant1, constant2, type_probing);
                    int second = table.find_id(id, temp_level1, constant1, constant2, type_probing);
                    sect_type(&head, id, temp_level1, "string");
                    cout << firstt + second << endl;
                }
                else if (num == 1 && numdu == 1) {
                    deletenode(&head);
                    throw TypeCannotBeInferred(line);
                }
                else if (numdu == 4) {
                    deletenode(&head);
                    throw TypeMismatch(line);
                }
                else if((numdu==2 && num ==3) || (numdu ==3 && num ==2)){
                    deletenode(&head);
                    throw TypeMismatch(line);
                }
            }
            else if (type == 5) {  //function
                //  cout<<"here1"<<endl;
                string iden;
                int i = 0;
                while (value[i] != '(') {  // lay ten function
                    iden += value[i];
                    i++;
                }
                if (!check_iden(iden)) {
                    deletenode(&head);
                    throw InvalidInstruction(line);
                }
                string inside = "";
                i++;
                if (value[i] == ')') {  // case function()
                    node* x = get_node(&head, iden, block_level);
                    if (x == nullptr ) {
                        deletenode(&head);
                        throw Undeclared(iden);
                    }
                    if (x->type == "ham0") {
                        node* y = get_node(&head, id, block_level);
                        //  cout<<"here2"<<endl;
                        if ( y == nullptr) {
                            deletenode(&head);
                            throw Undeclared(id);
                        }
                        if (y->type == "number" && x->type_for_ham == 0) {  // id co kieu number ma ham chua co kieu tra ve
                            x->type_for_ham = 1;
                            int firstt = table.find_id(iden, x->block_level, constant1, constant2, type_probing);
                            int second = table.find_id(id, x->block_level, constant1, constant2, type_probing);
                            cout << firstt + second << endl;
                        }
                        else if (y->type == "string" && x->type_for_ham == 0) {    // id co kieu string ma ham chua co kieu tra ve
                            x->type_for_ham = 2;
                            // cout<<"here2";
                            int firstt = table.find_id(iden, x->block_level, constant1, constant2, type_probing);
                            int second = table.find_id(id, x->block_level, constant1, constant2, type_probing);
                            cout << second + firstt << endl;
                        }
                        else if (y->type.empty() && x->type_for_ham == 1) {    // ham co kieu string ma id chua co kieu tra ve
                            y->type = "number";
                            int firstt = table.find_id(iden, x->block_level, constant1, constant2, type_probing);
                            int second = table.find_id(id, x->block_level, constant1, constant2, type_probing);
                            cout << firstt + second << endl;
                        }
                        else if (y->type.empty() && x->type_for_ham == 2) {    // ham co kieu string ma id chua co kieu tra ve
                            y->type = "string";
                            int firstt = table.find_id(iden, x->block_level, constant1, constant2, type_probing);
                            int second = table.find_id(id, x->block_level, constant1, constant2, type_probing);
                            cout << firstt + second << endl;
                        }
                        else if (y->type == "number" && x->type_for_ham == 1) {    // ham co kieu number, id cung number
                          //  y->type = "string";
                            int firstt = table.find_id(iden, x->block_level, constant1, constant2, type_probing);
                            int second = table.find_id(id, x->block_level, constant1, constant2, type_probing);
                            cout << firstt + second << endl;
                        }
                        else if (y->type == "string" && x->type_for_ham == 2) {    // ham co kieu string ,id cung kieu string
                          //  y->type = "string";
                            int firstt = table.find_id(iden, x->block_level, constant1, constant2, type_probing);
                            int second = table.find_id(id, x->block_level, constant1, constant2, type_probing);
                            cout << firstt + second << endl;
                        }
                        else if (y->type.empty() && x->type_for_ham == 0) {   //
                            deletenode(&head);
                            throw TypeCannotBeInferred(line);
                        }
                        else if ((y->type == "number" && x->type_for_ham == 2) || (y->type == "string" && x->type_for_ham == 1)||(y->type == "number" && x->type_for_ham == 3) || (y->type == "string" && x->type_for_ham == 3)) {   // khac kieu nhau
                           // cout<<"de";
                            deletenode(&head);
                            throw TypeMismatch(line);
                        }
                        else{
                            deletenode(&head);
                            throw InvalidInstruction(line);
                        }


                    }
                    else {
                        deletenode(&head);
                        throw TypeMismatch(line);
                    }
                }
                else {
                    string t1 = "";   // luu toan bo 123,43,'222',id
                    int step = 0;
                    int q = value.length() - 1;
                    while (i < q) {   // check tung tham so va luu vao checkk
                        t1 += value[i];
                        if (i == q - 1) {
                            inside += value[i];  // last bien
                            if (check_type(inside) == 3 || check_type(inside) == 6) {
                                deletenode(&head);
                                throw InvalidInstruction(line);
                            }
                        }
                        else if (value[i] == ',') {
                            if (check_type(inside) == 3) {
                                deletenode(&head);
                                throw InvalidInstruction(line);
                            }
                            inside = "";
                        }
                        else {
                            inside += value[i];
                        }
                        i++;
                    }    // bay gio co t1 luu toan 123,x,y,333, gio bien no thanh 121112 cac kieu
                    node* x = get_node(&head, iden, block_level);
                    if (x == nullptr) {
                        deletenode(&head);
                        throw Undeclared(iden);
                    }
                    step += table.find_id(iden, x->block_level, constant1, constant2, type_probing);
                    if (x->type == "string" || x->type == "number") {
                        deletenode(&head);
                        throw TypeMismatch(line);
                    }
                    string checkathon = x->parameter;
                    if(checkathon[0] == '0'){   // chua dc thiet lap
                    }
                    else {     // da dc thiet lapp
                        checkathon.pop_back();
                    }
                    int v =-1;
                    string sktt1 ;  // number
                    string faker ;   //chua dang cua tham so trong ham de so sanh voi function
                    int c9 = 0;
                    int e = t1.length();
                    while (c9 < e) {   // t1 chua 1,2,123,'111'    sktt1 chua tung o 1
                        if (c9 == e - 1) {
                            v++;
                            sktt1 += t1[c9];
                            if (check_type(sktt1) == 1) {
                                faker += "1";  //faker la string moi de so sanh
                            }
                            else if (check_type(sktt1) == 2) {
                                faker += "2";
                            }
                            else if (check_type(sktt1) == 4) {  //iden
                                if(!check_iden(sktt1)){
                                    deletenode(&head);
                                    throw InvalidInstruction(line);
                                }
                                //  splay.searchVIP(sktt1, block_level, &comparetime, &splaytime);
                                node* y = get_node(&head, sktt1, block_level);
                                if (y == nullptr) {
                                    deletenode(&head);
                                    throw Undeclared(sktt1);
                                }
                                step += table.find_id(sktt1, y->block_level, constant1, constant2, type_probing);

                                if (y->type == "number") {
                                    faker += "1";
                                }
                                else if (y->type == "string") {
                                    faker += "2";
                                }
                                else if(y->type.empty() && checkathon[v] == '0') {

                                   // cout<<sktt1<<endl;
                                    deletenode(&head);
                                    throw TypeCannotBeInferred(line);   // inden case function
                                }
                                else if(y->type.empty() && checkathon[v] == '1') {
                                    faker += "1";
                                    y->type = "number";
                                }
                                else if(y->type.empty() && checkathon[v] == '2') {
                                    faker += "2";
                                    y->type = "string";
                                }
                                else{
                                    deletenode(&head);
                                    throw TypeMismatch(line);
                                }
                            }
                            else {
                            }
                        }
                        else if (t1[c9] == ',') {
                            v++;
                            if (check_type(sktt1) == 3) {
                                deletenode(&head);
                                throw InvalidInstruction(line);
                            }
                            else if (check_type(sktt1) == 1) {
                                faker += "1";
                            }
                            else if (check_type(sktt1) == 2) {
                                faker += "2";
                            }
                            else if (check_type(sktt1) == 4) { //iden
                                if(!check_iden(sktt1)){
                                    deletenode(&head);
                                    throw InvalidInstruction(line);
                                }
                                node* y = get_node(&head, sktt1, block_level);
                                if (y == nullptr) {
                                    deletenode(&head);
                                    throw Undeclared(sktt1);
                                }
                                step += table.find_id(sktt1,y->block_level, constant1, constant2, type_probing);

                                if (y->type == "number") {
                                    faker += "1";
                                }
                                else if (y->type == "string") {
                                    faker += "2";
                                }
                                else if(y->type.empty() && checkathon[v] == '0') {
                                    // cout<<sktt1<<endl;
                                 //   count(&head);
                                    deletenode(&head);
                                    throw TypeCannotBeInferred(line);   // inden case function
                                }
                                else if(y->type.empty() && checkathon[v] == '1') {
                                    faker += "1";
                                    y->type = "number";
                                }
                                else if(y->type.empty() && checkathon[v] == '2') {
                                    faker += "2";
                                    y->type = "string";
                                }
                                else{
                                  //  cout<<"c";
                                    deletenode(&head);
                                    throw TypeMismatch(line);
                                }

                            }
                            sktt1 = "";
                        }
                        else {
                            sktt1 += t1[c9];
                        }
                        c9++;
                    }
                    string cou = x->type;   // so sanh so luong phan tu
                    int len2 = cou.length();
                    int a = 0;  // bien tam
                    for (int u = 3; u < len2; u++) {  // lay so size
                        a = a * 10 + (int(cou[u]) - 48);
                    }
                    int r = faker.length();
                    if(a != r){
                       // cout<<a<<endl;
                      //  cout<<faker<<endl;
                       // cout<<"e";
                        deletenode(&head);
                        throw TypeMismatch(line);
                    }

                    string EDG = x->parameter;  // lay type cac tham so cua ham
                    int f = (x->parameter).length();
                    string last ;
                    last += EDG[f - 1];  // lay kieu cua cua parameter
                    EDG.pop_back();
                    int cout0 = 0;
                    int n = EDG.length();   // check edg xem co phai 0000000
                    for (int im = 0; im < n; im++) {
                        if (EDG[im] != '0') {
                        }
                        else {
                            cout0++;
                        }
                    }
                    if (cout0 == n) {  // ham chua co type bat ki so nao
                        EDG = faker;
                        //  EDG+= last;
                        node* z = get_node(&head, id, block_level);
                        if (z == nullptr) {
                            deletenode(&head);
                            throw Undeclared(id);
                        }
                        step += table.find_id(id, z->block_level, constant1, constant2, type_probing);

                        if (z->type == "number") {
                            EDG += "1";
                            x->type_for_ham=1;
                        }
                        else if (z->type == "string") {
                            EDG += "2";
                            x->type_for_ham=2;
                        }
                        else if (z->type.empty()) {   // id va function chua co type
                            deletenode(&head);
                            throw TypeCannotBeInferred(line);
                        }
                        else {  // type ham
                          //  cout<<"v";
                            deletenode(&head);
                            throw TypeMismatch(line);
                        }
                        x->parameter = EDG;
                        // con thieu buoc lay trong hash
                        cout<<step<<endl;
                    }
                    else if (cout0 == 0) {    // da full tham so
                        if (faker == EDG) {
                            node* z = get_node(&head, id, block_level);
                            if (z == nullptr) {
                                deletenode(&head);
                                throw Undeclared(id);
                            }
                            step += table.find_id(id, z->block_level, constant1, constant2, type_probing);

                            if ((z->type == "number" && last == "1") || (z->type == "string" && last == "2")) {  // cung kieu number
                               // step += table.find_id(id, block_level, constant1, constant2, type_probing);
                             //   step += table.find_id(id, block_level, constant1, constant2, type_probing);
                                cout<<step<<endl;
                            }
                            else if(z->type.empty()){
                                if(last =="1"){
                                    z->type = "number";
                                }
                                else if(last == "2"){
                                    z->type = "string";
                                }
                                else{
                                  //  cout<<"z";
                                    deletenode(&head);
                                    throw TypeMismatch(line);
                                }
                            }
                            else {
                               // cout<<"d";
                                deletenode(&head);
                                throw TypeMismatch(line);
                            }
                        }
                        else {
                          // cout<<faker<<" "<<EDG<<endl;
                            deletenode(&head);
                            throw TypeMismatch(line);
                        }
                    }
                }
            }

        }
        else if (search_begin != -1) {
            if (first == 0) {
                deletenode(&head);
                throw InvalidInstruction(line);
            }
            block_level++;
        }
        else if (search_end != -1) {
            if (first == 0) {
                deletenode(&head);
                throw InvalidInstruction(line);
            }
            if(block_level ==0){
                deletenode(&head);
                throw UnknownBlock();
            }
            node* start = head;
            while(start != nullptr){
                if(start->block_level == block_level){
                    table.delete_level(start->id,block_level,constant1,constant2,type_probing,&step);
                    start->block_level = -1;
                    start->id = "";
                    start->parameter= "";
                    start->type = "";
                }
                start = start->next;
            }
            block_level--;
        }
        else if(search_lookup != -1){
            int n = 7;
            line += "@";
            string id;
            while (line[n] != '@') {
               id  += line[n];
                n++;
            }
            if(!check_iden(id)){
                deletenode(&head);
                throw InvalidInstruction(line);
            }
            line.pop_back();
            int temp =block_level;
            int co =0;
            while(temp >=0) {
                if (table.find_index(id, temp) != -1) {
                    cout << table.find_index(id, temp) << endl;
                    co =2;
                    break;
                }
                temp--;
            }
            if(co != 2) {
                deletenode(&head);
                throw Undeclared(id);
            }
        }
        else if (search_print != -1) {
            if (first == 0) {
                deletenode(&head);
                throw InvalidInstruction(line);
            }
            int n=0;
            int count=0;
            while(n<size){
                int k = table.search(n);
                if(k != -1){
                    count = k;
                }
                n++;
            }
            n=0;
            int co =0;
            while(n<size){
                int k = table.search(n);
                if(k != -1){
                    co++;
                    if(n==count){
                        printed(&head,k,1);
                    }
                    else
                        printed(&head,k,0);
                }
                n++;
            }
            if(co != 0) {
                cout << endl;
            }
            else{

            }
        }
        else if(search_call != -1){
            // chieu lam
            int m=5;
            string func;
            int ngoac =0;
            while(line[m] != '('){   // lay ten ham
                func += line[m];
                m++;
                if(m>=(int)line.length()){
                    deletenode(&head);
                    throw InvalidInstruction(line);
                }
            }
            if(!check_iden(func)){
                deletenode(&head);
                throw InvalidInstruction(line);
            }
            if(line[m] == '('){
                ngoac++;
            }
            int t = line.length();
            if(line[t-1] == ')'){
                ngoac++;
            }
            if(ngoac !=2){
                deletenode(&head);
                throw InvalidInstruction(line);
            }
            m++;
            string inside;
            line += "@";
            while(line[m] != '@'){
                inside += line[m];
                m++;
            }
            line.pop_back();
            node* x = get_node(&head,func,block_level);
            string t1 = "";   // luu toan bo 123,43,'222',id
            int i =0;
            int step = 0;
            string check ;
            int q = inside.length() - 1;
            while (i < q) {   // check tung tham so va luu vao checkk
                t1 += inside[i];
                if (i == q - 1) {
                    check += inside[i];  // last bien
                    if (check_type(check) == 3 || check_type(check) == 6) {
                        deletenode(&head);
                        throw InvalidInstruction(line);
                    }
                }
                else if (inside[i] == ',') {
                    if (check_type(check) == 3) {
                        deletenode(&head);
                        throw InvalidInstruction(line);
                    }
                    check = "";
                }
                else {
                    check += inside[i];
                }

                i++;
            }   // ta da co t1 chua het o trong ham ve check cac kieu co ve phu hop
            if( x == nullptr){
                deletenode(&head);
                throw Undeclared(func);
            }
            if(x->type_for_ham ==1 || x->type_for_ham ==2 || x->type_for_ham == -1){
                deletenode(&head);
                throw TypeMismatch(line);
            }
            string checkathon = x->parameter;
            if(checkathon[0] == '0'){   // chua dc thiet lap
            }
            else {     // da dc thiet lapp
                checkathon.pop_back();
            }
            int v =-1;
            string sktt1 ;  // number
            string faker ;   //chua dang cua tham so trong ham de so sanh voi function
            int c9 = 0;
            int e = t1.length();

            while (c9 < e) {   // t1 chua 1,2,123,'111'    sktt1 chua tung o 1
                if (c9 == e - 1) {
                    v++;
                    sktt1 += t1[c9];
                    if (check_type(sktt1) == 1) {
                        faker += "1";  //faker la string moi de so sanh
                    }
                    else if (check_type(sktt1) == 2) {
                        faker += "2";
                    }
                    else if (check_type(sktt1) == 4) {  //iden
                        if(!check_iden(sktt1)){
                            deletenode(&head);
                            throw InvalidInstruction(line);
                        }
                      //  cout<<sktt1<<endl;
                        //  splay.searchVIP(sktt1, block_level, &comparetime, &splaytime);
                        node* y = get_node(&head, sktt1, block_level);
                        if (y == nullptr) {
                            deletenode(&head);
                            throw Undeclared(sktt1);
                        }
                        step += table.find_id(sktt1, y->block_level, constant1, constant2, type_probing);

                        if (y->type == "number") {
                            faker += "1";
                        }
                        else if (y->type == "string") {
                            faker += "2";
                        }
                        else if(y->type.empty() && checkathon[v] == '0') {

                            // cout<<sktt1<<endl;
                            deletenode(&head);
                            throw TypeCannotBeInferred(line);   // inden case function
                        }
                        else if(y->type.empty() && checkathon[v] == '1') {
                            faker += "1";
                            y->type = "number";
                        }
                        else if(y->type.empty() && checkathon[v] == '2') {
                            faker += "2";
                            y->type = "string";
                        }
                        else{
                          //  cout<<"fd"<<endl;
                            deletenode(&head);
                            throw TypeMismatch(line);
                        }
                    }
                    else {
                    }
                }
                else if (t1[c9] == ',') {
                    v++;
                    if (check_type(sktt1) == 3) {
                        deletenode(&head);
                        throw InvalidInstruction(line);
                    }
                    else if (check_type(sktt1) == 1) {
                        faker += "1";
                    }
                    else if (check_type(sktt1) == 2) {
                        faker += "2";
                    }
                    else if (check_type(sktt1) == 4) { //iden
                        if(!check_iden(sktt1)){
                            deletenode(&head);
                            throw InvalidInstruction(line);
                        }
                        node* y = get_node(&head, sktt1, block_level);
                        if (y == nullptr) {
                            deletenode(&head);
                            throw Undeclared(sktt1);
                        }
                        step += table.find_id(sktt1,y->block_level, constant1, constant2, type_probing);

                        if (y->type == "number") {
                            faker += "1";
                        }
                        else if (y->type == "string") {
                            faker += "2";
                        }
                        else if(y->type.empty() && checkathon[v] == '0') {

                            // cout<<sktt1<<endl;
                            deletenode(&head);
                            throw TypeCannotBeInferred(line);   // inden case function
                        }
                        else if(y->type.empty() && checkathon[v] == '1') {
                            faker += "1";
                            y->type = "number";
                        }
                        else if(y->type.empty() && checkathon[v] == '2') {
                            faker += "2";
                            y->type = "string";
                        }
                        else{
                          //  cout<<sktt1<<endl;
                            deletenode(&head);
                            throw TypeMismatch(line);
                        }
                    }
                    sktt1 = "";
                }
                else {
                    sktt1 += t1[c9];
                }
                c9++;
            }
           // cout<<faker<<endl;
            string cou = x->type;   // so sanh so luong phan tu
            int len2 = cou.length();
            int a = 0;  // bien tam
            for (int i = 3; i < len2; i++) {  // lay so size
                a = a * 10 + (int(cou[i]) - 48);
            }
            int r = faker.length();
            if(a != r){
                deletenode(&head);
                throw TypeMismatch(line); //here
            }

            string EDG = x->parameter;  // lay type cac tham so cua ham
            int f = (x->parameter).length();
            string last ;
            last += EDG[f - 1];  // lay kieu cua cua parameter
            EDG.pop_back();
            int cout0 = 0;
            int n = EDG.length();   // check edg xem co phai 0000000
            for (int iz = 0; iz < n; iz++) {
                if (EDG[iz] != '0') {
                }
                else {
                    cout0++;
                }
            }
            if (cout0 == n) {  // ham chua co type bat ki so nao thi minh se cho so do vao
                EDG = faker;
                //  EDG+= last;
               // node* z = get_node(&head, id, block_level);
                if (x == nullptr) {
                    deletenode(&head);
                    throw Undeclared(func);
                }
                step += table.find_id(func, x->block_level, constant1, constant2, type_probing);  // lay step cua function

                    EDG += "3";
                    x->type_for_ham=3;  // void gan cho ham

                x->parameter = EDG;
                // con thieu buoc lay trong hash
                cout<<step<<endl;
            }
            else if (cout0 == 0) {    // da full tham so
                if (faker == EDG) {
                    step += table.find_id(func, x->block_level, constant1, constant2, type_probing);
                        cout<<step<<endl;
                }
                else {
                    deletenode(&head);
                    throw TypeMismatch(line);
                }
            }


        }
        else{
            deletenode(&head);
            throw InvalidInstruction(line);
        }
     //   first++;
    }
    if(block_level !=0){
        deletenode(&head);
        throw UnclosedBlock(block_level);
    }
  //   count(&head);
 //   table.print();
    deletenode(&head);
  //  cout<<first;
}

// 1 la number
// 2 la string
// so cuoi trong parameter la kieu ham tra ve
// 3 la void
