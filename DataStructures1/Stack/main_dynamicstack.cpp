#include <iostream>
#include "dynamicstack.h"                    //adicionar novas funções e limitar parar n dar loop infinito

using namespace std;

int main(){
    dynamicStack stack1;
    TypeItem item;
    int option;

    cout << "Dynamic Stack Generator" << endl;

    do{
        cout << "1 - Push" << endl;
        cout << "2 - Pop" << endl;
        cout << "3 - Print" << endl;
        cout << "0 - Exit" << endl;
        cout << "Choose an option from 0 to 3: ";

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
        else if(option == 0){
            cout << "Exiting program..." << endl;
            break;
        }
    } while(option >= 0 && option <= 3);

    return 0;

}