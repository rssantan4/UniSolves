#include <iostream>
#include "queue.h"

using namespace std;
    
    queue::queue(){
        first = 0;
        last = 0;
        estrutura = new ItemType[max_items];
    }

    queue::~queue(){
        delete[] estrutura;
    }

    bool queue::isEmpty(){
        return (first == last);
    }

    bool queue::isFull(){
        return ((last + 1) % max_items == first);
    }

    void queue::enqueue(ItemType item){
        if(isFull()){
            cout << "Queue is full!" << endl;
            cout << "Cannot insert" << item << endl;
        } else{
            estrutura[last % max_items] = item;
            last++;
        }

    }

    ItemType queue::dequeue(){
        if(isEmpty()){
            cout << "Queue is empty!" << endl;
            cout << "Anything was removed" << endl;
            return 0;
        } else{
            first++;
            return estrutura[(first-1) % max_items];
        }

    }

    void queue::print(){
        cout << "[";
        for(int i = first; i < last; i++){
            cout << estrutura[i % max_items] << " ";
        }
        cout << "]" << endl;
    }                 

    int queue::length(){
        return (last - first);
    }
