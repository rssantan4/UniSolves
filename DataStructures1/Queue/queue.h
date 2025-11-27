//queue.cpp
#include <iostream>

typedef int ItemType;
const int max_items = 100;

class queue {
    private:
    int first, last;
    ItemType* estrutura;  

    public:
        queue();                        //constructor(enfileirar)
        ~queue();                       //destructor(desenfileirar)
        bool isEmpty();                 //verify queue is empty
        bool isFull();                  //verify queue is full
        void enqueue(ItemType item);    //push 
        ItemType dequeue();             //pop
        int length();                   //return queue size
        void print();                   //print queue
};