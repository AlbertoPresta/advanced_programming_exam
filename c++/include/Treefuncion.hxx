#include"Tree.h"
#include<iostream>
#include<cmath>
#include<ctime>
#include<fstream>
#include<sstream>
#include <map>
/*
 Advanced programming project
 Authors: Alberto Presta and Andrea Gasparin
 Date: 27-01-2019
 
 function implemented in this file:
 getlast
 Size
 info
 insert
 find()
 ctr_insert
 linked-insert
 copy-move semantic
 clear and recursive_clear
 timer
  */



/*
 function getlast(): it returns the node with the greatest key (the last node)
 */
template<typename T,typename W,typename K>
typename Tree<T,W,K>::Node* Tree<T,W,K>::getlast() const  {
    Node* node = Root();
    while(node->right != nullptr) node = node->right;
    return node;
}

/*
 Size(): it returns the size of the tree
 */
template<typename T,typename W,typename K>
unsigned int Tree<T,W,K>::Size() const{return size_tree;}

/*
 info(): it returns the main info of the tree (useful to check if we have the right relation of order)
 */
template<typename T,typename W,typename K>
void Tree<T,W,K>::info() const{
    if (size_tree==0){cout<<"empty tree"<<endl;};
    cout<<"   root "<<root->key<<"   first "<<first->key<<"    size "<<size_tree<<endl;
    
}

/*
 insert(): it iserts a new node in the tree:
 First of all, if the size of the tree is equal to 0, it inserts the root
 Otherwise we pass through the tree with a while loop following the relation of order which characterizes the tree.
 At the end of the while loop we have arrived in the right leaf where to insert the new node and then we insert it in the right place, with the last if branch (it depends on the key).
 If we insert a key which is already present, we throw an exception
*/
template<typename T,typename W,typename K>
void Tree<T,W,K>::insert(T k,W v)  {
    //inserimento primo elemento
    if (size_tree==0) {Tree<T,W,K>::Node* elem=new Node{k,v}; first=elem ; root=elem; size_tree=1;return;};
    Node* p{root};
    
    
    bool FIRST{true}; //booleano che serve a identificare l'ultimo nodo a sinistra, first
    
    
    while(!(p->left ==nullptr && p->right==nullptr) && !(p->left==nullptr && less(k,p->key)) && !(p->right==nullptr && greater(k,p->key))) {
            if(less(k,p->key)) {p=p->left;} //scende a sinistra. Se lo fa una volta sicuramente non è l'ultimo elemento
            else {
                if(equal(p->key,k)) {cout<<"key already assigned: "<<k<<", value: "<<p->value<<endl;throw ex_key{};};
                p=p->right;FIRST=false;};      //speculare, se scende a destra una volta certamente non è il first
    };
    //per la condizione del while, p è l'ultimo nodo preesistente
    
    Node* elem=new Node{k,v,nullptr,nullptr,p}; //inserisce il nuovo nodo con p parente
    
    if(less(k,p->key)) {p->left=elem; if (FIRST==true) first=elem;} //aggiorna il ramo sinistro di p
    else {p->right=elem;  };          //aggiorna il ramo destro di p
    
    size_tree++; //aggiornamento grandezza albero
}



/*
 this is a "fast insert": it receives an integer n as input and it inserts to an empty tree exactly n nodes: it start from the root and then it inserts nodes with increasing keys.
 The result is a tree with n node totally unbalanced (suitable to do our test about performance)
 */
template<typename T,typename W,typename K>
void Tree<T,W,K>::Linked_insert(int n) {
    if (size_tree!=0){ return;};
    if((1<2)!=less(1,2)){    // if we have oper = oper<int>
        int j{n};
        int m{9};
        Node* elem=new Node{j,j};first=elem; root=elem; size_tree=1;
        for(int i{n-1};i>0;i--) {elem=new Node{i,m,nullptr,nullptr,elem};elem->parent->right=elem;size_tree++;};
        
    }
    else{  // case where oper = null_object<int>
        int j{1};
        Node* elem=new Node{j,j};first=elem ; root=elem;   size_tree=1;
        for(int i{2};i<=n;i++) {elem=new Node{i,j,nullptr,nullptr,elem};elem->parent->right=elem;size_tree++;};
    }
}

