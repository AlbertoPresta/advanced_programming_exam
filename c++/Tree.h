#include<iostream>
#include<memory>




using std::string;
using std::cout;
using std::endl;




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
    
    };

    Node* first;
    Node* root;
    Node* last;
    unsigned int size_tree; //grandezza dell'albero
    
    void ctr_insert(Tree& t, Node* n);
    
public:
    
    Node* First() const{return first;}
    Node* Last() const{return last;}
    Node* Root() const{return root;}
    unsigned int Size() const{return size_tree;}  //funzione per stampare la grandezza dell'albero
    
    template<typename OT,typename OW>
    friend std::ostream& operator<<(std::ostream&, const Tree<OT,OW>&);
    Tree(): //costruttore dell'albero
        first{nullptr},root{nullptr},last{nullptr},size_tree{0} {}
    void Insert(T k, W v);
    struct iterator;
    struct Constiterator;
    iterator find(const T& t);
    // implementazione della funzione trova
    bool trova(const T& t){
        Node* j{root};
        while(j!=nullptr){
            if(j->key == t){return true;}
            else{
                if(j->key > t) j=j->left;
                else j=j->right;}
        }
        return false;}
    
    iterator First(){return iterator{first};}
    iterator Last(){return iterator{last};}
    iterator Root(){return iterator{root};}
    iterator End(){return iterator{nullptr};}
  
    
};

//definisco la classe iteratore fuori della classe Tree
template<typename T ,typename W>
struct Tree<T,W>::iterator{
    using Node = Tree<T,W>::Node;
    Node* current;
    iterator(Node* p):
    current{p} {}
    
    
    T parent_key(){
        if(current->parent==nullptr) {
            cout<<"no parents,we are in the root!"<<endl;
            return current->key;
        }
        return current->parent->key;
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
    T& operator*() {
        return current->key;
    }
    T& operator!(){
        return current->value;
    }
    
    
    
    bool operator==(const iterator& b){return current==b.current;}
    bool operator!=(const iterator& b){return current!=b.current;}
    
   
};
template<typename T , typename W>
void Tree<T,W>::Insert(T k, W v){
//inserimento primo elemento
     if (size_tree==0) {Node* elem=new Node{k,v}; first=elem ; root=elem; last=elem; size_tree=1;return;};
     Node* p{root};
// VERIFICA CHE LA CHIAVE NON SIA GIA NELL'ALBERO
     if(trova(k)==true){
        string s{"chiave già presente"};
         cout<< s << endl;
         return ;}
      bool FIRST{true}; //booleano che serve a identificare l'ultimo nodo a sinistra, first
      bool LAST{true};
      while(!(p->left ==nullptr && p->right==nullptr) && !(p->left==nullptr && k<p->key) && !(p->right==nullptr && k>p->key)) {
           if(k<p->key) {p=p->left;LAST=false;} //scende a sinistra. Se lo fa una volta sicuramente non è l'ultimo elemento
           else {p=p->right;FIRST=false;}      //speculare, se scende a destra una volta certamente non è il first
            }
//per la condizione del while, p è l'ultimo nodo preesistente
      Node* elem=new Node{k,v,nullptr,nullptr,p}; //inserisce il nuovo nodo con p parente
      if(k<p->key) {p->left=elem; if (FIRST==true) first=elem;} //aggiorna il ramo sinistro di p
      else {p->right=elem; if (LAST==true) last=elem; };          //aggiorna il ramo destro di p
                size_tree++; //aggiornamento grandezza albero
}

