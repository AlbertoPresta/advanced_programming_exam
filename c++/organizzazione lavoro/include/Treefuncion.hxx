#include"Tree.h"
#include<iostream>
#include<cmath>
#include<ctime>
#include<fstream>
#include<sstream>
#include <map>
/*
 funzioni:
 getlast
 Size
 info
 insert
 ctr_insert
 linked-insert
 copy-move semantic
 rec_balance and balance
 clear and recursive_clear
 timer
 




 */
template<typename T,typename W,typename K>
typename Tree<T,W,K>::Node* Tree<T,W,K>::getlast() const  {
    Node* node = Root();
    while(node->right != nullptr) node = node->right;
    return node;
}


template<typename T,typename W,typename K>
unsigned int Tree<T,W,K>::Size() const{return size_tree;}


template<typename T,typename W,typename K>
void Tree<T,W,K>::info() const{
    if (size_tree==0){cout<<"empty tree"<<endl;};
    cout<<"   root "<<root->key<<"   first "<<first->key<<"    size "<<size_tree<<endl;
    
}
 
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

template<typename T,typename W,typename K>
void Tree<T,W,K>::Linked_insert(int n) {
    if((1<2)!=less(1,2)){    // caso in cui non abbiamo un
        int j{n};
        int m{9};
        Node* elem=new Node{j,j};first=elem; root=elem; size_tree=1;
        for(int i{n-1};i>0;i--) {elem=new Node{i,m,nullptr,nullptr,elem};elem->parent->right=elem;size_tree++;};
        
    }
    else{
        int j{1};
        Node* elem=new Node{j,j};first=elem ; root=elem;   size_tree=1;
        for(int i{2};i<=n;i++) {elem=new Node{i,j,nullptr,nullptr,elem};elem->parent->right=elem;size_tree++;};
    }
}





//ctr_insert used in copy semantic
template<typename T,typename W,typename K>
void Tree<T,W,K>::ctr_insert(Node* n) {
    insert(n->key, n->value);
    if(n->left==nullptr and n->right==nullptr) return;
    if(n->left!=nullptr) ctr_insert(n->left);
    if(n->right!=nullptr)ctr_insert(n->right);}


//-------------COPY SEMANTIC---------------------------//
// copy constructor
template<typename T,typename W,typename K>
Tree<T,W,K>::Tree(const Tree<T,W,K>& t):first{nullptr}, root {nullptr},size_tree{0},oper{t.oper} {
    ctr_insert(t.root);
}


//copy assignment
template<typename T,typename W,typename K>
Tree<T,W,K>& Tree<T,W,K>::operator=(const Tree<T,W,K>& t) {
    clear();
    ctr_insert(t.root);
    return *this;
}

//--------------MOVE SEMANTIC-----------------------//
//move constructor
template<typename T,typename W,typename K>
Tree<T,W,K>::Tree(Tree<T,W,K>&& t) : first{t.first}, root {t.root}, size_tree{t.size_tree}, oper{t.oper}  {
    t.root=nullptr;
    t.first=nullptr;
    t.size_tree=0;
}

//move assignment
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



//--------FUNZIONE balance()  and rec_balance()
template<typename T,typename W,typename K>
void Tree<T,W,K>::rec_balance (unsigned int s, Tree<T,W,K>& b, iterator m, int lun) noexcept {
    
    b.insert(*m,!m);
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


//balance
template<typename T,typename W,typename K>
void Tree<T,W,K>::balance() noexcept {
    
    Tree<T,W,K> b{this->oper};
    iterator i{first,*this};
    for(unsigned int ii{1};ii<size_tree/2+1;ii++) ++i;
    rec_balance(size_tree,b,i,size_tree);
    *this=std::move(b);}


template<typename T,typename W,typename K>
void Tree<T,W,K>::recursive_clear (Node* n) noexcept{
    if(n->left!=nullptr) recursive_clear(n->left);
    if(n->right!=nullptr) recursive_clear(n->right);
    delete n;
}


template<typename T,typename W,typename K>
void Tree<T,W,K>::clear() noexcept{
    if(size_tree==0) return;
    Node* n{root};
    root=nullptr;
    first=nullptr;
    recursive_clear(n);
    size_tree=0;
}



    
    

template<typename T,typename W,typename K>
W& Tree<T,W,K>::operator[]  (const T& k)  {
    iterator j{find(k)};
    if(j!=end()) return !j;
    insert(k,W{});
    iterator q{find(k)};
    return !q;
}

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
            if(size<=100000) A.balance();
            else A.Fast_Balance();
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
            
            
        }
        cout<<"****************************************"<<endl;
    }
}











