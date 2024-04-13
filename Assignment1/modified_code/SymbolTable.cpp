#include "SymbolTable.h"

bool SymbolTable::check_id(string id, int block_level, Node** head) {

    if (head == NULL)
        return false;
    else {
        Node* start = *head;
        while (start != NULL) {

            if (start->identifier == id && check_block(start, head) == true && start->block_level <= block_level) {   //&& check_block(start, head) == true && start->block_level <= block_level 
                return true;   
            }
            start = start->next;
        }
    }
    return false;
}
bool SymbolTable::check_idd(string id, int block, Node** head) {

    if (head == NULL)
        return false;
    else {
        Node* start = *head;
        while (start != NULL) {

            if (start->identifier == id && check_block(start, head) == true && start->block_level == block) {
                return true;  // đổi sang count 
            }
            start = start->next;
        }
    }
    return false;
}
int SymbolTable::check_id_type(string id, int block, string type, Node** head) {

    if (head == NULL) {
        return 0;  //false
    }
    else {
        Node* tmp = NULL;
        Node* start = *head;
        int i = 0;
        while (start != NULL) {

            if (start->identifier == id && start->block_level <= block && check_block(start, head) == true) { //&& start->type == type
                tmp = start;
                i++;
            }
            start = start->next;
        }

        if (i != 0 && tmp->type == type) {
            return 1;       // true
        }
        else if(i!=0 && tmp->type != type) {
            return 2;
        }
    }
    return 0;
}
bool SymbolTable::check_number(string id, int block, Node** head) {
   
    if (head == NULL) {
        return false;
    }
    else {
        Node* start = *head;
        Node* tmpp = *head;
        int count = 0;
        while (start != NULL) {

            if (start->identifier == id) {
                if (check_block(start, head) == true && start->block_level <= block) {
                    tmpp = start;
                    count++;
                }
            }
            start = start->next;
        }
        string t = tmpp->type;
        if (t == "string") {
            return false;
        }
        else if (count != 0) {

            return true;
        }
        else {
            return false;
        }
        return false;
    }
}
bool SymbolTable::check_block(Node* tmp, Node** head) {   
        Node* start = tmp;
        start->next = tmp->next;
        while (start->next != NULL) {
            if (start->block_level < tmp->block_level) {
                return false;
            }
            start = start->next;
        }
        return true; 
}
string SymbolTable::get_type(string id, int block, Node** head) {
    string tt;
    if (head == NULL) {
        return "false";
    }
    else {
        Node* tmp = *head;
        Node* start = *head;
        while (start != NULL) {

            if (start->identifier == id && start->block_level <= block) {
                tmp = start;
            }
            start = start->next;
        }
        tt = tmp->type;
        return tt;
    }
}
void SymbolTable::assign_value(string id, string value, int level, Node** head) {

    if (head == NULL) {

    }
    else {
        Node* tmp = *head;
        Node* start = *head;
        while (start != NULL) {

            if (start->identifier == id && start->block_level <= level) {
                tmp = start;
            }
            start = start->next;
        }
        tmp->value = value;
        //delete(start);
    }

}
void SymbolTable::assign_value2(string id, string idd, int block_level, Node** head) {
    Node* tmp = *head;
    Node* start = *head;
    string temp;
    while (start != NULL) {

        if (start->identifier == id && start->block_level <= block_level) {
            tmp = start;
        }
        start = start->next;
    }
    temp = tmp->value;
    //delete(start);
    assign_value(tmp->identifier, temp, tmp->block_level, head);

}
void SymbolTable::insert(string id, string Type, int block_level, Node** head)
{
    Node* p = new Node(id, Type, block_level, "");
    p->next = NULL;
    Node* start = *head;
    if (*head == NULL) {
        *head = p;
    }
    else {
        while (start->next != NULL)
            start = start->next;

        start->next = p;
    }
}
void SymbolTable::insert2(string name, int block, Node2** head2) {
    Node2* k = new Node2(name, block);
    k->nextt = NULL;
    Node2* startt = *head2;
    if (*head2 == NULL) {
        *head2 = k;
    }
    else {
        while (startt -> nextt != NULL)
            startt = startt->nextt;

        startt->nextt = k;
    }
    if (find(name, head2) == true) {
        del_node2(name, head2);
    }
}
void SymbolTable::del_node2(string id, Node2** head2) {
    Node2* startt = *head2;
    Node2* tmp = NULL;
    if (startt->id == id) {
        *head2 = startt->nextt;
        delete(startt);
    }
    else {
        while (startt->nextt != NULL && startt->id != id) {
            tmp = startt;
            startt = startt->nextt;
        }
        tmp->nextt = startt->nextt;
        delete(startt);
    }
}
bool SymbolTable::find(string id, Node2** head2) {
    if (*head2 == NULL) {
        return false;
    }
    else {
        Node2* startt = *head2;
        while (startt->nextt != NULL) {
            if (startt->id == id) {
                return true;
            }
            startt = startt->nextt;
        }
        return false;
    }
}
void SymbolTable::print_linkednist2(Node2** head2, int index) {
    if (*head2 == NULL) {
        cout << "";
    }
    else {
        Node2* start = *head2;
        string t = "";
        if (index == 1) {
            
            while (start != NULL) {
                t += start->id;
                t += "//";
                t += to_string(start->level);
                t += " ";
                start = start->nextt;
            }
            t.pop_back();
            cout << t << endl;
        }
        else {
            
            while (start != NULL) {
                string re = start->id;
                int r = re.length();
                string er;
                for (int i = r - 1; i >= 0; i--) {
                    er += re[i];
                }
                t += to_string(start->level);
                t += "//";
                t += er;
                t += " ";
                start = start->nextt;
            }
            t.pop_back();

            int g = t.length();
            string k; ;
            for (int i = g - 1; i >= 0; i--) {
                k += t[i];
            }
            cout << k << endl;
        }
        
    }
}
void SymbolTable::call_print(Node** head, Node2** head2,int level) {
    if (head == NULL) {
        cout << "";
    }
    else {
        Node* start = *head;
        while (start != NULL) {
            if (start->identifier != "BEGIN" && start->identifier != "END" && start->identifier != "LOOKUP" && start->identifier != "ASSIGN" && start->block_level <=level && check_block(start, head) == true) {
                insert2(start->identifier, start->block_level, head2);
            }
            start = start->next;
        }
    }
}
void SymbolTable::insert_else(string id, string type, int block_level, Node** head) {
    Node* end = new Node(id, type, block_level, "");
    end->next = NULL;
    Node* start = *head;
    if (*head == NULL) {
        *head = end;

    }
    else {
        while (start->next != NULL) {
            start = start->next;
        }
        start->next = end;
    }
}
void SymbolTable::lookup(string id, int block, Node** head, string line,int countp) 
{
    if (head == NULL) {
        deletenist(head);
        if (countp > 0) {
            deletenist2(head2);
            *head2 = NULL;
        }
        throw Undeclared(line);
        
    }
    else {
        Node* start = *head;
        Node* temp = *head;
        int count = 0;
        while (start->next != NULL) {
            if (start->identifier == id && start->block_level <= block && check_block(start, head) == true) {
                temp = start;
                count++;
            }

            start = start->next;
        }
        
        if (count != 0) {
            cout << temp->block_level << endl;

        }
        else {
            deletenist(head);
            head = NULL;
            if (countp > 0) {
                deletenist2(head2);
                *head2 = NULL;
            }
            throw Undeclared(line);
        }
    }
}
void SymbolTable::deletenist(Node** head)
{
    if (*head == NULL) {

    }
    else {
        Node* current = *head;
        Node* next = NULL;

        while (current != NULL)
        {
            next = current->next;
            delete(current);
            current = next;
        }
        *head = NULL;
    }
}
void SymbolTable::deletenist2(Node2** head2)
{
    if (*head2 == NULL) {
    }
    else {
        Node2* current = *head2;
        Node2* next = NULL;

        while (current != NULL)
        {
            next = current->nextt;
            delete(current);
            current = next;
        }
        *head2 = NULL;
    }
}
void SymbolTable::run(string filename)
{
    ifstream fileInput(filename);
    Node* head = NULL;
    int block_level = 0; int countp = 0;
    while (!fileInput.eof()) {
        string line;
        getline(fileInput,line);
        char insert[] = "INSERT ";
        char assign[] = "ASSIGN ";
        char number[] = "number";
        char strings[] = "string";
        char begin[] = "BEGIN";
        char end[] = "END";
        char lookup[] = "LOOKUP ";
        char print[] = "PRINT";
        char rprint[] = "RPRINT";
        int search_insert = line.find(insert);
        int search_assign = line.find(assign);
        int search_type1 = line.find(number);
        int search_type2 = line.find(strings);
        int search_begin = line.find(begin);
        int search_end = line.find(end);
        int search_lookup = line.find(lookup);
        int search_print = line.find(print);
        int search_rprint = line.find(rprint);
        string name = "";
        int n;
        SymbolTable create;        // Create new xymbol Table
        if (search_insert != -1 && line[0] == 'I') {
            // gọi khởi tạo một node mới

            n = 7;
            while (line[n] != ' ') {
                name += line[n];
                n++;
            }
            if (name[0] < 'a' || name[0] > 'z') {
                deletenist(&head);
                head = NULL;
                if (countp > 0) {
                    deletenist2(head2);
                    *head2 = NULL;
                }
                throw InvalidInstruction(line);
            }
            if (create.check_idd(name, block_level, &head) == true) {
                deletenist(&head);
                head = NULL;
                if (countp > 0) {
                    deletenist2(head2);
                    *head2 = NULL;
                }
                throw Redeclared(line);
            }
            else {
                if (search_type1 != -1) {

                    create.insert(name, number, block_level, &head);
                    cout << "success" << endl;
                }
                else if (search_type2 != -1) {

                    create.insert(name, strings, block_level, &head);
                    cout << "success" << endl;
                }
            }
        }
        else if (search_assign != -1 && line[0] == 'A') {
            n = 7;
            while (line[n] != ' ') {
                name += line[n];
                n++;
            }
            create.insert_else("ASSIGN", "", block_level, &head);
            if (create.check_id(name, block_level, &head) == false) {
                deletenist(&head);
                head = NULL;
                if (countp > 0) {
                    deletenist2(head2);
                    *head2 = NULL;
                }
                throw Undeclared(line);
            }
            else {
                string value = "";
                line += '@';
                n++;
                while (line[n] != '@') {
                    value += line[n];
                    n++;
                }
                int count_se = 0;
                int count_number = 0;
                int count_word = 0;
                int b = value.length() - 1;
                if (value[0] == '\'') {
                    count_se++;
                }
                if (value[b] == '\'') {
                    count_se++;
                }
                for (int i = 0; i < b + 1; i++) {
                    if (value[i] >= '0' && value[i] <= '9' && count_se == 0) {
                        count_number++;
                    }
                    else if (((value[i] >= 'a' && value[i] <= 'z') || (value[i] >= '0' && value[i] <= '9')) || value[i] == ' ') {
                        count_word++;
                    }
                    else if (value[i] >= 'A' && value[i] <= 'Z') {
                        count_word++;
                    }
                }
                string y = create.get_type(name, block_level, &head); 
                line.pop_back();
                int len = value.length();
                if ((count_number == len && check_number(name, block_level, &head) && count_se == 0) || (count_number == len-1 && check_number(name, block_level, &head) && count_se == 0 && value[0] == '-')) {
                    create.assign_value(name, value, block_level, &head);
                    cout << "success" << endl;

                }
                else if (count_word == len - 2 && check_number(name, block_level, &head) == false && count_se == 2) {
                    value.pop_back();
                    string value_string = value;
                    for (int s = 1; s < b; s++) {
                        value_string[s - 1] = value[s];
                    }
                    value_string.pop_back();
                    create.assign_value(name, value_string, block_level, &head);
                    cout << "success" << endl;

                }
                else if (create.check_id_type(value, block_level, y, &head) == 1) {
                    create.assign_value2(value, name, block_level, &head);
                    cout << "success" << endl;
                }
                else if (create.check_id_type(value, block_level, y, &head) == 2 && value[0] != '\'' && count_word > 0 && get_type(value, block_level, &head) !=y) {  //case khác type
                    deletenist(&head);
                    head = NULL;
                    if (countp > 0) {               // throw when different type
                        deletenist2(head2);
                        *head2 = NULL;
                    }
                    throw TypeMismatch(line);
                }
                else if (create.check_id_type(value, block_level, y, &head) == 2 && value[0] != '\'' && count_word > 0 && create.check_id(value, block_level, &head) == false) {
                    deletenist(&head);
                    head = NULL;
                    if (countp > 0) {
                        deletenist2(head2);
                        *head2 = NULL;           // throw when cant find value id
                    }
                    throw Undeclared(line);
                }
                else if (count_number == len && check_number(name, block_level, &head) == false && check_id(name, block_level, &head)) {
                    deletenist(&head);
                    head = NULL;
                    if (countp > 0) {
                        deletenist2(head2);   // throw when assign number for string id
                        *head2 = NULL;
                    }
                    throw TypeMismatch(line);
                }
                else if (count_word == len - 2 && check_number(name, block_level, &head) == true && check_id(name, block_level, &head) && value[0] == '\'') {
                    deletenist(&head);
                    head = NULL;
                    if (countp > 0) {
                        deletenist2(head2);     // throw when assign string for number id
                        *head2 = NULL;
                    }
                    throw TypeMismatch(line);
                }
                else {
                    deletenist(&head);
                    head = NULL;
                    if (countp > 0) {
                        deletenist2(head2);
                        *head2 = NULL;
                    }                  
                    throw Undeclared(line);
                }
            }
        }
        else if (search_begin != -1 && line[0] == 'B' && line.length() == 5) {
            block_level++;
            create.insert_else("BEGIN", "", block_level, &head);

        }
        else if (search_end != -1 && line[0] == 'E' && line.length() == 3) {
            block_level--;
            create.insert_else("END", "", block_level, &head);
            if (block_level < 0) {
                deletenist(&head);
                head = NULL;
                if (countp > 0) {
                    deletenist2(head2);
                    *head2 = NULL;
                }
                head = NULL;
                throw UnknownBlock();
            }
        }
        else if (search_lookup != -1 && line[0] == 'L') {
            n = 7;
            line += "@";
            while (line[n] != '@') {
                name += line[n];
                n++;
            }
            line.pop_back();
            create.insert_else("LOOKUP", "", block_level, &head);
            create.lookup(name, block_level, &head, line,countp);
        }
        else if (search_print != -1 && search_rprint == -1 && line[0] == 'P' && line.length() == 5) {
            countp++;
            call_print(&head, head2,block_level);
            print_linkednist2(head2, 1);
            deletenist2(head2);
            *head2 = NULL;
        }
        else if (search_rprint != -1 && line[0] == 'R' && line.length() == 6) {
            countp++;
            call_print(&head, head2,block_level);
            print_linkednist2(head2, 2);
            deletenist2(head2);
            *head2 = NULL;
        }
        else {
            deletenist(&head);
            head = NULL;
            if (countp > 0) {
                deletenist2(head2);
                *head2 = NULL;
            }
            throw InvalidInstruction(line);
        }
    }
    if (block_level > 0) {
        deletenist(&head);
        head = NULL;
        if (countp > 0) {
            deletenist2(head2);
            *head2 = NULL;
        }
        throw UnclosedBlock(block_level);
    }
    else if (block_level < 0) {
        deletenist(&head);
        head = NULL;
        if (countp > 0) {
            deletenist2(head2);
            *head2 = NULL;
        }
        throw UnknownBlock();
    }
    else {
        deletenist(&head);
        head = NULL;
        if (countp > 0) {
            deletenist2(head2);
            *head2 = NULL;
        }
    }
    

}
