#include <iostream>
#include "dynamicqueue.h"                    //adicionar novas funções e limitar parar n dar loop infinito

using namespace std;

int main(){
    dynamicQueue queue1;
    TypeItem item;
    int option;

    cout << "Dynamic Queue Generator" << endl;

    do{
        cout << "1 - Enqueue" << endl;
        cout << "2 - Dequeue" << endl;
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
            queue1.enqueue(item);
        } else if(option == 2){
            item = queue1.dequeue();
            cout << "Item removed: " << item << endl;
        } else if(option == 3){
            queue1.print();
        }
        else if(option == 0){
            cout << "Exiting program..." << endl;
            break;
        }
    } while(option >= 0 && option <= 3);

    return 0;

}