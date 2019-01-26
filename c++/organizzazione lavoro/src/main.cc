#include<iostream>
#include<memory>
#include"Tree.h"

#include <cstdlib>





int main(){
    try{
        Tree<int,int> A;
        cout<<"ECCO L'ALBERO A"<<endl<<endl;
        A.Linked_insert(20);
        A.info();
        cout<<"ECCO L'ALBERO A"<<endl<<endl;
        cout<<A<<endl<<endl;
        A.balance();
        cout<<"---------ALBERO A BILANCIATO---------"<<endl;
        cout<<A<<endl<<endl;
        cout<<"------------------"<<endl;
        Tree<int,int>::iterator p{A.begin()};
        cout<<*p<<endl;
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
       
    return 0;
    }

catch (const ex_key) {cout<<"exception has been thrown "<<endl;return 1;}
    catch(...) {cout<<"unexpected error "<<endl;}
    
}
