<<<<<<< HEAD
//12
#include<iostream>
#include<memory>
#include<utility>
#include<cmath>
#include<vector>
=======

#include<iostream>
#include<memory>
#include<utility>

>>>>>>> 116fc03f755b0d51e002d7e54356615a3b40b322
using std::string;
using std::cout;
using std::endl;


/*   mancancti!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
-const e no except
-ced e annesso operatore ++
-test
-test con oggetti
-ultimo punto
-error handling
    -caso chiavi uguali
    -vedere se metto oggetti, cioè se non è def l'overloading dell'operatore <
    
-aiuto devo pushare gli eserizi, e a sto punto i rivediamo

*/

//IN QUESTO  CODICE SI IMPLEMENTA I CONSTITERATOR INDIPENDENTEMENTE DAGLI ITERATOR--> MOLTO SCOMODO VISTO CHE IL CODICE DIVENTA INCREDIBILMENTE LUNGO: ITERATOR E CONST ITERATOR SONO PRATICAMENTE UGUALI! PROVO A FARE CLASSE EREDITATA!

template<typename T,typename W>
class Tree{
    
    struct Node{
        T key;
        W value;
        Node* left;
        Node* right;
        Node* parent;
        Node (T& k, W& v, Node* l=nullptr, Node* r=nullptr,Node* p=nullptr):
        key{k}, value{v}, left{l}, right{r}, parent{p} {}
        ~Node() {left=nullptr;right=nullptr;parent=nullptr;}
        
        /*
         //copy constructor per il nodo
         Node(const Tree<T, W>::Node& n):
         key{n.key}, value{n.value}, left{nullptr}, right{nullptr}, lparent{nullptr},rparent{nullptr} {}*/
        
    };
    
    Node* first;
    Node* root;
    Node* last;
    unsigned int size_tree; //grandezza dell'albero
<<<<<<< HEAD
        
=======
    
    void ctr_insert(Tree& t, Node* n) {
        t.Insert(n->key, n->value);
        if(n->left==nullptr and n->right==nullptr) return;
        if(n->left!=nullptr) ctr_insert(t,n->left);
        if(n->right!=nullptr)ctr_insert(t,n->right);}
    
>>>>>>> 116fc03f755b0d51e002d7e54356615a3b40b322
    
public:
    
    Node* First() const{return first;}
    Node* Last() const{return last;}
    Node* Root() const{return root;}
    void print() const{cout<<"first "<<first->key<<"   root "<<root->key<<"     last "<<last->key<<endl;}
    unsigned int Size() const{return size_tree;}  //funzione per stampare la grandezza dell'albero
    
    template<typename OT,typename OW>
    friend std::ostream& operator<<(std::ostream&, const Tree<OT,OW>&);
    Tree(): //costruttore dell'albero
<<<<<<< HEAD
        first{nullptr},root{nullptr},last{nullptr},size_tree{0} {}
        
=======
    first{nullptr},root{nullptr},last{nullptr},size_tree{0} {}
    
>>>>>>> 116fc03f755b0d51e002d7e54356615a3b40b322
    
    
    
    void Insert(T k, W v)  {
        //inserimento primo elemento
        if (size_tree==0) {Node* elem=new Node{k,v}; first=elem ; root=elem; last=elem; size_tree=1;return;};
        Node* p{root};
        
        
        bool FIRST{true}; //booleano che serve a identificare l'ultimo nodo a sinistra, first
        bool LAST{true};
        
        while(!(p->left ==nullptr && p->right==nullptr) && !(p->left==nullptr && k<p->key) && !(p->right==nullptr && k>p->key)) {
            if(k<p->key) {p=p->left;LAST=false;} //scende a sinistra. Se lo fa una volta sicuramente non è l'ultimo elemento
            else {p=p->right;FIRST=false;};      //speculare, se scende a destra una volta certamente non è il first
        };
        //per la condizione del while, p è l'ultimo nodo preesistente
        
        Node* elem=new Node{k,v,nullptr,nullptr,p}; //inserisce il nuovo nodo con p parente
        
        if(k<p->key) {p->left=elem; if (FIRST==true) first=elem;} //aggiorna il ramo sinistro di p
        else {p->right=elem; if (LAST==true) last=elem; };          //aggiorna il ramo destro di p
        
        size_tree++; //aggiornamento grandezza albero
    }
    
    
    
public: //forse va cancellato
    struct iterator{
        Node* current;
        iterator(Node* p):
        current{p} {}
        