/*
 function find():
 it receives a key in input and it searches it in the tree starting from the root
 If it finds the key it returns an iterator pointed to the node related to the key, otherwise it returns the nullptr
 
 */
template<typename T,typename W,typename K>
typename Tree<T,W,K>::iterator Tree<T,W,K>::find (const T& t) const {
    Node* j{root};
    
    while(j!=nullptr){
        if(equal(j->key,t)){  iterator k{j,*this}; return k;}
        
        else{
            if(greater(j->key,t)){j=j->left;}
            else{j=j->right;}}
        
    }
    cout<< "key not found!"<<endl;
    iterator k{j,*this};
    return k;
}




/*
 ctr_insert(Node* n): it is a private method which we use in the copy semantic:
 it is recursive and we use it to do a deep copy of a tree.
 First of all it inserts the node in the new tree calling the function insert
 Then if the node received in input is a leaf (no childred),  it returns nothing.
 Otherwise if the left son is different from the nullptr it calls itself with the input n->left.
 it does the same thing if the right son is different from nullptr
 */
template<typename T,typename W,typename K>
void Tree<T,W,K>::ctr_insert(Node* n) {
    insert(n->key, n->value);
    if(n->left==nullptr and n->right==nullptr) return;
    if(n->left!=nullptr) ctr_insert(n->left);
    if(n->right!=nullptr)ctr_insert(n->right);}


//--------------------------------------------COPY SEMANTIC--------------------------------------------------------//
/* copy constructor
 Copy constructor initializes a new tree from another one. It is built to be a deep copy, so at the end the two trees
 will be totally independent.
 It initializes the data tipes of the copy as first{nullptr}, root {nullptr},size_tree{0},oper{t.oper} and then it calls
 ctr_insert to fill the new tree.
 Obviously the input is const because we don't change it.
 */
template<typename T,typename W,typename K>
Tree<T,W,K>::Tree(const Tree<T,W,K>& t):first{nullptr}, root {nullptr},size_tree{0},oper{t.oper} {
    ctr_insert(t.root);
}


/*copy assignment
 this is the overloading of the operator = for the copy assignment (it creates a deep copy)
 First of all it calls the method clear which wipes out the content of the tree.
 then it does the copy with the function ctr_isert(t.root) and it returns the new tree.
 Obviously the input is const because we don't change it.
*/
template<typename T,typename W,typename K>
Tree<T,W,K>& Tree<T,W,K>::operator=(const Tree<T,W,K>& t) {
    clear();
    ctr_insert(t.root);
    return *this;
}

//----------------------------------------------------------MOVE SEMANTIC---------------------------------------------//
/*move constructor
 This is the constructor which initializes a new tree with move semantic. It receives a Tree in input as Rvalue ( we have
 to do a move).
 We initialize the new tree in this way: first{t.first}, root {t.root}, size_tree{t.size_tree}, oper{t.oper} and then we
 clear the old tree
 */
template<typename T,typename W,typename K>
Tree<T,W,K>::Tree(Tree<T,W,K>&& t) : first{t.first}, root {t.root}, size_tree{t.size_tree}, oper{t.oper}  {
    t.root=nullptr;
    t.first=nullptr;
    t.size_tree=0;
}

/*move assignment
 
 This is the overloading of the operator = for the move assignment.
 It works in a similar way to the move contructor: it clears the tree, then it does a move and then it clears the old tree
 */
