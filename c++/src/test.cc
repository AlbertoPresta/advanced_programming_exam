#include<iostream>
#include<memory>
#include"Tree.h"

#include <cstdlib>


/*
 Antother struct which represents the opposite relation of order respect than the default one
 */
template<typename T>
struct oper{ bool operator()(const T& a, const T& b) const {return(a>b);}};


int main(){
    try{
        //oper<int> o;
	Tree<int,int> A{};
	cout<<"inizio del timing "<<endl;
    timer(A);
    cout<<"fine del timing"<<endl;
	
        
    oper<int> o;
    Tree<int,int,oper<int>> B{o};
        
    return 0;
    }

   catch (const ex_key) {cout<<"exception has been thrown "<<endl;return 1;}
       catch(...) {cout<<"unexpected error "<<endl;}
    
   }