        //metodi di iterator!
        //metodo begin--> ritorn l'iteratore first,cioè quello con la chiave più piccola
        iterator begin(){
            return iterator{first};
        }
        //metodo end-->ritorna l'iteratore dopo last--> NON SICURO
        iterator end(){
            return iterator{nullptr};
        }
        
        // ritorna l'iteratore con chiave più grande
        iterator last(){
            return iterator{last};
        }
        //ritorna l'iteratore puntato alla radice
        iterator root(){
            return iterator{root};
        }
        iterator& operator++(){
            if(current->right!=nullptr){ //cerca se può scendere a destra
                current=current->right;
                if(current->left!=nullptr){
                    while(current->left!=nullptr){  //da qui scende a sinistra fin tanto possibile
                        current=current->left;
                    }
                }
                return *this;
            }
            else {
                if(current->key  <  current->parent->key) { //se può risale a destra
                    current=current->parent;
                    return *this;
                }
                else {
                    while(current->key  >  current->parent->key) { //in alternativa risale a sinistra
                        current=current->parent;
                    };
                    current=current->parent;  //infine sale a destra
                    return *this;
                };
                
            };
            return *this;
        }
        iterator& operator--(){
            if(current->left!=nullptr){ //cerca se può scendere a destra
                current=current->left;
                if(current->right!=nullptr){
                    while(current->right!=nullptr){  //da qui scende a sinistra fin tanto possibile
                        current=current->right;
                    }
                }
                return *this;
            }
            else {
                if(current->key  >  current->parent->key) { //se può risale a destra
                    current=current->parent;
                    return *this;
                }
                else {
                    while(current->key  <  current->parent->key) { //in alternativa risale a sinistra
                        current=current->parent;
                    };
                    current=current->parent;  //infine sale a destra
                    return *this;
                };
                
            };
            return *this;
            
        }
        T operator*() {
            return current->key;
<<<<<<< HEAD
            }
        W operator!(){
            return current->value;
=======
        }
        T operator!(){
            if(current->parent==nullptr) return 10000;
            return current->parent->key;
>>>>>>> 116fc03f755b0d51e002d7e54356615a3b40b322
        }
        bool operator==(const iterator& b){return current==b.current;}
        bool operator!=(const iterator& b){return current!=b.current;}
        
        Node* node() {return current;}
    };
    
    
    
    
    
    
    //CONST ITERATOR
    
    struct Constiterator{
<<<<<<< HEAD
          Node* current;
        Constiterator( Node* p): current{p} {}
    
    
=======
        Node* current;
        Constiterator( Node* p): current{p} {}
        
        
>>>>>>> 116fc03f755b0d51e002d7e54356615a3b40b322
        Constiterator cbegin() const {
            return Constiterator{first};
        }
        
        Constiterator cend() const {
            return Constiterator{nullptr};
        }
        
        Constiterator croot() const{
            return Constiterator{root};
        }
        Constiterator clast() const{
            return Constiterator{last};
        }
        T operator*() {
<<<<<<< HEAD
          return current->key;
            }
        W operator!(){
          return current->value;
            }
=======
            return current->key;
        }
        T operator!(){
            if(current->parent==nullptr) return 10000;
            return current->parent->key;
        }
>>>>>>> 116fc03f755b0d51e002d7e54356615a3b40b322
        
        bool operator==(const Constiterator& b){
            return current==b.current;
        }
        bool operator!=(const Constiterator& b){
            return current!=b.current;
<<<<<<< HEAD
            }
        
        T parent_key()  {
            if(current->parent==nullptr) {cout<<"we are in the root"<<endl; return current->key;};
            return current->parent->key;
        }
            
=======
        }
        
