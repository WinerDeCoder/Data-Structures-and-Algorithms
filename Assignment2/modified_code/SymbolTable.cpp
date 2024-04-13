#include "SymbolTable.h"

void SymbolTable::insertt(node** head, string key, int level){   // insert vao 1 cai linked de xoa node theo thu tu
    if(*head == nullptr){
        *head = new node(key,level);
    }
    else{
        node* start = *head;
        while(start->next != nullptr){
            start = start->next;
        }
        start-> next = new node(key,level);
    }
}

int SymbolTable::check_type(string value) {
    int r = value.length();
    if (r == 0) {
        return 5;  // empty
    }
    int count_number = 0;
    int count_word = 0;
    int count_nhay = 0;
    int b = value.length() - 1;
    if (value[0] == '\'') {
        count_nhay++;
    }
    if (value[b] == '\'') {
        count_nhay++;
    }
    if(count_nhay ==0){
        for (int i = 0; i < b + 1; i++) {
            if (value[i] >= '0' && value[i] <= '9') {
                count_number++;
            }
            else if((value[i] >= 'a' && value[i] <= 'z') || (value[i] >= 'A' && value[i] <= 'Z') || value[i] == '_'){
                count_word++;
            }
        }
        if(count_number == (b+1)){
            return 1;  //number
        }
        else if(count_word+count_number == (b+1) && (value[0] >='a' && value[0] <='z')){
            return 4;    // iden
        }
        else{
            return 3;    // nothing
        }
    }
    else if(count_nhay ==2 ) {
        for (int i = 1; i < b ; i++) {
            if ((value[i] >= '0' && value[i] <= '9')|| (value[i] >= 'a' && value[i] <= 'z') || (value[i] >= 'A' && value[i] <= 'Z' )|| value[i] ==' ' ) {
                count_number++;
            }
        }
        if(count_number == (b-1)){
            return 2;  // string
        }
        else{
            return 3;   // nothing
        }
    }
    return 3;

}

