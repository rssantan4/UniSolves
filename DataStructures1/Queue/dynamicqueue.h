//dynamic queue

typedef int TypeItem;

class node{
    public:
    TypeItem value; //data
    node* next;   //pointer to next node
};

class dynamicQueue{
    private:
        node* front;
        node* end;
    public:
        dynamicQueue();
        ~dynamicQueue();
        bool isfull();
        //memory full
        bool isempty();
        //memory empty
        void enqueue(TypeItem item);
        TypeItem dequeue();
        void print();
};