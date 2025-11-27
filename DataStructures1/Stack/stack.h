//stack.cpp
#include <iostream>

typedef int TypeItem;
const int max_itens = 100;

class stack {
    private:
    int top;                    //top of stack
    TypeItem* estrutura;        //stack

    public:
    stack();                    //constructor  
    ~stack();                   //destructor
    bool isfull();              //verift stack is full 
    bool isempty();             //verify stack is empty
    void push(TypeItem item);   //insere item no stack
    TypeItem pop();             //remove item do stack
    void print();               //print stack
    int length();               //return stack size
};