>>>>>>> 116fc03f755b0d51e002d7e54356615a3b40b322
        Constiterator& operator++(){
            {
                if(current->right!=nullptr){ //cerca se può scendere a destra
                    current=current->right;
                    if(current->left!=nullptr){
                        while(current->left!=nullptr){  //da qui scende a sinistra fin tanto possibile
                            current=current->left;
                        }
                    }
                    return *this;
                }
                else {
                    if(current->key  <  current->parent->key) { //se può risale a destra
                        current=current->parent;
                        return *this;
                    }
                    else {
                        while(current->key  >  current->parent->key) { //in alternativa risale a sinistra
                            current=current->parent;
                        };
                        current=current->parent;  //infine sale a destra
                        return *this;
                    };
                    
                };
                return *this;
            }
        };
        Constiterator& operator--(){
            if(current->left!=nullptr){ //cerca se può scendere a destra
                current=current->left;
                if(current->right!=nullptr){
                    while(current->right!=nullptr){  //da qui scende a sinistra fin tanto possibile
                        current=current->right;
                    }
                }
                return *this;
            }
            else {
                if(current->key  >  current->parent->key) { //se può risale a destra
                    current=current->parent;
                    return *this;
                }
                else {
                    while(current->key  <  current->parent->key) { //in alternativa risale a sinistra
                        current=current->parent;
                    };
                    current=current->parent;  //infine sale a destra
                    return *this;
                };
                
            };
            return *this;
            
        };
        Node* node() {return current;}
<<<<<<< HEAD
            
=======
        
>>>>>>> 116fc03f755b0d51e002d7e54356615a3b40b322
        ~Constiterator()= default;
    };
    
    
    
    //FINE CONST ITERATOR
    //METODO FIND
    iterator find(const T t){
        Node* j{root};
        while(j!=nullptr){
            if(j->key == t){
<<<<<<< HEAD
               cout<<"key found!"<<endl;
               return j;}
            else{
               if(j->key > t){j=j->left;}
               else{j=j->right;}}
            }
        cout<< "key not found!"<<endl;
        return j;
        }
private:
    void ctr_insert(Tree& t, Node* n) {
        t.Insert(n->key, n->value);
        if(n->left==nullptr and n->right==nullptr) return;
        if(n->left!=nullptr) ctr_insert(t,n->left);
        if(n->right!=nullptr)ctr_insert(t,n->right);}


public: 

   //copy semantics
    Tree (const Tree<T,W>& t):   //è da implementare la costruzione mediante il metodo insert
        first{nullptr},
        root {nullptr},
        last{nullptr},
        size_tree{0}  {
            ctr_insert(*this,t.root);
            }
=======
                cout<<"key found!"<<endl;
                return j;}
            else{
                if(j->key > t){j=j->left;}
                else{j=j->right;}}
        }
        cout<< "key not found!"<<endl;
        return j;
    }
    
    
    //copy semantics
    Tree (const Tree<T,W>& t):   //è da implementare la costruzione mediante il metodo insert
    first{nullptr},
    root {nullptr},
    last{nullptr},
    size_tree{0}  {
        ctr_insert(*this,t.root);
    }
>>>>>>> 116fc03f755b0d51e002d7e54356615a3b40b322
    
    Tree& operator=(const Tree<T,W>& t) {
        Clear();
        ctr_insert(*this,t.root);
<<<<<<< HEAD
=======
        cout<<"chiamato assignment"<<endl;
>>>>>>> 116fc03f755b0d51e002d7e54356615a3b40b322
        return *this;
    }
    
    Tree& operator=(Tree<T,W>&& t) {
        Clear();
        root=t.root;
        first=t.first;
        last=t.last;
        size_tree=t.size_tree;
        t.root=nullptr;
        t.first=nullptr;
        t.last=nullptr;
        t.size_tree=0;
<<<<<<< HEAD
        return *this;
    }


private:    

=======
        cout<<"chiamato move"<<endl;
        return *this;
    }
    
    
>>>>>>> 116fc03f755b0d51e002d7e54356615a3b40b322
    void recursive_clear(Node* n){
        Node* l{n->left};
        Node* r{n->right};
        delete n;
        n=nullptr;
        if(l==nullptr and r==nullptr) return;
        if(l!=nullptr) recursive_clear(l);
        if(r!=nullptr) recursive_clear(r);
<<<<<<< HEAD
        }  
    
    
