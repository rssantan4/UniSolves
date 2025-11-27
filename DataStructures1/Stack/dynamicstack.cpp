#include <iostream>
#include "dynamicstack.h"

using namespace std;

        dynamicStack::dynamicStack(){
            NodeTop = nullptr;

        }
        dynamicStack::~dynamicStack(){
            Node* tempPtr;
            while(NodeTop != nullptr){
                tempPtr = NodeTop;
                NodeTop = NodeTop->next;
                delete tempPtr;
            }
        }
        bool dynamicStack::isfull(){
            Node* newNode;
            try{
                Node* newNode = new Node;
                delete newNode;
                return false;
            } catch(bad_alloc exception){
                return true;
            }

        }     
        bool dynamicStack::isempty(){
            return (NodeTop == nullptr);
        }   
        void dynamicStack::push(TypeItem item){
            if(isfull()){
                cout << "Stack is full!" << endl;
                cout << "Cannot insert" << item << endl;
            } else{
                Node* newNode = new Node;
                newNode->value = item;
                newNode->next = NodeTop;
                NodeTop = newNode;
            }

        }
        TypeItem dynamicStack::pop(){
            if(isempty()){
                cout << "Stack is empty!" << endl;
                cout << "Cannot remove item" << endl;
                return 0;
            } else{
                TypeItem item = NodeTop->value;
                Node* tempPtr = NodeTop;
                NodeTop = NodeTop->next;
                delete tempPtr;
                return item;
            }
        }
        void dynamicStack::print(){
            Node* tempPtr = NodeTop;
            cout << "[";
            while(tempPtr != nullptr){
                cout << tempPtr->value << " ";
                tempPtr = tempPtr->next;
            }
            cout << "]" << endl;
        }