//pushato test2.cc
/******************************************************************
 *
 *
 *       Binary search tree class
 *
 *       In questi file implementiamo una classe per un bst.
 *       La classe ha come attributi privati una struct Node templetizzato che contiene i nodi dell'albero:
 *       Ogni nodo possiede una chiave, un valore, due pointer ai sottostante di sinistra e di destra e un pointer all'elemento sovrastante.
 *       La classe tree ha quattro variabili private: una size_tree che indica la dimensione dell'albero e tre pointer che indicano la
 *       la radice, l'elemento più piccolo e quello più grande.
 *
 *       L'albero ha inoltre due struct pubbliche: iterator e constiterator. La differenza fra le due consiste nella possibilità per gli iterator
 *       di modificare il valore del nodo a cui puntano. Anche per gli iterator tuttavia le chaivi sono accessibili solo in lettura, questo perchè
 *       altrimenti, una modifica della chiave potrebbe compromettere il funzionamento corretto dell'albero.
 *
 *       Molti dei metodi pubblici della classe fanno uso di sottofunzioni ricorsive, che sono però private per prevenirene un'utilizzo imoproprio
 *       essendo esse implementate solo ed esclusivamente per supportare i metodi pubblici da cui sono chiamate.
 *
 *
 *
 *******************************************************************/


/*   mancancti!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 
 -confronto std::map
 
 */




#include<iostream>
#include<utility>
#include<cmath>
#include<vector>
#include<ctime>
using std::string;
using std::cout;
using std::endl;


//classe errore funzionale al throw dell'exception
class ex_key {};


//classe Tree
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
    };
    
    //variabili dell'albero
    Node* first;
    Node* root;
    Node* last;
    
    unsigned int size_tree; //grandezza dell'albero
    
    
