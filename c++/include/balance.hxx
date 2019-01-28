#include<iostream>
#include"Tree.h"


/*
 Advanced programming project
 Authors: Alberto Presta and Andrea Gasparin
 Date: 27-01-2019

 we dedicate a file only for function balance




 functions implemented in this file:
 Bal_reisert
 left_branch_
 right_branch
 rec_Brance
 Fast_Balance






 Balance  method balances the tree, finding the median, detaching and reinserting below it all branches up to the root.
 It proceeds recursively on left and right subtrees median till no splitting is no longer possible
 
 The balance function, has been implemented to perform the balance of the tree without creating a new tree and reinserting all nodes in it.
 Tests proved that fast balance fails for trees bigger than 100000 with a 4G ram machine and 200000 with a 8Gram machine, where fast balance has succesfuly performed up to 9*E^7 on a 4Gram machine and up to  500000000 on a 8Gram machine.
 Morover, fast balance, even on trees for wich the regular balance worked has shown to be approximatively twice faster than regualar balance
 
 
 Balance():it finds the first median, detach the corrispondeng node from its parents. Then it rises the tree detaching branches or single nodes
 reinserting them below untill it reahes the root. The median then becomes the new root. Eventually it calls Rec_Balance passing an iteretor pointing to the median and the size of the tree as arguments
 
 Rec_Balance(): starting from the iterator argument, it perfomes the same procedure of  the balance. It splits in two sub trees the input tree according to the input size. It calculates the submedians of the two sides and then recall its self passing the two submedians and the two subsizes
 */
 
 

template<typename T,typename W,typename K>
void Tree<T,W,K>::balance() noexcept{
    
    
    if(size_tree<2) return;
    iterator i{first,*this};
    
    for(unsigned int ii{1};ii<size_tree/2+1;ii++) ++i;   //cerca la mediana
    if(i.node()->parent!=root){ //fino al nodo sotto la root
        while (i.node()->parent!= root) {
            Node* m{i.node()};  //mediana
            
            Node* a{i.node()};  //mediana per iterare
            if(less(a->parent->key , m->key)){
                while (less(a->parent->key , m->key)  and a->parent!= root) a=a->parent; //risale a sinistra fino a quando possibile
                left_branch_detaching(a,m); //stacca il pezzo da m ad a, riattacca m a a->parent
                Bal_reinsert(a,m); //reinserisce il pezzo reinserendo a
                a=m;  //aggiorna a
            };
            if (a->parent!= root) {
                while (greater(a->parent->key , m->key)  and a->parent!= root) a=a->parent;
                right_branch_detaching(a,m);
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
                left_branch_detaching(a,m);
                Bal_reinsert(a,m);
                a=m;
            };
            if (a->parent != r) {
                while (greater(a->parent->key , m->key ) and a->parent != r) a=a->parent;
                right_branch_detaching(a,m);
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
void Tree<T,W,K>::left_branch_detaching (Node* a, Node* m)noexcept{
    m->parent->right=nullptr;
    m->parent=a->parent;
    if(less(a->parent->key , m->key)) {a->parent->right=m;}
    else {a->parent->left=m;};
    a->parent=nullptr;
}
template<typename T,typename W,typename K>
void Tree<T,W,K>::right_branch_detaching (Node* a, Node* m) noexcept{
    m->parent->left=nullptr;
    m->parent=a->parent;
    if(less(a->parent->key, m->key)) {a->parent->right=m;}
    else {a->parent->left=m;};
    a->parent=nullptr;
}