public:   
=======
    }
>>>>>>> 116fc03f755b0d51e002d7e54356615a3b40b322
    void Clear() {
        if(size_tree==0) return;
        Node* n{root};
        root=nullptr;
        first=nullptr;
        last=nullptr;
        recursive_clear(n);
        size_tree=0;
    }
    
    
    
    //infine metto il distruttore di default
    ~Tree() {Clear();}
    
    
<<<<<<< HEAD







private:
    void rec_balance(int s, Tree<T,W>& b, Tree<T,W>::iterator m, int lun) {

        b.Insert(*m,!m);
        Node* p{b.Root()};
        if(b.Size()==s) return;

=======
    
    void rec_balance(int s, Tree<T,W>& b, Tree<T,W>::iterator m, int lun) {
        
        b.Insert(*m,9999);
        Node* p{b.Root()};
        if(b.Size()==s) return;
        
>>>>>>> 116fc03f755b0d51e002d7e54356615a3b40b322
        int lun_l{lun/2};
        int lun_r{lun-1-lun_l};
        iterator i{m};
        iterator j{m};
<<<<<<< HEAD

        if(lun_l>0) {
            for(int ii{1};ii<=lun_l/2+lun_l%2;ii++) --i;
            rec_balance(s,b,i,lun_l);
            };
        if(lun_r>0) {
            for(int jj{0};jj<=lun_r/2;jj++) ++j;
            rec_balance(s,b,j,lun_r);
            };
        return;  
    } 

    void Bal_reinsert(Node* n,Node* r) {
        Node* p{r};
        while(!(p->left ==nullptr and p->right==nullptr) and !
                (p->left==nullptr and n->key < p->key) and 
                !(p->right==nullptr and n->key > p->key)) 
            {
            if(n->key<p->key) {p=p->left;} 
            else {p=p->right;};      
                };
            if(n->key<p->key) {p->left=n;    n->parent=p; }       //aggiorna il ramo sinistro di p
            else         {p->right=n;   n->parent=p; };          //aggiorna il ramo destro di p
        } 
        
    void left_branch_deattaching(Node* a, Node* m){
        m->parent->right=nullptr;
        m->parent=a->parent;
        if(a->parent->key < m->key) {a->parent->right=m;}
        else {a->parent->left=m;};
        a->parent=nullptr;
    }

    void right_branch_deattaching(Node* a, Node* m) {
        m->parent->left=nullptr;
        m->parent=a->parent;
        if(a->parent->key < m->key) {a->parent->right=m;}
        else {a->parent->left=m;};
        a->parent=nullptr;
    }





    void Rec_Balance(Node* m, Node* r, int lun){
        if(m!=r){
        while (m->parent != r) {
            Node* a{m};
            if(a->parent->key < m->key){
                while (a->parent->key < m->key  and a->parent != r) a=a->parent;
                left_branch_deattaching(a,m);
                Bal_reinsert(a,m);
                a=m;
                };
            if (a->parent != r) {
                while (a->parent->key > m->key  and a->parent != r) a=a->parent;
                right_branch_deattaching(a,m);
                Bal_reinsert(a,m); 
                a=m;  };
            };
            };
            int lun_l{lun/2};
            int lun_r{lun-1-lun_l};
            iterator i{m};
            iterator j{m};
            
            if(lun_l>0) {
                for(int ii{1};ii<=lun_l/2+lun_l%2;ii++) --i;
                Rec_Balance(i.node(),m,lun_l);
                };
            if(lun_r>0) {
                for(int jj{0};jj<=lun_r/2;jj++) ++j;
                Rec_Balance(j.node(),m,lun_r);
                };
        return;  

} 
public: 

void balance() {

    Tree<T,W> b;
    iterator i{first};
    for(int ii{1};ii<size_tree/2+1;ii++) ++i;
    rec_balance(size_tree,b,i,size_tree);
    *this=std::move(b);}


void Balance(){
    
    
    if(size_tree<2) return;
    iterator i{first};
    for(int ii{1};ii<size_tree/2+1;ii++) ++i;   //cerca la mediana
    if(i.node()->parent!=root){ //fino al nodo sotto la root
        while (i.node()->parent!= root) {
            Node* m{i.node()};  //mediana
            Node* a{i.node()};  //mediana per iterare
            if(a->parent->key < m->key){
                while (a->parent->key < m->key  and a->parent!= root) a=a->parent; //risale a sinistra fino a quando possibile
                left_branch_deattaching(a,m); //stacca il pezzo da m ad a, riattacca m a a->parent
                Bal_reinsert(a,m); //reinserisce il pezzo reinserendo a
                a=m;  //aggiorna a
                };
            if (a->parent!= root) {
                while (a->parent->key > m->key  and a->parent!= root) a=a->parent;
                right_branch_deattaching(a,m);
                Bal_reinsert(a,m); 
                a=m;  };
            };
        };
     //ora che la mediana è sotto la root agisco sulla root
    i.node()->parent=nullptr; 
    if(i.node()->key<root->key) {root->left=nullptr;}
    else {root->right=nullptr;};
    Bal_reinsert(root,i.node()); //reinserisco la root
    root=i.node(); //ridefinisco la root
    Rec_Balance(i.node(),root,size_tree);
}
  
=======
        
        if(lun_l>0) {
            for(int ii{1};ii<=lun_l/2+lun_l%2;ii++) --i;
            cout<<endl;
            rec_balance(s,b,i,lun_l);
        };
        if(lun_r>0) {
            for(int jj{0};jj<=lun_r/2;jj++) ++j;
            rec_balance(s,b,j,lun_r);
        };
        return;
    }
    
    
    void balance() {
        cout<<root->key<<endl;
        Tree<T,W> b;
        iterator i{first};
        for(int ii{1};ii<size_tree/2+1;ii++) ++i;
        rec_balance(size_tree,b,i,size_tree);
        *this=std::move(b);
        cout<<"stampa "<<*this<<endl;
    }
    
    
    void Bal_reinsert(Node* n,Node* r) {
        Node* p{r};
        while(!(p->left ==nullptr and p->right==nullptr) and !(p->left==nullptr and n->key < p->key) and !(p->right==nullptr and n->key > p->key)) {
            if(n->key<p->key) {p=p->left;}
            else {p=p->right;};
        };
        
        
        if(n->key<p->key) {p->left=n;    n->parent=p; }       //aggiorna il ramo sinistro di p
        else         {p->right=n;   n->parent=p; };          //aggiorna il ramo destro di p
    }
    
    void Rec_Balance(Node* m, Node* r, int lun, int k){
        if(k>0){k--;
            cout<<endl<<endl<<"med "<<m->key<<"  root "<<r->key<<endl<<endl;
            
            if(m!=r){
                while (m->parent != r) {
                    
                    Node* a{m};
                    if(a->parent->key < m->key){
                        while (a->parent->key < m->key  and a->parent != r) {/*cout<<"left a key  "<<a->key<<endl;*/a=a->parent;};
                        cout<<"to the left "<<a->key<<endl;
                        cout<<*this<<endl;
                        //cout<<"left "<<a->key<<endl;
                        //cout<<"mp left  "<<m->parent->key<<endl;
                        m->parent->right=nullptr;
                        m->parent=a->parent;
                        if(a->parent->key < m->key) {a->parent->right=m;}
                        else {a->parent->left=m;};
                        a->parent=nullptr;
                        Bal_reinsert(a,m);
                        a=m;
                        cout<<"stampa"<<endl<<*this<<endl;};
                    if (a->parent != r) {
                        while (a->parent->key > m->key  and a->parent != r) {/*cout<<"right a key  "<<a->key<<endl;*/a=a->parent;};
                        cout<<"to the right "<<a->key<<endl;
                        cout<<*this<<endl;
                        m->parent->left=nullptr;
                        m->parent=a->parent;
                        if(a->parent->key < m->key) {a->parent->right=m;}
                        else {a->parent->left=m;};
                        a->parent=nullptr;
                        Bal_reinsert(a,m);
                        a=m;  };
                    cout<<"stampa"<<endl<<*this<<endl;
                };
            };
            int lun_l{lun/2};
            int lun_r{lun-1-lun_l};
            iterator i{m};
            iterator j{m};
            
            if(lun_l>0) {
                for(int ii{1};ii<=lun_l/2+lun_l%2;ii++) --i;
                Rec_Balance(i.node(),m,lun_l,k);
            };
            if(lun_r>0) {
                for(int jj{0};jj<=lun_r/2;jj++) ++j;
                Rec_Balance(j.node(),m,lun_r,k);
            };
            
            
        };
        return;
        
    }
    
    void Balance(){
        
        iterator i{first};
        for(unsigned int ii{1};ii<size_tree/2+1;ii++) ++i;
        Rec_Balance(i.node(),root,size_tree,25);
        root=i.node();
        
    }
    
