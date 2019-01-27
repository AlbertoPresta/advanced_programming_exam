#include"Tree.h"
#include<iostream>

/*
 Authors: Alberto Presta and Andrea Gasparin.
 This Header contains the implementation of iterator and Constiterator of our Tree class.
 Iterator and Constiterator are nested class of out Tree, and Moreover Constiterator is a derived class of iterator
 
 */
 
 
 




using std::string;
using std::cout;
using std::endl;




template<typename T,typename W,typename K>
class Tree<T,W,K>::iterator{
    using Node = Tree<T,W,K>::Node;
protected:
    Node* current;
    const K oper;
    null_object<T> static null;
public:
    iterator(Node* p, const  Tree<T,W,K>& t=null): //const
    current{p}, oper{t.oper} {}
    
    iterator(Node* p):
    current{p}, oper{null} {}
    
    bool less(const T& a,const  T&b) const  {return oper(a,b);}
    bool equal(const T& a,const  T&b) const  {if (!less(a,b) and !less(b,a)) return true; return false;}
    bool greater(const T& a,const T&b) const  {if (!less(a,b) and !equal(a,b)) return true; return false;}
    
    
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
            if(current->parent==nullptr) {current=nullptr; return *this;};
            if(less(current->key,current->parent->key) ){ //se può risale a destra
                current=current->parent;
                return *this;}
            
            else {
                //l'ultima condizione serve per evitare di proseguire se si arriva alla radice
                while(current->parent!=nullptr && greater(current->key  ,  current->parent->key)) { //in alternativa risale a sinistra
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
            if(current->parent==nullptr) {current=nullptr; return *this;}
            if(greater(current->key  ,  current->parent->key)) { //se può risale a destra
                current=current->parent;
                return *this;}
            
            else {
                while(less(current->key  , current->parent->key)) { //in alternativa risale a sinistra
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
    const T& parent_key() const  {
        if(current->parent==nullptr) {cout<<"we are in the root"<<endl; return current->key;};
        return current->parent->key;}

   
};


template<typename T,typename W,typename K>
typename Tree<T,W,K>::iterator Tree<T,W,K>::begin() const{return iterator{first,*this};}


template<typename T,typename W,typename K>
typename Tree<T,W,K>::iterator Tree<T,W,K>::end() const{return iterator{nullptr,*this};}

template<typename T,typename W,typename K>
    class Tree<T,W,K>::Constiterator : public Tree<T,W,K>::iterator {
    
    
public:
    using parent = Tree<T,W,K>::iterator;
    using parent::iterator;
        
    const T& operator*() const {return parent::operator*();}
    const W& operator!() const {return parent::operator!();}
    
    
    const Node* node() const {return parent::node();}
    
    
    const T&  parent_key() const {return parent::parent_key();}
    };
    

 template<typename T,typename W,typename K>
 typename Tree<T,W,K>::Constiterator Tree<T,W,K>::cbegin() const  { return Constiterator{first,*this};}

template<typename T,typename W,typename K>
 typename Tree<T,W,K>::Constiterator Tree<T,W,K>::cend() const {return Constiterator{nullptr,*this};}

template<typename T,typename W,typename K>
typename Tree<T,W,K>::iterator Tree<T,W,K>::find (const T& t) const {
         Node* j{root};
         int i{0};
         while(j!=nullptr){i++;
             if(equal(j->key,t)){ cout<<"key found! "<<endl;cout<<"number of iterations: "<<i<<endl; iterator k{j,*this}; return k;}
            
            else{
                if(greater(j->key,t)){j=j->left;}
                else{j=j->right;}}
            
         }
         cout<< "key not found!"<<endl;
         iterator k{j,*this};
         return k;
     }
