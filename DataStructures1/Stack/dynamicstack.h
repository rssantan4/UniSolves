//dynamic stack

typedef int TypeItem;

struct Node{
    TypeItem value;
    Node* next;
};

class dynamicStack{
    private:
        Node* NodeTop;
    public:
        dynamicStack();
        ~dynamicStack();
        bool isfull();     //memory full
        bool isempty();    //memory empty
        void push(TypeItem item);
        TypeItem pop();
        void print();
};