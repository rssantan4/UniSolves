#include <iostream>
#include "stack.h"                    //adicionar novas funções e limitar parar n dar loop infinito

using namespace std;

int main(){
    stack stack1;
    TypeItem item;
    int option;

    cout << "Stack Generator" << endl;

    do{
        cout << "1 - Push" << endl;
        cout << "2 - Pop" << endl;
        cout << "3 - Print" << endl;
        cout << "4 - Length" << endl;
        cout << "5 - Check if stack is full or how many items are left to stay full" << endl;
        cout << "6 - Check if stack is empty or how many items are left to stay empty" << endl;
        cout << "0 - Exit" << endl;
        cout << "Choose an option from 0 to 6: ";

        cin >> option;
        // Verifica se a entrada é válida
        if (cin.fail()) {
            cin.clear();                // limpa o erro
            cin.ignore(1000, '\n');     // descarta o restante da entrada
            cout << "Invalid input." << endl;
            continue;
        }

        if (option == 1){
            cout << "Enter an item: ";
            cin >> item;
            stack1.push(item);
        } else if(option == 2){
            item = stack1.pop();
            cout << "Item removed: " << item << endl;
        } else if(option == 3){
            stack1.print();
        }
        else if(option == 4){
            cout << "Stack length: " << stack1.length() << endl;
        }
        else if(option == 5){
            if (stack1.isfull()){
                cout << "Stack is full" << endl;
            }
            else if (!stack1.isfull()){
                cout << "Stack is not full" << endl;
                cout << "Number of items left to fill the stack: " << 100 - stack1.length() << endl;
            }
        }
        else if(option == 6){
            if (stack1.isempty()){
                cout << "Stack is empty" << endl;
            }
            else if (!stack1.isempty()){
                cout << "Stack is not empty" << endl;
                cout << "Number of items left to empty the stack: " << stack1.length() << endl;
            }
        }
        else if(option == 0){
            cout << "Exiting program..." << endl;
            break;
        }
    } while(option >= 0 && option <= 6);

    return 0;

}