>>>>>>> 116fc03f755b0d51e002d7e54356615a3b40b322
    
    
};

template<typename T,typename W>
std::ostream& operator<<(std::ostream& os, const Tree<T,W>& l) {
    if (l.Size()==0) {cout<<"empty tree"<<endl; return os;}
    else {
<<<<<<< HEAD
    typename Tree<T,W>::Constiterator j = l.first;
    for(; j!=l.last;++j){
        
        os <<"key: "<<*j<<"   value: " <<!j<<"      parent: "<<j.parent_key()<<endl;
        }
    os <<"key: "<<*j<<"   value: " <<!j<<"      parent: "<<j.parent_key()<<endl;

    return os ;}
=======
        typename Tree<T,W>::Constiterator j = l.first;
        int le,ri;
        for(; j!=l.last;++j){
            
            if(j.node()->left==nullptr) {le=99999;}
            else {le=j.node()->left->key;};
            if(j.node()->right==nullptr) {ri=99999;}
            else {ri=j.node()->right->key;};
            os <<"key: "<<*j<<"   parent: " <<!j<<"        left: "<<le<<"   right: "<<ri<<endl;
        }
        if(j.node()->left==nullptr) {le=99999;}
        else {le=j.node()->left->key;};
        if(j.node()->right==nullptr) {ri=99999;}
        else {ri=j.node()->right->key;};
        os <<"key: "<<*j<<"   parent: " <<!j<<"        left: "<<le<<"   right: "<<ri<<endl;
        
        return os ;}
