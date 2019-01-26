#include<iostream>


#ifndef TREE_H__
#define TREE_H__

using std::string;
using std::cout;
using std::endl;

class ex_key {};


template<typename T>
struct null_object{ bool operator()(T a, T b) {return(a<b);}};

template<typename T>
struct oper{ bool operator()(T a, T b) {return(a>b);}};

template<typename T,typename W, typename  K=null_object<T>>
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
    
    unsigned int size_tree; //grandezza dell'albero
    K oper;
    
    null_object<T> static null;
    
public:
    
    Node* Root() const{return root;}
    
    // metodo che restituisce node* al nodo più grande
    Node* getlast() const;  
    
    unsigned int Size() const; //funzione per stampare la grandezza dell'albero
   
    void info() const;
    
    Tree(K& o):
    root{nullptr},size_tree{0},oper{o} {}
    
    Tree():
    root{nullptr},size_tree{0},oper{null} {}
    
    bool less(const T& a,const T&b)  {return oper(a,b);}
    bool equal(const T& a,const T&b) {if (!less(a,b) and !less(b,a)) return true; return false;}
    bool greater(const T& a,const T&b) {if (!less(a,b) and !equal(a,b)) return true; return false;}
    
	void insert(T k, W v);
    
	// inizio delle dichiarazioni degli iteratori!
    class iterator;

	iterator begin() const ;
	iterator end() const ;
   
    //iterator root();

	 //inizio dichiarazione constiterator
    
  class Constiterator;
  
	 // fine dichiarazione constiterator

     Constiterator cbegin() const;
	 Constiterator cend() const;
	 //Constiterator croot() const;

     
	 iterator find(const T& t);

     
    
	 //inizio move and copy semantic
	 
	 Tree(const Tree<T,W,K>& t);
	Tree& operator=(const Tree<T,W,K>& t);
    Tree(Tree<T,W,K>&& t);
    
	Tree& operator=(Tree<T,W,K>&& t);
	
	void clear() noexcept;
	
    ~Tree() {clear();};   //RIMETTERE CLEAR ASSOLUTAMENTE!!!!
    
	
	void balance() noexcept;
	
    void Linked_insert(int n);
    void Fast_Balance() noexcept;
    W& operator[]  (const T& k) ;
    
private:
    void recursive_clear(Node* n) noexcept;
    
    void rec_balance(unsigned int s, Tree<T,W,K>& b, Tree<T,W,K>::iterator m, int lun) noexcept;

    void ctr_insert( Node* n);
    
    void Bal_reinsert (Node* n,Node* r) noexcept;
    void left_branch_deattaching (Node* a, Node* m) noexcept;
    void right_branch_deattaching (Node* a, Node* m) noexcept;
    void Rec_Balance (Node* m, Node* r, int lun) noexcept;
};









template<typename T,typename W, typename K>
std::ostream& operator<<(std::ostream& os, const Tree<T,W,K>& l) {
    if (l.Size()==0) {cout<<"empty tree"<<endl; return os;}
    else {
        typename Tree<T,W,K>::Constiterator j = l.cbegin();
        for(; j!=l.cend();++j){
            os <<"key: "<<*j<<"   value: " <<!j<<"      parent: "<<j.parent_key()<<endl;
        }
        
        
        return os ;}
}





#include "iterator.hxx"
#include "Treefuncion.hxx"
#include "fast_balance.hxx"

#endif



