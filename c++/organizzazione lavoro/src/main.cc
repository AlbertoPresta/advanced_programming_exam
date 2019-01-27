#include<iostream>
#include<memory>
#include"Tree.h"

#include <cstdlib>

/*
 In this main we want to test al features of our Tree
 
 */



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
        
        cout<<"value of the key found (it should be 12 ):   "<<*q<<endl;
        cout<<"values associated with the key:   "<<!q<<endl;
        cout<<"now we test the case when there isn't the key. "<<endl;
        A.find(1000);
       
        /*
         Test the operator [ ]
         */
        cout<<"OBS: operator [] print also what is written in function find"<<endl;
        for (int i =1; i<10; i++)
            cout<<"value associated to the key "<<i<<": "<< A[i] <<endl;
        cout<<"case when the key is not present"<<endl;
        cout<<"size of the tree before using operator [ ]:  "<<A.Size()<<endl;
        A[21]; // first find is negative, but the second one is positive!
        cout<<"Should be the default value of integer (0): "<<A[21]<<endl;
        cout<<"size of the tree after using operator [ ]:  "<<A.Size()<<endl;
         /*
        ++p;
        ++p;
        cout<<*p<<endl;
        --p;
        cout<<*p<<endl;
        cout<<"------------------"<<endl;
        
        oper<int> o;
        Tree<int,int,oper<int>> B{o};
        B.Linked_insert(20);
        cout<<"ALBERO B CON LINKED INSERT"<<endl;
        cout<<B<<endl;
        cout<<"PROVO PARENTESI []"<<endl;
        cout<<B[29]<<endl;
        
        
        
        
        
        // cout<<"q:   "<<q<<endl;
        cout<<"XXXXXXXXXXXXX"<<endl;
        Tree<int,int,oper<int>>::iterator q = B.find(12);
        ++q;
        B.info();
        B.Fast_Balance();
        cout<<"ECCO L'ALBERO B bilanciato:"<<endl<<endl;
        cout<<B<<endl<<endl;
        
        
        cout<<"+++++++++++++COPY SEMANTIC+++++++"<<endl;
        cout<<"copy constructor"<<endl;
        Tree<int,int,oper<int>> C{B};
        cout<<"albero C"<<endl;
        cout<<C<<endl;
        cout<<"albero B"<<endl;
        cout<<B<<endl;
        cout<<"copy assignment"<<endl;
        Tree<int,int,oper<int>> D = C;
        cout<<"albero C"<<endl;
        cout<<C<<endl;
        cout<<"albero D"<<endl;
        cout<<D<<endl;
        cout<<"-------------MOVESEMANTIC----------"<<endl;
        cout<<"move constructor"<<endl;
        Tree<int,int,oper<int>> E{std::move(D)};
        cout<<"albero E"<<endl;
        cout<<E<<endl;
        cout<<"albero D"<<endl;
        cout<<D<<endl;
        D.insert(9,9);
        D.insert(3,9);
        D.insert(12,9);
        cout<<D<<endl;
        cout<<"move assigment"<<endl;
        B=std::move(D);
        cout<<"albero B"<<endl;
        cout<<B<<endl;
        cout<<"albero D"<<endl;
        cout<<D<<endl;
       */
    return 0;
         
    }

catch (const ex_key) {cout<<"exception has been thrown "<<endl;return 1;}
    catch(...) {cout<<"unexpected error "<<endl;}
    
}
