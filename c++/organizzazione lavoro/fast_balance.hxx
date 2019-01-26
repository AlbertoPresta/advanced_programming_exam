#include<iostream>
#include"Tree.h"



/*
 funzioni:
 Bal_reisert
 left_branch_
 right_branch
 rec_Brance
 Fast_Balance
*/

template<typename T,typename W,typename K>
void Tree<T,W,K>::Fast_Balance() noexcept{
    
    
    if(size_tree<2) return;
    iterator i{first,*this};
    
    for(unsigned int ii{1};ii<size_tree/2+1;ii++) ++i;   //cerca la mediana
    if(i.node()->parent!=root){ //fino al nodo sotto la root
        while (i.node()->parent!= root) {
            Node* m{i.node()};  //mediana
            
            Node* a{i.node()};  //mediana per iterare
            if(less(a->parent->key , m->key)){
                while (less(a->parent->key , m->key)  and a->parent!= root) a=a->parent; //risale a sinistra fino a quando possibile
                left_branch_deattaching(a,m); //stacca il pezzo da m ad a, riattacca m a a->parent
                Bal_reinsert(a,m); //reinserisce il pezzo reinserendo a
                a=m;  //aggiorna a
            };
            if (a->parent!= root) {
                while (greater(a->parent->key , m->key)  and a->parent!= root) a=a->parent;
                right_branch_deattaching(a,m);
                Bal_reinsert(a,m);
                a=m;  };
        };
    };
    //ora la mediana è figlia della root, si puà infine agire sulla root
    i.node()->parent=nullptr;
    if(less(i.node()->key,root->key)) {root->left=nullptr;}
    else {root->right=nullptr;};
    
    Bal_reinsert(root,i.node()); //reinserisce la root
    root=i.node(); //ridefinisce la root
    Rec_Balance(i.node(),root,size_tree);
}

template<typename T,typename W,typename K>
void Tree<T,W,K>::Rec_Balance (Node* m, Node* r, int lun)noexcept{
    if(m!=r){
        while (m->parent != r) {
            Node* a{m};
            if(less(a->parent->key , m->key)){
                while (less(a->parent->key , m->key)  and a->parent != r) a=a->parent;
                left_branch_deattaching(a,m);
                Bal_reinsert(a,m);
                a=m;
            };
            if (a->parent != r) {
                while (greater(a->parent->key , m->key ) and a->parent != r) a=a->parent;
                right_branch_deattaching(a,m);
                Bal_reinsert(a,m);
                a=m;  };
        };
    };
    int lun_l{lun/2};
    int lun_r{lun-1-lun_l};
    iterator i{m,*this};
    iterator j{m,*this};
    
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

template<typename T,typename W,typename K>
void Tree<T,W,K>::Bal_reinsert (Node* n,Node* r) noexcept{
    Node* p{r};
    while(!(p->left ==nullptr and p->right==nullptr) and !
          (p->left==nullptr and less(n->key , p->key)) and
          !(p->right==nullptr and greater(n->key , p->key)))
    {
        if(less(n->key,p->key)) {p=p->left;}
        else {p=p->right;};
    };
    if(less(n->key,p->key)) {p->left=n;    n->parent=p; }       //aggiorna il ramo sinistro di p
    else         {p->right=n;   n->parent=p; };          //aggiorna il ramo destro di p
}

template<typename T,typename W,typename K>
void Tree<T,W,K>::left_branch_deattaching (Node* a, Node* m)noexcept{
    m->parent->right=nullptr;
    m->parent=a->parent;
    if(less(a->parent->key , m->key)) {a->parent->right=m;}
    else {a->parent->left=m;};
    a->parent=nullptr;
}
template<typename T,typename W,typename K>
void Tree<T,W,K>::right_branch_deattaching (Node* a, Node* m) noexcept{
    m->parent->left=nullptr;
    m->parent=a->parent;
    if(less(a->parent->key, m->key)) {a->parent->right=m;}
    else {a->parent->left=m;};
    a->parent=nullptr;
}