public:
    
    //info sull'albero
    Node* First() const{return first;}
    Node* Last() const{return last;}
    Node* Root() const{return root;}
    void print() const{cout<<"first "<<first->key<<"   root "<<root->key<<"     last "<<last->key<<"    size "<<size_tree<<endl;}
    unsigned int Size() const{return size_tree;}  //funzione per stampare la grandezza dell'albero
    
    
    //Costruttore dell'albero vuoto
    Tree(): //
    first{nullptr},root{nullptr},last{nullptr},size_tree{0} {}
    
    
    
    //insert simile una linked list, utile al performance testing
    void Linked_insert(int n) {
        int j{1};
        Node* elem=new Node{j,j};first=elem ; root=elem; last=elem;  size_tree=1;
        for(int i{2};i<n;i++) {elem=new Node{i,j,nullptr,nullptr,elem};elem->parent->right=elem;size_tree++;};
        last=elem;
    }
    
    //Metodo insert vero e proprio
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
    
    
    
    struct iterator {
        
        Node* current;
        iterator(Node* p):
        current{p} {}
        
        
        iterator& operator++(){
            if(current->right!=nullptr){ //cerca se può scendere a destra
                current=current->right;
                if(current->left!=nullptr){
                    while(current->left!=nullptr){  //da qui scende a sinistra fin tanto possibile
                        current=current->left;}
                }
                return *this;
            }
            
            else {
                if(current->key  <  current->parent->key) { //se può risale a destra
                    current=current->parent;
                    return *this;}
                
                else {
                    //l'ultima condizione serve per evitare di proseguire se si arriva alla radice
                    while(current->parent!=nullptr && current->key  >  current->parent->key ) { //in alternativa risale a sinistra
                        current=current->parent;
                    };
                    if(current->parent!=nullptr){ //se siamo arrivati in un nodo diverso dalla radice allora va bene
                        current=current->parent;  //infine sale a destra
                        return *this;}
                    
                    else{ // se siamo qua allora siamo nella radice,questo vuol dire che è partito dal last
                        current = nullptr;
                        return *this;}
                }
            }
            return *this;
        }
        
        iterator& operator--(){
            if(current->left!=nullptr){ //cerca se può scendere a destra
                current=current->left;
                if(current->right!=nullptr){
                    while(current->right!=nullptr){  //da qui scende a sinistra fin tanto possibile
                        current=current->right;}
                }
                return *this;
            }
            
            else {
                if(current->key  >  current->parent->key) { //se può risale a destra
                    current=current->parent;
                    return *this;}
                
                else {
                    while(current->key  <  current->parent->key) { //in alternativa risale a sinistra
                        current=current->parent;};
                    current=current->parent;  //infine sale a destra
                    return *this;
                };
                
            };
            return *this;
        }
        
        //la chiave non è accessibile. Una modifica della chiave potrebbe compromettere l'albero
        const T& operator*() const {return current->key;}
        
        W& operator!() const{return current->value;}  //ritorno del valore
        
        bool operator==(const iterator& b) const {return current==b.current;}
        bool operator!=(const iterator& b) const {return current!=b.current;}
        Node* node() const{return current;}
    };
    
    
    //metodi di iterator
    iterator ibegin(){
        return iterator{first};
    }
    //metodo end-->ritorna l'iteratore dopo last
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
    
    
    
    
    
    struct Constiterator{
        Node* current;
    public:
        Constiterator( Node* p): current{p} {}
        ~Constiterator()= default;
        
        
        const T& operator*() const  {return current->key;}
        const W& operator!() const {return current->value;}
        
        bool operator==(const Constiterator& b) const{
            return current==b.current;}
        
        bool operator!=(const Constiterator& b) const{
            return current!=b.current;}
        
        const Node* node() const {return current;}
        
        T& parent_key()  {
            if(current->parent==nullptr) {cout<<"we are in the root"<<endl; return current->key;};
            return current->parent->key;}
        
        Constiterator& operator++(){
            
            if(current->right!=nullptr){
                current=current->right;
                if(current->left!=nullptr){
                    while(current->left!=nullptr){
                        current=current->left;}
                }
                return *this;
            }
            
            else {
                if(current->key  <  current->parent->key) {
                    current=current->parent;
                    return *this;}
                
                else {
                    while(current->parent!=nullptr && current->key  >  current->parent->key) { current=current->parent;}
                    if(current->parent!=nullptr)   {current=current->parent; return *this;}
                    else  {current = nullptr; return *this;}
                };
                
                return *this;
            }
        }
        
        
        Constiterator& operator--(){
            if(current->left!=nullptr) {
                current=current->left;
                if(current->right!=nullptr){
                    while(current->right!=nullptr){ current=current->right;}
                }
                return *this;
            }
            else {
                if(current->key  >  current->parent->key) { current=current->parent;  return *this;}
                else {
                    while(current->key  <  current->parent->key) { current=current->parent;};
                    current=current->parent;  //infine sale a destra
                    return *this;
                };
                
            };
            return *this;
        }
    };
    //fine constiterator
    
    
    
    //Metodi dell'albero
    
    const Constiterator cbegin() const { return Constiterator{first};}
    const Constiterator cend() const { return Constiterator{nullptr};}
    const Constiterator croot() const {return Constiterator{root};}
    
    iterator find(const T t){
        Node* j{root};
        
        while(j!=nullptr){
            if(j->key == t){  cout<<"key found!"<<endl;
                iterator k {j};
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
    //la funzione ctr_insert è chiamata dai metodi della copy-move semantics
    void ctr_insert(Tree& t, Node* n) {
        t.Insert(n->key, n->value);
        if(n->left==nullptr and n->right==nullptr) return;
        if(n->left!=nullptr) ctr_insert(t,n->left);
        if(n->right!=nullptr)ctr_insert(t,n->right);}
    
    
public:
    
    //copy-move semantics
    
    Tree (const Tree<T,W>& t):
    first{nullptr},//************************ forse queste 4 non servono perché non è possibile usare il copy ctr con un oggetto già def
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
    
    
    
    // funzioni per il clear dell'albero
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
    
    //metodo che cancella l'albero in orizzontale
    void Iter_clear() {
        if (size_tree==0) return;
        iterator i{first};
        iterator j{i};
        root=nullptr;
        first=nullptr;
        while(i!=ilast()) {
            ++i;
            if(j.node()->right!=nullptr and j.node()->parent!=nullptr) {
                j.node()->right->parent=j.node()->parent;
                if(j.node()->right->key < j.node()->parent->key ) {j.node()->parent->left=j.node()->right;}
                else j.node()->parent->right=j.node()->right;
            };
            delete j.node() ;
            j=i;
        };
        delete i.node();
        last=nullptr;
        size_tree=0;
    }
    
    
    
    
    
    //funzioni per il balance
private:
    
    //funzione per il metodo rec_balance che lavora con una copy-move
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
    
    
    
    //funzioni chiamate da Rec_balance, chiamata a sua volta del secondo metodo Balance che agisce riassegnando i pointer
    
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
    
    
    
    
    //funzione ricorsiva chiamata dal metodo Balance
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
        //ora la mediana è figlia della root, si puà infine agire sulla root
        i.node()->parent=nullptr;
        if(i.node()->key<root->key) {root->left=nullptr;}
        else {root->right=nullptr;};
        Bal_reinsert(root,i.node()); //reinserisce la root
        root=i.node(); //ridefinisce la root
        Rec_Balance(i.node(),root,size_tree);
    }
    
    W& operator[](const T& k){
        iterator j{find(k)};
        if(j!=nullptr) return !j;
        Insert(k,W{});
        iterator q{find(k)};
        return !q;
        
    }
    
    //distrutore dell'albero
    ~Tree() {Clear();}
    
};
//fine della classe Tree



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
        A.Linked_insert(size);
        t=clock()-t;
        cout<<"Tempo per l'insert dell'albero:  "<<((float)t)/CLOCKS_PER_SEC<<endl<<endl;
        
        
        
        Tree<int, int>::iterator j{A.Last()};
        int search=*j;
        Tree<int, int>::iterator m{A.Last()};
        t=clock();
        m=A.find(search);
        t=clock()-t;
        cout<<"Tempo per il find:  "<<((float)t)/CLOCKS_PER_SEC<<endl<<endl;
        
        
        
        t=clock();
        A.Balance();
        t=clock()-t;
        cout<<"Tempo per il bilanciamento:  "<<((float)t)/CLOCKS_PER_SEC<<endl<<endl;
        
        
        t=clock();
        m=A.find(search);
        t=clock()-t;
        cout<<"Tempo per il find dopo il bilanciamento:  "<<((float)t)/CLOCKS_PER_SEC<<endl<<endl;
        
        
        
        t=clock();
        //A.Iter_clear();
        t=clock()-t;
        cout<<"Tempo per il delete:  "<<((float)t)/CLOCKS_PER_SEC<<endl<<endl;
        
        
        
        
        Tree<int,  int> B;
        t=clock();
        B.Linked_insert(size);
        t=clock()-t;
        cout<<"Tempo per l'insert dell'albero:  "<<((float)t)/CLOCKS_PER_SEC<<endl<<endl;
        Tree<int, int>::iterator k{B.Last()};
        
        search=*k;
        
        
        t=clock();
        B.Balance();
        t=clock()-t;
        cout<<"Tempo per il bilanciamento fast:  "<<((float)t)/CLOCKS_PER_SEC<<endl<<endl;
        
        t=clock();
        k=B.find(search);
        t=clock()-t;
        cout<<"Tempo per il find dopo il bilanciamento:  "<<((float)t)/CLOCKS_PER_SEC<<endl<<endl;
        
        
        cout<<endl<<endl<<endl;
        B.Clear();
        
        cout<<"OOOOOOOOOOOOOOOOOOOOOOOOOOO"<<endl;
        A[4];
        
        
        return 0;
        
    }
    
    
    
    
    catch (const ex_key) {cout<<"exception has been thrown "<<endl;return 1;}
    catch(...) {cout<<"unexpected error "<<endl;}
    
}
