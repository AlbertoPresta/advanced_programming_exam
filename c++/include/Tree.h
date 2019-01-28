/*
 
 Advanced programming project
 authors: Alberto Presta and Andrea Gasparin
 Date: 27-01-2019
 
 In this first file there are the declaration (a part from struct node which is fully implemented here) of the class Tree and all the methods which characterizes our project.
 */





#include<iostream>


#ifndef TREE_H__
#define TREE_H__

using std::string;
using std::cout;
using std::endl;



/*
 class which Error handling in case there is an insertion of an already present key. It is simply an empty struct
 */
class ex_key {};


/*
 struct which reperesents the default relation of order
*/
template<typename T>
struct null_object{ bool operator()(const T& a, const T& b) const {return(a<b);}};


/* start of the class Tree
 
 */

template<typename T,typename W, typename  K=null_object<T>>
class Tree{
    /*declaration and implementation of the struct node
     It simply contains the data types, constructor and destructor
     */
    struct Node{
        const T key;
        W value;
        Node* left;
        Node* right;
        Node* parent;
        Node (T& k,W& v, Node* l=nullptr, Node* r=nullptr,Node* p=nullptr):
        key{k}, value{v}, left{l}, right{r}, parent{p} {}
        ~Node() {left=nullptr;right=nullptr;parent=nullptr;}
    };
    
    //tree varaibles
    Node* first; //first node
    Node* root; // root node
    
    
    unsigned int size_tree; // size of the tree
    const  K oper;   // operation of the tree
    const null_object<T> static null; // inizialization of the a variable null_object
    
    
public:
     /*
      methods of the class tree: described in the other files
      
      */
    Node* Root() const{return root;}   // it returns the root
    Node* getfirst() const{return first;} // it returns the first
   
    Node* getlast() const;  // it returnas the node with the greatest key
    
    unsigned int Size() const; //it returns the size of the tree
   
    void info() const; // it returns the main info of the tree
    
     // contructors of the tree
    Tree( const K& o):
    root{nullptr},size_tree{0},oper{o} {}
    
    Tree():
    root{nullptr},size_tree{0},oper{null} {}
    
    bool less(const T& a,const T&b) const   {return oper(a,b);}
    bool equal(const T& a,const T&b) const {if (!less(a,b) and !less(b,a)) return true; return false;}
    bool greater(const T& a,const T&b) const  {if (!less(a,b) and !equal(a,b)) return true; return false;}
    
	void insert(T k, W v);
    
	// iterators
    class iterator;

	iterator begin() const ;
	iterator end() const ;
   
    

	 //inizio dichiarazione constiterator
    
  class Constiterator;
  
	 // fine dichiarazione constiterator

     Constiterator cbegin() const;
	 Constiterator cend() const;
	

     
	 iterator find(const T& t) const;

     
    
	 
    /*
     copy and move semantic
     */
	 
	 Tree(const Tree<T,W,K>& t);
	Tree& operator=(const Tree<T,W,K>& t);
    Tree(Tree<T,W,K>&& t);
    
	Tree& operator=(Tree<T,W,K>&& t);
	
    /*
     clear method
     */
	void clear() noexcept;
	
    /*
     destructor
     */
    ~Tree() {clear();};
    
	
	
    void Linked_insert(int n);
    /*
     second method of balance--> it calls Rec_Balance, left_branch_deattaching ,right_branch_deattaching and Bal_reinsert
     */
    void balance() noexcept;
    
    
    W& operator[]  (const T& k) ;
    const W& operator[]  (const T& k) const ;
    
    
    
private:
    void recursive_clear(Node* n) noexcept;
    
    //void rec_balance( Tree<T,W,K>& b, Tree<T,W,K>::iterator m, int lun) noexcept;

    void ctr_insert( Node* n);
    
    void Bal_reinsert (Node* n,Node* r) noexcept;
    void left_branch_detaching (Node* a, Node* m) noexcept;
    void right_branch_detaching (Node* a, Node* m) noexcept;
    void Rec_Balance (Node* m, Node* r, int lun) noexcept;
};








/*
 overloading of the operator <<
 */
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
#include "balance.hxx"

#endif



