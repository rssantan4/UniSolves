#include <iostream>
#include "stack.h"
    
using namespace std;   
    
    stack::stack(){
        top = 0;
        estrutura = new TypeItem[max_itens];
    }                     
    stack::~stack(){
        delete[] estrutura;
    }                   
    bool stack::isfull(){
        return (top == max_itens);
    }              
    bool stack::isempty(){
        return (top == 0);
    }            
    void stack::push(TypeItem item){
        if(isfull()){
            cout << "Stack is full!" << endl;
            cout << "Cannot insert" << item << endl;
        } else{
            estrutura[top] = item;
            top++;
        }
    }    
    TypeItem stack::pop(){
        if(isempty()){
            cout << "Stack is empty!" << endl;
            cout << "Cannot remove or return item" << endl;
            return 0;
        } else{
            top--;
            return estrutura[top];
        }
    }          
    void stack::print(){
        cout << "[";
        for(int i = 0; i < top; i++){
            cout <<estrutura[i] << " ";
        }
        cout << "]" << endl;
    }            
    int stack::length(){
        return top;
    }               