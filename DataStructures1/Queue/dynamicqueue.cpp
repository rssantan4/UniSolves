#include <iostream>
#include "dynamicqueue.h"

using namespace std;

        dynamicQueue::dynamicQueue(){
            front = nullptr;
            end = nullptr;
        }
        dynamicQueue::~dynamicQueue(){
            node* temp;
            while(front != nullptr){
                temp = front;
                front = front->next;
                delete temp;
            }
            end = nullptr;
        }
        bool dynamicQueue::isfull(){
            node* newNode;
            try{
                newNode = new node;
                delete newNode;
                return false;
            } catch(bad_alloc exception){
                return true;
            }
        }
        bool dynamicQueue::isempty(){
            return (front == nullptr);
        }
        void dynamicQueue::enqueue(TypeItem item){
            if(isfull()){
                cout << "Queue is full!" << endl;
                cout << "Cannot insert" << item << endl;
            } else{
                node* newNode = new node;
                newNode->value = item;
                newNode->next = nullptr;
                if(isempty()){
                    front = newNode;
                    end = newNode;
                } else{
                    end->next = newNode;
                    end = newNode;
                }
            }
        }
        TypeItem dynamicQueue::dequeue(){
            if(isempty()){
                cout << "Queue is empty!" << endl;
                cout << "Cannot remove item" << endl;
                return 0;
            } else{
                TypeItem item = front->value;
                node* temp = front;
                front = front->next;
                if (front == nullptr){
                    end = nullptr;
                }
                delete temp;
                return item;
            }
        }
        void dynamicQueue::print(){
            node* tempPtr = front;
            cout << "[";
            while(tempPtr != nullptr){
                cout << tempPtr->value << " ";
                tempPtr = tempPtr->next;
            }
            cout << "]" << endl;
        }