template<typename T,typename W,typename K>
Tree<T,W,K>& Tree<T,W,K>::operator=(Tree<T,W,K>&& t) {
    clear();
    root=t.root;
    first=t.first;
    size_tree=t.size_tree;
    t.root=nullptr;
    t.first=nullptr;
    t.size_tree=0;
    return *this;
}




 /*
 recursive_clear(Node*n): it is a recursive function used by clear() ant it wipes the contents of a single node.
 it receives in input a node * :
 if this node* has childred it calls recursive_clear for them.
 Then it deletes the node
 
*/
template<typename T,typename W,typename K>
void Tree<T,W,K>::recursive_clear (Node* n) noexcept{
    if(n->left!=nullptr) recursive_clear(n->left);
    if(n->right!=nullptr) recursive_clear(n->right);
    delete n;
}


/*
 It simply uses the function recursive_clear to wipe out all nodes of a tree
 */
template<typename T,typename W,typename K>
void Tree<T,W,K>::clear() noexcept{
    if(size_tree==0) return;
    Node* n{root};
    root=nullptr;
    first=nullptr;
    recursive_clear(n);
    size_tree=0;
}



    
    
/*
 This functions returns a  reference to the value associated to the key k. If the key is not present, a new node with key k is allocated having the value value_type{}.
 */

template<typename T,typename W,typename K>
W& Tree<T,W,K>::operator[]  (const T& k)  {
    iterator j{find(k)};
    if(j!=end()) return !j;
    insert(k,W{});
    iterator q{find(k)};
    return !q;
}

/*
 
 this method is useful if we deal with costant tree because they don't touch the tree.
 if the method doesn't find the key, it throws an exception!
 */
template<typename T,typename W,typename K>
const  W& Tree<T,W,K>::operator[] (const T& k) const  {
    Node* p = find(k).node();
    Constiterator m{p,*this};
    
    if(m==cend()){
        cout<<"key not found, so I throw an exception!"<<endl;
        throw;};
    
    return !m;
    }



/*
 This function is used to write the performance (in terms of time) in a file txt.
 It accepts only a tree<int,int,k> (key and value are integer).
 With two nested for loops we evaluate performance of tree of different size (from 10^4 to 9*10^6)
 We evaluate time for find before balance and find after balance.
 Then we also do a test for std::map
 
 All results are written in a file called test_data_iter.txt
 
 */
template<typename K>
void timer(Tree<int,int,K>& A){
    std::map<int ,int> name_map;
    clock_t t1,t2,t3,t4;
    string file_name="test_data_iter.txt";
    std::fstream f{file_name,f.app};
    f<<"--------------------TIME IN SECONDS--------------------"<<endl<<endl;
    f<<"Tree_size         find       balance        new find         log(N)         find_map"<< endl;
    f.close();
    long int size;
    for (int i{4};i<7;i++) {
        cout<<"*********************************************************"<<endl;
        cout<<"---------siamo alla potenza i: "<< i << "cioè: " << pow(10,i)<<endl;
        for (int h{1};h<10;h=h+1)
        {
            
            size=h*pow(10,i);
            A.Linked_insert(size);
            cout<<"size"<<endl;
            cout<<A.Size()<<endl;
            t1=clock();
            if(A.getlast()->key == size) A.find(size);
            else A.find(1);             // find!
            t1=clock()-t1;
            
            // balance
            t2=clock();
             A.balance();
            
            t2=clock()-t2;
            cout<<"effettuato balance"<<endl;
            // time after balance
            t3=clock();
            A.find(size-1);
            t3=clock()-t3;
            
            // ora tocca alla mappa
            for (int t = 1; t<=size; t++){
                name_map.insert(std::pair<int,int>(t,t));
            }
            t4 = clock();
            name_map.find(size);
            t4 = clock() - t4;
            
            f.open(file_name,f.app);
            
            
            f<<size<<"          "<<((float)t1)/CLOCKS_PER_SEC<<"          "<<((float)t2)/CLOCKS_PER_SEC<<"          "
            <<((float)t3)/CLOCKS_PER_SEC<<"      "<<log2(size)<<"         "<<((float)t4)/CLOCKS_PER_SEC<<endl;
            f.close();
            
            A.clear();
        }
        cout<<"****************************************"<<endl;
    }
}











