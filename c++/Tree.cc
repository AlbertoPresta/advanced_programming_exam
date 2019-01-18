#include<iostream>
#include<memory>

using std::string;

class Tree{

    struct Node{
        string key;
        double value;
        Node* left; 
        Node* right;
        Node* lparent;
        Node* rparent;
        Node (string k, double v, Node* l=nullptr, Node* r=nullptr,Node* lp=nullptr, Node* rp=nullptr):
        key{k}, value{v}, left{l}, right{r}, lparent{lp}, rparent{rp} {}
        
       
    };

    Node* first;
    Node* root;
    Node* last;
    unsigned int size_tree; //grandezza dell'albero

    
    public:
    Tree(): //costruttore dell'albero
        first{nullptr},root{nullptr},last{nullptr},size_tree{0} {}
        
        
    int Size() const{return size_tree;}  //funzione per stampare la grandezza dell'albero
    
    
    
    void Insert(string k, double v)  {
        //inserimento primo elemento
        if (size_tree==0) {Node* elem=new Node{k,v}; first=elem ; root=elem; last=elem; size_tree=1;return;};
        Node* p{root};
        
        
        bool FIRST{true}; //booleano che serve a identificare l'ultimo nodo a sinistra, first
        bool LAST{true};  
        
        while(!(p->left==nullptr and p->right==nullptr)and!(p->left==nullptr and k<p->key)and!(p->right==nullptr and k>p->key))
        //while(p->left!=nullptr or p->right!=nullptr)
         {
            if(k<p->key) {p=p->left;LAST=false;} //scende a sinistra. Se lo fa una volta sicuramente non è l'ultimo elemento
            else {p=p->right;FIRST=false;};      //speculare, se scende a destra una volta certamente non è il first
            };
        //per la condizione del while, p è l'ultimo nodo preesistente
        if(k<p->key) {
            Node* elem=new Node{k,v,nullptr,nullptr,nullptr,p}; //inserisce il nuovo nodo con p parente destro
            p->left=elem; //aggiorna il ramo destro di p
            if (FIRST==true) first=elem;
            }
        else {//tutto speculare
            Node* elem=new Node{k,v,nullptr,nullptr,p,nullptr};
            p->right=elem;
            if (LAST==true) last=elem;
            };
        size_tree++; //aggiornamento grandezza albero
        
        //std::cout<<p->key<<" left: "<<p->left<<"  right: "<<p->right<<"  lparent: "<<p->lparent<<"  rparent: "<<rparent<<std::endl;
    }
    
    
    
    
    struct iterator{
        Node* current;
        iterator(Node* p):
            current{p} {}
            
        iterator& operator++(){
            if(current->right!=nullptr){ //cerca se può scendere a destra
                current=current->right;
                if(current->left!=nullptr){  
                    while(current->left!=nullptr){  //da qui scende a sinistra fin tanto possibile
                        current=current->left;   
                        };
                    };
                return *this;  
            }
            else {
                if(current->rparent!=nullptr) { //se può risale a destra
                    current=current->rparent;
                    return *this;
                }
                else {
                    while(current->rparent==nullptr) { //in alternativa risale a sinistra 
                        current=current->lparent;
                    };
                    current=current->rparent;  //infine sale a destra
                    return *this;
                };
            
            };
            return *this;    
            }
        iterator& operator--(){
            //da implementare
            return *this;    
            }
        string& operator*() {
            return current->key;
            }
        bool operator==(const iterator& b){return current==b.current;}
        bool operator!=(const iterator& b){return current!=b.current;}
    };
    
    void print() {
    //queste sono le due linee che danno noie
    iterator i{first};
    while(i!=last) {std::cout<<*i<<std::endl; ++i;}
    std::cout<<last->key<<std::endl;
    //*****************************************************
    
    
    }
    

};


int main() {

Tree Albero;
std::cout<<Albero.Size()<<std::endl;
Albero.Insert("e",3);
Albero.Insert("a",1);
Albero.Insert("c",1);
Albero.Insert("b",1);
Albero.Insert("q",3);
Albero.Insert("g",8);
std::cout<<Albero.Size()<<std::endl<<std::endl;
Albero.print();
}