bool SymbolTable::check_iden(string iden){
    if(iden == "number" || iden == "string" || iden == "true" || iden == "false" ||  iden == "for" || iden == "else" || iden == "while"||iden=="return"){
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
    }
    int t = iden.length();
    if(t==1) {
        if (iden[0] < 'a' && iden[0] > 'z') {
            return false;
        }
    }
    else {
        if (iden[0] < 'a' && iden[0] > 'z') {
            return false;
        }
        for (int i = 1; i < t; i++) {
            if ((iden[i] >= 'a' && iden[i] <='z') || (iden[i] >= 'A' && iden[i] <='Z') || iden[i] =='_' || (iden[i] >= '0' && iden[i] <= '9')){

            }
            else{
                return false;
            }
        }
    }
    return true;
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

void SymbolTable::run(string filename) {
    ifstream fileInput(filename);
    SplayTree splay;
    node* head = nullptr;
    int block_level = 0; // int countp = 0;
    while (!fileInput.eof()) {
        string line;
        getline(fileInput, line);
        char insert[] = "INSERT ";
        char assign[] = "ASSIGN ";
        char number[] = "number";
        char strings[] = "string";
        char begin[] = "BEGIN";
        char end[] = "END";
        char lookup[] = "LOOKUP ";
        char print[] = "PRINT";
        int search_insert = line.find(insert);
        int search_assign = line.find(assign);
        int search_type1 = line.find(number);
        int search_type2 = line.find(strings);
        int search_begin = line.find(begin);
        int search_end = line.find(end);
        int search_lookup = line.find(lookup);
        int search_print = line.find(print);
        string name ="";
        string type = "";
        string last = "";
        int n;
        int splaytime = 0;
        int comparetime = 0;
        if (search_insert != -1 && line[0] == 'I') {
            n = 7;
            int all = 0,countspace=0;
            while (line[all] != '\0') {
                if (line[all] == ' ') {
                    countspace++;
                }
                all++;
            }
            if (countspace != 3) {
                splay.destroytree();
                deletenode(&head);
                throw InvalidInstruction(line);
            }
            while (line[n] != ' ') {   // tên id
                name += line[n];
                n++;
            }
            if(!check_iden(name)){
                splay.destroytree();
                deletenode(&head);
                throw InvalidInstruction(line);
            }
         /*   int kcc=0;
            int vc = splay.searchVIPPP(name, block_level, &kcc, &kcc);
            if(vc==1){
                splay.destroytree();
                deletenode(&head);
                throw Redeclared(line);
            }
            */
            n++;
            while (line[n] != ' ') {     // kiểu type
                type += line[n];
                n++;
            }
            int b = type.length()-1;
            n++;
            line += '@';
            while (line[n] != '@') {      // lay kieu false true
                last += line[n];
                n++;
            }
            line.pop_back();
            if(last != "true" && last != "false"){
                splay.destroytree();
                deletenode(&head);
                throw InvalidInstruction(line);
            }
            int temp_level = block_level;
            if (last == "true") {
                temp_level = 0;
            }
            if (name[0] < 'a' || name[0] > 'z') {

                splay.destroytree();
                deletenode(&head);
                throw InvalidInstruction(line);
            }
            else {
                if (type[0] != '(' && search_type1 != -1) {
                    int kcc=0;
                    int vc = splay.searchVIPPP(name, block_level, &kcc, &kcc);
                    if(vc==1){
                        splay.destroytree();
                        deletenode(&head);
                        throw Redeclared(line);
                    }
                    splay.insert(name, "number", temp_level,line,&comparetime,&splaytime);
                    insertt(&head,name,temp_level);
                    cout << comparetime << " " << splaytime << endl;
                }
                else if (type[0] != '(' && search_type2 != -1 ) {
                    int kcc=0;
                    int vc = splay.searchVIPPP(name, block_level, &kcc, &kcc);
                    if(vc==1){
                        splay.destroytree();
                        deletenode(&head);
                        throw Redeclared(line);
                    }
                    splay.insert(name, "string", temp_level,line,&comparetime,&splaytime);
                    insertt(&head,name,temp_level);
                    cout << comparetime << " " << splaytime << endl;
                }
                else if( type[0] == '(' && type[b-8] == ')' ){   //maybe kieu ham
                    string check1 ="";
                    for(int i=(b-7);i<=b;i++){
                        check1 += type[i];   // check ->string/number
                    }
                    if(check1 != "->string" && check1 != "->number"){
                        splay.destroytree();
                        deletenode(&head);
                        throw InvalidInstruction(line);
                    }
                    int h=0;
                    string typee ="";
                    if(b-8==1){  // case tham so rong
                        if(temp_level != 0){
                            splay.destroytree();
                            deletenode(&head);
                            throw InvalidDeclaration(line);
                        }
                        int kcc=0;
                        int vc = splay.searchVIPPP(name, block_level, &kcc, &kcc);
                        if(vc==1){
                            splay.destroytree();
                            deletenode(&head);
                            throw Redeclared(line);
                        }
                        splay.insert(name, type, temp_level,line,&comparetime,&splaytime); //insert()->string/number
                        cout << comparetime << " " << splaytime << endl;
                    }
                    else {   // case co tham so
                        for (int i = 1; i < b - 8; i++) {  // luu trong ngoac vao typee
                            typee += type[i];
                        }
                        string checkk = "";
                        int y =typee.length();
                        while (h < y) {   // check tung tham so va luu vao checkk
                            if (h == y - 1) {
                                checkk += typee[h];
                                if (checkk != "number" && checkk != "string") {
                                    splay.destroytree();
                                    deletenode(&head);
                                    throw InvalidInstruction(line);
                                }
                            }
                            else if (typee[h] == ',') {
                                if (checkk != "number" && checkk != "string") {
                                    splay.destroytree();
                                    deletenode(&head);
                                    throw InvalidInstruction(line);
                                }
                                checkk = "";
                            } else {
                                checkk += typee[h];
                            }
                            h++;
                        }
                        if(temp_level != 0){
                            splay.destroytree();
                            deletenode(&head);
                            throw InvalidDeclaration(line);
                        }
                        int kcc=0;
                        int vc = splay.searchVIPPP(name, block_level, &kcc, &kcc);
                        if(vc==1){
                            splay.destroytree();
                            deletenode(&head);
                            throw Redeclared(line);
                        }
                        splay.insert(name, type, temp_level, line, &comparetime, &splaytime);
                        cout << comparetime << " " << splaytime << endl;
                    }
                }
                else {
                    splay.destroytree();
                    deletenode(&head);
                    throw InvalidInstruction(line);
                }
            }
        }
        else if (search_assign != -1 && line[0] == 'A') {
            n = 7;
            while (line[n] != ' ') {  // lấy tên cần assign
                name += line[n];
                n++;
            }
            if (!check_iden(name)) {
                splay.destroytree();
                deletenode(&head);
                throw InvalidInstruction(line);
            }
            n++;
            string value;
            line += '@';
            while (line[n] != '@') {
                value += line[n];
                n++;
            }
            line.pop_back();
            int count_number = 0;
            int count_word = 0;
            int count_phay = 0;
            int count_ngoac = 0;
            int b = (value.length() - 1);
            if (value[0] == '\'') {
                count_phay++;
            }
            if (value[b] == '\'') {
                count_phay++;
            }
            if (value[b] == ')') {
                count_ngoac++;
            }
            int typhon = 0;
            if (count_ngoac == 1) {
                for (int i = 1; i < b; i++) {
                    if (value[i] == '(') {
                        count_ngoac++;
                    }
                }
                if (count_ngoac == 2) {
                    typhon = 4; // case function
                }
                else {
                    splay.destroytree();
                    deletenode(&head);
                    throw InvalidInstruction(line);
                }
            }
            else if (count_phay == 0) {
                for (int i = 0; i < b + 1; i++) {
                    if (value[i] >= '0' && value[i] <= '9') {
                        count_number++;
                    }
                    else if ((value[i] >= 'a' && value[i] <= 'z') || (value[i] >= 'A' && value[i] <= 'Z') ||
                               value[i] == '_') {
                        count_word++;
                    }
                    else {
                        splay.destroytree();
                        deletenode(&head);
                        throw InvalidInstruction(line);
                    }
                }
                if (count_number == (b + 1)) {
                    typhon = 1;  //number type
                }
                else if (count_word + count_number == (b + 1) && (value[0] >= 'a' && value[0] <= 'z')) {
                    typhon = 3;   // iden type
                }
                else {
                    splay.destroytree();
                    deletenode(&head);
                    throw InvalidInstruction(line);
                }
            }
            else if (count_phay == 2) {
                for (int i = 1; i < b; i++) {
                    if ((value[i] >= '0' && value[i] <= '9') || (value[i] >= 'a' && value[i] <= 'z') ||
                        (value[i] >= 'A' && value[i] <= 'Z') || value[i] == ' ') {
                        count_number++;
                    }
                    else {
                        splay.destroytree();
                        deletenode(&head);
                        throw InvalidInstruction(line);
                    }
                }
                if (count_number == (b - 1)) {
                    typhon = 2; //case string
                }
                else {
                    splay.destroytree();
                    deletenode(&head);
                    throw InvalidInstruction(line);
                }
            }

            if (typhon == 1) {  //number
                splay.searchVIP(name, block_level, &comparetime, &splaytime);//, &comparetime, &splaytime);
                if (splay.searchROOT(name, "number") == 0) {
                    cout << comparetime << " " << splaytime << endl;
                }
                else if (splay.searchROOT(name, "number") == -1) {
                    splay.destroytree();
                    deletenode(&head);
                    throw TypeMismatch(line);
                }
                else {
                    splay.destroytree();
                    deletenode(&head);
                    throw Undeclared(line);
                }
            }
            else if (typhon == 2) {  //string
                splay.searchVIP(name, block_level, &comparetime, &splaytime);//, &comparetime, &splaytime);
                if (splay.searchROOT(name, "string") == 0) {
                }
                else if (splay.searchROOT(name, "string") == -1) {
                    splay.destroytree();
                    deletenode(&head);
                    throw TypeMismatch(line);
                }
                else {
                    splay.destroytree();
                    deletenode(&head);
                    throw Undeclared(line);
                }
            }
            else if (typhon == 0) {  // co the ko can
                splay.destroytree();
                deletenode(&head);
                throw InvalidInstruction(line);
            }
            else if (typhon == 3) {  // case assign la 1 iden
                splay.searchVIP(value, block_level, &comparetime, &splaytime);
                if (splay.RootID() != value || splay.getRoot()== nullptr) {
                    splay.destroytree();
                    deletenode(&head);
                    throw Undeclared(line);
                }
                string a = splay.RootType();
                splay.searchVIP(name, block_level, &comparetime, &splaytime);
                if (splay.RootID() != name || splay.getRoot()== nullptr) {
                    splay.destroytree();
                    deletenode(&head);
                    throw Undeclared(line);
                }
                if (a != splay.RootType()) {
                    splay.destroytree();
                    deletenode(&head);
                    throw TypeMismatch(line);
                }
                cout << comparetime << " " << splaytime << endl;
            }
            else if (typhon == 4) {  // type function
                string iden;
                int i = 0;
                while (value[i] != '(') {  // lay ten function
                    iden += value[i];
                    i++;
                }
                if (!check_iden(iden)) {
                    splay.destroytree();
                    deletenode(&head);
                    throw InvalidInstruction(line);
                }
                string inside = "";
                i++;
                if(value[i] ==')'){  // case function()
                    splay.searchVIP(iden, block_level, &comparetime, &splaytime);
                    if(splay.RootID() != iden || splay.getRoot()== nullptr){
                        splay.destroytree();
                        deletenode(&head);
                        throw Undeclared(line);
                    }
                    string clone = splay.RootType();
                    if(clone[0] == '(' && clone[1] == ')'){
                        splay.searchVIP(name, block_level, &comparetime, &splaytime);
                        if(splay.RootID() != name || splay.getRoot()== nullptr){
                            splay.destroytree();
                            deletenode(&head);
                            throw Undeclared(line);
                        }
                        if(splay.RootType() == "string"){
                            if (clone == "()->string"){
                                cout<<comparetime<<" "<<splaytime<<endl;
                            }
                            else{
                                splay.destroytree();
                                deletenode(&head);
                                throw TypeMismatch(line);
                            }
                        }
                        else if(splay.RootType() == "number"){
                            if (clone == "()->number"){
                                cout<<comparetime<<" "<<splaytime<<endl;
                            }
                            else{
                                splay.destroytree();
                                deletenode(&head);
                                throw TypeMismatch(line);
                            }
                        }
                        else{
                            splay.destroytree();
                            deletenode(&head);
                            throw TypeMismatch(line);
                        }
                    }
                    else{
                        splay.destroytree();
                        deletenode(&head);
                        throw TypeMismatch(line);
                    }
                }
                else {  // >= 1 tham so
                    string t1 = "";   // luu toan bo 123,43,'222',id
                    int q = value.length() - 1;
                    while (i < q) {   // check tung tham so va luu vao checkk
                        t1 += value[i];
                        if (i == q-1) {
                            inside += value[i];  // last bien
                            if (check_type(inside) == 3 || check_type(inside) == 5) {
                                splay.destroytree();
                                deletenode(&head);
                                throw InvalidInstruction(line);
                            }
                        } else if (value[i] == ',') {
                            if (check_type(inside) == 3) {
                                splay.destroytree();
                                deletenode(&head);
                                throw InvalidInstruction(line);
                            }
                            inside = "";
                        } else {
                            inside += value[i];
                        }
                        i++;
                    }
                    splay.searchVIP(iden, 0, &comparetime,&splaytime);
                    if (splay.RootID() != iden || splay.getRoot()== nullptr) {
                        splay.destroytree();
                        deletenode(&head);
                        throw Undeclared(line);
                    }
                    if (splay.RootType() == "string" || splay.RootType() == "number") {
                        splay.destroytree();
                        deletenode(&head);
                        throw TypeMismatch(line);
                    }
                    string dwg = splay.RootType();  //dwg = (number)->string
                    string rng = "";
                    int h = 1;
                    int w = (dwg.length() - 9);
                    while (h < w) {   // rng = number
                        rng += dwg[h];
                        h++;
                    }
                    h=h+3;
                    string type_dwg="";
                    while(h< w+9){
                        type_dwg += dwg[h];
                        h++;
                    }
                    int count1 =0;
                    int count2 =0;
                    int dc = 0;
                    int cd =0;
                    int re = t1.length();
                    int er = rng.length();
                    while(dc < re){   // dem so dau phay cua gan
                        if(t1[dc] == ','){
                            count1++;
                        }
                        dc++;
                    }
                    while(cd < er){    // lay so dau phay cua ham
                        if(rng[cd] == ','){
                            count2++;
                        }
                        cd++;
                    }
                    if(count1 != count2 || er ==0 ){  //so sanh so dau phay1
                        splay.destroytree();
                        deletenode(&head);
                        throw TypeMismatch(line);
                    }
                    string sktt1 = "";  // number
                    string faker = "";   //chua dang cua tham so trong ham de so sanh voi function
                    int c9 = 0;
                    int e = t1.length();
                    while (c9 < e) {   // t1 chua 1,2,123,'111'    sktt1 chua tung o 1
                        if (c9 == e - 1) {
                            sktt1 += t1[c9];
                            if (check_type(sktt1) == 1) {
                                faker += "number,";  //faker la string moi de so sanh
                            }
                            else if (check_type(sktt1) == 2) {
                                faker += "string,";
                            }
                            else if (check_type(sktt1) == 4) {  //iden
                                splay.searchVIP(sktt1, block_level, &comparetime, &splaytime);
                                if (splay.RootID() != sktt1 || splay.getRoot()== nullptr) {
                                    splay.destroytree();
                                    deletenode(&head);
                                    throw Undeclared(line);
                                }
                                if (splay.RootType() == "number") {
                                    faker += "number,";
                                }
                                else if (splay.RootType() == "string") {
                                    faker += "string,";
                                }
                                else {
                                    splay.destroytree();
                                    deletenode(&head);
                                    throw TypeMismatch(line);   // inden case function
                                }
                            }
                            else {
                            }
                        } else if (t1[c9] == ',') {
                            if (check_type(sktt1) == 3) {
                                splay.destroytree();
                                deletenode(&head);
                                throw InvalidInstruction(line);
                            }
                            else if (check_type(sktt1) == 1) {
                                faker += "number,";
                            }
                            else if (check_type(sktt1) == 2) {
                                faker += "string,";
                            }
                            else if (check_type(sktt1) == 4) { //iden
                                splay.searchVIP(sktt1, block_level, &comparetime, &splaytime);
                                if (splay.RootID() != sktt1 || splay.getRoot()== nullptr) {
                                    splay.destroytree();
                                    deletenode(&head);
                                    throw Undeclared(line);
                                }
                                if (splay.RootType() == "number") {
                                    faker += "number,";
                                }
                                else if (splay.RootType() == "string") {
                                    faker += "string,";
                                }
                                else {
                                    splay.destroytree();
                                    deletenode(&head);
                                    throw TypeMismatch(line);   // inden case function
                                }
                            }
                            sktt1 = "";
                        } else {
                            sktt1 += t1[c9];
                        }
                        c9++;
                    }
                    faker.pop_back();
                    if (faker == rng) {
                        splay.searchVIP(name, block_level, &comparetime, &splaytime);
                        if(splay.RootID() != name || splay.getRoot()== nullptr){
                            splay.destroytree();
                            deletenode(&head);
                            throw Undeclared(line);
                        }
                        if(splay.RootType() == type_dwg){
                            cout<<comparetime<<" "<<splaytime<<endl;
                        }
                        else{
                            splay.destroytree();
                            deletenode(&head);
                            throw TypeMismatch(line);
                        }
                    }
                    else{
                        splay.destroytree();
                        deletenode(&head);
                        throw TypeMismatch(line);
                    }
                }

            }
        }
        else if (search_begin != -1 && line[0] == 'B' && line.length() == 5) {
            block_level++;
        }
        else if (search_end != -1 && line[0] == 'E' && line.length() == 3) {
            int i=block_level -1;
            if (i < 0) {
                splay.destroytree();
                deletenode(&head);
                throw UnknownBlock();
            }
            if(head == nullptr){
                block_level--;
                continue;
            }
            node* start = head;
            while(start != nullptr){
                if(start->block_level == block_level){
                    splay.deleteNode(start->idd,start->block_level,&splaytime);
                }
                start = start->next;
            }

            block_level--;
        }
        else if (search_lookup != -1) {
            n = 7;
            line += "@";
            while (line[n] != '@') {

                name += line[n];
                n++;
            }
            line.pop_back();
            if (check_type(name)==3) {
                splay.destroytree();
                deletenode(&head);
                throw InvalidInstruction(line);
            }
            int max = 0;
            splay.searchVIP(name, block_level,&max,&max);
            TreePtr x = splay.getRoot();
            if(x == nullptr) {
                splay.destroytree();
                deletenode(&head);
                throw Undeclared(line);
            }
            if(x->identifier != name){
                splay.destroytree();
                deletenode(&head);
                throw Undeclared(line);
            }
            cout<<x->level<<endl;
        }
        else if (search_print != -1) {
            if(splay.Empty()==0){

            }
            else {
                string rrr;
                splay.preorder(&rrr);
                rrr.pop_back();
                cout<<rrr;
                cout<<endl;
            }
        }
        else{
            splay.destroytree();
            deletenode(&head);
            throw InvalidInstruction(line);
        }
    }
    if(block_level !=0){
        splay.destroytree();
        deletenode(&head);
        throw UnclosedBlock(block_level);
    }
    splay.destroytree();
    deletenode(&head);

}

