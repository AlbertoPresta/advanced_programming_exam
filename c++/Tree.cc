//pushato test.cc
#include<iostream>
#include<utility>
#include<cmath>
#include<vector>
#include<ctime>
#include<chrono>
using std::string;
using std::cout;
using std::endl;



class ex_key {};


/*   mancancti!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 
 -test
 
 -ultimo punto
 
 
 
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
        Node (T& k,W& v, Node* l=nullptr, Node* r=nullptr,Node* p=nullptr):
        key{k}, value{v}, left{l}, right{r}, parent{p} {}
        ~Node() {left=nullptr;right=nullptr;parent=nullptr;}
        
        
        /*   //copy constructor per il nodo
         Node(const Tree<T, W>::Node& n):
         key{n.key}, value{n.value}, left{nullptr}, right{nullptr}, lparent{nullptr},rparent{nullptr} {}*/
        
    };
    
    Node* first;
    Node* root;
    Node* last;
    
    unsigned int size_tree; //grandezza dell'albero
    
    
public:
    
    Node* First() const{return first;}
    Node* Last() const{return last;}
    Node* Root() const{return root;}
    void print() const{cout<<"first "<<first->key<<"   root "<<root->key<<"     last "<<last->key<<"    size "<<size_tree<<endl;}
    unsigned int Size() const{return size_tree;}  //funzione per stampare la grandezza dell'albero
    
    //template<typename OT,typename OW>
    //friend std::ostream& operator<<(std::ostream&, const Tree<OT,OW>&);
    Tree(): //costruttore dell'albero
    first{nullptr},root{nullptr},last{nullptr},size_tree{0} {
        // Node* sentinel = new Node{T{},W{},nullptr,nullptr,nullptr};
    }
    
    
    
    //insert dedicato al time testing
    void test_insert(int n) {
        int j{1};
        Node* elem=new Node{j,j};first=elem ; root=elem; last=elem;  size_tree=1;
        for(int i{2};i<n;i++) {elem=new Node{i,j,nullptr,nullptr,elem};elem->parent->right=elem;size_tree++;};
        last=elem;
    }
    //Insert non accetta referenza perchè può essere chiamato by value
    void Insert(T k,W v)  {
        //inserimento primo elemento
        if (size_tree==0) {Node* elem=new Node{k,v}; first=elem ; root=elem; last=elem;  size_tree=1;return;};
        Node* p{root};
        
        
        bool FIRST{true}; //booleano che serve a identificare l'ultimo nodo a sinistra, first
        bool LAST{true};
        
        while(!(p->left ==nullptr && p->right==nullptr) && !(p->left==nullptr && k<p->key) && !(p->right==nullptr && k>p->key)) {
            if(k<p->key) {p=p->left;LAST=false;} //scende a sinistra. Se lo fa una volta sicuramente non è l'ultimo elemento
            else {
                if(p->key==k) {cout<<"key already assigned: "<<k<<", value: "<<p->value<<endl;throw ex_key{};};
                p=p->right;FIRST=false;};      //speculare, se scende a destra una volta certamente non è il first
        };
        //per la condizione del while, p è l'ultimo nodo preesistente
        
        Node* elem=new Node{k,v,nullptr,nullptr,p}; //inserisce il nuovo nodo con p parente
        
        if(k<p->key) {p->left=elem; if (FIRST==true) first=elem;} //aggiorna il ramo sinistro di p
        else {p->right=elem; if (LAST==true) last=elem; };          //aggiorna il ramo destro di p
        
        size_tree++; //aggiornamento grandezza albero
        
    }
    
    
    
    struct iterator{
        Node* current;
        iterator(Node* p):
        current{p} {}
        
        //metodi di iterator!
        //metodo begin--> ritorn l'iteratore first,cioè quello con la chiave più piccola
        
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
                    //l'ultima condizione serve per evitare di proseguire se si arriva alla radice
                    while(current->parent!=nullptr && current->key  >  current->parent->key ) { //in alternativa risale a sinistra
                        current=current->parent;
                    };
                    if(current->parent!=nullptr){ //se siamo arrivati in un nodo diverso dalla radice allora va bene
                        current=current->parent;  //infine sale a destra
                        return *this;
                    }
                    else{ // se siamo qua allora siamo nella radice,questo vuol dire che siamo partiti dal last!
                        current = nullptr;
                        return *this;
                    }
                }
                
            }
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
        const T& operator*() const {
            return current->key;
        }
        W& operator!() const{
            return current->value;
        }
        bool operator==(const iterator& b) const {return current==b.current;}
        bool operator!=(const iterator& b) const {return current!=b.current;}
        
        Node* node() const {return current;}
    };
    
    
    //metodi di iterator
    iterator ibegin(){
        return iterator{first};
    }
    //metodo end-->ritorna l'iteratore dopo last--> NON SICURO
    iterator iend(){
        return iterator{nullptr};
    }
    
    // ritorna l'iteratore con chiave più grande
    
    iterator ilast(){
        return iterator{last};
    }
    
    //ritorna l'iteratore puntato alla radice
    iterator iroot(){
        return iterator{root};
    }
    
    
    
    
    //CONST ITERATOR
    
    class Constiterator{
        Node* current;
    public:
        Constiterator( Node* p): current{p} {
            
        }
        
        
        
        const T& operator*() const  {
            return current->key;
        }
        const W& operator!() const {
            return current->value;
        }
        
        bool operator==(const Constiterator& b){
            return current==b.current;
        }
        bool operator!=(const Constiterator& b){
            return current!=b.current;
        }
        
        T& parent_key()  {
            if(current->parent==nullptr) {cout<<"we are in the root"<<endl; return current->key;};
            return current->parent->key;
        }
        
        Constiterator& operator++(){
            
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
                    //la condizione current->parent!=nullptr ci garantisce il non finire sulla radice
                    
                    while(current->parent!=nullptr && current->key  >  current->parent->key) { //in alternativa risale a sinistra
                        //cout<<"check-in "<<current->key<<endl;
                        current=current->parent;
                    }
                    if(current->parent!=nullptr){ //se siamo arrivati in un nodo diverso dalla radice allora va bene
                        current=current->parent;  //infine sale a destra
                        return *this;
                    }
                    else{ // se siamo qua allora siamo nella radice,questo vuol dire che siamo partiti dal last!
                        current = nullptr;
                        return *this;
                    }
                    
                };
                
                return *this;
            }
        }
        
        const Node* node() const {return current;}
        
        ~Constiterator()= default;
        
    private:
        
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
            
        }
    };
    
    
    
    //FINE CONST ITERATOR
    //METODO FIND
    iterator find(const T t){
        Node* j{root};
        
        while(j!=nullptr){
            if(j->key == t){
                cout<<"key found!"<<endl;
                iterator k{j};
                return k;}
            else{
                if(j->key > t){j=j->left;}
                else{j=j->right;}}
        }
        cout<< "key not found!"<<endl;
        iterator k{j};
        return k;
    }
