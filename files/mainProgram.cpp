#include<iostream>
#include<string>
using namespace std;

template<class T>
class node{
    public:
    string key;
    T value;
    node<T>* next;
    node(string k, T val){
        this->key = k;
        this->value = val;
        next = NULL;
    }

    ~node(){
        if(next!=NULL)
        delete next;
    }
    
};

template<class T>
class HashTable{
    node<T>** table;
    int current_size;
    int table_size;

    int hashFn(string key){
        int idx = 0;
        int p = 1;
        for(int j=0; j<key.length(); j++){
            idx = (idx + (key[j]*p))%table_size;
            p = (p*27)%table_size;
        }
        return idx;
    }

    void rehash(){
        node<T>** oldTable = table;
        int oldTable_size = table_size;
        table_size = 2*table_size+1;
        current_size = 0;
        table = new node<T>*[table_size];
        for(int i=0; i<table_size; i++){
            table[i] = NULL;
        }

        for(int i=0; i<oldTable_size; i++){
            node<T>* temp = oldTable[i];
            while(temp!=NULL){
                insert(temp->key, temp->value);
                temp = temp->next;
            }

            if(oldTable[i]!=NULL)
            delete oldTable[i];
        }
        delete [] oldTable;
    }

    public:
    HashTable(int ts = 7){
        table_size = ts;
        table = new node<T>*[table_size];
        current_size = 0;
        for(int i=0; i<table_size; i++){
            table[i] = NULL;
        }
    }
    
    void insert(string key, T value){
        int index = hashFn(key);
        node<T>* n = new node<T>(key, value);

        // Insert at head of the linked list with id = index
        n->next = table[index];
        table[index] = n;

        current_size++;

        float loadFactor = current_size/(1.0*table_size);
        if(loadFactor>0.7){
            rehash();
        }

    }

    void print(){
        for(int i=0; i<table_size; i++){
            cout<<"Bucket "<<i<<" : ";
            node<T>* temp = table[i];
            while(temp!=NULL){
                cout<<"-> "<<temp->key;
                temp = temp->next;
            }
            cout<<endl;
        }
    }
};

int main(){
    HashTable<int> price_menu;
    price_menu.insert("Burger", 120);
    price_menu.insert("Pepsi", 20);
    price_menu.insert("Noodles", 25);
    price_menu.insert("Pizza", 150);
    price_menu.insert("Coke", 40);
    price_menu.insert("BurgerPizza", 25);
    price_menu.insert("Noodles", 50);
    price_menu.insert("BurgerPizza", 100);
    price_menu.insert("Dosa", 60);
    price_menu.insert("Idli", 50);
    price_menu.insert("VadaPav", 20);
    price_menu.insert("Samosa", 10);
    price_menu.print();
    return 0;
}