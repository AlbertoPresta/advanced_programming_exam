//5
#include<iostream>
#include<memory>

using std::string;
using std::cout;
using std::endl;


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
    
    void ctr_insert(Tree& t, Node* n) {
        t.Insert(n->key, n->value);
        if(n->left==nullptr and n->right==nullptr) return;
        if(n->left!=nullptr) ctr_insert(t,n->left);
        if(n->right!=nullptr)ctr_insert(t,n->right);}

    
public:
    
    T First() const{return first->key;}
    T Last() const{return last->key;}
    T Root() const{return root->key;}
    unsigned int Size() const{return size_tree;}  //funzione per stampare la grandezza dell'albero
    
    template<typename OT,typename OW>
    friend std::ostream& operator<<(std::ostream&, const Tree<OT,OW>&);
    Tree(): //costruttore dell'albero
        first{nullptr},root{nullptr},last{nullptr},size_tree{0} {}
        
        
    
    
    
    
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
                        while(current->key  <  current->parent->key) { //in alternativa risale a sinistra
                            current=current->parent;
                            };
                            current=current->parent;  //infine sale a destra
		                       return *this;
		                   };
            
		               };
		               return *this;    
		               }
        //Iterator& operator--(){   --> secondo me non serve
            //da implementare
          //  return *this;    
            //}
        T operator*() {
            return current->key;
            }
        W operator!(){
            return current->value;
        }
        bool operator==(const iterator& b){return current==b.current;}
        bool operator!=(const iterator& b){return current!=b.current;}
        
        Node* node() const{return current;}
    };
    
    
    
    
    
    
    //CONST ITERATOR
    
    struct Constiterator{
         const Node* current;
        Constiterator(const Node* p): current{p} {}
    
    
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
          return current->key;
            }
        W operator!(){
          return current->value;
            }
        
        bool operator==(const Constiterator& b){
            return current==b.current;
            }
        bool operator!=(const Constiterator& b){
            return current!=b.current;
            }
            
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
            
        ~Constiterator()= default;
        };
    
    
    
    //FINE CONST ITERATOR
    //METODO FIND
   iterator find(const T t){
       Node* j{root};
       while(j!=nullptr){
         
           if(j->key == t){
               cout<<"key found!"<<endl;
               return j;
           }
           else{
               if(j->key > t){
                 
                   j=j->left;
                  
               }
               
               else{
                 
                    j=j->right;
                  
               }
           }
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
   


    void recursive_clear(Node* n){
        Node* l{n->left};
        Node* r{n->right};
        delete n;
        n=nullptr;
        if(l==nullptr and r==nullptr) return;
        if(l!=nullptr) recursive_clear(l);
        if(r!=nullptr) recursive_clear(r);
        }
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
};

template<typename T,typename W>
std::ostream& operator<<(std::ostream& os, const Tree<T,W>& l) {
    if (l.Size()==0) {cout<<"empty tree"<<endl; return os;}
    else {
    typename Tree<T,W>::Constiterator j = l.first;
    for(; j!=l.last;++j){
        os <<"key: "<<*j<<"   value: " <<!j<<endl;
        }
    os <<"key: "<<*j<<"   value: " <<!j<<endl;

    return os ;}
}

int main() {

Tree<string, long long int> Albero;

Albero.Insert("alberto",3409941121);
Albero.Insert("giacomo",3389543211);
Albero.Insert("francesco",3393578976);
Albero.Insert("giulia",3315899435);
Albero.Insert("eleonora",338775523);
Albero.Insert("andrea",340987436);

cout<<"size "<<Albero.Size()<<"  first "<<endl<<endl;
Albero.First();

cout<<endl<<"ecco l'albero!"<<endl;
cout<< Albero <<endl;
   

    Tree<string,long long int>::iterator j{Albero.find("giulia")};

    cout<<*j<<endl<<endl;

Tree<string, long long int> Albero_copia{Albero};
cout<<endl<<"Albero copia"<<endl<<Albero_copia<<endl<<endl;
Albero.Insert("gigi",1);
cout<<endl<<"Albero"<<endl<<Albero<<endl<<endl;
cout<<endl<<"Albero copia"<<endl<<Albero_copia<<endl<<endl;
Albero_copia.Insert("maurizio",2);
cout<<endl<<"Albero"<<endl<<Albero<<endl<<endl;
cout<<endl<<"Albero copia"<<endl<<Albero_copia<<endl<<endl;
Albero_copia.Clear();
//cout<<endl<<"Albero"<<endl<<Albero<<endl<<endl;
cout<<endl<<"Albero copia"<<endl<<Albero_copia<<endl<<endl;
Tree<string, long long int> Albero_vuoto;
Albero_vuoto.Clear();
cout<<Albero_vuoto<<endl;

}