private:
    void ctr_insert(Tree& t, Node* n) {
        t.Insert(n->key, n->value);
        if(n->left==nullptr and n->right==nullptr) return;
        if(n->left!=nullptr) ctr_insert(t,n->left);
        if(n->right!=nullptr)ctr_insert(t,n->right);}
    
    
public:
    const Constiterator cbegin() const {
        return Constiterator{first};
    }
    
    const Constiterator cend() const {
        
        return Constiterator{nullptr};
    }
    
    const Constiterator croot() const{
        return Constiterator{root};
    }
    
    
    //copy semantics
    Tree (const Tree<T,W>& t):
    first{nullptr},
    root {nullptr},
    last{nullptr},
    size_tree{0}  {
        ctr_insert(*this,t.root);
    }
    
    Tree (Tree<T,W>&& t):
    first{nullptr},
    root {nullptr},
    last{nullptr},
    size_tree{0}  {
        ctr_insert(*this,t.root);
        t.Clear();
        t.root=nullptr;
        t.first=nullptr;
        t.last=nullptr;
        t.size_tree=0;
    }
    
    Tree& operator=(const Tree<T,W>& t) {
        Clear();
        ctr_insert(*this,t.root);
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
        return *this;
    }
    
    
private:
    
    void recursive_clear (Node* n) noexcept{
        Node* l{n->left};
        Node* r{n->right};
        delete n;
        n=nullptr;
        if(l==nullptr and r==nullptr) return;
        if(l!=nullptr) recursive_clear(l);
        if(r!=nullptr) recursive_clear(r);
    }
    
    
