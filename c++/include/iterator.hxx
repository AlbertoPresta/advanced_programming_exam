#include"Tree.h"
#include<iostream>

/*
 Authors: Alberto Presta and Andrea Gasparin.
 This Header contains the implementation of iterator and Constiterator of our Tree class.
 Iterator and Constiterator are nested class of our Tree, and Moreover Constiterator is a derived class of iterator.
 
 there is also the implem
 
 */
 
 
 




using std::string;
using std::cout;
using std::endl;


/* ITERATOR: they have the following data types:
- node* current
 - the operation oper which characterizes the tree
*/
template<typename T,typename W,typename K>
class Tree<T,W,K>::iterator{
    using Node = Tree<T,W,K>::Node;
protected:
    Node* current;
    const K oper;
    const null_object<T> static null;
public:
    iterator(Node* p, const  Tree<T,W,K>& t=null):
    current{p}, oper{t.oper} {}
    
    iterator(Node* p):
    current{p}, oper{null} {}
    
    // these are the operation which we use to compare different keys; obviously they depend on oper
    bool less(const T& a,const  T&b) const  {return oper(a,b);}
    bool equal(const T& a,const  T&b) const  {if (!less(a,b) and !less(b,a)) return true; return false;}
    bool greater(const T& a,const T&b) const  {if (!less(a,b) and !equal(a,b)) return true; return false;}
    
    
    /*
     this is the overloading of the operator++ which allows us to move in the tree from a node to the
     following one
     
     */
    iterator& operator++(){
        if(current->right!=nullptr){   //it tries to go down to the right
            current=current->right;
            if(current->left!=nullptr){
                while(current->left!=nullptr){  //form here it goes down to the left as it is possible
                    current=current->left;}
            }
            return *this; // it returns the iterator
        }
        
        else {  // if we are here, it means that it can't go down to the right
            if(current->parent==nullptr) {current=nullptr; return *this;};
            if(less(current->key,current->parent->key) ){ //if it is possible it goes up to the right
                current=current->parent;
                return *this;}
            
            else {
                //current-> parent!= nullptr is useful in order not to finish in the root
                while(current->parent!=nullptr && greater(current->key  ,  current->parent->key)) { //in alternativa risale a sinistra
                    current=current->parent;
                };
                if(current->parent!=nullptr){ //if we are here it means that we don't start from the last
                    current=current->parent;  //it goes up to the right
                    return *this;}
                
                else{    // if we are here it means that we are started from the last
                    
                    current = nullptr;
                    return *this;}
            }
        }
        return *this;
    }
    
    
    /*
     
     specular to the operator--
     */
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
    
    /*
     operator which returns the key of current.
     */
    const T& operator*() const {return current->key;}
    
    /*
     operator which returns the value of current.
     */
    W& operator!() const{return current->value;}  //ritorno del valore
    /*
     boolean operator
     
     */
    bool operator==(const iterator& b) const {return current==b.current;}
    bool operator!=(const iterator& b) const {return current!=b.current;}
    Node* node() const{return current;}
    /*
     functions which gives to us the key of the parent of the node pointed by the iterator: is is useful to understand id the tree is balance
     */
    const T& parent_key() const  {
        if(current->parent==nullptr) {cout<<"we are in the root"<<endl; return current->key;};
        return current->parent->key;}

   
};


/*
 method which returns an iterator pointed to the first node
 */
template<typename T,typename W,typename K>
typename Tree<T,W,K>::iterator Tree<T,W,K>::begin() const{return iterator{first,*this};}

/*
 method which returns an iterator characterized by nullptr
 */

template<typename T,typename W,typename K>
typename Tree<T,W,K>::iterator Tree<T,W,K>::end() const{return iterator{nullptr,*this};}


/*
 implementation of the class Constiterator as derived class of iterator
 
 */
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
    
/*
 
 We have the method cbegin() and cend() which do the same thing od end() and begin() for COnstiterator
 
 */



 template<typename T,typename W,typename K>
 typename Tree<T,W,K>::Constiterator Tree<T,W,K>::cbegin() const  { return Constiterator{first,*this};}

template<typename T,typename W,typename K>
 typename Tree<T,W,K>::Constiterator Tree<T,W,K>::cend() const {return Constiterator{nullptr,*this};}



