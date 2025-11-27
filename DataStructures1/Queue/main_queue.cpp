#include <iostream>
#include "queue.h"
    
using namespace std;

int main(){
    queue queue1;
    ItemType item;
    int option;

    cout << "Queue Generator" << endl;

    do{
        cout << "1 - Enqueue" << endl;
        cout << "2 - Dequeue" << endl;
        cout << "3 - Print" << endl;
        cout << "4 - Length" << endl;
        cout << "0 - Exit" << endl;
        cout << "Choose an option from 0 to 4: ";

        cin >> option;
        // Verifica se a entrada é válida
        if (cin.fail()) {
            cin.clear();                // limpa o erro
            cin.ignore(1000, '\n');     // descarta o restante da entrada
            cout << "Invalid input." << endl;
            continue;
        }

        if (option == 1){
            cout << "Enter an item to enqueue: ";
            cin >> item;
            queue1.enqueue(item);
        } else if (option == 2){
            item = queue1.dequeue();
            cout << "Removed item from queue: " << item << endl;
        } else if (option == 3){
            queue1.print();
        } else if (option == 4){
            cout << "Length: " << queue1.length() << endl;
        }
        else if(option == 0){
            cout << "Exiting. . ." << endl;
            break;
        }
    }while(option >= 0 && option <= 4);

    return 0;

}