public:
    void Clear() noexcept{
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
    
    
    
    
    
    
    
    
    
private:
    
    
    
    void rec_balance (unsigned int s, Tree<T,W>& b, Tree<T,W>::iterator m, int lun) noexcept{
        
        b.Insert(*m,!m);
        if(b.Size()==s) return;
        
        int lun_l{lun/2};
        int lun_r{lun-1-lun_l};
        iterator i{m};
        iterator j{m};
        
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
    
    void Bal_reinsert (Node* n,Node* r) noexcept{
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
    
    void left_branch_deattaching (Node* a, Node* m)noexcept{
        m->parent->right=nullptr;
        m->parent=a->parent;
        if(a->parent->key < m->key) {a->parent->right=m;}
        else {a->parent->left=m;};
        a->parent=nullptr;
    }
    
    void right_branch_deattaching (Node* a, Node* m) noexcept{
        m->parent->left=nullptr;
        m->parent=a->parent;
        if(a->parent->key < m->key) {a->parent->right=m;}
        else {a->parent->left=m;};
        a->parent=nullptr;
    }
    
    
    
    
    
    void Rec_Balance (Node* m, Node* r, int lun)noexcept{
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
    
    void balance() noexcept{
        
        Tree<T,W> b;
        iterator i{first};
        for(unsigned int ii{1};ii<size_tree/2+1;ii++) ++i;
        rec_balance(size_tree,b,i,size_tree);
        *this=std::move(b);}
    
    
    void Balance() noexcept{
        
        
        if(size_tree<2) return;
        iterator i{first};
        for(unsigned int ii{1};ii<size_tree/2+1;ii++) ++i;   //cerca la mediana
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
    
    W& operator[](const T& k){
        iterator j{find(k)};
        if(j!=nullptr) return !j;
        Insert(k,W{});
        iterator q{find(k)};
        return !q;
        
    }
    
    
    
};

template<typename T,typename W>
std::ostream& operator<<(std::ostream& os, const Tree<T,W>& l) {
    if (l.Size()==0) {cout<<"empty tree"<<endl; return os;}
    else {
        typename Tree<T,W>::Constiterator j =l.cbegin();
        for(; j!=l.cend();++j){
            os <<"key: "<<*j<<"   value: " <<!j<<"      parent: "<<j.parent_key()<<endl;
        }
        
        
        return os ;}
}











int main() {
    
    try{
        cout<<endl<<endl<<endl;
        
        
        
        long int size=1*pow(10,4);
        
        
        
        Tree<int,  int> A;
        clock_t t{clock()};
        A.test_insert(size);
        t=clock()-t;
        cout<<"Tempo per l'insert dell'albero:  "<<((double)t)/CLOCKS_PER_SEC<<endl<<endl;
        
        
        
        Tree<int, int>::iterator j{A.Last()};
        int search=*j;
        Tree<int, int>::iterator m{A.Last()};
        
        t=clock();
        m=A.find(search);
        t=clock()-t;
        cout<<"Tempo per il find:  "<<((double)t)/CLOCKS_PER_SEC<<endl<<endl;
        
        
        
        t=clock();
        A.Balance();
        t=clock()-t;
        cout<<"Tempo per il bilanciamento:  "<<((double)t)/CLOCKS_PER_SEC<<endl<<endl;
        
        
        t=clock();
        
        m=A.find(search);
        t=clock()-t;
        
        cout<<"Tempo per il find dopo il bilanciamento:  "<<((long double)t)/CLOCKS_PER_SEC<<endl<<endl;
        
        
        
        t=clock();
        //A.Clear();
        t=clock()-t;
        cout<<"Tempo per il delete:  "<<((double)t)/CLOCKS_PER_SEC<<endl<<endl;
        
        
        
        
        Tree<int,  int> B;
        t=clock();
        B.test_insert(size);
        t=clock()-t;
        cout<<"Tempo per l'insert dell'albero:  "<<((double)t)/CLOCKS_PER_SEC<<endl<<endl;
        Tree<int, int>::iterator k{B.Last()};
        
        search=*k;
        
        
        t=clock();
        B.Balance();
        t=clock()-t;
        cout<<"Tempo per il bilanciamento fast:  "<<((double)t)/CLOCKS_PER_SEC<<endl<<endl;
        
        t=clock();
        
        k=B.find(search);
        t=clock()-t;
        
        
        cout<<"Tempo per il find dopo il bilanciamento:  "<<((double)t)/CLOCKS_PER_SEC<<endl<<endl;
        
        
        cout<<endl<<endl<<endl;
        
        
        
        
        return 0;
        
    }
    
    
    
    
    catch (const ex_key) {cout<<"exception has been thrown "<<endl;return 1;}
    catch(...) {cout<<"unexpected error "<<endl;}
    
}
