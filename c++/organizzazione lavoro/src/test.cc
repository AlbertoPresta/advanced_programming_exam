#include<iostream>
#include<memory>
#include"Tree.h"

#include <cstdlib>


int main(){
    try{
        //oper<int> o;
	Tree<int,int> A{};
	cout<<"inizio del timing "<<endl;
    timer(A);
    cout<<"fine del timing"<<endl;
	
    
        
    return 0;
    }

   catch (const ex_key) {cout<<"exception has been thrown "<<endl;return 1;}
       catch(...) {cout<<"unexpected error "<<endl;}
    
   }
