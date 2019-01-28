#include<iostream>
#include<memory>
#include"Tree.h"

#include <cstdlib>

/*
 In this main we want to test al features of our Tree
 
 */


/*
 Antother struct which represents the opposite relation of order respect than the default one
 */
template<typename T>
struct oper{ bool operator()(const T& a, const T& b) const {return(a>b);}};


int main(){
    try{
        /*
         Constructor of the Tree--> it should create an empty tree
        */
        Tree<int,int> A{};
        cout<<"it should print empty tree:    "<<A<<endl;
        /*
         insert method
         */
        for (int i = 1; i<=20;i++) A.insert(i,i);
        cout<<"Now the tree should have 20 nodes, the root should be key = 1, as well as the first"<<endl;
        A.info();
        cout<<"ECCO L'ALBERO A"<<endl<<endl;
        cout<<A<<endl;
        
        /*
         method balance--> we print alse the key of the parent in order to find out if the tree is balanced
         */
        A.balance();
        cout<<"---------ALBERO A BILANCIATO---------"<<endl;
        cout<<A<<endl<<endl;
        cout<<"------------------"<<endl;
        /*
         now we initialize an iterator with the proper constructor
         */
        Tree<int,int>::iterator p{A.getfirst(),A};
        cout<<"now it should be print 1:  "<<endl;
        
        cout<<*p<<endl;
        /*
         testing funtion find both when we find the key and when we dont' find the key.
         Also we control if operators * and ! work
         */
         Tree<int,int>::iterator q = A.find(12);
        /*
         creation of an iterator pointed to the root.
         */
        Tree<int,int>::iterator z{A.Root()};
        
        cout<<"value of the key found (it should be 12 ):   "<<*q<<endl;
        cout<<"values associated with the key:   "<<!q<<endl;
        cout<<"now we test the case when there isn't the key. "<<endl;
        A.find(1000);
       
        /*
         Test the operator [ ]
         */
       
        for (int i =1; i<10; i++)
            cout<<"value associated to the key "<<i<<": "<< A[i] <<endl;
        cout<<"case when the key is not present"<<endl;
        cout<<"size of the tree before using operator [ ]:  "<<A.Size()<<endl;
        A[21]; // first find is negative, but the second one is positive!
        cout<<"Should be the default value of integer (0): "<<A[21]<<endl;
        cout<<"size of the tree after using operator [ ]:  "<<A.Size()<<endl;
        /*
         NOW WE WANT TO CONTROL MOVE AND COPY SEMANTIC
         */
        cout<<"*********************MOVE AND COPY SEMANTIC********************"<<endl<<endl<<endl;
        
        cout<<"------COPY CONSTRUCTOR------"<<endl;
        cout<<"Tree<int,int> B{A}"<<endl<<endl;
        Tree<int,int> B{A}; // should be a deep copy
        cout<<"Tree B"<<endl;
        cout<<B<<endl<<endl;
        cout<<"Tree A"<<endl;
        cout<<B<<endl<<endl;
        cout<< "now I try to change B, A should'change"<<endl;
        B.insert(23,23);
        //verification that B is a deep copy
        if (B.Size()!=A.Size()) cout<<"Copy constructor works well! "<<endl<<endl;
        else cout<<" we have a problem!"<<endl;
        cout<<"------COPY ASSIGNMENT------"<<endl;
        Tree<int,int> C;
        for (int i=30; i<=45; i++) C.insert(i,i);
        cout<<"Tree C before the copy assignment: "<<endl<<endl;
        cout<<C<<endl<<endl<<endl;
        cout<<"C = A"<<endl<<endl;;
        C = A; // now C should be equal to A
        cout<<"now C should be equal to A! "<<endl;
        cout<<"Tree C after the copy assignment: "<<endl<<endl;
        cout<<C<<endl;
        cout<<"Tree A after copy assignment ( it is the same tree). "<<endl<<endl;
        cout<<A<<endl;
        cout<<"------MOVE CONSTRUCTOR------"<<endl;
        cout<<"Tree<int,int> D{std::move(A)};"<<endl<<endl;
        Tree<int,int> D{std::move(A)};
        cout<<"Tree D  (should be equal to A)"<<endl<<endl;
        cout<<D<<endl;
        if (A.Size()==0)cout<<" A is an empty Tree now, so move constructor works well!"<<endl<<endl;
        else cout<<"We have a problem!"<<endl;
         cout<<"------MOVE ASSIGNMENT------"<<endl;
        Tree<int,int> E;
        for (int i=30; i<=45; i++) E.insert(i,i);
        cout<<"Tree E before move assignment!"<<endl<<endl;
        cout<<E<<endl<<endl;
        cout<<"E = std::move(D)"<<endl;
        E = std::move(D);
        cout<<"Tree E after move assignment!"<<endl<<endl;
        cout<<E<<endl<<endl;
        if (D.Size()==0)cout<<"D is an empty Tree now, so move semantic works well!"<<endl<<endl;
        else cout<<"We have a problem!"<<endl;
        cout<<endl<<endl<<endl;
        /*
         Now we want to test the clear method, which should clear the content of the tree
         */
        cout<<"***********************CLEAR**************************"<<endl<<endl<<endl;
        Tree<int,int> F{};
        for (unsigned int i = 1; i<30;i++) F.insert(i,i);
        cout<<"Tree F: "<<endl<<endl;
        cout<<F<<endl<<endl;
        cout<<"F.clear()"<<endl<<endl;
        F.clear();
        if(F.Size()==0){cout<<"F is an empy tree now!"<<endl<<endl;}
        else cout<<"clear did not work well"<<endl<<endl;
        cout<<endl<<endl<<endl;
        cout<<"***************** Tree with reverse relation of order***************"<<endl<<endl;
        /*
         now we want initialize tree using the struct oper, which creates tree following the oppposite relation
         of order requested by the exercise
         */
        
        oper<int> o;
        cout<<"Tree<int,int,oper<int>> G{o};"<<endl<<endl;
        Tree<int,int,oper<int>> G{o};
        for (int i = 1; i<=20;i++) G.insert(i,i);
        cout<<"now the first should be equal to 20!!"<<endl;
        G.info();
        cout<<"ECCO L'ALBERO G"<<endl<<endl;
        cout<<G<<endl;
        /*
         last thing that we test is the second method of balance
         */
        cout<<"*****************************************FAST_BALANCE***************"<<endl;
        cout<<"G.balance();"<<endl<<endl;
        G.balance();
        cout<<G<<endl;
        
        /*
         this part use const [] const 
         */
        const Tree<int,int,oper<int>> pp{G};
        cout<<pp[2]<<endl;;
    return 0;
         
    }

catch (const ex_key) {cout<<"exception has been thrown "<<endl;return 1;}
    catch(...) {cout<<"unexpected error "<<endl;}
    
}
