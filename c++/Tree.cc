#include<iostream>
#include<cstdlib>
#include<vector>

using namespace std;

struct Link{
    int key;
    Link* left;
    Link* right;
    
    Link(int k, Link* l=nullptr, Link* r=nullptr):
        key{k},left{l},right{r} {}
    
    ~Link() {left=nullptr;right=nullptr;}
    
};

struct List{
    Link* first;
    Link* last;
    struct iterator{
        Link* current;
        
        iterator(Link* c):
            current{c} {}
            
        iterator& operator++(){
            current=current->right;
            return *this; }
        int& operator*() {
            return current->key;
            }
        bool operator==(const iterator& b){return current==b.current;}
        bool operator!=(const iterator& b){return current!=b.current;}
    
    void balance(){
        
    }
    
    };
};


int main() {
    vector<int> keys{1, 2, 6, 8, 10, 12, 13, 18, 21, 23, 24, 27, 32, 33, 34, 41, 43, 45, 47, 48};
    Link* node=new Link{keys[0]};
    List lista{node,nullptr};
    for (unsigned int i{1};i<keys.size();i++) {
        node=new Link{keys[i],node,nullptr};
        node->left->right=node;
    }
    
    List::iterator i{lista.first};

    while (i!=lista.last) {cout<<*i<<endl;++i;};
}
