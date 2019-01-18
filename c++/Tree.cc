#include<iostream>
#include<memory>

using std::string;

//IN QUESTO  CODICE SI IMPLEMENTA I CONSTITERATOR INDIPENDENTEMENTE DAGLI ITERATOR--> MOLTO SCOMODO VISTO CHE IL CODICE DIVENTA INCREDIBILMENTE LUNGO: ITERATOR E CONST ITERATOR SONO PRATICAMENTE UGUALI! PROVO A FARE CLASSE EREDITATA!

template<typename T,typename W>
class Tree{

    struct Node{
        T key;
        W value;
        Node* left; 
        Node* right;
        Node* lparent;
        Node* rparent;
        Node (T& k, W& v, Node* l=nullptr, Node* r=nullptr,Node* lp=nullptr, Node* rp=nullptr):
        key{k}, value{v}, left{l}, right{r}, lparent{lp},rparent{rp} {}
        ~Node()=default;
       
    };

    Node* first;
    Node* root;
    Node* last;
    unsigned int size_tree; //grandezza dell'albero

    
public:
    template<typename OT,typename OW>
    friend std::ostream& operator<<(std::ostream&, const Tree<OT,OW>&);
    Tree(): //costruttore dell'albero
        first{nullptr},root{nullptr},last{nullptr},size_tree{0} {}
        
        
    unsigned int Size() const{return size_tree;}  //funzione per stampare la grandezza dell'albero
    
    
    
    void Insert(T k, W v)  {
        //inserimento primo elemento
        if (size_tree==0) {Node* elem=new Node{k,v}; first=elem ; root=elem; last=elem; size_tree=1;return;};
        Node* p{root};
        
        
        bool FIRST{true}; //booleano che serve a identificare l'ultimo nodo a sinistra, first
        bool LAST{true};  
        
        while(!(p->left ==nullptr && p->right==nullptr) && !(p->left==nullptr && k<p->key) && !(p->right==nullptr && k>p->key)) {
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
    }
    
    
    
public:
    struct iterator{
        Node* current;
        iterator(Node* p):
            current{p} {}
        
        //metodi di iterator!
        //metodo begin--> ritorn l'iteratore first,cioè quello con la chiave più piccola
        iterator begin(){
            return iterator{first};
            }
        //metodo end-->ritorna l'iteratore dopo last--> NON SICURO
        iterator end(){
           return iterator{nullptr};
        }
        
        // ritorna l'iteratore con chiave più grande
        iterator last(){
            return iterator{last};
        }
        //ritorna l'iteratore puntato alla radice
        iterator root(){
            return iterator{root};
        }
        iterator& operator++(){
                if(current->right!=nullptr){ //cerca se può scendere a destra
                    current=current->right;
                    if(current->left!=nullptr){
                        while(current->left!=nullptr){  //da qui scende a sinistra fin tanto possibile
                            current=current->left;
                            }
                        }
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
        //Iterator& operator--(){   --> secondo me non serve
            //da implementare
          //  return *this;    
            //}
        T operator*() {
            return current->key;
            }
        W operator!(){
            return current->value;
        }
        bool operator==(const iterator& b){return current==b.current;}
        bool operator!=(const iterator& b){return current!=b.current;}
    };
    
    //CONST ITERATOR
    
    struct Constiterator{
         const Node* corrente;
        Constiterator(const Node* p): corrente{p} {}
    
    
    Constiterator cbegin() const {
        return Constiterator{first};
    }
    
    Constiterator cend() const {
        return Constiterator{nullptr};
    }
    
    Constiterator croot() const{
        return Constiterator{root};
    }
    Constiterator clast() const{
        return Constiterator{last};
    }
    T operator*() {
      return corrente->key;
        }
    W operator!(){
      return corrente->value;
        }
    
    bool operator==(const Constiterator& b){
        return corrente==b.corrente;
        }
    bool operator!=(const Constiterator& b){
        return corrente!=b.corrente;
        }
        
    Constiterator& operator++(){
        if(corrente->right!=nullptr){ //cerca se può scendere a destra
            corrente=corrente->right;
            if(corrente->left!=nullptr){
                while(corrente->left!=nullptr){  //da qui scende a sinistra fin tanto possibile
                        corrente=corrente->left;
                    }
                }
            return *this;
            }
            else {
                if(corrente->rparent!=nullptr) { //se può risale a destra
                    corrente=corrente->rparent;
                    return *this;
                }
                else {
                    while(corrente->rparent==nullptr) { //in alternativa risale a sinistra
                        corrente=corrente->lparent;
                    };
                    corrente=corrente->rparent;  //infine sale a destra
                    return *this;
                };
                
            };
            return *this;
        }
        
    ~Constiterator()= default;
    };
    
    
    
    //FINE CONST ITERATOR
    //METODO FIND
   iterator find(const T t){
       Node* j{root};
       while(j!=nullptr){
         
           if(j->key == t){
               std::cout<<"key found!"<<std::endl;
               return j;
           }
           else{
               if(j->key > t){
                 
                   j=j->left;
                  
               }
               
               else{
                 
                    j=j->right;
                  
               }
           }
       }
       std::cout<< "key not found!"<<std::endl;
       return j;
   }
       
//infine metto il distruttore di default
    ~Tree()=default;
};

template<typename T,typename W>
std::ostream& operator<<(std::ostream& os, const Tree<T,W>& l) {
    typename Tree<T,W>::Constiterator j = l.first;
    for(; j!=l.last;++j){
        os <<"key: "<<*j<<"   value: " <<!j<<std::endl;
        }
    os <<"key: "<<*j<<"   value: " <<!j<<std::endl;

    return os ;
}

int main() {

Tree<string, long long int> Albero;

Albero.Insert("alberto",3409941121);
Albero.Insert("giacomo",3389543211);
Albero.Insert("francesco",3393578976);
Albero.Insert("giulia",3315899435);
Albero.Insert("eleonora",338775523);
Albero.Insert("andrea",340987436);

std::cout<<Albero.Size()<<std::endl<<std::endl;

std::cout<<"ecco l'albero!"<<std::endl;
std::cout<< Albero <<std::endl;
   

    Tree<string,long long int>::iterator j{Albero.find("giulia")};

    std::cout<<*j<<std::endl;
}