>>>>>>> 116fc03f755b0d51e002d7e54356615a3b40b322
}




int main() {
<<<<<<< HEAD


std::vector<int> indici{43, 21, 23, 7, 2, 26, 49, 11, 5, 60, 45, 61, 41, 56, 30, 57, 46, 17, 53, 14, 33, 31, 15, 38, 29, 6, 59, 12, 3, 28, 36, 52, 13, 55, 54, 20, 39, 1, 44, 40, 48, 8, 35, 32, 47, 62, 51, 18, 25, 0, 58, 19, 16, 50, 42, 4, 10, 34, 37, 24, 22, 27, 9};


Tree<int, long long int> A;
for(int i{1};i<16;i++) {A.Insert(i,0);};
cout<<A<<endl;
A.print();
A.Balance();
A.print();
cout<<endl<<"++++++++++++++"<<endl <<A<<endl;
int height{0};
//for (int i{0};i<=5;i++) {height+=pow(2,i);cout<<" "<<height<<endl;};

p=A.find(100)
while (p!=A.cend()) {cout<<*p<<endl;p++;};


=======
    
    
    
    
    
    Tree<int, long long int> A;
    A.Insert(8,1);
    A.Insert(2,2);
    A.Insert(3,3);
    A.Insert(4,5);
    A.Insert(5,0);
    A.Insert(6,0);
    A.Insert(7,0);
    A.Insert(1,0);
    A.Insert(9,0);
    A.Insert(10,0);
    A.Insert(11,0);
    A.Insert(12,0);
    A.Insert(15,0);
    A.Insert(14,0);
    A.Insert(13,0);
    //cout<<A<<endl;
    A.print();
    A.Balance();
    A.print();
    cout<<endl<<"++++++++++++++"<<endl <<A<<endl;
    
    Tree<int, long long int> B{A};
    B.Insert(16,2);
    cout<<B<<endl;
    A=B;
    cout<<A<<endl;
    
>>>>>>> 116fc03f755b0d51e002d7e54356615a3b40b322
}
