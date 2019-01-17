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
    bool trova(const T& t);
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

